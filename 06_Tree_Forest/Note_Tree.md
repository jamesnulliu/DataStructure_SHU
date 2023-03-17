# 1. 中英词汇对应表

1. 树 **tree**
    - 二叉树 **binary tree**
        - 完全二叉树 **complete binary tree**
        - 满二叉树 **full binary tree**
    - 堆 **heap**
        - 配对堆 **pairing heap**
        - 区间堆 **interval heap**
    - 左高树 **leftist tree**
        - 高度优先左高树 **height-biased leftist tree**
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

---

# 2. Binary Tree
## 2.1. 定义
1. **[binary tree]** 是一个有限个元素的集合(可以为空). 当二叉树非空, 其中一元素被称为 **root**, 余下元素(如果有)被划分为两棵二叉树, 分别被称为该元素的 **left child** 和 **right child**.
2. **[full binary tree]** 是一棵恰好有 $2^h-1$ 个元素的二叉树. 
3. **[complete binary tree]** 是除底层外为 **full binary tree**, 且底层节点集中于左边的树.

## 2.2. 性质
1. 一棵 **binary tree** 有 $n$ 个元素, 则有 $n-1$ 条边.
2. 一棵 **binary tree** 高度为 $h$ , $ h \geq 0 $ , 则它最少有 $h$ 个元素, 最多有 $2^h-1$ 个元素.
3. 一颗 **binary tree** 有 $n$ 个元素, $n>0$ , 那么它的高度最大为 $n$, 最小为 $\lceil \log_2 (n+1) \rceil$ .
4. 一颗 **complete binary tree** 有 $n$ 个元素, 那么它的高度为 $\log_2 (n+1)$ .
5. 设一颗 **complete binary tree** 中一元素的编号为 $i$ , $1 \leq i \leq n$ , 则有以下关系:
    - 若 $i = 1$ , 则该元素为二叉树的 **root**; 若 $i>1$ , 则其 **parent** 的编号为 $\lceil i/2 \rceil$ .
    - 若 $2i>n$ , 则该元素无 **left child**; 否则, 其 **left child** 的编号为 $2i$ .
    - 若 $2i+1>n$ , 则该元素无 **right child**; 否则, 其 **right child** 的编号为 $2i+1$ .

---

# 3. Heap
## 3.1. 定义
1. **[max(min) tree]** 一棵树, 其中每个节点的值都大于(小于)或等于其 **children** (如果有)的值.  
2. **[max(min) heap]** **max(min) tree** + **complete binary tree**. 

## 3.2. 性质

1. **heap** 是一种 **隐式数据结构 (implicit data structure)**. 用完全二叉树表示的堆在数组中**隐式储存** (没有明确的指针或其他数据能够用来重塑这种结构). 由于没有储存**结构信息**, 这种表示方法的空间利用率很高, 没有浪费任何空间; 又由于用数组形式储存, 它的时间效率也很高. 

# 4. Leftist Tree

## 4.1. 定义

1. The binary tree with **external nodes** (to fill up the empty subtrees, opposite to internal nodes) is called **extened binary tree**.

2. $s(x)$ 是 from **node x** to its **subtree's external node** 的左右路径中**最短**的一条.

   If **x** is an **external node**, $s(x)=0$ .

   If **x** is an **internal node**, $s(x)=\min\{s(LeftChild),s(RightChild)\}+1$ .

3. **[HBLT]** 当且仅当一颗 **binary tree** 的任何一个 **internal node** 的 $s(LeftChild)$ 都大于或等于 $s(RightChild)$, 这颗 binary tree 被称为 **height-biased lefist tree (HBLT)**.

4. **[WBLT]** 设 $w(x)$ 表示 **node x** 所有 **descendent node** 的数量, 则当且仅当一颗 **binary tree** 的任何一个 **internal node** 的 $w(LeftChild)$ 都大于或等于 $w(RightChild)$, 这颗 binary tree 被称为 **weight-biased lefist tree (HBLT)**.

5. **[max(min) HBLT]** **HBLT** + **max(min) tree**.

6. **[max(min) WBLT]** **WBLT** + **max(min) tree**.

## 4.2. 性质

1. 令 **x** is an **interal node** of an **HBLT**:

   - 以 x 为 root 的 (sub)tree 的节点数量 至少 为 $2^{s(x)}-1$ .

      > **证明:** 根据 **性质 4.1.2.** , 由于到达 **external node** 的最短路径为 $s(x)$ , 因此在自 **x** 向下一直到第  $s(x)-1$ 层都无 **external node**. 也就是说, 自该层向上到 **x** 是一棵 **complete binary tree**. 根据 性质 2.2.2. 以 **x** 为 root 的 **(sub)tree** 至少包含上述 **complete binary tree** 的 $2^{s(x)}-1$ 个节点. 而再往下的层就不能确定节点的数量了.

   - 若以 **x** 为 **root** 的 **(sub)tree** 有 **m** 个节点, 那么 $s(x)$ 最多为 $\log_{2}{(m+1)}$ .

   - 从 **x** 到一个 **external node** 的最右路径 (即从 x 开始延 **Right Child** 移动的路径) 的长度为 $s(x)$ .



​		

