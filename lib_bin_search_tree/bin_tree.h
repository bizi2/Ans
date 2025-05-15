/* #ifndef LIB_TBIN_TREE_H_
#define LIB_TBIN_TREE_H_

#include <iostream>
#include <stdexcept>
#include <algorithm> // для std::max
template <typename T>
class TBinSearchTree;
template <typename T>
class TreeNode {
    friend class TBinSearchTree<T>;
    T value;              // Значение узла
    TreeNode* left;       // Левый потомок
    TreeNode* right;      // Правый потомок
    TreeNode* parent;

public:
    // Конструктор по умолчанию
    TreeNode() : left(nullptr), right(nullptr) {}
    
    // Основной конструктор
    TreeNode(T value, TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr) 
        : value(value), left(left), right(right) {}
    
    // Конструктор копирования
    TreeNode(const TreeNode<T>& node);
    
    // Деструктор (очищаем память)
    ~TreeNode() {
        delete left;
        delete right;
    }
    
    // Получить значение узла
    T get_value() const { return value; }
    
    // Получить левого потомка
    TreeNode<T>* get_left_node() const { return left; }
    
    // Получить правого потомка
    TreeNode<T>* get_right_node() const { return right; }
    
    // Высота левого поддерева
    int get_left_height() const;
    
    // Высота правого поддерева
    int get_right_height() const;
    
    TreeNode<T>* get_uncle() const;
    // Оператор присваивания
    TreeNode<T>& operator=(const TreeNode<T>& node);
};

// Реализация конструктора копирования
template <typename T>
TreeNode<T>::TreeNode(const TreeNode<T>& node) 
    : value(node.value), left(nullptr), right(nullptr) {
    if (node.left) left = new TreeNode<T>(*node.left);
    if (node.right) right = new TreeNode<T>(*node.right);
}

// Реализация вычисления высоты левого поддерева
template <typename T>
int TreeNode<T>::get_left_height() const {
    if (!left) return 0;
    return 1 + std::max(left->get_left_height(), left->get_right_height());
}

// Реализация вычисления высоты правого поддерева
template <typename T>
int TreeNode<T>::get_right_height() const {
    if (!right) return 0;
    return 1 + std::max(right->get_left_height(), right->get_right_height());
}
template <typename T>
TreeNode<T>* TreeNode<T>::get_uncle() const {
    if (!parent) {
        return nullptr;
    }
    if (!parent->parent) {
        return nullptr;
    }
    
    // Если родитель является левым потомком дедушки, то дядя - правый потомок дедушки
    if (parent == parent->parent->left) {
        return parent->parent->right;
    }
    // Иначе дядя - левый потомок дедушки
    else {
        return parent->parent->left;
    }
}
// Реализация оператора присваивания
template <typename T>
TreeNode<T>& TreeNode<T>::operator=(const TreeNode<T>& node) {
    if (this != &node) {
        // Очищаем старые потомки
        delete left;
        delete right;
        
        // Копируем значение
        value = node.value;
        
        // Копируем потомков (если они есть)
        left = node.left ? new TreeNode<T>(*node.left) : nullptr;
        right = node.right ? new TreeNode<T>(*node.right) : nullptr;
    }
    return *this;
}

#endif // LIB_TBIN_TREE_H_ */