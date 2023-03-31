#include "Tree.h"

template<class _ElemTy>
struct bNode
{
    _ElemTy data;
    bNode* child;
    bNode* sibling;
};

template<class _ElemTy>
class Tree_binary
{
    using Node = bNode<_ElemTy>;
private:
    Node* _root = nullptr;
public:
    Tree_binary() = default;
    Tree_binary(const Tree<_ElemTy>& tree) {
        auto troot = tree.get_root().get();
        std::cout << troot->data;
    }
};
