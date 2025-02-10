#ifndef DSU_H
#define DSU_H

template <typename T>
class DSU {

    int _size;
    int *_parent;
    int *_rank;

public:
    DSU(int size = 0);
    ~DSU();
    void make_set(int elem);
    int find(int elem);
    void union_sets(int first, int second);
    void clear();

};

template <typename T>
DSU<T>::DSU(int size) : _size(size), _parent(new int[size]), _rank(new int[size]) {
    for (int i = 0; i < size; ++i) {
        _parent[i] = i;
        _rank[i] = 1;
    }
}

template <typename T>
DSU<T>::~DSU() {
    delete[] _parent;
    delete[] _rank;
}

template <typename T>
void DSU<T>::make_set(int elem) {
 if (elem >= 0 && elem < _size) {
        _parent[elem] = elem;
        _rank[elem] = 1;
    }
}

template <typename T>
int DSU<T>::find(int elem) {
    if (elem < 0 || elem >= _size) {
        throw logic_error("Element out of range");
    }

    if (_parent[elem] != elem) {
        _parent[elem] = find(_parent[elem]);
    }
    return _parent[elem];
}

template <typename T>
void DSU<T>::union_sets(int first, int second) {
    int first_root = find(first);
    int second_root = find(second);

    if (first_root == -1 || second_root == -1 || first_root == second_root) {
        return;
    }

    if (_rank[first_root] < _rank[second_root]) {
        _parent[first_root] = second_root;
    } else {
        _parent[second_root] = first_root;
        if (_rank[first_root] == _rank[second_root]) {
            _rank[first_root]++;
        }
    }
}

template <typename T>
void DSU<T>::clear() {
    delete[] _parent;
    delete[] _rank;
    _parent = nullptr;
    _rank = nullptr;
    _size = 0;
}

#endif  // DSU_H