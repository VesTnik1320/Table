#include "pch.h"
#include "../Table/SortTable.h"


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