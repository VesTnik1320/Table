#pragma once
#include "Table.h"
#include "ArrayTable.h"
#include "Record.h"
template <typename Tkey, typename TVal>  
class ScanTable : public ArrayTable<Tkey, TVal> {  
public:  
    ScanTable(int _size) : ArrayTable<Tkey, TVal>(_size) {}  

    bool Find(Tkey key) {  
        for (int i = 0; i < this->DataCount; i++) {  
            this->eff++;  
            if (key == this->pRec[i].key) {  
                this->Curr = i;  
                return true;  
            }  
        }  
        this->Curr = this->DataCount;  
        return false;  
    }  

    void Insert(Tkey key) {
        if (Find(key))
            throw - 2;  // ��� ����������
        if (this->DataCount == this->size)
            throw - 1;  // ��� �����

        this->pRec[this->Curr].key = key;
        this->DataCount++;
        this->eff++;
    }


    void Delete(Tkey key) {  
        if (!Find(key)) throw -3;  
        this->pRec[this->Curr] = this->pRec[this->DataCount - 1];  
        this->DataCount--;  
        this->eff++;  
    }  

    void Clear()  {  
        this->DataCount = 0;  
    }  

    void Reset()  {  
        this->Curr = 0;  
    }  

    void GoNext()  {  
        if (this->Curr < this->DataCount)  
            this->Curr++;  
    }  

    bool IsEnd()  {  
        return this->Curr >= this->DataCount;  
    }  

    Record<Tkey, TVal> GetCurr()  {  
        if (this->Curr < this->DataCount)  
            return this->pRec[this->Curr];  
        throw -4;  
    }  

    bool IsFull() const  {  
        return this->DataCount == this->size;  
    }  
};