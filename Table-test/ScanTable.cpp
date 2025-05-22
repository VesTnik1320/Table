#include "pch.h"
#include "../Table/ScanTable.h"
#include "../Table/Record.h"

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