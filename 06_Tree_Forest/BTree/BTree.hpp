#pragma once
#include <iostream>
#include <queue>
#include <ranges>
#include "BTreeNode.hpp"

/*
  B-Tree of order m
  - Any node containing p keys must have p+1 children
  - Root contains at least 1 key with 2 children
  - Any node except root contains at least ceil(m/2) children
  - Any node contains at most m children with m-1 elements
*/

template<class KeyTy, long long m>
class BTree
{
public:
    using Index = long long;
    using Size = long long;

    using Node = BTreeNode<KeyTy, m>;
    using NodePtr = Node::NodePtr;
    using const_NodePtr = Node::const_NodePtr;

public:
    inline NodePtr search(const KeyTy& key);
    const_NodePtr  search(const KeyTy& key) const;
public:
    inline void insert(const KeyTy& key);
private:
    void rec_insert(NodePtr tRoot, const KeyTy& key, NodePtr parent);
public:
    friend class erase_fn;
    class erase_fn
    {
    public:
        erase_fn(BTree& btree) :_root(btree._root) {}
        inline void operator()(const KeyTy& key);
    private:
        void rec_erase(NodePtr curNode, const KeyTy& key, NodePtr parent);
        template<class _NodeIt>
        bool try_rotate(NodePtr parent, _NodeIt curNodeInParChildren);
        template<class _NodeIt>
        void merge(NodePtr parent, _NodeIt curNodeInParChildren);
    private:
        NodePtr& _root;
    };
    erase_fn erase{ *this };
    void printTree() const;

private:  // Utility Functions
    // @brief Calculate ceil(x over 2).
    static constexpr int64_t ceilOver2(int64_t x) { return (x & 1LL) ? (x >> 1) + 1 : (x >> 1); }
    // @brief Find the node where key belongs (where it is or "should" be if inserted).
    inline NodePtr find_belonging(NodePtr tRoot, const KeyTy& key, NodePtr* parent = nullptr);
    // @brief Find the node where key belongs (where it is or "should" be if inserted).
    const_NodePtr  find_belonging(const_NodePtr tRoot, const KeyTy& key, const_NodePtr* parent = nullptr) const;

private:
    NodePtr _root{ std::make_shared<Node>() };
};

template<class KeyTy, long long m>
typename BTree<KeyTy, m>::NodePtr
BTree<KeyTy, m>::search(const KeyTy& key)
{
    return std::const_pointer_cast<Node>(
        static_cast<const BTree<KeyTy, m>&>(*this).search(key)
    );
}

template<class KeyTy, long long m>
typename BTree<KeyTy, m>::const_NodePtr
BTree<KeyTy, m>::search(const KeyTy& key) const
{
    const_NodePtr belonging = find_belonging(_root, key);
    auto target = std::ranges::find(belonging->keys, key);
    if (target == belonging->keys.end()) return nullptr;
    else return belonging;
}

template<class KeyTy, long long m>
typename BTree<KeyTy, m>::NodePtr
BTree<KeyTy, m>::find_belonging(NodePtr tRoot, const KeyTy& key, NodePtr* parent)
{
    const_NodePtr constParent{};
    // Invoke const version
    auto target = std::const_pointer_cast<Node>(
        static_cast<const BTree<KeyTy, m>&>(*this).find_belonging(tRoot, key, &constParent)
    );
    if (parent != nullptr) { *parent = std::const_pointer_cast<Node>(constParent); }
    return target;
}

template<class KeyTy, long long m>
typename BTree<KeyTy, m>::const_NodePtr
BTree<KeyTy, m>::find_belonging(const_NodePtr tRoot, const KeyTy& key, const_NodePtr* parent) const
{
    Index i = 0;
    while (i < (Size)tRoot->keys.size() && key > tRoot->keys[i]) { ++i; }
    if ((i < (Size)tRoot->keys.size() && tRoot->keys[i] == key) || tRoot->is_leaf()) return tRoot;
    if (parent != nullptr) { *parent = tRoot; }
    return find_belonging(tRoot->children[i], key, parent);
}

template<class KeyTy, long long m>
void BTree<KeyTy, m>::insert(const KeyTy& key)
{
    rec_insert(_root, key, nullptr);
}

template<class KeyTy, long long m>
void BTree<KeyTy, m>::rec_insert(NodePtr curNode, const KeyTy& key, NodePtr parent)
{
    // Find the first key that is not smaller than {key}
    auto targetIter = std::ranges::lower_bound(curNode->keys, key);
    // Reuturn if {key} already exists
    if (targetIter != curNode->keys.end() && *targetIter == key) return;
    // If {tRoof} is leaf, insert {key} to {curNode} :
    if (curNode->is_leaf()) {
        curNode->keys.insert(targetIter, key);
    }
    // Or {curNode} is not leaf, go deeper to find appropriate position to insert:
    else {
        rec_insert(curNode->children.at(targetIter - curNode->keys.begin()), key, curNode);
    }
    // If overflows, split {tRoot->keys}
    if ((Size)curNode->keys.size() == m) {
        constexpr Size d = ceilOver2(m) - 1;
        // The key to move upward
        KeyTy midKey = curNode->keys[d];
        // Create a new node
        NodePtr rightPart = std::make_shared<Node>();
        // Copy keys to {rightPart}
        rightPart->keys.assign(curNode->keys.begin() + d + 1, curNode->keys.end());
        curNode->keys.resize(d);

        // If {tRoot} is not leaf, copy children to {rightParent}
        if (!curNode->is_leaf()) {
            rightPart->children.assign(curNode->children.begin() + d + 1, curNode->children.end());
            curNode->children.resize(d + 1);
        }

        // If The splited node is root, create a new root
        if (parent == nullptr) {
            NodePtr rootNew = std::make_shared<Node>();
            rootNew->keys.assign({ midKey });
            rootNew->children.assign({ curNode, rightPart });
            _root = rootNew;
        }
        // If the splited node is not root, use {parent}
        else {
            // Find the appropriate position for {key} to insert
            auto keyInPar = std::ranges::lower_bound(parent->keys, key);
            // Insert {key} to parent keys
            keyInPar = parent->keys.insert(keyInPar, midKey);
            // Calculate the index of {key} in parent keys
            Index keyIndex = keyInPar - parent->keys.begin();
            // Update parent's children
            parent->children.insert(parent->children.begin() + keyIndex + 1, rightPart);
        }
    }
    return;
}

template<class KeyTy, long long m>
void BTree<KeyTy, m>::erase_fn::operator()(const KeyTy& key)
{
    rec_erase(_root, key, nullptr);
}

template<class KeyTy, long long m>
void BTree<KeyTy, m>::erase_fn::rec_erase(NodePtr curNode, const KeyTy& key, NodePtr parent)
{
    // Find the first key that is not smaller than {key}
    auto keyInCurKeys = std::ranges::lower_bound(curNode->keys, key);
    // Found {key}, try to erase it
    if (keyInCurKeys != curNode->keys.end() && *keyInCurKeys == key) {
        // If the found {key} is not in leaf, exchange it with its left subtree's max key
        if (!curNode->is_leaf()) {
            NodePtr leftSubtree = curNode->children.at(keyInCurKeys - curNode->keys.begin());
            NodePtr leftestNode = leftSubtree;
            // Go to the rightest node of left subtree
            while (!leftestNode->is_leaf()) { leftestNode = leftestNode->children.back(); }
            // Swap the target key and subtree's max key
            std::swap(*keyInCurKeys, leftestNode->keys.back());
            // Dive into left subtree to erase the swapped{key}
            rec_erase(leftSubtree, key, curNode);
        }
        // Or current node is leaf
        else {
            // Erase the key directly, adjust each node from bottom to top later
            curNode->keys.erase(keyInCurKeys);
        }
    }
    // Or not found {key}, try go deeper
    else {
        // Return if {key} doesn't exist
        if (curNode->is_leaf()) return;
        // Go to deeper recursion to find the key
        rec_erase(curNode->children.at(keyInCurKeys - curNode->keys.begin()), key, curNode);
    }
    if (curNode == _root) {
        // Root must have at least one node
        if (_root->keys.size() == 0 && _root->children.size() != 0) { _root = _root->children.front(); }
        return;
    }
    // If the num of keys in {curNode} is less than min num, adjest the node
    if ((Size)curNode->keys.size() < ceilOver2(m) - 1) {
        auto curNodeInParChildren = std::ranges::find(parent->children, curNode);
        if (curNode->is_leaf() && try_rotate(parent, curNodeInParChildren) == true) { return; }
        merge(parent, curNodeInParChildren);
    }
}

template<class KeyTy, long long m>
template<class _NodeIt>
bool BTree<KeyTy, m>::erase_fn::try_rotate(NodePtr parent, _NodeIt curNodeInParChildren)
{
    // If parent is nullptr, current node must be _root. Rotation is impossible.
    if (parent == nullptr) return false;

    NodePtr& curNode = *curNodeInParChildren;
    Index curNodeIdxInParChildren = curNodeInParChildren - parent->children.begin();

    // Get left sibling and right sibling of curent node; nullptr if non-exist
    NodePtr leftSibling = curNodeInParChildren == parent->children.begin() ?
        nullptr : *(curNodeInParChildren - 1);
    NodePtr rightSibling = curNodeInParChildren == parent->children.end() - 1 ?
        nullptr : *(curNodeInParChildren + 1);

    // If left sibling has enough keys:
    if (leftSibling != nullptr && (Size)leftSibling->keys.size() >= ceilOver2(m)) {
        // Choose a key from left sibling
        KeyTy chosenKey = leftSibling->keys.back();
        // Erase the chosen key from left sibling
        leftSibling->keys.pop_back();
        // Move down a key from parent
        curNode->keys.insert(curNode->keys.begin(), parent->keys.at(curNodeIdxInParChildren - 1));
        // Move up the chosen key to parent
        parent->keys[curNodeIdxInParChildren - 1] = chosenKey;
        return true;
    }
    // Else if right sibling has enough keys:
    else if (rightSibling != nullptr && (Size)rightSibling->keys.size() >= ceilOver2(m)) {
        KeyTy chosenKey = rightSibling->keys.front();
        rightSibling->keys.erase(rightSibling->keys.begin());
        curNode->keys.push_back(parent->keys.at(curNodeIdxInParChildren));
        parent->keys[curNodeIdxInParChildren] = chosenKey;
        return true;
    }

    return false;
}

template<class KeyTy, long long m>
template<class _NodeIt>
void BTree<KeyTy, m>::erase_fn::merge(NodePtr parent, _NodeIt curNodeInParChildren)
{
    NodePtr& curNode = *curNodeInParChildren;
    Index curNodeIdxInParChildren = curNodeInParChildren - parent->children.begin();

    // Get left sibling and right sibling of curent node; nullptr if non-exist
    NodePtr leftSibling = curNodeInParChildren == parent->children.begin() ?
        nullptr : *(curNodeInParChildren - 1);
    NodePtr rightSibling = curNodeInParChildren == parent->children.end() - 1 ?
        nullptr : *(curNodeInParChildren + 1);

    // Merge cur to left sibling:
    if (leftSibling != nullptr) {
        // The key in parent between {curNode} and {leftSibling}
        auto midKeyInPar = parent->keys.begin() + curNodeIdxInParChildren - 1;
        // Insert the key from parent to {leftSibling}
        leftSibling->keys.push_back(*midKeyInPar);
        // Insert the keys of {curNode} to {leftSibling}
        std::ranges::copy(curNode->keys, std::back_inserter(leftSibling->keys));
        // Insert the children of {curNode} to {leftSibling}
        std::ranges::copy(curNode->children, std::back_inserter(leftSibling->children));
        // Erase {midKeyInParent}
        parent->keys.erase(midKeyInPar);
        // Erase {curNodeInParChildren}
        parent->children.erase(curNodeInParChildren);
    }
    // Merge cur to right sibling:
    else if (rightSibling != nullptr) {
        // Same as above
        auto midKeyInPar = parent->keys.begin() + curNodeIdxInParChildren;
        rightSibling->keys.insert(rightSibling->keys.begin(), *midKeyInPar);
        std::ranges::copy(rightSibling->keys, std::back_inserter(curNode->keys));
        std::swap(rightSibling->keys, curNode->keys);
        std::ranges::copy(rightSibling->children, std::back_inserter(curNode->children));
        std::swap(rightSibling->children, curNode->children);
        parent->keys.erase(midKeyInPar);
        parent->children.erase(curNodeInParChildren);
    } else {
        throw "[ERR] What the fuck?";
    }
}

template<class KeyTy, long long m>
void BTree<KeyTy, m>::printTree() const
{
    std::queue<NodePtr> nodeQueue;
    nodeQueue.push(_root);
    Size nodeNumThisLevel = _root->keys.size();
    Size nodeNumNextLevel = 0;

    if (nodeNumThisLevel == 0) {
        std::cout << "Empty Tree." << std::endl;
        return;
    }

    while (!nodeQueue.empty()) {
        NodePtr curNode = nodeQueue.front();
        nodeQueue.pop();
        for (NodePtr& child : curNode->children) {
            nodeNumNextLevel += child->keys.size();
            nodeQueue.push(child);
        }
        std::cout << "[";
        for (KeyTy& key : curNode->keys) {
            std::cout << key << ", ";
            --nodeNumThisLevel;
        }
        std::cout << "\b\b] ";
        if (nodeNumThisLevel == 0) {
            std::cout << std::endl;
            nodeNumThisLevel = nodeNumNextLevel;
            nodeNumNextLevel = 0;
        }
    }

    std::cout << std::endl;
}