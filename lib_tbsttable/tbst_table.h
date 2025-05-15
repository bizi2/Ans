#ifndef LIB_TBST_TABLE_H_
#define LIB_TBST_TABLE_H_

#include <iostream>
#include <stdexcept>
#include "../lib_list/list.h"
#include "../lib_pair/pair.h"
#include "../lib_bin_search_tree/bin_search_tree.h"
#include "../lib_itable/itable.h"

template <typename TKey, typename TVal>
class TBSTable : public ITable<TKey, TVal> {
    TBinSearchTree<TKey, TVal> _data;
    TList<TPair<TKey, TVal>> _itemsList; // Для хранения элементов

public:
    // Обновляем список элементов при каждой модификации
    void UpdateItems() {
        _itemsList.Clear();
        _data.InOrderTraversal([this](const TKey& key, const TVal& val) {
            _itemsList.PushBack(TPair<TKey, TVal>(key, val));
        });
    }

    void Insert(const TKey& key) override {
        _data.Insert(key, TVal());
        UpdateItems();
    }

    void Insert(const TKey& key, const TVal& val) override {
        _data.Insert(key, val);
        UpdateItems();
    }

    void Remove(const TKey& key) override {
        _data.Remove(key);
        UpdateItems();
    }

    TVal* Find(const TKey& key) override {
        auto node = _data.Search(key);
        return node ? &(node->value) : nullptr;
    }

    size_t Size() const override {
        return _data.Count();
    }

    bool IsEmpty() const override {
        return _data.IsEmpty();
    }

    TList<TPair<TKey, TVal>>& Items() override {
        return _itemsList;
    }
};

#endif // LIB_TBST_TABLE_H_