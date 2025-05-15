#ifndef LIB_KUCHA_H_
#define LIB_KUCHA_H_

#include <iostream>
#include <stdexcept>

#include "../lib_vector/vector.h"
template <typename T,  bool isMinHeap = false>
class Heap {
private:
    T* _data;            // Динамический массив для хранения элементов
    size_t _capacity;     // Текущая вместимость кучи
    size_t _size;         // Количество элементов в куче

public:

     void resize(size_t new_capacity);
    void heapify_up(size_t index);
    void heapify_down(size_t index);
    size_t parent(size_t index) const;
    size_t left_child(size_t index) const;
    size_t right_child(size_t index) const;

    Heap();
    explicit Heap(size_t initial_capacity);
    Heap(const Heap& other);
    Heap(Heap&& other) noexcept;
    ~Heap();
    bool compare(const T& a, const T& b) const { // Компаратор для min/max кучи
        return isMinHeap ? (a < b) : (a > b);
    }

    void push_heap(const T& value);
    void pop_heap();
    void emplace(size_t index, const T& value);

    const T& top() const;
    inline bool is_empty() const noexcept;

    
};

template<typename T , bool isMinHeap>
size_t Heap<T , isMinHeap>::parent(size_t index) const{
    if (index == 0) {
        return 0; 
    }
    return ((index - 1) / 2);
}
template<typename T , bool isMinHeap>
size_t Heap<T , isMinHeap>::left_child(size_t index) const{
    return 2 * index + 1;
}
template<typename T , bool isMinHeap>
size_t Heap<T , isMinHeap>::right_child(size_t index) const{
    return 2 * index + 2;
}
template<typename T, bool isMinHeap>
void Heap<T, isMinHeap>::resize(size_t new_capacity) {
    if (new_capacity < _size) new_capacity = _size;
    if (new_capacity == _capacity) return;
    
    T* new_data = new T[new_capacity];
    std::move(_data, _data + _size, new_data);
    delete[] _data;
    
    _data = new_data;
    _capacity = new_capacity;
}
template<typename T , bool isMinHeap>
void Heap<T , isMinHeap>:: heapify_up(size_t index){
    while (index > 0 && compare(_data[index], _data[parent(index)])){
        std::swap(_data[index], _data[parent(index)] );
        index = parent(index);
    }
}
template<typename T , bool isMinHeap>
void Heap<T , isMinHeap>:: heapify_down(size_t index){
    size_t or_index = index;
    if(left_child(index) < _size && compare(_data[left_child(index)] , _data[or_index])){
        or_index = left_child(index);
    }
    if(right_child(index) < _size && compare(_data[right_child(index)], _data[or_index])){
        or_index = right_child(index);
    }
    if(index != or_index) {
        std::swap(_data[index] , _data[or_index]);
        heapify_down(or_index);
    }
}
template <typename T, bool isMinHeap>
Heap<T, isMinHeap>::Heap() 
    : _capacity(10),
      _size(0),
      _data(new T[_capacity])
{}
// Конструктор с параметром начальной вместимости
template <typename T , bool isMinHeap>
Heap<T , isMinHeap>::Heap(size_t initial_capacity = 10) 
    : _capacity(initial_capacity), _size(0) {
    if (_capacity < 1) {
        _capacity = 1;  // Минимальная вместимость
    }
    _data = new T[_capacity];
}

// Конструктор копирования
template <typename T , bool isMinHeap>
Heap<T , isMinHeap>::Heap(const Heap& other) 
    : _capacity(other._capacity), _size(other._size) {
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}

// Конструктор перемещения
template <typename T , bool isMinHeap>
Heap<T , isMinHeap>::Heap(Heap&& other) noexcept 
    : _data(other._data), _capacity(other._capacity), _size(other._size) {
    other._data = nullptr;
    other._capacity = 0;
    other._size = 0;
}

// Деструктор
template <typename T , bool isMinHeap>
Heap<T , isMinHeap>::~Heap() {
    delete[] _data;
}

template<typename T , bool isMinHeap>
void Heap<T , isMinHeap>:: push_heap(const T& value){
    if(_size == _capacity){
        resize(_capacity * 2);
    }
    _data[_size] = value;

    heapify_up(_size);
    _size ++;
}
template<typename T , bool isMinHeap>
void Heap<T , isMinHeap>:: pop_heap(){
    if (_size == 0) {
        throw std::out_of_range("Heap is empty"); 
    }
    // перемещаем последний элемент в корень
    _data[0] = _data[_size - 1];
    _size--;
    
    // перестраиваем кучу, если она не пуста
    if (_size > 0) {
        heapify_down(0);
    }

}
template<typename T , bool isMinHeap>
void Heap<T , isMinHeap>:: emplace(size_t index, const T& value){
    if (index >= _capacity) {
        throw std::out_of_range("Index exceeds heap capacity");
    }

    if (index < _size) {
        _data[index] = value;
        if (index > 0 && compare(_data[index], _data[parent(index)])) {
            heapify_up(index);
        } else {
            heapify_down(index);
        }
    } else if (index == _size) {
        push_heap(value);
    } else {
        throw std::logic_error(" index > size");
    }
}

template<typename T , bool isMinHeap>
const  T& Heap<T , isMinHeap>:: top() const{
    if (_size == 0) {
        throw std::out_of_range("Heap is empty");
    }
    return _data[0];
}
template<typename T , bool isMinHeap>
inline bool Heap<T , isMinHeap>::is_empty() const noexcept {
    return _size == 0;
}


#endif //  LIB_KUCHA_H_