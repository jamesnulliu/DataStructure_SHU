# 1. 定义&概念

1. **[max(min) tree]** 一棵树, 其中每个节点的值都大于(小于)或等于其 **children** (如果有)的值.  

2. **[max(min) heap]** **max(min) tree** + **complete binary tree**. 

3. 设一颗 **complete binary tree** 中一元素的编号为 $i$ , $1 \leq i \leq n$ , 则有以下关系:
    - 若 $i = 1$ , 则该元素为二叉树的 **root**; 若 $i>1$ , 则其 **parent** 的编号为 $\lceil i/2 \rceil$ .
    - 若 $2i>n$ , 则该元素无 **left child**; 否则, 其 **left child** 的编号为 $2i$ .
    - 若 $2i+1>n$ , 则该元素无 **right child**; 否则, 其 **right child** 的编号为 $2i+1$ .
    
# 2. maxHeap()::initialize()

## 2.1. 完整代码

```cpp
template<class T>
void maxHeap<T>::initialize(T* theHeap, int theSize)
{
    delete[] heap; // Empty the memory of "T* maxHeap<T>::heap".
    heap = theHeap; // Make "heap" points to "theHeap".
    heapSize = theSize; // Set the "heapSize".

    // 'root' would iterates from "heapSize/2" and keep decreasing until reaches real root.
    for (int root = heapSize / 2; root >= 1; root--) {
        // Pick up the current element of 'root'.
        T rootElement = heap[root];
        int child = 2 * root;
        // 'child' iterates from the child of current root, but cannot be larger than 'heapSize'.
        for (; child <= heapSize; child *= 2) {
            // Ensure 'heap[child]' the larger one among the brothers.
            if (child < heapSize && heap[child] < heap[child + 1]) {
                child++;
            }
            // IF: 'rootElement' can be put in 'heap[child/2]'.
            if (rootElement >= heap[child]) {
                break;
            }
            // IF: "rootElement" cannot be put in "heap[child/2]".
            // Move 'heap[child]' to 'heap[root]'.
            heap[root] = heap[child];
            // Re-allocate the next level to 'child'.
        }
        heap[child / 2] = rootElement;
    }
}
```

## 2.2. 代码解释

![p-2](C:\Users\james\.Project\DSA-Learning\DSAA-in-Cpp-Sartaj-Sahni\12_PriorityQueue\image\p-2.jpg)

以上图为例, 假设我们要将数组 `heap[1:11]` 初始化为 max heap, 先将 `root=heapSize/2=11/2=5` 作为外层 for 循环的迭代器. `root` 将会以 5-4-3-2-1 的顺序迭代.

假设我们的 `root` 迭代到了 `heap[2]` , 那就说明以 `heap[4]` 和 `heap[5]` 为 root 的 subtree 都已经是排好序的 max heap.

因为不确定这两个 subtree 由 `heap[2]` 作 root 连接是否还是合法的 max heap , 因此我们要通过内层的 for 循环找到 `heap[2]` 中储存的 `20` 的合适储存位置.

怎么找到合适的储存位置呢? 说到底就是要找到一条路径直到一个比 `20` 小的元素, 路径上所有元素上移一个结点, 最后将 `20` 填入元素比其小的结点的 parent node 中.

需要注意的是, 为了所有元素上移后仍满足 定义 1.1, 在从 `root` 向下寻找路径的过程中, 我们总是要寻找 child nodes 中元素较大的那个.

在上图中, 从 `heap[2]` 开始寻找插入位置:

- 内层 for 循环 从 `heap[child=2*2=4]` 开始, 先由 if 语句块 找到同层所含元素更大的结点 `heap[child=child+1=5]` ;
- 由于 `35` 大于 `20`, 我们把 `35` 填入他的 parent node (`heap[2]`) 中, 然后迭代 `child=child*2=10` ;
- 由 if 语句块 找到同层所含元素更大的结点 `heap[child=child+1=11]` ;
- 由于 `15` 小于 `20`, 结束内层 for 循环, 跳入外层 for 循环, 将 `20` 填入 `heap[child/2]` .

这样, 以 `heap[2]` 为 root 的 subtree 就是一个排好序的 max heap 了.



