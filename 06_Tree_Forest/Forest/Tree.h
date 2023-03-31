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
    _ElemTy data = {};
    std::vector<TreeNode<_ElemTy>*> children = {};
};

template<class _ElemTy>
class Tree
{
    friend class build_fn;
public:
    using Node = TreeNode<_ElemTy>;
private:
    Node* _root;
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
     * |---------------------------------------|     +     +       |
     * | INPUT 1 and INPUT 2 are the same      |     h     i       |
     * -------------------------------------------------------------
    */
    class build_fn
    {
    private:
        Node** _rRoot;
        // std::deque<std::istringstream> inputQueue = {};
    public:
        build_fn(Tree<_ElemTy>& tree) : _rRoot(&(tree._root)) {}
        void operator()() {
            std::cout << "[Tree] Tree Building start: " << std::endl;
            auto inputQueue = std::move(getALine());
            _ElemTy data{};                 // Create a data with default constructor
            inputQueue.front() >> data;  // Input the only value (root is a single node, having no siblings)
            *_rRoot = new Node{ data };     // Create {root}
            build_bfs();
        }
    private:
        // @brief Split a string to several istringstreams by detecting '[' and ']'.
        std::vector<std::istringstream> spliter(const std::string& str) {
            std::vector<std::istringstream> istreamQueue{};
            std::string tempStr{};
            for (auto ch : str) {
                switch (ch) {
                case '[': { tempStr.clear(); break; }
                case ']': { 
                    std::istringstream istr(str);
                    istreamQueue.push_back(istr); 
                    break; 
                }
                default: { tempStr += ch; break; }
                }
            }
            // [TODO] Should I add EOF to the end?
            return std::move(istreamQueue);
        }

        std::vector<std::istringstream> getALine() {
            std::string inputLine{};
            std::getline(std::cin, inputLine);
            return std::move(spliter(inputLine));
        }

        /**
         * @brief Make a sequence of (Node*)children with input stream.
         * 
         * @param istr Input stream, consisting of rear strings saperated with whitespaces.
         * @return std::vector<Node*>
         */
        std::vector<Node*> makeChildren(std::istringstream& istr) {
            _ElemTy data{};
            std::vector<Node*> ret;
            while(istr.good()){                          // Keep reading from input stream
                istr >> data;                            // Input an element
                ret.push_back((Node*)(new Node{data}));  // Create and push back a new node to vector
            }
            return std::move(ret);
        }

        void build_bfs(){
            std::queue<Node*> parentQueue;  // A queue to store the parents waiting for construction
            parentQueue.push(*_rRoot);      // Push {root} to queue as the next step is to build it's children

            while (!parentQueue.empty()) {
                auto inputQueue = std::move(getALine());
                for (auto& istr : inputQueue) {
                    Node* current = parentQueue.front();  // Get queue front
                    parentQueue.pop();                    // Pop queue
                    if(istr.str().empty()){ continue; }
                    current->children = std::move(makeChildren(istr)); // Update {current->children}
                    for(auto child: current->children) {
                        parentQueue.push(child);  // Push all children to {parentQueue}
                    }
                }
            }

        }
    };
public:
    build_fn build{ *this };
};
