#pragma once
#include <iostream>
#include <utility>
#include <cstring>
constexpr int MAX_CAPACITY = 100;

template<class T>
class arrayBinaryTree
{
public:
	arrayBinaryTree(int c = MAX_CAPACITY) :capacity(c) {
		tNode = new std::pair<bool, T>[capacity + 1];
		memset(tNode, 0, (capacity + 1) * sizeof(std::pair<bool, T>));
	}
	~arrayBinaryTree() {
		delete[] tNode;
	}
	void visit(int index);
	void preOrder(int i);
	void inOrder(int i);
	void postOrder(int i);
	void levelOrder();
private:
	std::pair<bool, T>* tNode;
	int capacity;
	int last;
};dddddddddddddd

template<class T>
void arrayBinaryTree<T>::visit(int index) {
	if (tNode[index].first) {
		std::cout << tNode[index].second;
	}
}

template<class T>
void arrayBinaryTree<T>::preOrder(int i) {
	while (i <= last) {
		visit(i);
		preOrder(2 * i);
		preOrder(2 * i + 1);
	}
}

template<class T>
void arrayBinaryTree<T>::inOrder(int i) {
	while (i <= last) {
		inOrder(2 * i);
		visit(i);
		inOrder(2 * i + 1);
	}
}

template<class T>
void arrayBinaryTree<T>::postOrder(int i) {
	while (i <= last) {
		postOrder(2 * i);
		postOrder(2 * i + 1);
		visit(i);
	}
}

template<class T>
void arrayBinaryTree<T>::levelOrder() {
	for (int i = 1; i <= last; i++) {
		visit(i);
	}
}
