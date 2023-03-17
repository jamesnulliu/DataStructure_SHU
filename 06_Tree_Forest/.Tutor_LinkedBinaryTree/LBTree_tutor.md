# Linked Binary Tree Learning Tutorial
## I Function Object and Lambda Expression
Go to definition of func `preOrder___print()` , read the comments.  
### What is function Object?
When you define a class `A`, after overriding `operator()`, `A` could be a **Function Object Type (or Class, Struct, whatever)**. Check following example:
```cpp
// Definition of class A.
class A{
    void operator()(int x, int y /*Argument List*/){
        std::cout << x << y;
    }
}
```
With class `A`, you can define an instance of `A` and use it just as a function. Check following example:
```cpp
class A; // Declaration of class {A}
A funcObj; // {funcObj} is an instance of class {A}.
funcObj(3,4); // Invoke {operator()} in class {A}.
A()(3,4); // Create an anonmyous instatce and invode {operator()}.
```
### Lambda Expressions
**Lambda Expressions** acts similarlly as function objects, without defining a specific class (i.e., class `A` in previous example). Check following example:
```cpp
auto lambdaObj = [/*Capture List*/](int a, int b /*Argument List*/){
    std::cout << a << b;
};
lambdaObj(3,4); // The result is the same as writing {funcObj(3,4);}.
```
Type of a lambda expression is complicated, and our codes will not involve the Capture List. As a result, we would not go further in these two subjects.  

## II Explanation of Prints
Still checking `preOrder__print()`, we can see after defining a lambda object `visit`, the function called another function named `dfs___preOrder()` .  
This function is the recursion body of preOrder tarversion.  
So then we go to check the definition of `dfs___preOrder()`.

### Template Function in Template Class
It is noticable that the out-of-class definition has TWO template declarations, like the following format:
```cpp
template<class ElemTy>
template<class _Pred>
void LBinTree<ElemTy>::dfs___preOrder( ... ){ 
    ... 
}
```
This is because `dfs___preOrder()` is a **template function** in a template class.  
Please go back to the declaration of this function, which is inside the class defination.  
We can see somethin in the following pattern:

```cpp
template<class ElemTy>
class LBinTree{
public:
    // Declaration of func {dfs___preOrder()}:
    template<class _Pred>
    void dfs___preOrder(LBTNode<ElemTy>* t, const _Pred& pred);
}
```
It's worth noting that template parameter `ElemTy` and `_Pred` are totally different parameters in different templates (former is a class template, and latter is a function template).  
So when defining such kind of function out side the class, you should not write something like:

```cpp
template<class A, class B>
void MyClass::foo(...) {...} // WRONG!
```
Moreover, given such class and instance:

```cpp
template<class A>
class MyClass{
    template<class B>
    void foo1(){ std::cout << x; }
    template<class B>
    void foo2(const B& x){ std::cout << x;}
}
MyClass<int> obj; // An instance of class {MyClass}.
```
You should write something like following codes to invoke function `foo1`:
```cpp
obj.foo1<double>(); // Okay, {obj} is still {MyClass<int>} type, {B} is {double}.
obj.foo1(); // Invalid, we do not know what {B} should be.
```
To invoke `foo2`, we can ommit the template parameter list **if the function parameter list assures the template parameter**. Check following example:
```cpp
obj.foo2<char>('a'); // Okay, explicitly offer the template parameter, which is {char}.
obj.foo2(1.0); // Okay, the compiler would deduce the template parameter according to function parameter. {1.0} is a {double}, so {B} would be {double}.
obj.foo1(); // Invalid, the compiler cannot deduce what {B} should be.
```

Now you have known how `preOrder___print()` works, and thanks for god that `inOrder____print()` and `postOrder__print()` work similarly.  

Actually these three are all **DFS**(Deep-First-Search) algorithms.  
The algorithm goes as deeper as it can, then turns back if it meets the end (or block).  

**DFS** can be written in both recursive way and non-recursive way, which should use a **Stack**.  
Try it!

### LevelOrder, BFS
**BFS**(Breadth-First-Search) is a different searching strategy compared to DFS. 

Usually, we implement this algorithm with the help of a **queue**.  

In our codes, `levelOrder_print()` invokes `bfs_levelOrder()`, and the latter is the real implementation.  
So now please go to the definition of `bfs_levelOrder()`.  

We will not cover how BFS works, please read the code on your own.  

There is still one thing needs to mention, that is, you should never create a container holding **references**.  
In our code, every element in queue `que` is a pointer.  
When you push some pointer into `que`, it actually creates a new pointer, and then copies your some-pointer's value to the newly created one.  

Reference can never be created, because a reference is no an instance.  

## Insert
After learning previous functions, you should have had a basic impression of how things work in trees.  
Now, try to read definitions of func `insert_to_left_` and `insert_to_right` , they are extremely simple.

## Other Functions
Now there are only several functions left. You can read in the following sequence, or pick whatever you like to learn.  
1. `size()` counts the number of nodes with DFS and lambda expression.
2. `height()` counts the height of tree with DFS.
3. `find_bfs()` and `find_dfs()` find nodes according to element value respectively with BFS and DFS.
4. `findParent()` find a node's parent with BFS.

They are not so hard to read, keep moving!



