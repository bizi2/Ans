// Copyright 2024 Anvar
#pragma once
#include <iostream>
#include <stdexcept>  // Для исключений

template <typename T>
class TNode {
    T _value;
    TNode<T>* pnext;

public:
    TNode(T value, TNode* next = nullptr);
    explicit TNode(const TNode& nod);

    TNode<T>* next() const;   // Изменено на const
    void next(TNode<T>* nod);
    T value() const;          // Изменено на const
    void set_value(T value);

    TNode<T>& operator=(const TNode& nod);
    bool operator==(T value) const;  // Изменено на const
};

template <typename T>
TNode<T>::TNode(T value, TNode* next) : _value(value), pnext(next) { }

template <typename T>
TNode<T>::TNode(const TNode& nod) : _value(nod._value), pnext(nod.pnext) { }

template <typename T>
TNode<T>* TNode<T>::next() const {
    return pnext;
}

template <typename T>
void TNode<T>::next(TNode<T>* nod) {
    pnext = nod;
}

template <typename T>
T TNode<T>::value() const {
    return _value;
}

template <typename T>
void TNode<T>::set_value(T value) {
    _value = value;
}

template <typename T>
TNode<T>& TNode<T>::operator=(const TNode<T>& nod) {
    if (this != &nod) {  // Проверка на самоприсваивание
        _value = nod._value;
        pnext = nod.pnext;
    }
    return *this;
}

template <typename T>
bool TNode<T>::operator==(T value) const {
    return _value == value;
}

template <typename T>
class TList {
public:
    TNode<T>* head = nullptr;
    TNode<T>* last = nullptr;

    TList() = default;
    TList(const TList& list);
    ~TList();

    void push_front(const T& value) noexcept;
    void push_back(const T& value) noexcept;
    void insert(TNode<T>* node, const T& value);
    void insert(size_t pos, const T& value);
    TNode<T>* find(const T& value) const noexcept;
    bool isEmpty() const noexcept;
    void pop_front();
    void pop_back();
    void erase(TNode<T>* node);
    void erase(size_t pos);
    void replace(TNode<T>* node, const T& value);
    void replace(size_t pos, const T& value);
};

template <typename T>
TList<T>::TList(const TList<T>& list) : head(nullptr), last(nullptr) {
    TNode<T>* current = list.head;
    while (current != nullptr) {
        push_back(current->value());
        current = current->next();
    }
}

template <typename T>
TList<T>::~TList() {
    while (head != nullptr) {
        pop_front();
    }
}

template <typename T>
void TList<T>::push_front(const T& value) noexcept {
    TNode<T>* newNode = new TNode<T>(value, head);
    head = newNode;
    if (last == nullptr) {
        last = head;
    }
}

template <typename T>
void TList<T>::push_back(const T& value) noexcept {
    TNode<T>* newNode = new TNode<T>(value);
    if (last == nullptr) {
        head = newNode;
        last = head;
    } else {
        last->next(newNode);
        last = newNode;
    }
}

template <typename T>
void TList<T>::insert(TNode<T>* node, const T& value) {
    if (node == nullptr) {
        throw std::invalid_argument("Node pointer is nullptr");
    }
    TNode<T>* newNode = new TNode<T>(value, node->next());
    node->next(newNode);
    if (node == last) {
        last = newNode;
    }
}

template <typename T>
void TList<T>::insert(size_t pos, const T& value) {
    if (pos == 0) {
        push_front(value);
        return;
    }
    TNode<T>* cur = head;
    for (size_t i = 0; i < pos - 1; ++i) {
        if (cur == nullptr) throw std::logic_error("Out of range");
        cur = cur->next();
    }
    insert(cur, value);
}

template <typename T>
TNode<T>* TList<T>::find(const T& value) const noexcept {
    TNode<T>* cur = head;
    while (cur != nullptr) {
        if (cur->value() == value) {
            return cur;
        }
        cur = cur->next();
    }
    return nullptr;
}

template <typename T>
bool TList<T>::isEmpty() const noexcept {
    return head == nullptr;
}

template <typename T>
void TList<T>::pop_front() {
    if (isEmpty()) throw std::runtime_error("List is empty");
    TNode<T>* temp = head;
    head = head->next();
    delete temp;
    if (head == nullptr) {
        last = nullptr; // Если список пуст, сбрасываем указатель на последний элемент
    }
}

template <typename T>
void TList<T>::pop_back() {
    if (isEmpty()) throw std::runtime_error("List is empty");
    if (head == last) {
        delete head;
        head = nullptr;
        last = nullptr;
        return;
    }
    TNode<T>* current = head;
    while (current->next() != last) {
        current = current->next();
    }
    delete last;
    last = current;
    last->next(nullptr);
}

template <typename T>
void TList<T>::erase(TNode<T>* node) {
    if (node == nullptr) {
        throw std::invalid_argument("Node pointer is nullptr");
    }
    if (node == head) {
        pop_front();
        return;
    }
    TNode<T>* current = head;
    while (current != nullptr && current->next() != node) {
        current = current->next();
    }
    if (current == nullptr) throw std::runtime_error("Node not found");
    current->next(node->next());
    delete node;
    if (node == last) {
        last = current;
    }
}

template <typename T>
void TList<T>::erase(size_t pos) {
    if (pos == 0) {
        pop_front();
        return;
    }
    TNode<T>* cur = head;
    for (size_t i = 0; i < pos - 1; ++i) {
        if (cur == nullptr) throw std::logic_error("Out of range");
        cur = cur->next();
    }
    if (cur == nullptr || cur->next() == nullptr) throw std::logic_error("Out of range");
    erase(cur->next());
}

template <typename T>
void TList<T>::replace(TNode<T>* node, const T& value) {
    if (node == nullptr) throw std::invalid_argument("Node pointer is nullptr");
    node->set_value(value);
}

template <typename T>
void TList<T>::replace(size_t pos, const T& value) {
    TNode<T>* cur = head;
    for (size_t i = 0; i < pos; ++i) {
        if (cur == nullptr) throw std::logic_error("Out of range");
        cur = cur->next();
    }
    replace(cur, value);
}
