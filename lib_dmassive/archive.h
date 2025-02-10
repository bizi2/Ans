// Copyright 2024 Anvar
#pragma once
#include <iostream>
#include <utility>
#include <algorithm>
#define STEP_CAPACITY 15
#define MAX_CAPACITY 100000

enum State { empty, busy, deleted };

namespace algorithm {
template<typename T>
inline void swap(T& val_1, T& val_2) noexcept {
    T tmp = val_1;
    val_1 = val_2;
    val_2 = tmp;
}
}

template <typename T>
class TDMassive {
    T* _data;
    State* _states;
    size_t _capacity;
    size_t _size;
    size_t _deleted;

 public:
 
    TDMassive();
    TDMassive(const TDMassive& archive);
    TDMassive(const T* arr, size_t n);
    TDMassive(size_t n, T value);
    TDMassive(const TDMassive& archive, size_t pos, size_t n);
    explicit TDMassive(size_t n);

    ~TDMassive();

    void print() const noexcept;

    inline bool empty() const noexcept;
    inline bool full() const noexcept;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    State get_state(size_t index) const;

    void set_size(size_t size) noexcept;
    const T* data() const;

    void swap(TDMassive& archive);

    TDMassive& assign(const TDMassive& archive);

    void clear();
    void resize(size_t n, T value = NULL);
    void reserve(size_t n = 15);

    void push_back(T value);  // добавление элемента (в конец)
    void pop_back();  // удаление элемента (из конца)
    void push_front(T value);  // добавление элемента (в начало)
    void pop_front();  // удаление элемента (из начала)
    TDMassive& insert(const T* arr, size_t n, size_t pos);
    TDMassive& insert(T value, size_t pos);

    TDMassive& replace(size_t pos, T new_value);

    TDMassive& erase(size_t pos, size_t n);
    TDMassive& remove_all(T value);
    TDMassive& remove_first(T value);
    TDMassive& remove_last(T value);
    TDMassive& remove_by_index(size_t pos);

    size_t* find_all(T value) const noexcept;
    size_t find_first(T value) const;
    size_t find_last(T value) const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    TDMassive& operator=(const TDMassive& other);
    State getState(size_t index) const;
    size_t getDeletedCount() const;
 private:
    size_t count_value(T value)  const noexcept;
    void repacking();
};


template <typename T>
TDMassive<T>::TDMassive() {
    _size = 0;
    _capacity = STEP_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < STEP_CAPACITY; i++) {
        _states[i] = State::empty;
    }
}
template<typename T>
TDMassive <T>::TDMassive(const TDMassive& archive) :
_size(archive._size) , _capacity(archive._capacity), _deleted(archive._deleted) {
    _data = new T[_capacity];
    _states = new State[_capacity];
    if(archive._states[0] == State::deleted){
        for (size_t i = 0; i < _size - 1; i++) {
            _data[i] = archive._data[i + 1];
            _states[i] = archive._states[i + 1];
        }
        _size--;
    } else {
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = archive._data[i];
            _states[i] = archive._states[i];
        }
    }
    for (size_t i = _size; i < _capacity; ++i) {
        _states[i] = State::empty;
    }

}
template<typename T>
TDMassive<T>::TDMassive(const T* arr, size_t n): 
_size(n) , _capacity((n > STEP_CAPACITY) ? n : STEP_CAPACITY), _deleted(0) {
    _data = new T[_capacity];
    _states = new State[_capacity];
    
    for (size_t i = 0; i < _size; i++) {
        _data[i] = arr[i];
        _states[i] = State::busy;
    }
    for (size_t i = _size; i < _capacity; i++) {
        _states[i] = State::empty;
    }


}
template<typename T>
TDMassive<T>::TDMassive(size_t n, T value) :
    _size(n), _capacity((n > STEP_CAPACITY) ? n : STEP_CAPACITY), _deleted(0) {
    if (n == 0) {
        _data = nullptr;
        _states = nullptr;
    }
    else {
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (size_t i = 0; i < _size; i++) {
            _data[i] = value;
            _states[i] = State::busy;
        }
        for (size_t i = _size; i < _capacity; i++) {
            _states[i] = State::empty;
        }
    }
}
template<typename T>
TDMassive<T>::TDMassive(const TDMassive& archive, size_t pos, size_t n): 
    _size(n), _capacity((n > STEP_CAPACITY) ? n : STEP_CAPACITY) {
    if (pos + n > archive._size) {
        throw std::out_of_range("invalid");
    }
    _data = new T[_capacity];
    _states = new State[_capacity];

    for (size_t i = 0; i < _capacity; i++) {
        _data[i] = archive._data[pos + i];
        _states[i] = archive._states[pos + i];
    }
    for (size_t i = n; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}
template<typename T>
TDMassive<T>::TDMassive(size_t n) : _size(0), _capacity(n), _deleted(0) {
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
    if (_states[0] == State::deleted) {
        ++_deleted;
        --_size;
    }
}

template <typename T>
TDMassive<T>::~TDMassive() {
    delete[] _data;
    delete[] _states;
    _data = nullptr;
}

template <typename T>
inline bool TDMassive<T>::empty() const noexcept {
    return _size == 0;
}

template <typename T>
inline bool TDMassive<T>::full() const noexcept {
    return _size == _capacity;
}
template<typename T>
size_t TDMassive<T>::size() const noexcept {
    return _size;
}

template<typename T>
size_t TDMassive<T>::capacity() const noexcept {
    return _capacity;

}
template<typename T>
const T* TDMassive<T>::data() const {

/*     if (_states[0] == State::busy) {
        for (size_t i = _size; i > 0; i--) {
            _data[i] = _data[i - 1];
            _states[i] = _states[i - 1];
        }
        return _data;
    } */
    /* if(_states[0] == State::busy){
        for (size_t i = _size; i > 0; --i) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
        }
    } */
    return _data;
}
template<typename T>
void TDMassive<T>::swap(TDMassive& archive) {
    std::swap(_data, archive._data);
    std::swap(_states, archive._states);
    std::swap(_capacity, archive._capacity);
    std::swap(_size, archive._size);
    std::swap(_deleted, archive._deleted);
}
template<typename T> 
TDMassive<T>& TDMassive<T>:: assign(const TDMassive& archive) {
  if (this != &archive) {
    delete[] _data;
    delete[] _states;

    _capacity = archive._capacity;
    _size = archive._size;
    _deleted = archive._deleted;

    _data = new T[_capacity];
    _states = new State[_capacity];

    for (size_t i = 0; i < _capacity; i++) {
      _data[i] = archive._data[i];
      _states[i] = archive._states[i];
    }
  }

  return *this;
}
template<typename T>
void TDMassive<T>::clear() {
    _size = 0;
    _deleted = 0;
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}
template<typename T>
void TDMassive<T>::resize(size_t n, T value) {
    if (n > _capacity) {
        T* new_data = new T[n];
        State* new_states = new State[n];
        for (size_t i = 0; i < _size; i++) {
            new_data[i] = _data[i];
            new_states[i] = _states[i];
        }

        for (size_t i = _size; i < n; i++) {
            new_data[i] = value;
            new_states[i] = State::busy;


        }

        if (_data) {
            delete[] _data;
            _data = nullptr;
        }
        if (_states) {
            delete[] _states;
            _states = nullptr;
        }
        _data = new_data;
        _states = new_states;
        _capacity = n;
    }else {
        for (size_t i = _size; i < n; i++) {
            _data[i] = value;
            _states[i] = State::busy;
        }
    }
    _size = n;
}
template<typename T>
void TDMassive<T>::reserve(size_t n) {
    if (n > _capacity) {
        T* new_data = new T[n];// написать формулу со step capacity
        State* new_states = new State[n];
        for (size_t i = 0; i < _size; i++) {
            new_data[i] = _data[i];
            new_states[i] = _states[i];

        }
        delete[] _data;
        delete[] _states;
        _data = new_data;
        _states = new_states;
        _capacity = n;
    }
}
template<typename T>
void TDMassive<T>::push_back(T value){
    if (_size == -1) {
        throw std::out_of_range("masive is full");
    }
    if (this->full()) {
        reserve(_capacity + 1);
    }

    _data[_size] = value;
    _states[_size] = State::busy;
    _size++;

}
template<typename T>
void TDMassive<T>::pop_back() {
    if (_size <= 0) {
        throw std::logic_error("Error in function" \
        "TDMassive<T>& insert(const T* arr, size_t n, size_t pos)\":"
        " wrong position value.");
    }
    else{
        _states[_size - 1] = State::empty;
        _size--;
    }
}
template<typename T>
void TDMassive<T>::pop_front() {
    if (_size - _deleted <= 0) {
        throw std::logic_error("Error in function" \
            "TDMassive<T>& insert(const T* arr, size_t n, size_t pos)\":"
            " wrong position value.");
    }
    if (_size == -1) {
        throw std::out_of_range("masive is full");
    }
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] != State::deleted) {
            _states[i] = State::deleted;
            break;
        }
    }
    _deleted++;
    _size--;
}
template<typename T>
void TDMassive<T>::push_front(T value) {
    if (this->full()) {
        reserve(_capacity + STEP_CAPACITY);
    }
    if (_size == -1) {
        throw std::out_of_range("masive is full");
    }
    for (size_t i = _size; i > 0; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[0] = value;
    _states[0] = State::busy;
    _size++;
}

template<typename T>
TDMassive<T>& TDMassive<T>::insert(const T* arr, size_t n, size_t pos) {
    if (_size < pos) {
        throw std::logic_error("Error in function \
\"TDMassive<T>& insert(T value, size_t pos)\": wrong position value.");
    }
    if (_size + n > _capacity) {
        reserve(_capacity + n);
    }
    for (size_t i = _size; i > pos; --i) {
        _data[i + n - 1] = _data[i - 1];
        _states[i + n - 1] = _states[i - 1];
    }
    for (size_t i = 0; i < n; ++i) {
        _data[pos + i] = arr[i];
        _states[pos + i] = State::busy;
    }
    _size += n;
    return *this;
}
template <typename T>
TDMassive<T>& TDMassive<T>::insert(T value, size_t pos) {
    if (_size < pos) {
        throw std::logic_error("Error in function \
\"TDMassive<T>& insert(T value, size_t pos)\": wrong position value.");
    }
    if (this->full()) {
        size_t newCapacity = _capacity + STEP_CAPACITY;
        if (newCapacity < _capacity) {
            throw std::overflow_error("Maximum capacity reached.");
        }
        this->reserve(newCapacity);
    }
    for (size_t i = _size; i > pos; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[pos] = value;
    _states[pos] = State::busy;
    _size++;

    return *this;
}
template<typename T>
TDMassive<T>& TDMassive<T>::replace(size_t pos, T new_value) {
    if (_size <= pos) {
        throw std::logic_error("Error in function \
\"TDMassive<T>& insert(T value, size_t pos)\": wrong position value.");
    }
    if (this->full()) {
        size_t newCapacity = _capacity + STEP_CAPACITY;
        if (newCapacity < _capacity) {
            throw std::overflow_error("Maximum capacity reached.");
        }
        this->reserve(newCapacity);
    }
    _data[pos] = new_value;
    _states[pos] = State::busy;
    return *this;

}
template<typename T>
TDMassive<T>& TDMassive<T>::erase(size_t pos, size_t n) {
    if (pos >= _size || pos + n > _size) {
        throw std::out_of_range("Error in function \"TDMassive<T>& erase(size_t pos, size_t n)\": position or range out of bounds.");
    }
    for (size_t i = pos; i < pos + n; ++i) {
        _states[i] = State::deleted;
    }
    for (size_t i = pos + n; i < _size; ++i) {
        _data[i - n] = _data[i];
        _states[i - n] = _states[i];
    }
    _size -= n;
    return *this;
}
template<typename T>
TDMassive<T>& TDMassive<T>::remove_all(T value) {
    size_t shift = 0;

    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] == value) {
            _states[i] = State::deleted;
            ++shift;
        }
        else if (shift > 0) {
            _data[i - shift] = _data[i];
            _states[i - shift] = _states[i];
        }
    }

    _size -= shift;
    return *this;
}
template<typename T>
TDMassive<T>& TDMassive<T>::remove_first(T value) {
    size_t index = _size;
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value) {
            index = i;
            break;
        }
    }
    if (index < _size) {
        for (size_t i = index; i < _size - 1; i++) {
            _data[i] = _data[i + 1];
        }
        _size--;
        _states[_size] = State::deleted;
    }
    return *this;
}
template<typename T>
TDMassive<T>& TDMassive<T>::remove_last(T value) {
    for (size_t i = _size; i >= 1; --i) {
        if (_data[i - 1] == value) {
            _states[i - 1] = State::deleted;
            for (size_t j = i - 1; j < _size;++j) {
                _data[j] = _data[j + 1];
                _states[j] = _states[j + 1];
            }
            _size--;
            break;
        }
    }
    return *this;
}
template<typename T>
TDMassive<T>& TDMassive<T>::remove_by_index(size_t pos) {
    if (pos >= _size) {
        throw std::out_of_range("Index out of range");
    }
    _states[pos] = State::deleted;
    for (size_t i = pos; i < _size - 1; ++i) {
        _data[i] = _data[i + 1];
        _states[i] = _states[i + 1];
    }
    _size--;
    return *this;
}
template <typename T>
void TDMassive<T>::print() const noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] != State::deleted) {
            std::cout << _data[i] << ", ";
        }
    }
}

template <typename T>
size_t* TDMassive<T>::find_all(T value) const noexcept {
    size_t count = this->count_value(value);
    if (count == 0) {
        return nullptr;
    }
    size_t* found_positions = new size_t[count + 1];
    found_positions[0] = count;
    size_t found_count = 0;

    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] == value && _states[i] != State::deleted) {
            found_positions[++found_count] = i;
        }
    }

    return found_positions;
}
template <typename T>
size_t TDMassive<T>::find_first(T value) const{
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value && _states[i] != State::deleted) {
            return i;
        }
    }
    return -1;

 }


template <typename T>
size_t TDMassive<T>::find_last(T value) const {
    for (size_t i = _size; i > 0; i--) {
        if (_data[i] == value && _states[i] != State::deleted) {
            return i;
        }
    }
    return -1;
}
template <typename T>
State TDMassive<T>::getState(size_t index) const {
    return _states[index];
}
template <typename T>
size_t TDMassive<T>::count_value(T value) const noexcept {
    size_t count = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value && _states[i] != State::deleted) {
            count++;
        }
    }
    return count;
}
template <typename T>
size_t TDMassive<T>::getDeletedCount() const {
    size_t count = 0;
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::deleted) {
            ++count;
        }
    }
    return count;
}
template <typename T>
T& TDMassive<T>::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Индекс выходит за пределы массива");
    }
    for (size_t i = index; i < _size; i++){
        if(_states[i] == State::busy ){
            return _data[i];
        }
    }
    throw std::out_of_range("Элемент не найден");
}

template <typename T>
const T& TDMassive<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Индекс выходит за пределы массива");
    }
    for (size_t i = index; i < _size; i++){
        if(_states[i] == State::busy ){
            return _data[i];
        }
    }
    throw std::out_of_range("Элемент не найден");
}
template <typename T>
TDMassive<T>& TDMassive<T>::operator=(const TDMassive<T>& other) {
   if (this != &other) {
        delete[] _data;
        delete[] _states;
        _size = other._size;
        _capacity = other._capacity;
        _deleted = other._deleted;
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (size_t i = 0; i < _size; i++) {
            _data[i] = other._data[i];
            _states[i] = other._states[i];
        }
    }
    return *this;
}



