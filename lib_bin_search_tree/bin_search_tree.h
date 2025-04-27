#ifndef LIB_TBIN_SEARCH_TREE_H_
#define LIB_TBIN_SEARCH_TREE_H_

#include <iostream>
#include <stdexcept>
#include "../lib_bin_search_tree/bin_tree.h"
template <typename T>
class TBinSearchTree
{
    TreeNode<T>* root = nullptr;
 public : 
    TBinSearchTree() = default;
    ~TBinSearchTree();
    TBinSearchTree(const TBinSearchTree& other);
    TreeNode<T>* search(T val); // поиск
    TreeNode<T>* insert(T val); // вставить
    TreeNode<T> remove(TreeNode<T>* left , TreeNode<T>* right, TreeNode<T>* node); //удаление
    TreeNode<T> replace(TreeNode<T>* left , TreeNode<T>* right, TreeNode<T>* node , T value); // замена 
    TreeNode<T> copyTREE(TreeNode<T>* node);

};


//TBinSearchTree<T> :: TBinSearchTree(const TBinSearchTree& other){

template<typename T>
TreeNode<T>* TBinSearchTree<T> :: search(T val) {
    TreeNode<T>* current = root;
    while (current != nullptr)
    {
        if(val == current->value){
            return current;
        }
        else if (val < current ->value) {
            current = current ->left;
        }
        else {
            current = current->right;
        }
    }
    return nullptr;
    
}

template<typename T>
TreeNode<T>* TBinSearchTree<T> :: insert(T val){
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode<T>* current = root;
    if (val = current->value){
        if(current->left == nullptr) {
            current->left = val
        }
        else {
            val = current->left;
        }
    }
    if (val = current-> value) {
        if (current->right == nullptr) {
            current->right = val;
        }
        else {
            val = current->right;
        }
    }
}
#endif //LIB_TBIN_SEARCH_TREE_H_