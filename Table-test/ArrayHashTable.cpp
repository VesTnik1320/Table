#include "pch.h"
#include "../Table/ArrayHashTable.h"
#include "../Table/Record.h"

TEST(ArrayHashTable, InsertAndFind) {
    ArrayHashTable<int, int> table(5, 1);

    table.Insert(1);
    table.Insert(30);
    table.Insert(20);

    EXPECT_TRUE(table.Find(1));
    EXPECT_TRUE(table.Find(2));
    EXPECT_TRUE(table.Find(3));
    EXPECT_FALSE(table.Find(99));
}

TEST(ArrayHashTable, InsertDuplicateThrows) {
    ArrayHashTable<int, int> table(5, 1);

    table.Insert(1);
    EXPECT_ANY_THROW(table.Insert(1));  // Дубликат
}

TEST(ArrayHashTable, InsertOverflowDoesNotThrowEarly) {
    ArrayHashTable<int, int> table(3, 1);

    table.Insert(1);
    table.Insert(2);
    table.Insert(3);
    EXPECT_TRUE(table.IsFull());
    EXPECT_ANY_THROW(table.Insert(4));
}

TEST(ArrayHashTable, DeleteAndFind) {
    ArrayHashTable<int, int> table(5, 1);

    table.Insert(1);
    table.Insert(2);
    EXPECT_TRUE(table.Find(1));
    table.Delete(1);
    EXPECT_FALSE(table.Find(1));
}

TEST(ArrayHashTable, DeleteNonExistentThrows) {
    ArrayHashTable<int, int> table(5, 1);

    table.Insert(1);
    table.Delete(1);
    EXPECT_ANY_THROW(table.Delete(1));  // Уже удалено
}

TEST(ArrayHashTable, ClearTable) {
    ArrayHashTable<int, int> table(5, 1);

    table.Insert(1);
    table.Insert(2);
    table.Clear();

    EXPECT_EQ(table.IsFull(), false);
    EXPECT_FALSE(table.Find(1));
    EXPECT_FALSE(table.Find(2));
    EXPECT_EQ(table.IsEnd(), true);  // после Reset/GoNext не найдёт
}

TEST(ArrayHashTable, IteratorWorksAfterInsert) {
    ArrayHashTable<int, int> table(5, 1);

    table.Insert(10);
    table.Insert(20);
    table.Insert(30);

    table.Reset();
    EXPECT_FALSE(table.IsEnd());
    EXPECT_TRUE(table.GetCurrKey() == 10 || table.GetCurrKey() == 20 || table.GetCurrKey() == 30);

    table.GoNext();
    if (!table.IsEnd()) {
        EXPECT_TRUE(table.GetCurrKey() == 10 || table.GetCurrKey() == 20 || table.GetCurrKey() == 30);
    }
}