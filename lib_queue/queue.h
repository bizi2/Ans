// Copyright 2024 Anvar

#ifndef LIB_QUEUE_QUEUE_H_
#define LIB_QUEUE_QUEUE_H_


#include <iostream>
#include <stdexcept>

#include "../lib_dmassive/archive.h"

template <typename T>
class TQueue {

    TDMassive<T> _data;
 public:
    TQueue();
    TQueue(const TQueue& other);
    TQueue& operator=(const TQueue& other);
    ~TQueue();

    void push_back(const T& value);
    void pop_front();
    T front() const;
    bool empty() const;
    size_t size() const;

    void print() const;
};

template <typename T>
TQueue<T>::TQueue() : _data() {}

template <typename T>
TQueue<T>::TQueue(const TQueue& other) : _data(other._data) {}

template <typename T>
TQueue<T>& TQueue<T>::operator=(const TQueue& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

template <typename T>
TQueue<T>::~TQueue() {
}

template <typename T>
void TQueue<T>::push_back(const T& value) {
    _data.push_back(value);
}
template <typename T>
void TQueue<T>::pop_front() {
    _data.pop_front();
}
template <typename T>
T TQueue<T>::front() const {
    if (empty()) {
        throw std::logic_error(
            "Queue is empty, cannot retrieve front element.");
    }
    return _data[0];  // Возвращаем первый элемент
}
template <typename T>
bool TQueue<T>::empty() const {
    return _data.empty();
}
template <typename T>
size_t TQueue<T>::size() const {
    return _data.size();
}

template <typename T>
void TQueue<T>::print() const {
    _data.print();
}
#endif  // LIB_QUEUE_QUEUE_H_
