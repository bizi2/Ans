/* // Copyright 2024 Anvar
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define FRIEND_TEST_CASES

#include "../gtest/gtest.h"
#include "../lib_itable/unsorted_table_list.h"
#include "../lib_itable/itable.h"

TEST(TUnsortedTableTest, InsertAndUpdateValue) {
    TUnsortedTable<int, int> table;
    
    // 1. Проверка пустой таблицы
    int* found = table.Find(1);
    ASSERT_EQ(found, nullptr);
    
    // 2. Вставка нового элемента
    table.Insert(1, 100);
    
    // Проверка вставки
    found = table.Find(1);
    ASSERT_NE(found, nullptr);    // Проверяем, что указатель не nullptr
    ASSERT_EQ(*found, 100);       // Проверяем значение через разыменование
    
    // 3. Обновление значения
    table.Insert(1, 200);
    
    // Проверка обновления
    found = table.Find(1);
    ASSERT_NE(found, nullptr);
    ASSERT_EQ(*found, 200);       // Проверяем новое значение
    
    // 4. Проверка размера
    ASSERT_EQ(table.Size(), 1);
    
    // 5. Проверка удаления
    table.Remove(1);
    ASSERT_EQ(table.Find(1), nullptr);
    ASSERT_EQ(table.Size(), 0);
} */