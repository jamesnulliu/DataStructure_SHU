# 图(Graph)
> P210  

## I 定义
$$
\text{Graph}=(V,E)
$$
其中
$$
V= \lbrace x|x\in \text{Data Object} \rbrace
$$
是数据元素的集合, 一般被称为**顶点(Vertex)**.
另外:
$$
E= \lbrace (v,w)|v,w\in V \rbrace \\
\text{or} \\
E= \lbrace \langle v,w \rangle |(v,w\in V)\wedge (\text{Path}(v,w)) \rbrace
$$
表示数据元素之间的关系, 也叫**边(edge)**集合;  
$\text{Path}(v,w)$ 表示从顶点 $v$ 到顶点 $w$ 的一条单向通路, 它有方向.  

- 无向图: $(v,w)$ 无序
- 有向图: $\langle v,w \rangle$ 有序  

> P211  

对图进行一些限制:
1. 图中不能有自身环
2. 两个顶点之间相关联的边不能多余一条.

## II 术语
> P212  

1. **完全图(complete graph)**  
    $n$ 个顶点的无向图有 $n(n-1)/2$ 条边, 则被称为完全无向图;  
    $n$ 个顶点的有向图有 $n(n-1)$ 条边, 则被称为完全有向图;

2. **权(weight)**  
    边上的相关系数. 带权图也被称为**网络(network)**.

3. **邻接点(adjacent vertex)**  
    若 $(v,w)$ 是无向图 $\text{G}$ 中的一条边, 则称 $v$ 与 $w$ 互为邻接顶点, 且边 $(v,w)$ 称为依附于顶点 $v$ 和 $w$.  
    若 $\langle v,w \rangle$ 是有向图 $\text{G}$ 中的一条弧, 则称顶点 $v$ 邻接到顶点 $w$ (也称 $v$ 是 $w$ 的前驱, ..., 弧 $\langle v,w \rangle$ 与顶点 $v$ & $w$ 相关联).

4. **子图(subgraph)**  
    设有两个图 $\text{G}=(V,E)$ 以及 $\text{G}'=(V',E')$,  
    若 $V'\subseteq V$ 并且 $E'\subseteq E$ ,
    则称 $\text{G}'$ 是 $\text{G}$ 的子图.

5. **顶点的度(degree)**
    无向图中, 顶点 $v$ 的度等于依附于顶点 $v$ 的边的条数, 记作
    $$
    \text{TD}(v)
    $$
    有向图中, 以 $v$ 为**起始点**的有向边条数称为顶点 $v$ 的出度, 记作  
    $$
    \text{OD}(v)
    $$
    以顶点 $v$ 为**终点**的有向边条数称为顶点 $v$ 的入度, 记作  
    $$
    \text{ID}(v)
    $$
    有向图中顶点 $v$ 的度数为入度和出度之和:
    $$
    \text{TD}(v)=\text{ID}(v)+\text{OD}(v)
    $$
    一般的, 若图 $\text{G}$ 中有 $n$ 个顶点, $e$ 条边(或弧), 则有:
    $$
    e=\frac{\text{TD}(v_1)+\text{TD}(v_2)+\cdots+\text{TD}(v_n)}{2}
    $$

6. **路径(path)**
    在图 $\text{G}=(V,E)$ 中, 若从顶点 $v_i$ 出发, 沿一些边(或弧)经过一系列顶点 $v_{p1},v_{p2},\cdots,v_{pk}$ 最终达到顶点 $v_j$ , 则称顶点序列 $(v_i,v_{p1},v_{p2},\cdots,v_{pk},v_j)$  为顶点 $v_i$ 到顶点 $v_j$ 的一条路径.

7. **路径长度(path length)**

    对于不带权的图,  路径长度为路径上边的数目;  
    对于带权图, 路径长度为各边上权之和.

8. **简单路径与回路(cycle)**
    若路径上各点均不相同, 则称为简单路径;  
    若路径上第一个顶点和最后一个相同, 则称该路径为回路或环.

9. **连通图与连通分量(connected graph and connected component)**
    无向图中, 若两顶点间存在路径, 则称这两个顶点是连通的.  
    如果无向图中任意两个顶点都是联通的, 则称此无向图是连通图.  
    非连通图的极大连通子图(包括所有连通的顶点和这些顶点依附的所有的边)叫做连通分量.

10. **强连通图与强连通分量(strongly connected digraph)**
    有向图中, 对于两个顶点 $v_i$ 和 $v_j$ , 若同时存在 $v_i$ 到 $v_j$ 和 $v_j$ 到 $v_i$ 的路径, 则称 $v_i$ 和 $v_j$ 是强连通.  
    若有向图中任意两个顶点都是强连通的, 则称此有向图为强连通图.  
    非强连通图的极大强连通子图叫做强连通分量. 单个顶点可以组成一个子图.

11. **生成树(spanning tree)**
     一个连通图的生成树是它的极小连通子图, 包含图中全部 $n$ 个顶点和仅使这 $n$ 个顶点连通的 $n-1$ 条边.  
     如果一个有向图只有一个入度为 $0$ 的顶点, 其他顶点入度均为 $1$ , 则这个有向图为有向树.  
     一个有向图的生成森林由若干棵有向树组成, 生成森林含有图中所有顶点, 且只有足以构成若干棵树互不相交的有向树的弧.

## III 图的基本操作

> P213

参考文件 Graph.h , 定义了图的抽象类和方法.

## IV 图的储存结构

### 1 邻接矩阵(Adjacency Matrix)

需要一个顶点矩阵记录每个顶点信息, 还需要一个矩阵表示各顶点之间的关系, 称为邻接矩阵.  
设图 $\text{G}=(V,E)$ 是一个有n个顶点的图, 则图的邻接矩阵是一个二维数组 $\text{Arcs}[n][n]$ , 其定义为:
$$
\text{Arcs}[i][j]=
\begin{cases}
1, & \text{if } \langle i,j \rangle \in E \text{ or } (i,j) \in E  \\ 
0, & \text{otherwise}
\end{cases}
$$
下图给出了无向图和有向图邻接矩阵的示例:

![Graph_01](https://github.com/jamesnulliu/DataStructure_SHU/blob/main/07_Graph/img/Graph_01.png?raw=true)

