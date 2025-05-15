#pragma once
#include <iostream>


template <typename T>
class TPolinom {
public:
    TPolinom();
    TPolinom(const TPolinom& polinom);
    TPolinom(TPolinom&& polinom);
    TPolinom& operator=(const TPolinom& polinom);
    TPolinom& operator=(TPolinom&& polinom);
    ~TPolinom();

    void print() const noexcept;

private:
    T* _data;
    size_t _size = 0;
};



