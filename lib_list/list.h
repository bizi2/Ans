// Copyright 2024 Anvar
#pragma once
#include <iostream>
#include <stdexcept>
template <typename T>
class TList;
template <typename T>
class TNode
{


public:
    TNode<T> *pnext;
    TNode();
    TNode(T value, TNode *next);
    TNode(const TNode &nod);
    ~TNode();
    TNode<T> &operator=(const TNode &nod);
    void next(TNode<T> *nod);
    T value;


    bool operator==(T value) const;
    friend std::ostream &operator<<(std::ostream &os, const TNode<T> &node);

    friend std::istream &operator>>(std::istream &is, TNode<T> &node);

    friend class TList<T>;
  
    
};

template <typename T>
TNode<T>::TNode() : value(), pnext(nullptr){}

template <typename T>
TNode<T>::TNode(T value, TNode *next) : value(value), pnext(nullptr) {}

template <typename T>
TNode<T>::TNode(const TNode &nod) : value(nod.value), pnext(nod.pnext) {}

template <typename T>
TNode<T>::~TNode()
{
}
template <typename T>
void TNode<T>::next(TNode<T> *nod) {
    pnext = nod;
}
template <typename T>
TNode<T> &TNode<T>::operator=(const TNode &nod)
{
    if (this != &nod)
    {
        value = nod.value;
    }
    return *this;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const TNode<T> &node)
{
    os << node.value;
    return os;
}

template <typename T>
std::istream &operator>>(std::istream &is, TNode<T> &node)
{
    is >> node.value;
    return is;
}

template <typename T>
class TList {

public:
    TList();
    TList(const TList &list);
    TList<T>& operator=(const TList<T>& other);
    ~TList();
    void push_front(const T &value) noexcept;
    void push_back(const T &value) noexcept;
    void insert(TNode<T> *node, const T &value);
    void insert(size_t pos, const T &value);
    void insertFront(const T &value);
    void insertAfter(const T &value, const T &afterValue);
    void insertAt(const T& value, size_t position);
    TNode<T> *find(const T &value) const noexcept;
    bool isEmpty() const noexcept;
    void pop_front();
    void pop_back();
    void removeValue(const T &value);
    void removeAt(size_t position);
    void erase(TNode<T> *node);
    void erase(size_t pos);
    void replace(TNode<T> *node, const T &value);
    void replace(size_t pos, const T &value);
private:
        class Iterator {
    public:
        Iterator(TNode<T>* node = nullptr) : current(node) {}

        Iterator& operator++() {
            if (current) {
                current = current->pnext;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        T& operator*() {
            return current->value;
        }

        T* operator->() {
            return &current->value;
        }

    private:
        TNode<T>* current;
    };
    public:
    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

public:
    TNode<T> *head = nullptr;
    TNode<T> *tail = nullptr;

};


template <typename T>
TList<T>::TList() : head(nullptr), tail(nullptr) {}

template <typename T>
TList<T>::TList(const TList<T> &list) : head(nullptr), tail(nullptr)
{
    head = nullptr;
    tail = nullptr;
    TNode<T>* current = list.head;
    while (current) {
        push_back(current->value);
        current = current->pnext;
    }
}
template <typename T>
TList<T>& TList<T>::operator=(const TList<T>& other) {
    if (this != &other) {
        while (head != nullptr) {
            TNode<T>* next = head->pnext;
            delete head;
            head = next;
        }
        tail = nullptr;
        TNode<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->pnext;
        }
    }
    return *this;

}
template <typename T>
TList<T>::~TList() {
    while (head != nullptr) {
        TNode<T>* next = head->pnext;
        delete head;
        head = next;
    }
}

template <typename T>
void TList<T>::push_front(const T &value) noexcept
{
    TNode<T>* newNode = new TNode<T>(value, head);
    head = newNode;
    if (tail == nullptr) {
        tail = newNode;
    }
}
template <typename T>
void TList<T>::push_back(const T &value) noexcept
{
    TNode<T>* newNode = new TNode<T>(value, nullptr);
    if (tail == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->pnext = newNode;
        tail = newNode;
    }
}

template <typename T>
void TList<T>::insert(TNode<T> *node, const T &value) {
    TNode<T>* newNode = new TNode<T>(value, nullptr);
    newNode->next(node->pnext);
    node->next(newNode);
    if (newNode == tail) {
        tail = newNode;
    }
}

template <typename T>
void TList<T>::insert(size_t pos, const T& value) {
    if (pos == 0) {
        push_front(value);
    } else {
        TNode<T>* current = head;
        size_t index = 0;
        while (current && index < pos - 1) {
            current = current->pnext;
            index++;
        }
        if (current) {
            TNode<T>* newNode = new TNode<T>(value, nullptr);
            newNode->next(current->pnext);
            current->next(newNode);
            if (newNode == tail) {
                tail = newNode;
            }
        }
    }
}
template <typename T>
void TList<T>::insertAfter(const T &value, const T &afterValue)
{
    TNode<T> *current = head;
    while (current && current->value != afterValue) {
        current = current->pnext;
    }
    if (current) {
        TNode<T>* newNode = new TNode<T>(value, nullptr);
        newNode->next(current->pnext);
        current->next(newNode);
        if (newNode == tail) {
            tail = newNode;
        }
    }
}

template <typename T>
void TList<T>::insertFront(const T &value)
{
    TNode<T> *newNode = new TNode<T>(value, head);
    head = newNode;
    if (tail == nullptr)
    {
        tail = newNode;
    }
}


template <typename T>
void TList<T>::insertAt(const T& value, size_t position) {
    if (position == 0) {
        insertFront(value);
    } else {
        TNode<T>* current = head;
        size_t index = 0;
        while (current && index < position - 1) {
            current = current->pnext;
            index++;
        }
        if (current) {
            TNode<T>* newNode = new TNode<T>(value, nullptr);
            newNode->next(current->pnext);
            current->next(newNode);
            if (newNode == tail) {
                tail = newNode;
            }
        }
    }
}

template <typename T>
TNode<T> *TList<T>::find(const T &value) const noexcept
{
    TNode<T> *current = head;
    while (current && current->value != value)
    {
        current = current->pnext;
    }
    return current; // returns null if value is not found
}
template <typename T>
bool TList<T>::isEmpty() const noexcept
{
    return head == nullptr && tail == nullptr;
}

template <typename T>
void TList<T>::pop_front()
{
    
    TNode<T>* temp = head;
    head = head->pnext;
    delete temp;
}

template <typename T>
void TList<T>::pop_back()
{
    if (head) {
        if (head == tail) {  // Если в списке только один элемент
            delete head;
            head = tail = nullptr;
        } else {
            TNode<T>* current = head;
            while (current->pnext != tail) {  // Идем до предпоследнего элемента
                current = current->pnext;
            }
            delete tail;
            current->pnext = nullptr;
            tail = current;  // Обновляем указатель на tail
        }
    }
}

template <typename T>
void TList<T>::removeValue(const T &value)
{
    if (head) {
        TNode<T>* current = head;
        TNode<T>* prev = nullptr;
        while (current && current->value != value) {
            prev = current;
            current = current->pnext;
        }
        if (current) {
            if (prev) {
                prev->next(current->pnext);
            } else {
                head = current->pnext;
            }
            delete current;
            if (head == nullptr) {
                tail = nullptr;
            }
        }
    }
}

template <typename T>
void TList<T>::removeAt(size_t position) {
    if (position == 0) {
        pop_front();
    } else {
        TNode<T>* current = head;
        TNode<T>* prev = nullptr;
        size_t index = 0;
        while (current && index < position) {
            prev = current;
            current = current->pnext;
            index++;
        }
        if (current) {
            if (prev) {
                prev->next(current->pnext);
            } else {
                head = current->pnext;
            }
            delete current;
            if (head == nullptr) {
                tail = nullptr;
            }
        }
    }
}
template <typename T>
void TList<T>::erase(TNode<T> *node) {
    if (node == nullptr) {
        throw std::invalid_argument("Node pointer is nullptr");
    }
    TNode<T>* current = head;
    TNode<T>* prev = nullptr;
    while (current && current != node) {
        prev = current;
        current = current->pnext;
    }
    if (current) {
        if (prev) {
            prev->next(current->pnext);
        } else {
            head = current->pnext;
        }
        delete current;
        if (head == nullptr) {
            tail = nullptr;
        }
    }
}

template <typename T>
void TList<T>::erase(size_t pos) {
    if (pos == 0) {
        erase(head);
        return;
    }
    TNode<T> *cur = head;
    for (size_t i = 0; i < pos - 1; ++i) {
        if (cur == nullptr) throw std::logic_error("Out of range");
        cur = cur->pnext;
    }
    erase(cur);
}
template <typename T>
void TList<T>::replace(TNode<T> *node, const T &value) {
    if (node == nullptr) {
        throw std::invalid_argument("Node pointer is nullptr");
    }
    node->value;
}
template <typename T>
void TList<T>::replace(size_t pos, const T &value) {
    if (pos == 0) {
        head->value = value;
        return;
    }
    TNode<T> *cur = head;
    for (size_t i = 0; i < pos - 1; ++i) {
        if (cur == nullptr) throw std::logic_error("Out of range");
        cur = cur->pnext;
    }
    if (cur->pnext == nullptr) throw std::logic_error("Out of range");
    cur->pnext->value = value;
}
