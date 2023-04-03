# 树与森林
## 一些术语  
1. 终端结点/叶子结点：度为0的结点  
2. 祖先：从当前结点出发到根结点经过的所有结点（不含当前结点）  
3. 子孙：以当前结点为根的子树中包含的所有结点（不含当前结点）  
4. 兄弟：双亲相同的结点  
5. 堂兄弟：在同一层但双亲不同的结点  
  
## 表示形式  
1. 树形表示法  
2. 集合表示法  
3. 缩进表示法  
4. 广义表表示法

* * *  
## 存储结构  
<center>  
    <img src="https://i.328888.xyz/2023/04/03/ibCYgC.png" width = "320">  
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.1 一棵树</div>  
</center>  
  
### 1. 双亲表示法（重点）  
**顺序存储**，`parent`域存储双亲结点的下标，根结点的parent为-1  
<center>  
    <img src="https://i.328888.xyz/2023/04/03/ibCKS8.png" width = "520">  
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.2 双亲表示法</div>  
</center>     
  
* 优点：方便求双亲  
* 缺点：不方便求**孩子**和**兄弟**  

改进方案：增加`first_child`（第一个孩子）域和`right_sibling`（右兄弟）域，不存在记为-1  

### 2. 孩子表示法  
(A) 多重链表法  
与二叉树的链式存储相似，但由于结点度数不同，因此指针域有两种设置方式  

方式一：指针域个数 = 该结点的度数  
* 优点：节省存储空间  
* 缺点：各结点**不同构**，操作不易实现  
  
方式二：指针域个数 = 树的度数  
* 优点：各结点同构，操作容易实现    
* 缺点：浪费存储空间（适用于**各结点的度接近树的度**的情况）  
  
(B) 结点数组法  
顺序存储各结点数据，`children`域存放**孩子链表**的头指针    
一个孩子结点由两个域组成：一个域存储该孩子在结点数组中的下标，另一个域存储右兄弟的指针  
<center>  
    <img src="https://i.328888.xyz/2023/04/03/ibCh1p.png"width = "340"/>
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.3 孩子表示法(结点数组法)</div>  
</center>  
  
### 3.双亲—孩子表示法  
在结点数组中增加一个`parent`域  
  
### 4.孩子—兄弟表示法（重点）  
链式存储，每个结点由`first_sibling`域、`data`域和`right_sibling`域组成  
求孩子结点只需通过`first_sibling`域找到第一个孩子，再不断通过`right_sibling`域找所有兄弟     
<center> 
   <img src="https://i.328888.xyz/2023/04/03/ibCa1Q.png" width = "310"/>
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.4 孩子—兄弟表示法</div>  
</center>

* 优点：采用与二叉树相似的二叉链表，**与转换为二叉树后的结构一致**  
* 缺点：难以求双亲（可增加`parent`域）  
* * *  
  
## 转换  
### 树转二叉树  
1. 把兄弟结点全部连起来（绿线）  
2. 在**原连线**中，只保留每个结点与**第一个孩子**结点之间的连线（红线）  
3. 美化  
<center> 
   <img src="https://i.328888.xyz/2023/04/03/ibCGbk.png" width = "570"/>
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.5 树转二叉树</div>  
</center>
  
转换结果是唯一的：  
* 左孩子为原来的第一个孩子，右孩子为原来的右兄弟  
* 根结点**没有右孩子**  
* 转换后的结构与**孩子—兄弟表示法的存储结构一致**（区别仅在于指针域的名称）  
* * *  
### 森林转二叉树  
1. 将每棵树转换为二叉树  
2. 将当前二叉树作为前一棵二叉树根结点的**右子树**  
<center> 
    <img src="https://i.328888.xyz/2023/04/03/ibCdzL.png" width = "500"/>
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.6 森林转二叉树</div>  
</center>

* * *  
### 二叉树转森林（森林转二叉树的逆操作）  
1. 若**结点X为左孩子**（绿色），则将结点X沿**右分支**找到的所有结点（黄色）与**X的双亲**相连  
2. 删除**原连线**中的所有**右分支**(红线)  
3. 美化  
<center> 
    <img src="https://i.328888.xyz/2023/04/03/ibCoXv.png" width = "510"/>
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.7 二叉树转森林</div>  
</center>

当根结点无右子树时，可作为二叉树转一般树的方法  
* * *  
## 遍历  
### 树的遍历
 <center>  
    <img src="https://i.328888.xyz/2023/04/03/ibCYgC.png" width = "320">  
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.8 还是这棵树</div>  
</center>   
  
1. 先根遍历：ABEFKLCGDHIMNJ  
仿照二叉树先序遍历  
结果与转化为二叉树后的**先序遍历**序列一致  
  
2. 后根遍历：EKLFBGCHMNIJDA  
仿照二叉树后序遍历  
结果与转化为二叉树后的**中序遍历**序列一致  
  
3. 层次遍历：ABCDEFGHIJKLMN  
  
### 森林的遍历  
 <center>  
    <img src="https://i.328888.xyz/2023/04/03/ibCFix.png" width = "330">  
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.9 一片森林</div>  
</center>   
  
1. 先根遍历：ABC DEFHGIJ KLM  
相当于对每一棵树依次进行**树的先根遍历**  
结果与转化为二叉树后的**先序遍历**序列一致  
  
2. 中根遍历：BCA EHFIJGD LMK  
相当于对每一棵树依次进行**树的后根遍历**  
结果与转化为二叉树后的**中序遍历**序列一致  
 
3. 后根遍历：CB HJIGFE ML KDA  
结果与转化为二叉树后的**后序遍历**序列一致  

* * *  

# 并查集  
等价关系（$x\equiv y$）：自反、对称、传递  
将集合S分为若干等价类：  
1. 将S拆分成单元素集合  
2. 依次将一个等价对中两个元素所在的集合合并起来  

* * *  

并查集用森林表示（采用**双亲表示法**），一棵树表示一个等价类  
**根结点的双亲为-k**，其中k为该树的元素个数  
  
## 三个操作  
下面以商集$\{\{A,B,C,D\}, \{E,F,G,H\}, \{I,J,K\} \}$为例  
### 1.  `UFSets(arr[], length)`：将集合拆分为单元素集合  
* 将元素转入结点数组  
* 将所有元素的双亲设为-1  
 
初始化森林的时间复杂度为$O(n)$  
<center>  
    <img src="https://i.328888.xyz/2023/04/03/ibCsK3.png" width = "410">  
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.10 初始化</div>  
</center>  
  
###  2. `Find(elem)`：求元素elem所在树的根下标  
* 找到元素elem的下标  
* 不断通过双亲向上移动，直至当前结点的双亲下标为负（说明当前结点为根结点）  

查找所需时间的上界不超过$O(height+1)$  
  
<center>  
    <img src="https://i.328888.xyz/2023/04/03/ibCQCE.png" width = "420">  
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.11 Find(H)</div>  
</center> 

### 3. `Union(elem1, elem2)`：将elem2所在的集合并入elem1所在的集合  
1. 找到elem1和elem2各自所在树的根结点  
2. 更新elem1所在树的元素个数  
3. 将elem2树根结点的双亲更改为elem1的根结点  
 
合并所需时间为$O(1)$  
  
<center>  
   <img src="https://i.328888.xyz/2023/04/03/ibCSCU.png" width = "520">  
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.12 Union(J, G)</div>  
</center>

* * *  

## 优化  
核心思路：尽量减小树的深度  
### 1. WeightedUnion：带加权规则的合并  
使用`Union`函数时，可能会产生**退化树（长链）**  
对于集合$\{e_1, e_2, ..., e_n\}$，退化树查找元素$e_i$所需的时间为$O(i)$  
  
优化方法：合并时，总是**将元素少的树合并到元素多的树上**  
`WeightedUnion`执行时间比`Union`稍多一些，但仍为$O(1)$  
  
### 2. CollapsingFind：使用折叠规则压缩路径的查找  
每处理一个等价对，需要执行两次`Find`和最多一次`WeightedUnion`  
  
优化方法：查找时，将从目标结点到根结点经过的所有结点的**双亲更改为根结点**  
`CollapsingFind`执行时间比`Find`更长，但能减少以后查找的时间  
<center>  
    <img src="https://i.328888.xyz/2023/04/03/ibC9Uy.png" width = "400">  
    <br>  
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;  
    display: inline-block;  
    color: #999;  
    padding: 2px;">Pic.13 CollapsingFind(H)</div>  
</center>