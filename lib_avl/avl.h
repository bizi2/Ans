#ifndef LIB_AVL_TREE_H_
#define LIB_AVL_TREE_H_

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "../lib_avl/avl_node.h"
template<typename T>
class AVLTree {
    AVLNode<T>* root;
    void clear(AVLNode<T>* node);
    AVLNode<T>* insert(AVLNode<T>* node , T key);
    AVLNode<T>* remove(AVLNode<T>* node,T key );
    bool search(const AVLNode<T>* node,T key ) const ;
    AVLNode<T>* rightRotate(AVLNode<T>* node);
    AVLNode<T>* leftRotate(AVLNode<T>* node);
    AVLNode<T>* min_value_node(AVLNode<T>* node);
    int height(AVLNode<T>* node) const;
    int balance(AVLNode<T>* node) const;
 public:
    AVLTree() : root(nullptr) {}
    
    ~AVLTree();
    
    void insert(T key);
   
    void remove(T key);
    bool search(T key) const;
    AVLNode<T>* getRoot() const {
        return root;
    }
};
template<typename T>
bool AVLTree<T>:: search(T key) const { return search(root, key); }
template<typename T>
void AVLTree<T>::clear(AVLNode<T>* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}
template<typename T>
AVLTree<T>::~AVLTree() {
    clear(root);
}
template<typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node , T key){
    if(node == nullptr){
        return new AVLNode<T>(key);
    }
    if(key < node->key) {
        node ->left = insert(node ->left , key);
    }
    else if(key > node->key) {
        node->right= insert(node->right, key);
    }
    else {
            throw std::invalid_argument("double key: ");
    }
    node->height = 1 + (std::max(height(node->left) , height(node->right)));
    int balanceFactor = balance(node);
    if(balanceFactor > 1 && key < node->left->key){
        return rightRotate(node);
        //         B                     A
        //       /  \                   /  \ 
        //      A    C                 D     B 
        //    /  \             >      /     /  \ 
        //   D    E                  X     E    C 
        //    \ 
        //     X
    }
    if(balanceFactor < -1 && key > node->right->key){
        return leftRotate(node);
        //     A                     B
        //   /  \                   /  \ 
        //  C    B                 A     E 
        //     /  \     >        /  \   /  
        //    D    E            C    D X
        //          \ 
        //           X
    }
    if(balanceFactor > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
        //         C                     C                     B
        //        / \                   / \                   / \ 
        //       A   L                 B   L                 A   C 
        //      / \          >        / \         >         / \ / \ 
        //     D   B                 A   F                 D  E F  L
        //        / \               / \                      / 
        //       E   F             D   E                    X 
        //      /                     / 
        //     X                     X
    }
    if((balanceFactor < -1 )&& key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
        //       A (balance=-2)               A                          B 
        //      / \                          / \                       /   \ 
        //     K   C (disbalanced)          K   B (new right)        A      C
        //        / \           =>             / \        =>        / \    / \ 
        //       B   E                        D   C                K   D  F   E 
        //      / \                              / \                     / 
        //     D   F                            F   E                   X 
        //        /                            / 
        //       X                            X 
    }
    return node;
}
template<typename T>
void AVLTree<T>::insert(T key) {
    root = insert(root, key);
}
template<typename T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* node,T key ){
     if (!node) {
        throw std::out_of_range("Ключ не найден: ");
    }
    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        if ((node->left == nullptr) || (node->right == nullptr)) {
            AVLNode<T>* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            AVLNode<T>* temp = min_value_node(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }

    if (node == nullptr) {
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));
    if (balance(node) > 1 && balance(node->left) >= 0) {
        return rightRotate(node);
    }
    if (balance(node) > 1 && balance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance(node) < -1 && balance(node->right) <= 0) {
        return leftRotate(node);
    }
    if (balance(node) < -1 && balance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}
template<typename T>
void AVLTree<T>::remove(T key) {
    root = remove(root, key);
}
template<typename T>
bool AVLTree<T>::search(const AVLNode<T>* node, T key) const {
    if (!node) return false;
    if (key == node->key) return true;
    return key < node->key ? search(node->left, key) : search(node->right, key);
}

template<typename T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* B ){
    //              A           B 
    //            /            / \ 
    //           B       >    C   A 
    //          / \              / 
    //         C   D            D 
    if (!B || !B->left) {
        throw std::logic_error("Невозможно выполнить правый поворот");
    }
    AVLNode<T>* A = B->left;
    AVLNode<T>* D = A->right;
    A->right = B;
    B->left =D;
    B->height = std::max(height(B->left), height(B->right)) + 1;
    A->height = std::max(height(A->left),height(A->right)) + 1;
    return A;
}
template<typename T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* A){
    //    A              B 
    //     \            / \ 
    //      B    >     A   D 
    //     / \          \ 
    //    C   D          C 
    if (!A || !A->right) {
    throw std::logic_error("Невозможно выполнить левый поворот");
    }
    AVLNode<T>* B = A->right;
    AVLNode<T>* C = B->left;
    B->left = A;
    A->right = C;
    A->height = std::max(height(A->left),height(A->right)) + 1;
    B->height= std::max(height(B->left),height(B->right)) + 1;
    return B;
}

template<typename T>
AVLNode<T>* AVLTree<T>::min_value_node(AVLNode<T>* node){
    if (!node) {
        throw std::invalid_argument("Узел не существует");
    }
    AVLNode<T>* current = node;
    while (current->left) {
        current = current->left;
    }
    return current;
}
template<typename T>
int AVLTree<T>:: height(AVLNode<T>* node) const{
    if(node == nullptr){
        return 0;
    }
    return node ->height;
}
template<typename T>
int AVLTree<T>:: balance(AVLNode<T>* node) const{
    if(node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}
#endif  // LIB_AVL_TREE_H_