#pragma once
#include <vector>
#include <iostream>
#include <deque>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>

template<class _ElemTy>
struct TreeNode
{
    _ElemTy data;
    std::vector<TreeNode<_ElemTy>*> children;
};

template<class _ElemTy>
class Tree
{
    friend class build_fn;
public:
    using Node = TreeNode<_ElemTy>;
private:
    Node* root;
public:
    Tree() = default;
    Tree(const Tree&) = delete;
    /**
     * @brief Build tree with input, check following example.
     * @examp ------------------------------------------------------
     * | $INPUT 1$         | $INPUT 2$         | $VISUALIZE$       |
     * | >>>      [a]      | >>> [a]           |        a (root)   |
     * | >>>   [b    c  d] | >>> [b c d]       |     +--+--+       |
     * | >>> [e  f] [] [g] | >>> [e f] [] [g]  |     b  c  d       |
     * | >>> [] [h]    [i] | >>> [] [h] [i]    |  +--+     +       |
     * | >>>     []     [] | >>> [] []         |  e  f     g       |
     * |                   |                   |     +     +       |
     * |                   |                   |     h     i       |
     * -------------------------------------------------------------
    */
    class build_fn
    {
    private:
        Node* buildRoot;
        std::deque<std::istringstream> childrenQueue = {};
    public:
        build_fn(Tree<_ElemTy>& tree) :buildRoot(tree.root) {}
        void operator()() {
            std::cout << "[Tree] Tree Building start: " << std::endl;
            std::string inputLine{};
            std::getline(std::cin, inputLine);          // Get a line of input
            auto childrenQueue = spliter(inputLine);      // Split the line
            _ElemTy data{};                             // Create a data with default constructor
            childrenQueue[0] >> data;                     // Input the only value (root is a single node, having no siblings)
            buildRoot = new Node{ data };                    // Create {root}

            std::queue<Node*> parentQueue;              // Create a queue to store the parents waiting for construction
            parentQueue.push(buildRoot);                     // Push {root} to queue as the next step is to build it's children

            while (!parentQueue.empty()) {
                Node* current = parentQueue.front();    // Get queue front
                parentQueue.pop();                      // Pop queue
            }
        }
    private:
        std::vector<std::istringstream> spliter(const std::string& str) {
            std::vector<std::istringstream> childrenQueue{};
            std::string tempStr{};
            for (auto ch : str) {
                switch (ch) {
                case '[': { tempStr.clear(); break; }
                case ']': { childrenQueue.emplace_back(str); break; }
                default: { tempStr += ch; break; }
                }
            }
            return childrenQueue;
        }

        std::string readInput() {
            std::string tempStr{};
            while (std::cin.good()) {
                std::getline(std::cin, tempStr);
                auto tempChildrenVec = spliter(tempStr);
                childrenQueue.insert(childrenQueue.begin(), tempChildrenVec.begin(), tempChildrenVec.end());
            }
        }
    };
public:
    build_fn build{ *this };
};
