# 1. 问题概述

假设 `x` 是第一棵 HBLT 的 `root`, 类型为 `binaryTreeNode<std::pair<int, T>>*&` ,

假设 `y` 是第二棵 HBLT 的 `root`, 类型为 `binaryTreeNode<std::pair<int, T>>*&` ,

目的: 合并 x 和 y 所指向的两棵 HBLT, 合并结果储存在 x 中.

# 2. 完整代码

带注释的完整代码:

```cpp
template<class T>
void maxHBLT<T>::m_meld(binaryTreeNode<std::pair<int, T>>*& x,
                        binaryTreeNode<std::pair<int, T>>*& y)
{
    if (y == nullptr) {
        return;
    }
    if (x == nullptr) {
        // This is the meld operation.
        // When "x" is the rightest external node, replace "x" with "y".
        x = y; 
        return;
    }
    if (x->element.second < y->element.second) {
        std::swap(x, y);
    }
    // Suppose that "m_meld(x->rightChild, y)" meld "x->rightChild" with "y".
    // Only traverse the rightest path of "x".
    m_meld(x->rightChild, y);
    // After "x->rightChild" is melded with "y",
    // following code adjests the tree whose root is "x" to an HBLT.
    if (x->leftChild == nullptr) {
        // "std::swap()" costs 3 steps, but here we only spends 2 steps.
        x->leftChild = x->rightChild;
        x->rightChild = nullptr;
        // Reset the value of "s(x)".
        x->element.first = 1;
    } else {
        // Make sure the "s(x->leftChild)" is larger than "s(x->rightChild)".
        if (x->leftChild->element.first < x->rightChild->element.first) {
            // If not smaller, exchange "x->leftChild" and "x->rightChild".
            std::swap(x->leftChild, x->rightChild);
            // Reset the value of "s(x)".
            x->element.first = x->rightChild->element.first + 1;
        }
    }
}
```

# 3. 代码实现逻辑

先从最简单的两个节点看起.