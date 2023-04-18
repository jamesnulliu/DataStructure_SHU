#pragma once
#include <vector>
#include <iostream>
#include <deque>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>
#include <typeinfo>

template<class _Elem> class tree_build_fn;

template<class _ElemTy>
struct TreeNode
{
    _ElemTy data = {};
    std::vector<std::shared_ptr<TreeNode<_ElemTy>>> children = {};
};

template<class _ElemTy>
class Tree
{
public:
    template<class _Elem> friend class tree_build_fn;

    using bNode = TreeNode<_ElemTy>;
    using NodePtr = std::shared_ptr<bNode>;
    using const_NodePtr = std::shared_ptr<const bNode>;
    using build_fn = tree_build_fn<_ElemTy>;

private:
    NodePtr _root{ nullptr };

public:
    Tree() = default;
    Tree(const Tree&) = delete;
    ~Tree() = default;

    NodePtr get_root() { return _root; }
    const_NodePtr get_root() const { return const_cast<Tree<_ElemTy>*>(this)->get_root(); }

    build_fn build{ *this };
};

/**
 * @brief Build tree with input, check following example.
 * @examp -----------------------------------------------------+
 * | $INPUT 1          | $INPUT 2          | $VISUALIZE$       |
 * | >>>      [a]      | >>> [a]           |        a (root)   |
 * | >>>   [b    c  d] | >>> [b c d]       |     +--+--+       |
 * | >>> [e  f] [] [g] | >>> [e f] [] [g]  |     b  c  d       |
 * | >>> [] [h]    [i] | >>> [] [h] [i]    |  +--+     +       |
 * | >>>     []     [] | >>> [] []         |  e  f     g       |
 * |---------------------------------------|     +     +       |
 * | INPUT 1 and INPUT 2 are the same      |     h     i       |
 * +-----------------------------------------------------------+
*/
template<class _ElemTy>
class tree_build_fn
{
private:
    using Node = TreeNode<_ElemTy>;
    using NodePtr = std::shared_ptr<Node>;
private:
    NodePtr* _rRoot;  // Pointer to Tree::_root
public:
    tree_build_fn(Tree<_ElemTy>& tree) : _rRoot(&(tree._root)) {}

    void operator()(std::istream& in) {
        if (&in == &std::cin) printf("### Tree: Tree building start\n$ Please enter the nodes:\n$ ");

        // Build root: @{
        _ElemTy data{};                          // Create a data with default constructor
        auto vec = getline_split(in);
        if (vec.empty()) return;                 // Return if there is no input
        vec.front() >> data;                     // Input the only value (root is a single node, having no siblings)
        *_rRoot = std::make_shared<Node>(data);  // Create {root}
        // @}

        // Build other nodes:
        build_bfs(in);
        if (&in == &std::cin) printf("\b\b### Tree: Tree building ends.\n");
    }

private:
    // @brief Split a string to several istringstreams by detecting '[' and ']'.
    std::vector<std::istringstream> spliter(const std::string& str) {

        // Preprocess {str}, get rid of spaces at head:
        auto it = str.begin();
        while (it != str.end() && *it == ' ') { ++it; }
        if (it == str.end()) return {};  // There is nothing except ' ' in input string

        std::string tempStr(it, str.end());
        std::vector<std::istringstream> istrQueue{};

        for (auto ch : str) {  // Split {tempStr}
            switch (ch) {
            case '[': { tempStr.clear(); break; }
            case ']': { istrQueue.emplace_back(tempStr); break; }
            case '#': { return istrQueue; }
            default: { tempStr += ch; break; }
            }
        }

        return istrQueue;
    }

    // @brief Get a line from console input, and return a vector of splited istringstreams.
    std::vector<std::istringstream> getline_split(std::istream& in) {
        std::string inputLine{};
        std::getline(in, inputLine);
        if (&in == &std::cin) printf("$ ");
        return spliter(inputLine);
    }

    // @brief Make a sequence of (Node*)children with input stream.
    // @param istr Input stream, consisting of rear strings saperated with whitespaces.
    std::vector<NodePtr> makeChildren(std::istringstream& istr) {
        _ElemTy data{};
        std::vector<NodePtr> ret;
        while (true) {  // Keep reading from input stream until there is nothing
            istr >> data;                        // Input an element
            if (!istr.good()) { break; }
            ret.emplace_back(new Node{ data });  // Create and push back a new node to vector
        }
        return ret;
    }

    void build_bfs(std::istream& in) {
        std::queue<NodePtr> parentQueue;  // The main queue for BFS, to store the parents waiting for construction
        parentQueue.push(*_rRoot);        // Push {_root} to queue as the next step is to build it's children

        while (!parentQueue.empty()) {
            std::vector<std::istringstream> inputQueue = std::move(getline_split(in));
            std::string inputLine{};
            for (auto& istr : inputQueue) {
                NodePtr current = parentQueue.front();              // Get queue front
                parentQueue.pop();                                  // Pop queue
                if (istr.str().empty()) { continue; }
                current->children = std::move(makeChildren(istr));  // Update {current->children}
                for (auto child : current->children) {              // Push all children to {parentQueue}
                    parentQueue.push(child);
                }
            }
        }
    }
};
