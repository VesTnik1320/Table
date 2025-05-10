#pragma once
#include "ArrayTable.h"
#include "Table.h"
#include "ScanTable.h"
#include "SortTable.h"

template <typename Tkey, typename TVal>
class HashTable : public Table<TKey, TVal> {
protected:
	int size;
	virtual int HashFunc(Tkey key) {
		return (key % size);
	}
};
