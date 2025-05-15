
#ifndef LIB_STACK_LIST_H_
#define LIB_STACK_LIST_H_

#include <iostream>
#include <stdexcept>
#include "../lib_list/list.h"

template <typename T>
class TStack_LIST {
public:
    TStack_LIST();
    ~TStack_LIST();

    void push(const T& value);
    void pop();
    T top() const;
    bool isEmpty() const;
    size_t size() const;

private:
    TList<T> list;
};

template <typename T>
TStack_LIST<T>::TStack_LIST() {}

template <typename T>
TStack_LIST<T>::~TStack_LIST() {}

template <typename T>
void TStack_LIST<T>::push(const T& value) {
    list.push_front(value);
}

template <typename T>
void TStack_LIST<T>::pop() {
    if (list.isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    list.pop_front();
}

template <typename T>
T TStack_LIST<T>::top() const {
    if (list.isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return list.head->value;
}

template <typename T>
bool TStack_LIST<T>::isEmpty() const {
    return list.isEmpty();
}

template <typename T>
size_t TStack_LIST<T>::size() const {
    size_t count = 0;
    TNode<T>* current = list.head;
    while (current != nullptr) {
        ++count;
        current = current->pnext;
    }
    return count;
}
#endif  // LIB_STACK_LIST_H_
