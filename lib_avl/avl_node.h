#ifndef LIB_AVL_NODE_H_
#define LIB_AVL_NODE_H_

#include <iostream>
#include <stdexcept>
template<typename T>
class AVLNode {
 public:
    T key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(T k);
};
template<typename T>
AVLNode<T>:: AVLNode(T k)
        : key(k)
        , left(nullptr)
        , right(nullptr)
        , height(1) {}
#endif // LIB_AVL_NODE_H_