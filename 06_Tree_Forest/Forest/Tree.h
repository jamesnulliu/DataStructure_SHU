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

template<class _ElemTy>
struct TreeNode
{
    _ElemTy data = {};
    std::vector<std::shared_ptr<TreeNode<_ElemTy>>> children = {};
};

template<class _ElemTy>
class Tree
{
    friend class build_fn;
public:
    using bNode = TreeNode<_ElemTy>;
    using NodePtr = std::shared_ptr<bNode>;

private:
    NodePtr _root;

public:
    Tree() = default;
    Tree(const Tree&) = delete;
    ~Tree() = default;

    NodePtr& get_root() { return _root; }
    const NodePtr& get_root() const { return const_cast<Tree<_ElemTy>*>(this)->get_root(); }

public:

    /**
     * @brief Build tree with input, check following example.
     * @examp ------------------------------------------------------
     * | $INPUT 1          | $INPUT 2          | $VISUALIZE$       |
     * | >>>      [a]      | >>> [a]           |        a (root)   |
     * | >>>   [b    c  d] | >>> [b c d]       |     +--+--+       |
     * | >>> [e  f] [] [g] | >>> [e f] [] [g]  |     b  c  d       |
     * | >>> [] [h]    [i] | >>> [] [h] [i]    |  +--+     +       |
     * | >>>     []     [] | >>> [] []         |  e  f     g       |
     * |---------------------------------------|     +     +       |
     * | INPUT 1 and INPUT 2 are the same      |     h     i       |
     * -------------------------------------------------------------
    */
    class build_fn
    {
    private:
        NodePtr* _rRoot;  // Pointer to Tree::_root

    public:
        build_fn(Tree<_ElemTy>& tree) : _rRoot(&(tree._root)) {}

        void operator()() {
            printf("$ Tree: Tree building start\n$ Please enter the nodes:\n$ ");

            // Build root: @{
            _ElemTy data{};                          // Create a data with default constructor
            getline_split().front() >> data;         // Input the only value (root is a single node, having no siblings)
            *_rRoot = std::make_shared<bNode>(data);  // Create {root}
            // @}

            // Build other nodes:
            build_bfs();
            printf("Tree: Tree building ends.\n");
        }

    private:
        // @brief Split a string to several istringstreams by detecting '[' and ']'.
        std::vector<std::istringstream> spliter(const std::string& str) {
            std::vector<std::istringstream> istreamQueue{};
            std::string tempStr{};
            for (auto ch : str) {  // Split {str}
                switch (ch) {
                case '[': { tempStr.clear(); break; }
                case ']': { istreamQueue.emplace_back(tempStr); break; }
                default: { tempStr += ch; break; }
                }
            }
            return istreamQueue;
        }

        // @brief Get a line from console input, and return a vector of splited istringstreams.
        std::vector<std::istringstream> getline_split() {
            std::string inputLine{};
            std::getline(std::cin, inputLine);
            printf("$ ");
            return spliter(inputLine);
        }

        // @brief Make a sequence of (Node*)children with input stream.
        // @param istr Input stream, consisting of rear strings saperated with whitespaces.
        std::vector<NodePtr> makeChildren(std::istringstream& istr) {
            _ElemTy data{};
            std::vector<NodePtr> ret;
            while (istr.good()) {                    // Keep reading from input stream until there is nothing
                istr >> data;                        // Input an element
                ret.emplace_back(new bNode{ data });  // Create and push back a new node to vector
            }
            return ret;
        }

        void build_bfs() {
            std::queue<NodePtr> parentQueue;  // The main queue for BFS, to store the parents waiting for construction
            parentQueue.push(*_rRoot);        // Push {_root} to queue as the next step is to build it's children

            while (!parentQueue.empty()) {
                std::vector<std::istringstream> inputQueue = std::move(getline_split());
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

public:
    build_fn build{ *this };
};