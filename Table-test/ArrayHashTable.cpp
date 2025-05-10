#include "pch.h"
#include "../Table/ArrayHashTable.h"

TEST(ArrayHashTable, CANT_INSERT_FULL)
{
	ArrayHashTable<int, int> ht1;
	for (int i = 0; i < 10; i++)
	{
		ht1.Insert(i, i);
	}
	EXPECT_ANY_THROW(ht1.Insert(10, 10));
}

TEST(ArrayHashTable, CANT_INSERT_BEING)
{
	ArrayHashTable<int, int> ht1;
	ht1.Insert(10, 100);
	EXPECT_ANY_THROW(ht1.Insert(10, 10));
}

TEST(ArrayHashTable, CORRECT_INSERT)
{
	ArrayHashTable<int, int> ht1;
	int a[5] = { 40, 2, 1, 4, 0 };
	for (size_t i = 0; i < 5; i++)
	{
		ht1.Insert(a[i], a[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(ht1.Find(a[i]), true);
	}
}

TEST(ArrayHashTable, CORRECT_DELETE)
{
	ArrayHashTable<int, int> ht1;
	int a1[5] = { 40, 2, 1, 4, 0 };
	int a2[4] = { 40, 1, 2, 0 };
	for (size_t i = 0; i < 5; i++)
	{
		ht1.Insert(a1[i], a1[i]);
	}
	ht1.Delete(4);
	EXPECT_EQ(!ht1.Find(4), true);
}

TEST(ArrayHashTable, CANT_DELETE_NO_BEING)
{
	ArrayHashTable<int, int> ht1;
	EXPECT_ANY_THROW(ht1.Delete(10));
}

TEST(ArrayHashTable, CORRECT_ASSING)
{
	ArrayHashTable<int, int> ht1, ht2;
	for (int i = 0; i < 5; i++)
	{
		ht1.Insert(i, i);
	}
	ht2 = ht1;
	ht2.Delete(4);
	EXPECT_EQ(ht1.Find(4), true);
	EXPECT_EQ(ht2.Find(4), false);
}