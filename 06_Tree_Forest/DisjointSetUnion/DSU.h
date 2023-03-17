// Disjoint Set Union
#pragma once
#include <initializer_list>
#include <compare>
#include <algorithm>
#include <vector>

template<class T>
struct Node
{
    using Index = long long;
    T data;
    Index parent; // If possitve, indicates parent; otherwise, abs val indicates the num of elems.
};

template<class T>
class DSU
{
public:
    using Index = long long;
public:
    DSU(std::initializer_list<T> list);
    virtual ~DSU() {}

    // @brief Get the elem of index {pos}.
    Node<T>& get_node(Index pos) { return *(elem_vec.begin() + pos); }
    // @brief Get the elem of index {pos}.
    const Node<T>& get_node(Index pos) const { return get_node(pos); }
    // @brief Return the position(index) of element {elem}.
    Index find(const T& elem) const;
    // @brief Find the root of {elem}'s equiv class. Returns {-1} if {elem} not exisits.
    Index find_root(const T& elem) const;
    Index find_root_collapse(const T& elem);
    // @brief Union 2 set which respectively contains elem {a} and {b};
    void set_union(const T& a, const T& b);
    void set_weightUnion(const T& a, const T& b);
    // @brief Determine whether {a} and {b} are in the same equivalence class.
    bool whe_equiv(const T& a, const T& b) const;

protected:
    std::vector<Node<T>> elem_vec;
};

template <class T>
DSU<T>::DSU(std::initializer_list<T> list) {
    elem_vec.resize(list.size());
    auto vec_it = elem_vec.begin();
    auto list_it = list.begin();
    while (list_it != list.end() && vec_it != elem_vec.end()) {
        *vec_it = { *list_it,-1 }; // Initialize all Node::root to {-1}.
        ++vec_it;
        ++list_it;
    }
}

template<class T>
DSU<T>::Index DSU<T>::find(const T& elem) const {
    auto it = std::ranges::find(elem_vec, elem, &Node<T>::data);
    Index res = first - elem_vec.begin();
    return res;
}

template<class T>
DSU<T>::Index DSU<T>::find_root(const T& elem) const {
    // Find the Index of {elem}:
    Index ptr = find(elem);
    // IF: Not found element:
    if (ptr == elem_vec.size()) {
        return -1;
    }
    // Find root:
    while (ptr > -1) {
        ptr = get_node(ptr).parent;
    }
    return ptr;
}

template<class T>
void DSU<T>::set_union(const T& a, const T& b) {
    Index rootA = find_root(a);
    Index rootB = find_root(b);
    if (rootA != rootB && rootA != -1 && rootB != -1) {
        get_node(rootA).parent += get_node(rootB).parent;
        get_node(rootB).parent = rootA;
    }
}

template<class T>
void DSU<T>::set_weightUnion(const T& a, const T& b) {
    auto rootA = find_root(a);
    auto rootB = find_root(b);
    if (rootA == rootB || rootA == -1 || rootB == -1) return;
    Index elemNum = get_node(rootA).parent + get_node(rootB).parent;
    if (get_node(rootA).parent <= get_node(rootB).parent) {
        get_node(rootB).parent = rootA;
        get_node(rootA).parent = elemNum;
    } else {
        get_node(rootA).parent = rootB;
        get_node(rootB).parent = elemNum;
    }
}

template<class T>
DSU<T>::Index DSU<T>::find_root_collapse(const T& elem) {
    Index pos = find(elem);
    // IF not found {elem}:
    if (pos == elem_vec.size()) return -1;
    // Find root:
    Index root = find_root(elem);
    // Collapse:
    while (root != get_node(pos).parent) {
        // Get parent index of node[pos]:
        Index parent = get_node(pos).parent;
        // Change node[pos]'s parent to {root}:
        get_node(pos).parent = root;
        // Iterate to node[pos]'s parent, i.e., node[parent].
        pos = parent;
    }
    return root;
}
