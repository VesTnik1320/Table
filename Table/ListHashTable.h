#pragma once
#include "ArrayTable.h"
#include "Table.h"
#include "ScanTable.h"
#include "SortTable.h"
#include "HashTable.h"
#include "ArrayHashTable.h"
#include <iterator>

template <typename Tkey, typename TVal>
class ListHashTable : public HashTable
{
protected:
	List<TRecord<Tkey, TVal>>* pList;
	int CurrList;
	List <TRecord>::iterator CurrI;
public:
	ListHashTable<Tkey, TVal> ::ListHashTable(int _size = 100) : HashTable(_size) {
		size = _size;
		pList = new List<TRecord<Tkey, TVal>>[size];
		CurrList = -1;
	}
	//~ListHashTable
	//+IsFull, в теории можно взять из линейного списка
	bool ListHash<Tkey, TVal> ::Find(Tkey key) {
		CurrList = HashFunc(_key);
		bool res = false;
		for (CurrI = pList[CurrList].begin(); CurrI != pList[CurrList].end(); CurrI++) {
			eff++;
			if (CurrI->key == _key) { //мб CurrI->key не сработает
				res = true;
				break;
			}
		}
		return res;
	}
	bool ListHash<Tkey, TVal> ::Insert(Record rec) {
		if (Find(rec.key)))
			throw "Error, this record exists!"
		pList[CurrList].InsFirst(rec);
		DataCount++;
		eff++;
		return true;
	}

	bool ListHash<Tkey, TVal> ::Delete(Tkey key) {
		if (!Find(rec.key)))
		throw "Error, Key not find!"
			pList[CurrList].erase(CurrI);
		DataCount--;
		eff++;
		return true;
	}

	void Reset() {
		CurrList = 0;
		CurrI = pList[CurrList].begin();
		while (Curr! == pList[CurrList].end())
		{
			CurrList++;
			if (CurrList >= size)
				break;
			CurrI = pList[CurrList].begin();
		}
	}

	bool IsEnd() {
		return CurrList >= size;
	}

	void GoNext() {
		CurrI++;
		while (Curr != = pList[CurrList].end())
		{
			CurrList++;
			if (CurrList >= size)
				break;
			CurrI = pList[CurrList].begin();
		}
	}
};