#include "Table.h"
#include "ArrayTable.h"
#include "Record.h"
template <typename Tkey, typename TVal>  
class ScanTable : public ArrayTable<Tkey, TVal> {  
public:  
    ScanTable(int _size) : ArrayTable<Tkey, TVal>(_size) {}  

    bool Find(Tkey key) override {  
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

    void Insert(Tkey key) override {
        if (Find(key))
            throw - 2;  // Уже существует
        if (this->DataCount == this->size)
            throw - 1;  // Нет места

        this->pRec[this->Curr].key = key;
        this->DataCount++;
        this->eff++;
    }


    void Delete(Tkey key) override {  
        if (!Find(key)) throw -3;  
        this->pRec[this->Curr] = this->pRec[this->DataCount - 1];  
        this->DataCount--;  
        this->eff++;  
    }  

    void Clear() override {  
        this->DataCount = 0;  
    }  

    void Reset() override {  
        this->Curr = 0;  
    }  

    void GoNext() override {  
        if (this->Curr < this->DataCount)  
            this->Curr++;  
    }  

    bool IsEnd() override {  
        return this->Curr >= this->DataCount;  
    }  

    Record<Tkey, TVal> GetCurr() override {  
        if (this->Curr < this->DataCount)  
            return this->pRec[this->Curr];  
        throw -4;  
    }  

    bool IsFull() const override {  
        return this->DataCount == this->size;  
    }  
};