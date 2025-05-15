#ifndef LIB_PAIR_PAIR_H_
#define LIB_PAIR_PAIR_H_

#include <iostream>
#include <string>
#include <stdexcept>

template <class T1, class T2> class TPair;

template <class T1, class T2>
class TPair {
    T1 _first;
    T2 _second;
public:
    TPair() : _first(T1()), _second(T2()) { }
    TPair(const T1& first, const T2& second) : _first(first), _second(second) { }
    TPair(const TPair& pair) : _first(pair._first), _second(pair._second) { }
    ~TPair() { }

    inline T1 first() const noexcept;
    inline T2 second() const noexcept;
    inline void set_first(const T1& value) noexcept;
    inline void set_second(const T2& value) noexcept;
    TPair<T1, T2>& operator=(const TPair<T1, T2>& pair) noexcept;

    void swap(TPair<T1, T2>& pair) noexcept;
};

template <class T1, class T2>
inline T1 TPair<T1, T2>::first() const noexcept {
    return _first;
}

template <class T1, class T2>
inline T2 TPair<T1, T2>::second() const noexcept {
    return _second;
}

template <class T1, class T2>
inline void TPair<T1, T2>::set_first(const T1& value) noexcept {
    _first = value;
}

template <class T1, class T2>
inline void TPair<T1, T2>::set_second(const T2& value) noexcept {
    _second = value;
}

template <class T1, class T2>
TPair<T1, T2>& TPair<T1, T2>::operator=(const TPair<T1, T2>& pair) noexcept {
    if (this != &pair) {
        _first = pair._first;
        _second = pair._second;
    }
    return *this;
}



template <class T1, class T2>
void TPair<T1, T2>::swap(TPair<T1, T2>& pair) noexcept {
    std::swap(_first, pair._first);
    std::swap(_second, pair._second);
}

#endif  // LIB_PAIR_PAIR_H_