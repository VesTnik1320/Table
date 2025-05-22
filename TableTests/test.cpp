#include "pch.h"
#include "../Table/ArrayHashTable.h"
#include "../Table/Record.h"
#include "../Table/ScanTable.h"
#include "../Table/SortTable.h"
#include "../Table/Table.h"

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
// --------------

TEST(ScanTable, InsertAndFind) {
    ScanTable<int, int> table(5);

    table.Insert(1);
    EXPECT_TRUE(table.Find(1));

    table.Insert(2);
    EXPECT_TRUE(table.Find(2));
}

TEST(ScanTable, InsertDuplicateThrows) {
    ScanTable<int, int> table(3);

    table.Insert(1);
    EXPECT_ANY_THROW(table.Insert(1));  // дубликат
}

TEST(ScanTable, InsertOverflowThrows) {
    ScanTable<int, int> table(2);

    table.Insert(1);
    table.Insert(2);
    EXPECT_ANY_THROW(table.Insert(3));  // превышение размера
}

TEST(ScanTable, DeleteExisting) {
    ScanTable<int, int> table(3);

    table.Insert(1);
    EXPECT_NO_THROW(table.Delete(1));
    EXPECT_FALSE(table.Find(1));
}

TEST(ScanTable, DeleteNonExistingThrows) {
    ScanTable<int, int> table(2);
    EXPECT_ANY_THROW(table.Delete(42));
}

TEST(ScanTable, ClearResetsCount) {
    ScanTable<int, int> table(3);
    table.Insert(1);
    table.Clear();
    EXPECT_FALSE(table.Find(1));
    EXPECT_TRUE(table.IsEnd());
}

TEST(ScanTable, IterationWorks) {
    ScanTable<int, int> table(3);
    table.Insert(1);
    table.Insert(2);
    table.Reset();

    int count = 0;
    while (!table.IsEnd()) {
        Record<int, int> rec = table.GetCurr();
        EXPECT_TRUE(rec.key == 1 || rec.key == 2);
        table.GoNext();
        count++;
    }
    EXPECT_EQ(count, 2);
}

TEST(ScanTable, GetCurrThrowsAtEnd) {
    ScanTable<int, int> table(1);
    table.Insert(1);
    table.Reset();
    table.GoNext(); // за предел
    EXPECT_ANY_THROW(table.GetCurr());
}

TEST(ScanTable, IsFullCheck) {
    ScanTable<int, int> table(2);
    EXPECT_FALSE(table.IsFull());
    table.Insert(1);
    table.Insert(2);
    EXPECT_TRUE(table.IsFull());
}
//--------------

TEST(SortTable, InsertAndFind) {
    SortTable<int, int> table(5);

    table.Insert(1);
    table.Insert(3);
    table.Insert(2);

    EXPECT_TRUE(table.Find(1));
    EXPECT_TRUE(table.Find(2));
    EXPECT_TRUE(table.Find(3));
    EXPECT_FALSE(table.Find(5));
}

TEST(SortTable, InsertDuplicateThrows) {
    SortTable<int, int> table(3);

    table.Insert(1);
    EXPECT_ANY_THROW(table.Insert(1));  // дубликат
}

TEST(SortTable, InsertOverflowThrows) {
    SortTable<int, int> table(2);

    table.Insert(1);
    table.Insert(2);
    EXPECT_ANY_THROW(table.Insert(3));
}

TEST(SortTable, DeleteExisting) {
    SortTable<int, int> table(3);

    table.Insert(1);
    table.Insert(2);
    EXPECT_NO_THROW(table.Delete(1));
    EXPECT_FALSE(table.Find(1));
}

TEST(SortTable, DeleteNonExistingThrows) {
    SortTable<int, int> table(2);
    table.Insert(1);
    EXPECT_ANY_THROW(table.Delete(42));
}

TEST(SortTable, SelectSortWorks) {
    SortTable<int, int> table(3);
    table.Insert(3);
    table.Insert(1);
    table.Insert(2);
    table.SelectSort();

    table.Reset();
    EXPECT_EQ(table.GetCurr().key, 1);
    table.GoNext();
    EXPECT_EQ(table.GetCurr().key, 2);
    table.GoNext();
    EXPECT_EQ(table.GetCurr().key, 3);
}

TEST(SortTable, QSortRecWorks) {
    SortTable<int, int> table(3);
    table.Insert(9);
    table.Insert(2);
    table.Insert(5);
    table.QSortRec(0, 2);

    table.Reset();
    EXPECT_EQ(table.GetCurr().key, 2);
    table.GoNext();
    EXPECT_EQ(table.GetCurr().key, 5);
    table.GoNext();
    EXPECT_EQ(table.GetCurr().key, 9);
}

TEST(SortTable, MergeSortWorks) {
    SortTable<int, int> table(4);
    table.Insert(8);
    table.Insert(3);
    table.Insert(6);
    table.Insert(1);
    table.MergeSort(0, 3);

    table.Reset();
    EXPECT_EQ(table.GetCurr().key, 1);
    table.GoNext();
    EXPECT_EQ(table.GetCurr().key, 3);
    table.GoNext();
    EXPECT_EQ(table.GetCurr().key, 6);
    table.GoNext();
    EXPECT_EQ(table.GetCurr().key, 8);
}