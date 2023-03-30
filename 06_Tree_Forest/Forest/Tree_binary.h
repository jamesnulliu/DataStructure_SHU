template<class _ElemTy>
struct Node
{
    ElemTy data;
    Node* child;
    Node* sibling;
};

template<class _ElemTy>
class Tree_binary
{
private:
    Node* root = nullptr;
public:
    Tree_binary() = default;
};
