#pragma once
#include "TreeTable.h"

enum Status { H_DEC, H_OK, H_INC };

template< typename TKey, typename TVal>
struct TNode
{
    int bal;
    Status status;
};

template< typename TKey, typename TVal>
class BalTreeTable : public TreeTable<TKey, TVal> {
protected:
    int InsBalTree(TNode*& pNode, TRecord rec);
    int BalTreeLeft(TNode*& pNode);
    int BalTreeRight(TNode*& pNode);
public:
    bool Insert(TRecord rec) {
        if (Find(rec.key))
            throw "Error this key exists!"
            InsBalTree(pRoof, rec);
    }

    int InsBalTree(TNode*& pNode, TRecord rec) {
        int res = H_OK;
        if (pNode == nullptr) {
            pNode = new TNode(rec);
            res = H_INC;
            DataCount++;
        }
        else if (pNode->rec.key > rec.key) {
            int tmp = InsBalTree(pNode->pleft, rec);
            if (tmp == H_INC)
                res = BalTreeLeft(pNode);
        }
        else {
            int tmp = InsBalTree(pNode->pRight, rec);
            if (tmp == H_INC)
                rec = BalTreeRight(pNode);
        }
        return res;
    }

    int BalTreeLeft(TNode*& pNode) {
        int res = H_OK;
        if (pNode->bal == BAL_RIGHT) {
            pNode->bal = BAL_OK;
            res = H_OK;
        }
        else if (pNode->bal == BAL_OK) {
            pNode->bal = BAL_LEFT;
            res = H_INC;
        }
        else if (pNode->bal == BAL_LEFT) {
            TreeNode<TKey, TVal>* p1 = pNode->pLeft;
            if (p1->bal == BAL_LEFT) {
                pNode->pLeft = p1->pRight;
                p1->pRight = pNode;
                pNode->bal = BAL_OK;
                pNode = p1;
                pNode->bal = BAL_OK;
            }
            else {
                TreeNode<TKey, TVal>* p2 = p1->pRight;
                p1->pRight = p2->pLeft;
                p2->pLeft = p1;
                pNode->pLeft = p2->pRight;
                p2->pRight = pNode;
                if (p2->bal == BAL_LEFT) {
                    pNode->bal = BAL_RIGHT;
                }
                else {
                    pNode->bal = BAL_OK;
                }
                if (p2->bal == BAL_RIGHT) {
                    pNode->bal = BAL_LEFT;
                }
                else {
                    p1->bal = BAL_OK;
                }
                pNode = p2;
                pNode->bal = BAL_OK;
                res = H_OK;
            }
        }
        return res;
    }

    int BalTreeRight(TNode*& pNode) {
        int res = H_OK;
        if (pNode->bal == BAL_LEFT) {
            pNode->bal = BAL_OK;
            res = H_OK;
        }
        else if (pNode->bal == BAL_OK) {
            pNode->bal = BAL_RIGHT;
            res = H_INC;
        }
        else if (pNode->bal == BAL_RIGHT) {
            TreeNode<TKey, TVal>* p1 = pNode->pRight;
            if (p1->bal == BAL_RIGHT) {
                pNode->pRight = p1->pLeft;
                p1->pLeft = pNode;
                pNode->bal = BAL_OK;
                pNode = p1;
                pNode->bal = BAL_OK;
            }
            else {
                TreeNode<TKey, TVal>* p2 = p1->pLeft;
                p1->pLeft = p2->pRight;
                p2->pRight = p1;
                pNode->pRight = p2->pLeft;
                p2->pLeft = pNode;
                if (p2->bal == BAL_RIGHT) {
                    pNode->bal = BAL_LEFT;
                }
                else {
                    pNode->bal = BAL_OK;
                }
                if (p2->bal == BAL_LEFT) {
                    pNode->bal = BAL_RIGHT;
                }
                else {
                    p1->bal = BAL_OK;
                }
                pNode = p2;
                pNode->bal = BAL_OK;
                res = H_OK;
            }
        }
        return res;
    }

    int DeleteRec(TreeNode<TKey, TVal>*& pNode, TKey key)
    {
        int res = H_OK;
        eff++;
        if (pNode == nullptr) throw - 1;
        if (pNode->rec.key < key)
        {
            int tmp = DeleteRec(pNode->pRight, key);
            if (tmp != H_OK) res = BalTreeLeft(pNode);
        }
        else if (key < pNode->rec.key)
        {
            int tmp = DeleteRec(pNode->pLeft, key);
            if (tmp != H_OK) res = BalTreeRight(pNode);
        }
        else
        {
            dataCount--;
            if (pNode->pLeft == nullptr && pNode->pRight == nullptr)
            {
                delete pNode;
                pNode = nullptr;
                res = H_DEC;
            }
            else if (pNode->pLeft == nullptr)
            {
                pNode->rec = pNode->pRight->rec;
                delete pNode->pRight;
                pNode->pRight = nullptr;
                pNode->bal = BAL_OK;
            }
            else if (pNode->pRight == nullptr)
            {
                pNode->rec = pNode->pLeft->rec;
                delete pNode->pLeft;
                pNode->pLeft = nullptr;
                pNode->bal = BAL_OK;
            }
            else
            {
                TreeNode<TKey, TVal>* tmpLeft = pNode->pLeft;
                TreeNode<TKey, TVal>* tmpRight = pNode->pRight;
                TreeNode<TKey, TVal>* pMin = FindMin(tmpRight);
                res = RemoveMin(pNode);
                pNode->rec = pMin->rec;
                delete pMin;
                pNode->pLeft = tmpLeft;
                pNode->pRight = tmpRight;
                if (res != H_OK)
                {
                    BalTreeLeft(pNode, false);
                }
            }
        }
        return res;
    }

    int RemoveMin(TreeNode<TKey, TVal>*& pNode)
    {
        eff++;
        int res = H_OK;
        if (pNode->pLeft == nullptr)
        {
            pNode = pNode->pRight;
            res = H_DEC;
        }
        else
        {
            res = RemoveMin(pNode->pLeft);
            if (res != H_OK) res = BalTreeRight(pNode, false);
        }
        return res;
    }

    TreeNode <TKey, TVal> BalTreeTable <TKey, TVal>::FindMin(TNode* pNode) {
        while (pNode->pLeft != nullptr) {
            pNode = pNode->pLeft;
            eff++;
            return pNode;
        }
    }

    void Delete(TKey key)
    {
        if (IsEmpty()) return;
        DeleteRec(pRoot, key);
    }
};
