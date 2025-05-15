#pragma once
#include <iostream>
#include <utility>
#include <algorithm>
#include "../lib_dmassive/archive.h"

template <typename T> class TVector;
template <typename T>
TVector<T> operator*(const TVector<T>& vec, T scalar);
template <typename T>
TVector<T> operator*(T scalar, const TVector<T>& vec);

template <typename T>
class TVector {
    TDMassive<T> _data;
    size_t _start_index;

public:
    TVector();
    TVector(const TVector& vec);
    explicit TVector(size_t n, size_t start_index = 0);
    ~TVector();

    void print() const noexcept;

    inline bool empty() const noexcept;
    inline bool full() const noexcept;

    size_t size() const noexcept;
    size_t start_index() const noexcept;
    const T* data() const;

    void swap(TVector& vec);

    TVector& assign(const TVector& vec);

    void clear();
    void resize(size_t n, T value = T());

    void push_back(T value);
    void pop_back();

    TVector& insert(const T* arr, size_t n, size_t pos);
    TVector& insert(T value, size_t pos);

    TVector& replace(size_t pos, T new_value);
    void push_front(T value);
    void pop_front();

    TVector& erase(size_t pos, size_t n);
    TVector& remove_all(T value);
    TVector& remove_first(T value);
    TVector& remove_last(T value);
    TVector& remove_by_index(size_t pos);

    size_t* find_all(T value) const noexcept;
    size_t find_first(T value) const;
    size_t find_last(T value) const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    TVector& operator=(const TVector& vec) noexcept;
    TVector operator+(const TVector& vec) const;
    TVector operator-(const TVector& vec) const;
    friend TVector<T> operator*<T>(const TVector<T>& vec, T scalar);
    friend TVector<T> operator*<T>(T scalar, const TVector<T>& vec);
    TVector& operator+=(const TVector& vec);
    TVector& operator-=(const TVector& vec);
    TVector& operator*=(const TVector<T>& other);
    TVector& operator*=(const T& scalar);
    bool operator==(const TVector& vec) const;
    bool operator!=(const TVector& vec) const;

    class Iterator {
    public:
        Iterator(TVector<T>* vec, size_t index) : _vec(vec), _index(index) {}

        Iterator& operator++() {
            ++_index;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++_index;
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return _index == other._index;
        }

        bool operator!=(const Iterator& other) const {
            return _index != other._index;
        }

        T& operator*() {
            return (*_vec)[_index];
        }

        T* operator->() {
            return &(*_vec)[_index];
        }

    private:
        TVector<T>* _vec;
        size_t _index;
    };

    Iterator begin() {
        return Iterator(this, _start_index);
    }

    Iterator end() {
        return Iterator(this, _start_index + _data.size());
    }
};

template <typename T>
TVector<T>::TVector() : _start_index(0) {}

template <typename T>
TVector<T>::TVector(const TVector& vec) :
    _data(vec._data), _start_index(vec._start_index) {}

template <typename T>
TVector<T>::TVector(size_t n, size_t start_index) :
    _data(n - start_index), _start_index(start_index) {}

template <typename T>
TVector<T>::~TVector() {}

template <typename T>
void TVector<T>::print() const noexcept {
    for (size_t i = _start_index; i < _data.size(); ++i) {
        std::cout << _data[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
inline bool TVector<T>::empty() const noexcept {
    return _data.empty();
}

template <typename T>
inline bool TVector<T>::full() const noexcept {
    return _data.full();
}

template <typename T>
size_t TVector<T>::size() const noexcept {
    return _data.size();
}

template <typename T>
size_t TVector<T>::start_index() const noexcept {
    return _start_index;
}

template <typename T>
const T* TVector<T>::data() const {
    return _data.data();
}

template <typename T>
void TVector<T>::swap(TVector& vec) {
    _data.swap(vec._data);
    std::swap(_start_index, vec._start_index);
}

template <typename T>
TVector<T>& TVector<T>::assign(const TVector& vec) {
    _data.assign(vec._data);
    _start_index = vec._start_index;
    return *this;
}

template <typename T>
void TVector<T>::clear() {
    _data.clear();
    _start_index = 0;
}

template <typename T>
void TVector<T>::resize(size_t n, T value) {
    if (n > _data.capacity()) {
        throw std::out_of_range("out of range. capacity < size");
    }
    _data.resize(n, value);
}

template <typename T>
void TVector<T>::push_back(T value) {
    if ((_data.size() + 1) > _data.capacity()) {
        throw std::out_of_range("out of range. capacity < size");
    }
    _data.push_back(value);
}

template <typename T>
void TVector<T>::pop_back() {
    if (_data.empty()) {
        throw std::out_of_range("pop_back() called on empty vector");
    }
    _data.pop_back();
}

template <typename T>
void TVector<T>::push_front(T value) {
    if ((_data.size() + 1) > _data.capacity()) {
        throw std::out_of_range("out of range. capacity < size");
    }
    _data.push_front(value);
}

template <typename T>
void TVector<T>::pop_front() {
    if (_data.empty()) {
        throw std::out_of_range("pop_front() called on empty vector");
    }
    _data.pop_front();
}

template <typename T>
TVector<T>& TVector<T>::insert(const T* arr, size_t n, size_t pos) {
    if (pos > _data.size()) {
        throw std::out_of_range("out of range. pos > size");
    }
    if ((_data.size() + n) > _data.capacity()) {
        throw std::out_of_range("out of range. capacity < size");
    }
    _data.insert(arr, n, pos);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::insert(T value, size_t pos) {
    if (pos > _data.size()) {
        throw std::out_of_range("out of range. pos > size");
    }
    if ((_data.size() + 1) > _data.capacity()) {
        throw std::out_of_range("out of range. capacity < size");
    }
    _data.insert(value, pos);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::replace(size_t pos, T new_value) {
    if (pos >= _data.size()) {
        throw std::out_of_range("out of range. pos >= size");
    }
    _data.replace(pos, new_value);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::erase(size_t pos, size_t n) {
    if (pos >= _data.size()) {
        throw std::out_of_range("out of range. pos >= size");
    }
    if ((pos + n) > _data.size()) {
        throw std::out_of_range("out of range. pos + n > size");
    }
    _data.erase(pos, n);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::remove_all(T value) {
    _data.remove_all(value);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::remove_first(T value) {
    _data.remove_first(value);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::remove_last(T value) {
    _data.remove_last(value);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::remove_by_index(size_t pos) {
    if (pos >= _data.size()) {
        throw std::out_of_range("out of range. pos >= size");
    }
    _data.remove_by_index(pos);
    return *this;
}

template <typename T>
size_t* TVector<T>::find_all(T value) const noexcept {
    return _data.find_all(value);
}

template <typename T>
size_t TVector<T>::find_first(T value) const {
    return _data.find_first(value);
}

template <typename T>
size_t TVector<T>::find_last(T value) const {
    return _data.find_last(value);
}

template <typename T>
T& TVector<T>::operator[](size_t index) {
    if (index >= _data.size()) {
        throw std::out_of_range("out of range. index >= size");
    }
    return _data[index - _start_index];
}

template <typename T>
const T& TVector<T>::operator[](size_t index) const {
    if (index >= _data.size()) {
        throw std::out_of_range("out of range. index >= size");
    }
    return _data[index - _start_index];
}

template <typename T>
TVector<T>& TVector<T>::operator=(const TVector& vec) noexcept {
    if (this != &vec) {
        _data = vec._data;
        _start_index = vec._start_index;
    }
    return *this;
}

template <typename T>
TVector<T> TVector<T>::operator+(const TVector<T>& vec) const {
    if (this->size() != vec.size()) {
        throw std::logic_error("Vectors must have the same size for addition.");
    }
    TVector<T> result(this->size(), this->_start_index);
    for (size_t i = 0; i < this->size(); ++i) {
        result.push_back((*this)[i] + vec[i]);
    }
    return result;
}

template <typename T>
TVector<T> TVector<T>::operator-(const TVector<T>& vec) const {
    if (this->size() != vec.size()) {
        throw std::logic_error("Vectors must have the same size for subtraction.");
    }
    TVector<T> result(this->size(), this->_start_index);
    for (size_t i = 0; i < this->size(); ++i) {
        result.push_back((*this)[i] - vec[i]);
    }
    return result;
}

template<typename T>
TVector<T>& TVector<T>::operator+=(const TVector& vec) {
   size_t pos = 0;
    size_t pos2 = 0;
    for (size_t i = 0; i < size(); i++) {
        if (_start_index + i < vec._start_index) {
            pos++;
            pos2++;
            continue;
        }
        if (_start_index <= vec._start_index + i) {
            replace(pos - 1, _data[pos++] + vec._data[i - pos2]);
        }
    }
    return *this;
}

template<typename T>
TVector<T>& TVector<T>::operator-=(const TVector& vec) {
    if (this->size() != vec.size()) {
        throw std::logic_error("Vectors must have the same size for subtraction.");
    }
    for (size_t i = 0; i < this->size(); ++i) {
        (*this)[i] -= vec[i];
    }
    return *this;
}

template<typename T>
TVector<T>& TVector<T>::operator*=(const T& scalar) {
        for (size_t i = 0; i < this->size(); ++i) {
            (*this)[i] *= scalar;
        }
        return *this;
}
template<typename T>
TVector<T>& TVector<T>::operator*=(const TVector<T>& other) {
    if (this->size() != other.size()) {
        throw std::logic_error("Vectors must have the same size for addition.");
    }
    TVector<T> result(this->size() * 2, this->_start_index);
    for (size_t i = 0; i < this->size(); ++i) {
        result.push_back((*this)[i]);
    }
    for (size_t i = 0; i < other.size(); ++i) {
        result.push_back(other[i]);
    }
    *this = result;
    return *this;
}



template<typename T>
bool TVector<T>::operator==(const TVector& vec) const {
    if ((_start_index != vec._start_index) || (size() != vec.size())) {
        return false;
    }
    for (size_t i = 0; i < size(); i++) {
        if (_data[i] != vec._data[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool TVector<T>::operator!=(const TVector& vec) const {
    if ((_start_index != vec._start_index) || (size() != vec.size())) {
        return true;
    }
    for (size_t i = 0; i < size(); i++) {
        if (_data[i] != vec._data[i]) {
            return true;
        }
    }
    return false;
}

template<typename T>
TVector<T> operator*<T>(const TVector<T>& vec, T scalar) {
    TVector<T> result(vec._data.capacity(), vec._start_index);
    for (size_t i = 0; i < vec.size(); i++) {
        result.push_back(vec[i] * scalar);
    }
    return result;
}

template<typename T>
TVector<T> operator*<T>(T scalar, const TVector<T>& vec) {
    return vec * scalar;
}
