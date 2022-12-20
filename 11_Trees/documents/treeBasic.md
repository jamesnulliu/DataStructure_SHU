# 0. 注意事项与声明
**本文摘录整理自 *Data Structures, Algorithms, and Applications in C++*.**  
  
作者: JamesNULLiu  
邮箱: jamesnulliu@outlook.com  
博客: [ ]( )  
  
**学习笔记 请注明出处 欢迎留言**  
  
# 1. 中英词汇对应表
1. 树 **tree**
    - 二叉树 **binary tree**
        - 完全二叉树 **complete binary tree**
        - 满二叉树 **full binary tree**
    - 堆 **heap**
        - 配对堆 **pairing heap**
        - 区间堆 **interval heap**
    - 左高树 **leftist tree**
    - 竞赛树 **tournament tree**
    - AVL树 **AVL tree**
    - 红黑树 **red-black tree**
    - 伸展树 **splay tree**
    - 字典树/前缀树/单词查找树/键树 **tries**
    - 后缀树 **suffix tree**
2. 结构
    - 根 **root**
    - 子树 **subtree**
    - 孩子 **children**
    - 双亲 **parent**
    - 兄弟 **sibling**
    - 祖先 **ancestor**
    - 后代 **descendent**
    - 叶子 **leaf**

# 2. Binary Tree
## 2.1. 定义
1. **[binary tree]** 是一个有限个元素的集合(可以为空). 当二叉树非空, 其中一元素被称为 **根**, 余下元素(如果有)被划分为两棵二叉树, 分别被称为该元素的 **左子树** 和 **右子树**.
2. **[full binary tree]** 是一棵恰好有 \(2^h-1\) 个元素的二叉树.
3. **[complete binary tree]** 是除底层外为 **full binary tree**, 且底层结点集中于左边的树.

## 2.2. 性质
1. 一棵 **binary tree** 有 $ n $ 个元素, 则有 \(n-1\) 条边.
2. 一棵 **binary tree** 高度为 \(h\), \( h \geq 0 \), 则它最少有 \(h\) 个元素, 最多有 \(2^h-1\) 个元素.
3. 一颗 **binary tree** 有 \(n\) 个元素, \(n>0\), 那么它的高度最大为 \(n\), 最小为 \(\lceil \log_2 (n+1) \rceil\).
4. 一颗 **complete binary tree** 有 \(n\) 个元素, 那么它的高度为 \(\log_2 (n+1)\).
5. 设一颗 **complete binary tree** 中一元素的编号为 \(i\), \(1 \leq i \leq n\), 则有以下关系:
    - 若 \(i = 1\), 则该元素为二叉树的 **root**; 若 \(i>1\), 则其 **parent** 的编号为 \(\lceil i/2 \rceil\).
    - 若 \(2i>n\), 则该元素无 **left child**; 否则, 其 **left child** 的编号为 \(2i\).
    - 若 \(2i+1>n\), 则该元素无 **right child**; 否则, 其 **right child** 的编号为 \(2i+1\).

# 3. Heap
## 3.1. 定义
1. **[max(min) tree]** 一棵树, 其中每个结点的值都大于(小于)或等于其 **children** (如果有)的值.  
2. **[max(min) heap]** **max(min) tree** + **complete binary tree**. 