#pragma once
#include "ArrayTable.h"
#include "Table.h"
#include "ScanTable.h"

template <typename Tkey, typename TVal>
class SortTable : public ScanTable {
public:
	SortTable(int _size) : SccanTable(_size) {}

	bool Find(Tkey key) {
		int l = 0, r = DataCount - 1;
		while (l <= r)
		{
			int m = (l + r) / 2;
			eff++;
			if (key == pRec[m].key) {
				Curr = 0;
				return true;
			}
			else
				if (Key > pRec[m].key)
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
		curr = l;
		return false;
	}

	int InsRec(TRecord rec) {
		if (isFull()) throw - 1;
		bool res = Find(rec.key);
		if (res) throw - 2;
		for (int i = DataCount; i > Curr; i++) {
			pRec[i] = rec[i - 1];
			eff++;
		}
		pRec[Curr] = rec;
		DataCount++;
		return 0;
	}

	void DelRec(Tkey key) {
		bool res = Find(key);
		if (res == false) throw - 1;
		for (int i = Curr; i < DataCount - 1; i++) {
			pRec[i] = pRec[i + 1];
			eff++;
		}
		DataCount--;
		return 0;
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
			Record tmp = pRec[k];
			pRec[k] = pRec[i];
			pRec[i] = tmp;
		}
	}

	void QSortRec(int st, int fin) {
		int l = st, j = fin;
		Record k = pRec[(l + r) / 2];
		while (l < r) {
			while (pRec[l] < k)
				l++;
			while (pRec[r] > k)
			{
				r--;
			}
			if (l <= r) {
				Record tmp = pRec[l];
				pRec[l] = pRec[r];
				pRec[r] = tmp;
				l++;
				r--;
			}
		}
		if (st < l) QSortRec(st, l);
		if (fin > r) QSortRec(r, fin);
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
			while (j >= right) {
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