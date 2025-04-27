// Copyright 2024 Anvar
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define FRIEND_TEST_CASES

#include "../gtest/gtest.h"
#include "../lib_itable/unsorted_table_list.h"
#include "../lib_itable/itable.h"

TEST(TUnsortedTableTest, InsertAndUpdateValue) {  // Изменили имя
    TUnsortedTable<int, int> table;
    
    // Проверяем, что элемента изначально нет
    int* found = table.Find(1);
    ASSERT_EQ(found, nullptr);
    
    // Вставляем новый элемент
    table.Insert(1, 100);
    
    // Проверяем, что элемент добавлен
    found = table.Find(1);
    ASSERT_NE(found, nullptr);
    ASSERT_EQ(*found, 100);
    
    // Обновляем значение
    table.Insert(1, 200);
    
    // Проверяем обновление
    found = table.Find(1);
    ASSERT_NE(found, nullptr);
    ASSERT_EQ(*found, 200);
    EXPECT_EQ(found, 200);
}