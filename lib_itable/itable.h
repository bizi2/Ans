#ifndef LIB_ITABLE_H_
#define LIB_ITABLE_H_

#include <iostream>
#include <stdexcept>
#include "../lib_list/list.h"
#include "../lib_pair/pair.h"

template <typename TKey, typename TVal>
class ITable {
public:
    virtual ~ITable() = default;
    virtual void Insert(const TKey& key) = 0;
    virtual void Insert(const TKey& key, const TVal& val) = 0;
    virtual void Remove(const TKey& key) = 0;
    virtual TVal* Find(const TKey& key) = 0;
    virtual size_t Size() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual TList<TPair<TKey, TVal>>& Items() = 0;  // Основная строка с ошибкой
};

#endif  // LIB_ITABLE_H_