/* // Copyright 2024 Anvar
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define FRIEND_TEST_CASES
#include "../gtest/gtest.h"
#include "../lib_tbsttable/tbst_table.h"
#include "../lib_itable/itable.h"
TEST(TBSTableTest, InsertAndFind) {
    TBSTable<int, std::string> table;
    
    // Проверка пустой таблицы
    EXPECT_TRUE(table.isEmpty());
    EXPECT_EQ(table.find(1), nullptr);
    EXPECT_FALSE(table.contains(1));
    EXPECT_EQ(table.size(), 0);
    
    // Вставка элементов
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    
    // Проверка наличия элементов
    EXPECT_FALSE(table.isEmpty());
    EXPECT_NE(table.find(1), nullptr);
    EXPECT_EQ(*table.find(1), "one");
    EXPECT_NE(table.find(2), nullptr);
    EXPECT_EQ(*table.find(2), "two");
    EXPECT_NE(table.find(3), nullptr);
    EXPECT_EQ(*table.find(3), "three");
    EXPECT_TRUE(table.contains(1));
    EXPECT_TRUE(table.contains(2));
    EXPECT_TRUE(table.contains(3));
    EXPECT_FALSE(table.contains(4));
}

TEST(TBSTableTest, Remove) {
    TBSTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    
    // Удаление существующего элемента
    EXPECT_TRUE(table.remove(2));
    EXPECT_FALSE(table.contains(2));
    EXPECT_EQ(table.find(2), nullptr);
    EXPECT_TRUE(table.contains(1));
    EXPECT_TRUE(table.contains(3));
    
    // Удаление несуществующего элемента
    EXPECT_FALSE(table.remove(99));
}

TEST(TBSTableTest, UpdateValue) {
    TBSTable<int, std::string> table;
    table.insert(1, "one");
    
    // Обновление значения
    table.insert(1, "updated one");
    EXPECT_NE(table.find(1), nullptr);
    EXPECT_EQ(*table.find(1), "updated one");
}

TEST(TBSTableTest, ConstFind) {
    TBSTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    
    // Проверка константного метода find
    const auto& constTable = table;
    const std::string* value = constTable.find(1);
    EXPECT_NE(value, nullptr);
    EXPECT_EQ(*value, "one");
    EXPECT_EQ(constTable.find(3), nullptr);
}

TEST(TBSTableTest, Items) {
    TBSTable<int, std::string> table;
    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(2, "two");
    
    auto items = table.items();
    EXPECT_EQ(items.size(), 3);
    
    // Проверяем наличие всех элементов
    EXPECT_TRUE(VectorContains(items, TPair<int, std::string>(1, "one")));
    EXPECT_TRUE(VectorContains(items, TPair<int, std::string>(2, "two")));
    EXPECT_TRUE(VectorContains(items, TPair<int, std::string>(3, "three")));
}

TEST(TBSTableTest, ComplexTypes) {
    TBSTable<std::string, TVector<int>> table;
    
    // Проверка работы со сложными типами
    TVector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    
    TVector<int> vec2;
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);
    
    table.insert("first", vec1);
    table.insert("second", vec2);
    
    EXPECT_NE(table.find("first"), nullptr);
    EXPECT_EQ(table.find("first")->size(), 3u);
    EXPECT_EQ((*table.find("first"))[0], 1);
    
    EXPECT_NE(table.find("second"), nullptr);
    EXPECT_EQ(table.find("second")->size(), 3u);
    EXPECT_EQ((*table.find("second"))[2], 6);
}

TEST(TBSTableTest, Size) {
    TBSTable<int, std::string> table;
    EXPECT_EQ(table.size(), 0);
    
    table.insert(1, "one");
    EXPECT_EQ(table.size(), 1);
    
    table.insert(2, "two");
    EXPECT_EQ(table.size(), 2);
    
    table.remove(1);
    EXPECT_EQ(table.size(), 1);
    
    table.remove(2);
    EXPECT_EQ(table.size(), 0);
} */