#ifndef LIB_TBIN_SEARCH_TREE_H_
#define LIB_TBIN_SEARCH_TREE_H_

#include <iostream>
#include <stdexcept>
#include <utility> // Для std::move

template <typename Key, typename Value>
class TBinSearchTree {
    // Узел дерева
    struct Node {
        Key key;            // Ключ
        Value value;        // Значение
        Node* left;         // Левый потомок
        Node* right;        // Правый потомок
        Node* parent;       // Родитель
        
        // Конструктор узла
        Node(const Key& k, const Value& v) 
            : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr) {}
        
        // Альтернативный конструктор для семантики перемещения
        Node(const Key& k, Value&& v) 
            : key(k), value(std::move(v)), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    
    Node* root = nullptr;  // Корень дерева

public: 
    // Конструктор по умолчанию
    TBinSearchTree() = default;
    
    // Деструктор (очищает память)
    ~TBinSearchTree() {
        clear(root);
    }
    
    // Конструктор копирования
    TBinSearchTree(const TBinSearchTree& other) {
        copyTree(root, other.root, nullptr);
    }
    
    // Оператор присваивания
    TBinSearchTree& operator=(const TBinSearchTree& other) {
        if (this != &other) {
            clear(root);
            copyTree(root, other.root, nullptr);
        }
        return *this;
    }

    // Основные операции
    Node* search(const Key& key) const;             // Поиск по ключу
    void insert(const Key& key, const Value& value); // Вставка (копирование значения)
    void insert(const Key& key, Value&& value);     // Вставка (перемещение значения)
    void remove(const Key& key);                    // Удаление по ключу
    Node* minimum() const;                          // Минимальный элемент
    Node* maximum() const;                          // Максимальный элемент
    bool isEmpty() const { return root == nullptr; } // Проверка на пустоту

private: 
    // Вспомогательные методы
    Node* minimum(Node* node) const;                // Поиск минимума в поддереве
    Node* maximum(Node* node) const;                // Поиск максимума в поддереве
    void removeNode(Node* node);                    // Удаление узла
    Node* findNode(const Key& key) const;           // Поиск узла по ключу
    void copyTree(Node*& newNode, const Node* oldNode, Node* parent); // Копирование дерева
    void clear(Node* node);                         // Очистка дерева
};

template <typename Key, typename Value>
void TBinSearchTree<Key, Value>::copyTree(Node*& newNode, const Node* oldNode, Node* parent) {
    if (oldNode == nullptr) {
        newNode = nullptr;
        return;
    }
    
    newNode = new Node(oldNode->key, oldNode->value);
    newNode->parent = parent;
    copyTree(newNode->left, oldNode->left, newNode);
    copyTree(newNode->right, oldNode->right, newNode);
}

template <typename Key, typename Value>
void TBinSearchTree<Key, Value>::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename Key, typename Value>
typename TBinSearchTree<Key, Value>::Node* TBinSearchTree<Key, Value>::minimum(Node* node) const {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) node = node->left;
    return node;
}

template <typename Key, typename Value>
typename TBinSearchTree<Key, Value>::Node* TBinSearchTree<Key, Value>::minimum() const {
    return minimum(root);
}

template <typename Key, typename Value>
typename TBinSearchTree<Key, Value>::Node* TBinSearchTree<Key, Value>::maximum(Node* node) const {
    if (node == nullptr) return nullptr;
    while (node->right != nullptr) node = node->right;
    return node;
}

template <typename Key, typename Value>
typename TBinSearchTree<Key, Value>::Node* TBinSearchTree<Key, Value>::maximum() const {
    return maximum(root);
}

template <typename Key, typename Value>
typename TBinSearchTree<Key, Value>::Node* TBinSearchTree<Key, Value>::search(const Key& key) const {
    Node* current = root;
    while (current != nullptr) {
        if (key == current->key) return current;
        current = key < current->key ? current->left : current->right;
    }
    return nullptr;
}

template <typename Key, typename Value>
void TBinSearchTree<Key, Value>::insert(const Key& key, const Value& value) {
    if (root == nullptr) {
        root = new Node(key, value);
        return;
    }

    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            // Ключ уже существует, обновляем значение
            current->value = value;
            return;
        }
    }

    Node* newNode = new Node(key, value);
    newNode->parent = parent;
    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

template <typename Key, typename Value>
void TBinSearchTree<Key, Value>::insert(const Key& key, Value&& value) {
    if (root == nullptr) {
        root = new Node(key, std::move(value));
        return;
    }

    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            // Ключ уже существует, перемещаем значение
            current->value = std::move(value);
            return;
        }
    }

    Node* newNode = new Node(key, std::move(value));
    newNode->parent = parent;
    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

template <typename Key, typename Value>
typename TBinSearchTree<Key, Value>::Node* TBinSearchTree<Key, Value>::findNode(const Key& key) const {
    return search(key);
}

template <typename Key, typename Value>
void TBinSearchTree<Key, Value>::removeNode(Node* node) {
    if (node == nullptr) return;

    // Случай 1: Узел без детей
    if (node->left == nullptr && node->right == nullptr) {
        if (node->parent != nullptr) {
            if (node->parent->left == node) {
                node->parent->left = nullptr;
            } else {
                node->parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }
        delete node;
    }
    // Случай 2: Узел с одним ребенком
    else if (node->left == nullptr || node->right == nullptr) {
        Node* child = (node->left != nullptr) ? node->left : node->right;
        
        if (node->parent != nullptr) {
            if (node->parent->left == node) {
                node->parent->left = child;
            } else {
                node->parent->right = child;
            }
            child->parent = node->parent;
        } else {
            root = child;
            child->parent = nullptr;
        }
        delete node;
    }
    // Случай 3: Узел с двумя детьми
    else {
        Node* successor = minimum(node->right);
        node->key = successor->key;
        node->value = std::move(successor->value);
        removeNode(successor);
    }
}

template <typename Key, typename Value>
void TBinSearchTree<Key, Value>::remove(const Key& key) {
    Node* nodeToDelete = findNode(key);
    if (nodeToDelete != nullptr) {
        removeNode(nodeToDelete);
    }
}

#endif // LIB_TBIN_SEARCH_TREE_H_