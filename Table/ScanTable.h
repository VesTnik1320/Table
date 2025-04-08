#pragma once
#include "ArrayTable.h"
#include "Table.h"

template <typename Tkey, typename TVal>
class SccanTable : public ArrayTable {

	SccanTable(int _size) : ArrayTable(_size) {}

	bool Find(Tkey key) {
		for (int i = 0; i < DataCount; i++) {
			eff++;
			if (key == pRec[i].key) {
				Curr = i;
				return true;
			}
		}
			Curr = DataCount;
			return false;
	}

	void Insert(Record record) {
		if (Find(record.key))
			throw - 2;
		//проверка на полноту
		pRec[Curr] = record;
		DataCount++;
		eff++;
	}

	void Delete(Tkey key) {
		if (!Find(key)) throw - 3;
		pRec[Curr] = pRec[DataCount - 1];
		DataCount--;
		eff++;
	}
};