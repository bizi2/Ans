
#ifndef LIB_MAX_HEAP_H_
#define LIB_MAX_HEAP_H_

#include <iostream>
#include <stdexcept>
template <class TVal>
class MaxHeap {
    TVal* _data;
    size_t _capacity, _size;
 public:
    MaxHeap(size_t size = 0);
    MaxHeap(size_t size, const TVal* arr);
/* … */
    inline size_t left(size_t size) const;
    inline size_t right(size_t) const;
    inline size_t parent(size_t) const;
    inline bool is_empty() const noexcept;
    void insert(TVal) noexcept;
    // void erase(size_t);
    void emplace(size_t, TVal);
    inline TVal max() const;
    TVal remove_max();
 private:
    void max_heapify() noexcept;
    void sift_down(size_t) noexcept;
    void sift_up(size_t) noexcept;
};

template<typename TVal>
MaxHeap<TVal>::MaxHeap(size_t size = 0){
    _capacity = size; 
    _data = new TVal[_capacity]; 

}
template<typename TVal>
MaxHeap<TVal>::MaxHeap(size_t size, const TVal* arr){
    _capacity = size;
    _data = new TVal[_capacity]
    for(size_t i = 0; i < _size; i++){
        _data[i] = arr[i]
    }

}
template<typename TVal>
inline MaxHeap<TVal>:: size_t left(size_t size){
    
}
#endif // LIB_MAX_HEAP_H_