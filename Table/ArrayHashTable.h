#pragma once
#include "ArrayTable.h"
#include "Table.h"
#include "ScanTable.h"
#include "SortTable.h"
#include "HashTable.h"

enum Status {Free, Deleted, Used};

template <typename Tkey, typename TVal>
class ArrayHashTable: public HashTable<TKey, TVal>
{
protected:
	Record<Tkey, TVal>* pRec;
	int step, curr;
	Status status;
public:
	ArrayHashTable<Tkey, TVal>::ArrayHashTable(int _size, int _step) {
		if (_size <= 0 || _step < 1)
			throw "Error size or step!"
		size = _size;
		step = _step;
		pRec = new Record[size];
		for (int i = 0; i < size; i++)
			pRec[i] = Free;
	}
	//деструктор
	bool Find(Tkey key) {
		curr = HashFunc(key);
		int tmp = -3;
		for (int i = 0; i < size; i++) {
			eff++;
			if (pRec[curr] == Free)
				break;
			else
				if (pRec[curr] == Deleted && tmp == -3)
					tmp = curr;
				else
				{
					if (pRec[curr].key == key)
						return true;
				}
			curr = (curr + step) % size;
		}
		if (tmp != -3)
			curr = tmp;
		return false;
	}

	bool Insert(TRecord rec) {
		if (Find(rec.key))
			throw "Error this rec exists!"
		pRec[curr] = rec;
		pRec[curr] = Used;
		DataCount++;
		eff++;
		return true;
	}

	void Del(Tkey key) {
		if (!Find(rec.key))
			throw "Error this rec was deleted!"
		pRec[curr] = Deleted;
		DataCount--;
		eff++;
		return ;
	}

	void Reset() {
		curr = 0;
		while ((pRec[curr] == Free || pRec[curr] == Deleted) && curr < size))
		{
			curr++;
		}
	}

	void GoNext() {
		curr++;
		while ((pRec[curr] == Free || pRec[curr] == Deleted) && curr < size))
		{
			curr++;
		}
	}

	bool IsEnd() {
		return curr == size;
	}
};


