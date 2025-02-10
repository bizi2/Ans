#ifndef LIB_STACK_STACK_H_
#define LIB_STACK_STACK_H_

#include <iostream>
#include "../lib_dmassive/archive.h"

template <typename T>
class TStack {
    TDMassive<T> _data;

public:
    TStack();
    TStack(const TStack& other);
    TStack& operator=(const TStack& other);
    ~TStack();

    void push(const T& value);
    void pop();
    T top() const;
    bool empty() const;
    size_t size() const;

    void print() const;
};

template <typename T>
TStack<T>::TStack() : _data() {}

template <typename T>
TStack<T>::TStack(const TStack& other) : _data(other._data) {}

template <typename T>
TStack<T>& TStack<T>::operator=(const TStack& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

template <typename T>
TStack<T>::~TStack() {}

template <typename T>
void TStack<T>::push(const T& value) {
    _data.push_back(value);
}

template <typename T>
void TStack<T>::pop() {
    _data.pop_back();
}

template <typename T>
T TStack<T>::top() const {
    if (empty()) {
        throw std::underflow_error("Stack underflow");
    }
    return _data[_data.size() - 1];
}

template <typename T>
bool TStack<T>::empty() const {
    return _data.empty();
}

template <typename T>
size_t TStack<T>::size() const {
    return _data.size();
}

template <typename T>
void TStack<T>::print() const {
    _data.print();
}

#endif  // LIB_STACK_STACK_H_
