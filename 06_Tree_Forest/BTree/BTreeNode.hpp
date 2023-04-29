#pragma once
#include <vector>
#include <memory>
#include <algorithm>

/*
  B-Tree of order m
  - Any node containing p keys must have p+1 children
  - Root contains at least 1 key with 2 children
  - Any node except root contains at least ceil(m/2) children
  - Any node contains at most m children with m-1 elements
*/

template<class KeyTy, long long m>
struct BTreeNode
{
public:
    using Index = long long;
    using Size = long long;

    using NodePtr = std::shared_ptr<BTreeNode<KeyTy, m>>;
    using const_NodePtr = std::shared_ptr<const BTreeNode<KeyTy, m>>;

    std::vector<KeyTy> keys{};
    std::vector<NodePtr> children{};

    bool is_leaf() const { return children.empty(); }
};