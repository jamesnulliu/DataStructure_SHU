#pragma once

template<class T>
struct ChainNode
{
	T element;
	ChainNode<T>* next;
	ChainNode(T e = 0, ChainNode<T>* n = nullptr) :element(e), next(n) {}
};

template<class T>
class Chain
{
protected:
	int m_size;
	ChainNode<T>* link;
	void init();
public:
	int size() const;
	bool empty() const;
	Chain();
	~Chain();
	ChainNode<T>* get_firstNode() const;
	void insert(const T&);
};

template<class T>
void Chain<T>::init() {
	link = new ChainNode<T>;
	m_size = 0;
}

template<class T>
int Chain<T>::size() const {
	return m_size;
}

template<class T>
bool Chain<T>::empty() const {
	return !m_size;
}

template<class T>
Chain<T>::Chain() {
	init();
}

template<class T>
Chain<T>::~Chain() {
	ChainNode<T>* p = link;
	while (link) {
		p = p->next;
		delete link;
		link = p;
	}
}

template<class T>
ChainNode<T>* Chain<T>::get_firstNode() const {
	return link->next;
}

template<class T>
void Chain<T>::insert(const T& data) {
	ChainNode<T>* node = new ChainNode<T>(data, link->next);
	link->next = node;
	m_size++;
}