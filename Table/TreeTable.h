#pragma once
#include "ArrayTable.h"
#include "Table.h"
#include "ScanTable.h"
#include "SortTable.h"
#include "Record.h"
const int BAL_OK = 0; const int BAL_LEFT = -1; const int BAL_RIGHT = 1;
template< typename Tkey, typename TVal>
struct TreeNode {
	Record<Tkey, TVal> rec;
	TreeNode* pLeft, * pRight;
	int bol,pos,level;
};

template <typename Tkey, typename TVal>
class TreeTable : public Table<Tkey, TVal> {
protected:
	TreeNode<Tkey, TVal> *pRoof, *pCurr, *pPrev;
	Stack<TreeNode*> st;
public:
	virtual TKey GetCurrKey() { return pCurr->rec.key; }
	virtual TVal GetCurrVal() { return pCurr->rec.val; }
	virtual Record<Tkey, TVal> GetCurrRec() { return pCurr->rec; }
	//конструктор - ставим все на nullptr
	//деструктор - когда-нибудь попозже( будет обход всей структуры)
	bool Find(Tkey key) {
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
			throw "Error this key exists!";
		DataCount++;
		eff++;
		TreeNode<Tkey, TVal>* newN = new TreeNode<Tkey, TVal>;
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

	void Delete(Tkey key){
		bool res = Find(key);
		if (!res) return;
		TreeNode<Tkey, TVal>* pDel = pCurr;
		if (pCurr->pRight == nullptr) {
			if (pPrev == nullptr) pRoof = pCurr->pLeft;
			else
				pPrev->pLeft = pCurr->pLeft;
		}
		else if (pCurr->pLeft == nullptr) {
				if (pPrev == nullptr)
					pRoof = pCurr->pRight;
				else
					if (pCurr = pPrev->pRight)
						pPrev->pLeft = pCurr->pRight;
					else
						pPrev->pRight = pCurr->pRight;
			
		}
		else
		{
			TreeNode<Tkey, TVal>* pN = pCurr->pLeft;
			pPrev = pCurr;
			while (pN->pRight != nullptr) {
				pPrev = pN;
				eff++;
				pN = pN->pRight;
			}
			pCurr->rec = pN->rec;
			if (pCurr->pLeft == pN)
				pCurr->pLeft = pN->pLeft;
			else
				pPrev->pRight = pN->pLeft;
			pDel = pN;
		}
		delete pDel;
		DataCount--;
		eff++;
		}

	void Reset() {
		pCurr = pRoof;
		stack.clear();
		while (pCurr->pLeft != nullptr)
		{
			stack.push(pCurr);
			pCurr = pCurr->pLeft;
		}
		stack.push(pCurr);
		pos = 0;
	}

	void GoNext() {
		pCurr = pCurr->pRight;
		stack.pop();
		if ((pCurr == nullptr) && (!stack.Empty()))
			pCurr = stack.pop();
		else {
			while (pCurr->pLeft != nullptr)
			{
				stack.push(pCurr);
				pCurr = pCurr->pLeft;
			}
			stack.push(pCurr);
		}
		pos++;
	}

	bool IsEnd() {
		return (pos == DataCount);
	}

};