#pragma once
#include "Table.h"
#include "Record.h"
template<typename TKey, typename TValue>
class ArrayTable : public Table<TKey, TValue>
{
protected:
    int size, Curr;
    Record<TKey, TValue>* pRec; 
public:
    ArrayTable(int size) : size(size), pRec(new Record<TKey, TValue>[size]), Curr(0), Table() {}
    
    TKey GetCurrKey() { return pRec[Curr].key; }
    TValue GetCurrVal() { return pRec[Curr].val; } // Fixed: Changed TVal to TValue
    Record<TKey, TValue> GetCurrRec() { return pRec[Curr]; } // Fixed: Changed TVal to TValue
    ~ArrayTable() { delete[] pRec; }
    void Clear() { dataCount = 0; }
    bool IsFull() const { return DataCount == size; }
    bool IsEmpty() { return size == 0; }

    ArrayTable(const ArrayTable& arrayTable)
    {
        size = arrayTable.size;
        Curr = arrayTable.Curr;

        delete[] pRec;
        pRec = new Record<TKey, TValue>[size];
        for (int i = 0; i < size; i++)
        {
            pRec[i] = arrayTable.pRec[i];
        }
    }
    void Reset() { Curr = 0; }
    void GoNext() { Curr++; }
    bool IsEnd() { return (DataCount == Curr); }
};