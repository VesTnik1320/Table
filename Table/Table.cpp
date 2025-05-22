// main.cpp
#include <iostream>
#include "ArrayHashTable.h"
#include "ListHashTable.h"

int main() {
    ArrayHashTable<int, int> arrTable(10);
    //ListHashTable<int, int> listTable(10);

    arrTable.Insert(1);
    arrTable.Insert(2);

    std::string val;
    if (arrTable.Find(1)) {
        std::cout << "Found key 1: " << val << std::endl;
    }

    //listTable.Insert(3);
    //listTable.Insert(13); // same bucket as 3 if size = 10

    //if (listTable.Find(13)) {
    //    std::cout << "Found key 13 in list: " << val << std::endl;
    //}

    return 0;
}
