// Copyright 2024 Anvar

#ifndef LIB_QUEUE_QUEUE_H_
#define LIB_QUEUE_QUEUE_H_


#include <iostream>
#include <stdexcept>

#include "../lib_dmassive/archive.h"

template <typename T>
class TQueue {
 private:
    TDMassive<T> _data;

 public:
    TQueue();
    TQueue(const TQueue& other);
    TQueue& operator=(const TQueue& other);
    ~TQueue();

    void enqueue(const T& value);
    void dequeue();
    T front() const;
    bool empty() const;
    size_t size() const;
    void erase(size_t index);  // Метод для удаления элемента по индексу

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
    _data.clear();
}

template <typename T>
void TQueue<T>::enqueue(const T& value) {
    _data.push_back(value);
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
void TQueue<T>::dequeue() {
    if (empty()) {
        throw std::logic_error("Queue is empty, cannot dequeue.");
    }
    _data.erase(0);  // Удаляем первый элемент
}

template <typename T>
void TQueue<T>::print() const {
    _data.print();
}
#endif  // LIB_QUEUE_QUEUE_H_
