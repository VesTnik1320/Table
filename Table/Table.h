#pragma once

template<typename TKey, typename TVal>
struct Record
{
    TKey key;
    TVal val;
};

template<typename TKey, typename TValue>
class Table
{
protected:
    int DataCount; 
    int Eff; 
public:
    Table() : DataCount(0), Eff(0) {};
    virtual ~Table() {};

    int GetDataCount();
    int GetEff();

    void ClearEff();

    bool IsEmpty() const {
        if (DataCount == 0)
            return true;
        return false;
    }

    virtual bool IsFull() const = 0;  

    virtual bool Find(TKey key) = 0;
    virtual void Insert(Record rec) = 0;
    virtual void Delete(TKey key) = 0;

    virtual void Reset() = 0;
    virtual void GoNext() = 0;
    virtual bool IsEnd() = 0;

    virtual Record GetCurr() = 0;
    virtual TKey GetCurrKey() = 0;
    virtual TValue GetCurrVal() = 0;

    friend std::ostream& operator<<(std::ostream& os, const Table& t)
    {
        for (t.Reset(); !t.IsEnd(); t.GoNext())
        {
            os << t.GetCurr() << endl;
        }
        return os;
    }
};