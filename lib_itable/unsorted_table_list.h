#ifndef LIB_UNITABLE_H_
#define LIB_UNITABLE_H_

#include <iostream>
#include <stdexcept>
#include <functional>
#include "../lib_list/list.h"
#include "../lib_pair/pair.h"
#include "../lib_itable/itable.h"
#include "../lib_vector/vector.h"

template <typename TKey, typename TVal>
class TUnsortedTable : public ITable<TKey, TVal>{
    TList<TPair<TKey, TVal>> _data;
public:
    ~TUnsortedTable() = default;
    TUnsortedTable() = default;
    TUnsortedTable& operator=(const TUnsortedTable&) = delete;


    void Insert(const TKey& key , const TVal& val) override;
    void Remove(const TKey& key) override;
    void Insert(const TKey& key) override;
    TVal* Find(const TKey& key) override;
    size_t Size() const override;
    bool IsEmpty() const override;
    TList<TPair<TKey, TVal>>& Items() override {
        return _data;
    }
};
template<typename TKey, typename TVal>
void TUnsortedTable<TKey,TVal>::Insert(const TKey& key) {
    for(auto& item : _data) {
        if(item.first == key) {
            return; // Ключ уже есть — ничего не делаем
        }
    }
    _data.push_back(TPair<TKey, TVal>(key, TVal())); // Добавляем ключ с default-значением
};

template<typename TKey, typename TVal>
void TUnsortedTable<TKey,TVal>::Insert(const TKey& key, const TVal& val) {
    for(auto& item : _data) {
        if(item.first == key) {
            item.second = val;  // Обновляем значение, если ключ уже есть
            return;
        }
    }
    _data.push_back(TPair<TKey, TVal>(key, val));
};
template<typename TKey, typename TVal>
void TUnsortedTable<TKey, TVal>::Remove(const TKey& key) {
    for (auto it = _data.begin(); it != _data.end(); ++it) {
        if (it->first == key) {
            _data.erase(it);
            return;
        }
    }
};


template<typename TKey, typename TVal>
TVal* TUnsortedTable<TKey,TVal>::Find(const TKey& key) {
    for(auto& item : _data) {
        if(item.first == key) {
            return &item.second;
        }
    }
    return nullptr;
};
template<typename TKey, typename TVal>
size_t TUnsortedTable<TKey, TVal>::Size() const {
    return _data.size();
};
template<typename TKey, typename TVal>
bool TUnsortedTable<TKey, TVal>::IsEmpty() const { return _data.empty(); };

#endif  //LIB_UNITABLE_H_