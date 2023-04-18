#pragma once
#include "Tree.h"
#include <memory>

template<class _ElemTy>
struct bNode
{
    using NodePtr = std::shared_ptr<bNode>;
    _ElemTy data;
    NodePtr child;
    NodePtr sibling;
};

template<class _ElemTy>
class ChildSiblingTree
{
public:
    using Node = bNode<_ElemTy>;
    using NodePtr = std::shared_ptr<Node>;
    using const_NodePtr = std::shared_ptr<const Node>;

protected:
    NodePtr _root{ nullptr };

public:
    ChildSiblingTree() = default;
    ChildSiblingTree(const Tree<_ElemTy>& tree) { transfer(tree, _root); }
    ChildSiblingTree(const ChildSiblingTree<_ElemTy>& tree) {
        _root = rec_build(tree.get_root());
    }

    void transfer(const Tree<_ElemTy>& sourceTree, NodePtr& destRoot) {
        auto sourceRoot = sourceTree.get_root();
        if (sourceRoot == nullptr) { return; }  // Return if {tree} is empty
        destRoot = std::make_shared<Node>(sourceRoot->data);    // Create root
        destRoot->child = std::move(rec_build(sourceRoot->children.cbegin(), sourceRoot->children.cend()));
    }

public:
    NodePtr get_root() {
        return _root;
    }

    const_NodePtr get_root() const {
        return _root;
    }

    int64_t count_leaves() const {
        int64_t cnt = 0;
        rec_count_leaves(get_root(), cnt);
        return cnt;
    }

    int64_t count_leaves(NodePtr root) const {
        int64_t cnt = 0;
        rec_count_leaves(root, cnt);
        return cnt;
    }

    int64_t count_height() const {
        return rec_count_height(get_root());
    }

    int64_t count_height(NodePtr root) const {
        return rec_count_height(root);
    }

    int64_t count_1degree() const {
        int64_t cnt = 0;
        rec_count_1degree(get_root(), cnt);
        return cnt;
    }

protected:
    NodePtr rec_build(std::vector<std::shared_ptr<TreeNode<_ElemTy>>>::const_iterator tnode,
        std::vector<std::shared_ptr<TreeNode<_ElemTy>>>::const_iterator end);

    NodePtr rec_copy(NodePtr troot);

    void rec_count_leaves(const_NodePtr root, int64_t& cnt) const;

    int64_t rec_count_height(const_NodePtr root) const;

    void rec_count_1degree(const_NodePtr root, int64_t& cnt) const;
};

template<class _ElemTy>
ChildSiblingTree<_ElemTy>::NodePtr ChildSiblingTree<_ElemTy>::rec_build(
    std::vector<std::shared_ptr<TreeNode<_ElemTy>>>::const_iterator tnode,
    std::vector<std::shared_ptr<TreeNode<_ElemTy>>>::const_iterator end
) {
    if (tnode == end) { return nullptr; }
    NodePtr btnode = std::make_shared<Node>((*tnode)->data);
    btnode->child = std::move(rec_build((*tnode)->children.cbegin(), (*tnode)->children.cend()));
    btnode->sibling = std::move(rec_build(++tnode, end));
    return btnode;
}

template<class _ElemTy>
ChildSiblingTree<_ElemTy>::NodePtr ChildSiblingTree<_ElemTy>::rec_copy(NodePtr troot) {
    if (troot == nullptr) return nullptr;
    NodePtr node = new Node{ troot->data };
    node->child = rec_copy(troot->child);
    node->sibling = rec_copy(troot->sinbling);
    return node;
}
template<class _ElemTy>
void ChildSiblingTree<_ElemTy>::rec_count_leaves(const_NodePtr root, int64_t& cnt) const {
    if (root == nullptr) { return; }
    if (root->child == nullptr) { ++cnt; }
    rec_count_leaves(root->child, cnt);
    rec_count_leaves(root->sibling, cnt);
}

template<class _ElemTy>
int64_t ChildSiblingTree<_ElemTy>::rec_count_height(const_NodePtr root) const {
    if (root == nullptr) { return 0; }
    return std::max(rec_count_height(root->child) + 1, rec_count_height(root->sibling));
}

template<class _ElemTy>
void ChildSiblingTree<_ElemTy>::rec_count_1degree(const_NodePtr root, int64_t& cnt) const {
    if (root == nullptr) { return; }
    if (root->child != nullptr && root->child->sibling == nullptr) { ++cnt; }
    rec_count_1degree(root->child, cnt);
    rec_count_1degree(root->sibling, cnt);
}
