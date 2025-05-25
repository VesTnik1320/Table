#pragma once
#include <list>
#include "HashTable.h"
#include <iterator>
#include "Record.h"
template <typename TKey, typename TVal>
class ListHashTable : public HashTable<TKey, TVal>
{
protected:
    std::list<Record<TKey, TVal>>* pList;
    int CurrList;
    typename std::list<Record<TKey, TVal>>::iterator currI;

public:
    ListHashTable(int _size = 100) : HashTable<TKey, TVal>(_size) {
        this->size = _size;
        pList = new std::list<Record<TKey, TVal>>[_size];
        CurrList = -1;
    }

    ~ListHashTable() {
        delete[] pList;
    }

    bool Find(TKey key)  {
        CurrList = this->HashFunc(key);
        for (currI = pList[CurrList].begin(); currI != pList[CurrList].end(); ++currI) {
            this->Eff++;
            if (currI->key == key)
                return true;
        }
        return false;
    }

    void Insert(Record<TKey, TVal> rec)  {
        if (this->DataCount == this->size - 1)
            throw "Error, no space for new record!";
        if (Find(rec.key))
            throw "Error, this record already exists!";

        pList[CurrList].InsFirst(rec);
        this->DataCount++;
        this->Eff++;
    }

    void Insert(TKey key, TVal val) {
        if (Find(key))
            throw "Error, key already exists!";

        Record<TKey, TVal> tmp(key, val);
        pList[CurrList].InsFirst(tmp);
        this->DataCount++;
        this->Eff++;
    }

    void Delete(TKey key)  {
        if (!Find(key))
            throw "Error, key not found!";

        pList[CurrList].erase(currI);
        this->DataCount--;
        this->Eff++;
    }

    void Reset()  {
        CurrList = 0;
        currI = pList[CurrList].begin();
        while (currI == pList[CurrList].end() && CurrList < this->size - 1) {
            CurrList++;
            currI = pList[CurrList].begin();
        }
    }

    bool IsEnd() {
        return CurrList >= this->size;
    }

    void GoNext()  {
        if (currI != pList[CurrList].end())
            ++currI;

        while (currI == pList[CurrList].end() && CurrList < this->size - 1) {
            CurrList++;
            currI = pList[CurrList].begin();
        }
    }

    void Clear()  {
        this->DataCount = 0;
        for (int i = 0; i < this->size; i++) {
            pList[i].clear();
        }
    }

    bool IsFull() const  {
        return this->DataCount >= this->size - 1;
    }

    Record<TKey, TVal> GetCurr()  {
        if (IsEnd())
            throw "Error: iterator at end position";
        return *currI;
    }

    TKey GetCurrKey() {
        return GetCurr().key;
    }

    TVal GetCurrVal() {
        return GetCurr().value;
    }
};