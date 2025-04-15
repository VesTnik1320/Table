#pragma once
#include "ArrayTable.h"
#include "Table.h"
#include "ScanTable.h"
#include "SortTable.h"
#include "Record.h"

template< typename TKey, typename TVal>
struct TreeNode {
	TRecord <TKey, TVal> rec;
	TreeNode* pLeft, * pRight;
	int bol;
};

template <typename Tkey, typename TVal>
class TreeTable : public Table {
protected:
	TreeNode<TKey, TVal> *pRoof, *pCurr, *pPrev;
	Stack<TreeNode*> st;
public:
	//конструктор - ставим все на nullptr
	//деструктор - когда-нибудь попозже( будет обход всей структуры)
	bool Find(TKey key) {
		pCurr = pRoof;
		pPrev = nullptr;
		while (pCurr != nullptr) {
			eff++;
			if (pCurr->rec.key == key)
				return true;
			if (pCurr->rec.key > key) {
				pPrev = pCurr;
				pCurr = pCurr->pLeft;
			}
			else
			{
				pPrev = pCurr;
				pCurr = pCurr->pRight;
			}
		}
		pCurr = pPrev;
		return false;
	}

	bool Insert(Record rec) {
		bool res = Find(rec.key);
		if (res)
			throw "Error! This kei exists"
		DataCount++;
		eff++;
		TreeNode<TKey, TVal>* newN = new TreeNode<Tkey, TVal>;
		newN->rec = rec;
		pLeft = nullptr;
		pRight = nullptr;
		if (pRoof == nullptr)
			pRoof = newN;
		else
			if (pCurr->rec.key > rec.key)
				pCurr->pLeft = newN;
			else
				pCurr->pRight = newN;
		return true;
	}

	

};