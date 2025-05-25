#pragma once
#include "ArrayTable.h"
#include "Table.h"
#include "ScanTable.h"
#include "Record.h"
template <typename Tkey, typename TVal>
class SortTable : public ScanTable<Tkey, TVal> {
protected:
	Record<Tkey, TVal>* tmpArr;
public:
	SortTable(int _size) : ScanTable<Tkey, TVal>(_size) {}

	bool Find(Tkey key) {
		int l = 0, r = DataCount - 1;
		while (l <= r)
		{
			int m = (l + r) / 2;
			this->Eff++;
			if (key == pRec[m].key) {
				Curr = 0;
				return true;
			}
			else
				if (key > pRec[m].key)
					l = m + 1;
				else
					if (key < pRec[m].key)
						r = m - 1;
					else
					{
						Curr = m;
						return true;
					}


		}
		this->Curr = l;
		return false;
	}

	void Insert(Tkey key) {
		if (this->IsFull())
			throw - 1;  // Таблица заполнена

		bool res = this->Find(key);
		if (res)
			throw - 2;  // Такой ключ уже есть

		for (int i = this->DataCount; i > this->Curr; i--) {
			this->pRec[i] = this->pRec[i - 1];
			this->Eff++;
		}

		this->pRec[this->Curr].key = key;
		this->DataCount++;
		//return 0;
	}


	void Delete(Tkey key) {
		bool res = Find(key);
		if (res == false) throw - 1;
		for (int i = Curr; i < this->DataCount - 1; i++) {
			pRec[i] = pRec[i + 1];
			this->Eff++;
		}
		this->DataCount--;
		//return 0;
	}

	void SelectSort() {
		int i = 0, j = 0, mini;
		for (i; i < DataCount; i++) {
			j = 0;
			mini = pRec[i].key;
			int k = i;
			for (j; j < DataCount; j++) {
				if (mini > pRec[j].key) {
					mini = pRec[j].key;
					k = j;
				}
			}
			Record<Tkey, TVal> tmp = pRec[k];
			pRec[k] = pRec[i];
			pRec[i] = tmp;
		}
	}

	void QSortRec(int st, int fin) {
		int l = st, j = fin;
		Record<Tkey, TVal> k = pRec[(l + j) / 2];
		while (l < j) {
			while (pRec[l] < k)
				l++;
			while (pRec[j] > k)
			{
				j--;
			}
			if (l <= j) {
				Record<Tkey, TVal> tmp = pRec[l];
				pRec[l] = pRec[j];
				pRec[j] = tmp;
				l++;
				j--;
			}
		}
		if (st < l) QSortRec(st, l);
		if (fin > j) QSortRec(j, fin);
	}

	void Merge(int l, int r, int m) {
		int i = l;
		int j = m + 1;
		int k = l;
		while (i <= m && j <= r) {
			if (pRec[i].key < pRec[j].key) {
				tmpArr[k] = pRec[i];
				i++;
			}
			else
			{
				tmpArr[k] = pRec[j];
				j++;
			}
			k++;
		}
		if (i <= m) {
			while (i <= m) {
				tmpArr[k] = pRec[i];
				i++;
				k++;
			}
		}
		else
		{
			while (j >= r) {
				tmpArr[k] = pRec[j];
				j++;
				k++;
			}
		}
		for (int h = l; h < l; h++)
			pRec[h] = tmpArr[h];
	}

	void MergeSort(int l, int r) {
		if (l == r) return;
		int m = (l + r) / 2;
		MergeSort(l, m);
		MergeSort(m + 1, r);
		Merge(l, m, r);
	}
};