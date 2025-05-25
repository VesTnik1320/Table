#pragma once
#include "Record.h"
#include "Table.h"
#include <stack>
#include <vector>

const int BAL_OK = 0;
const int BAL_LEFT = -1;
const int BAL_RIGHT = 1;

// Предварительное объявление класса TreeTable
template <class TKey, class TVal> class TreeTable;

// Структура TreeNode должна быть объявлена ДО класса TreeTable
template <class TKey, class TVal>
struct TreeNode
{
    Record<TKey, TVal> rec;
    TreeNode* pLeft, * pRight;
    int bal;

    TreeNode(TKey k, TVal v) : rec(k, v), pLeft(nullptr), pRight(nullptr), bal(BAL_OK) {}
    bool operator<(const TreeNode<TKey, TVal>& r) const { return rec.key < r.rec.key; }
    bool operator==(const TreeNode<TKey, TVal>& r) const { return rec.key == r.rec.key; }
};

template <class TKey, class TVal>
class TreeTable : public Table<TKey, TVal>
{
    int pos, level;
protected:
    TreeNode<TKey, TVal>* pRoot, * pCurr, * pPrev;
    std::stack<TreeNode<TKey, TVal>*> st;

    void DelNode(TreeNode<TKey, TVal>* node) {
        if (node == nullptr) return;
        DelNode(node->pLeft);
        DelNode(node->pRight);
        delete node;
    }

public:
    TreeTable() : pRoot(nullptr), pCurr(nullptr), pPrev(nullptr), pos(0), level(0) {}

    ~TreeTable() {
        DelNode(pRoot);
    }

    bool Find(TKey key)  {
        this->Eff = 0;
        pCurr = pRoot;
        pPrev = nullptr;
        while (pCurr != nullptr) {
            this->Eff++;
            if (key > pCurr->rec.key) {
                pPrev = pCurr;
                pCurr = pCurr->pRight;
            }
            else if (key < pCurr->rec.key) {
                pPrev = pCurr;
                pCurr = pCurr->pLeft;
            }
            else {
                return true;
            }
        }
        this->Eff++;
        pCurr = pPrev;
        return false;
    }

    void Insert(TKey key, TVal val)  {
        if (Find(key)) throw - 1;
        TreeNode<TKey, TVal>* tmp = new TreeNode<TKey, TVal>(key, val);
        if (pCurr == nullptr) {
            pRoot = tmp;
        }
        else if (key > pCurr->rec.key) {
            pCurr->pRight = tmp;
        }
        else {
            pCurr->pLeft = tmp;
        }
        this->Eff++;
        this->DataCount++;
    }

    void Insert(Record<TKey, TVal> rec) {
        Insert(rec.key, rec.val);
    }

    void Delete(TKey key)  {
        if (!Find(key)) throw - 1;

        TreeNode<TKey, TVal>* nodeToDelete = pCurr;

        // Case 1: Node has only left child
        if (nodeToDelete->pRight == nullptr && nodeToDelete->pLeft != nullptr) {
            TreeNode<TKey, TVal>* child = nodeToDelete->pLeft;
            if (nodeToDelete == pRoot) {
                pRoot = child;
            }
            else {
                if (pPrev->pLeft == nodeToDelete) {
                    pPrev->pLeft = child;
                }
                else {
                    pPrev->pRight = child;
                }
            }
        }
        // Case 2: Node has only right child
        else if (nodeToDelete->pLeft == nullptr && nodeToDelete->pRight != nullptr) {
            TreeNode<TKey, TVal>* child = nodeToDelete->pRight;
            if (nodeToDelete == pRoot) {
                pRoot = child;
            }
            else {
                if (pPrev->pLeft == nodeToDelete) {
                    pPrev->pLeft = child;
                }
                else {
                    pPrev->pRight = child;
                }
            }
        }
        // Case 3: Node is a leaf
        else if (nodeToDelete->pLeft == nullptr && nodeToDelete->pRight == nullptr) {
            if (nodeToDelete == pRoot) {
                pRoot = nullptr;
            }
            else {
                if (pPrev->pLeft == nodeToDelete) {
                    pPrev->pLeft = nullptr;
                }
                else {
                    pPrev->pRight = nullptr;
                }
            }
        }
        // Case 4: Node has both children
        else {
            TreeNode<TKey, TVal>* beforeMaxLeft = nodeToDelete;
            TreeNode<TKey, TVal>* maxLeft = nodeToDelete->pLeft;
            while (maxLeft->pRight != nullptr) {
                this->Eff++;
                beforeMaxLeft = maxLeft;
                maxLeft = maxLeft->pRight;
            }
            nodeToDelete->rec = maxLeft->rec;
            if (nodeToDelete->pLeft == maxLeft) {
                nodeToDelete->pLeft = maxLeft->pLeft;
            }
            else {
                beforeMaxLeft->pRight = maxLeft->pLeft;
            }
            this->Eff++;
            nodeToDelete = maxLeft;
        }
        delete nodeToDelete;
        this->DataCount--;
    }

    bool IsFull() const  {
        try {
            TreeNode<TKey, TVal>* tmp = new TreeNode<TKey, TVal>(TKey(), TVal());
            delete tmp;
            return false;
        }
        catch (...) {
            return true;
        }
    }

    void Clear()  {
        DelNode(pRoot);
        pRoot = pCurr = pPrev = nullptr;
        this->DataCount = pos = 0;
    }

    void Reset()  {
        pos = 0;
        pCurr = pRoot;
        while (!st.empty()) st.pop();
        while (pCurr != nullptr && pCurr->pLeft != nullptr) {
            st.push(pCurr);
            pCurr = pCurr->pLeft;
        }
    }

    void GoNext()  {
        if (pCurr == nullptr) return;

        if (pCurr->pRight != nullptr) {
            pCurr = pCurr->pRight;
            while (pCurr->pLeft != nullptr) {
                st.push(pCurr);
                pCurr = pCurr->pLeft;
            }
        }
        else if (!st.empty()) {
            pCurr = st.top();
            st.pop();
        }
        else {
            pCurr = nullptr;
        }
        pos++;
    }

    bool IsEnd()  {
        return pos >= this->DataCount;
    }

    TKey GetCurrKey()  {
        if (pCurr == nullptr) throw - 1;
        return pCurr->rec.key;
    }

    TVal GetCurrVal()  {
        if (pCurr == nullptr) throw - 1;
        return pCurr->rec.val;
    }

    Record<TKey, TVal> GetCurr()  {
        if (pCurr == nullptr) throw - 1;
        return pCurr->rec;
    }

    void PrintTree(ostream& os) {
        level = 0;
        PrintRec(os, pRoot);
    }

private:
    void PrintRec(ostream& os, TreeNode<TKey, TVal>* p) {
        if (p == nullptr) return;
        for (int i = 0; i < level; i++) os << " ";
        os << level << " level: " << p->rec.key << endl;
        level++;
        PrintRec(os, p->pRight);
        PrintRec(os, p->pLeft);
        level--;
    }
};