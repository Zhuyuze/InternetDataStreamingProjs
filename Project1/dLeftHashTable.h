#ifndef DLEFTHASHTABLE_H
#define DLEFTHASHTABLE_H
#include <iostream>
#include <fstream>
#include "hashTable.h"

using namespace std;
class dLeftHashTable: public hashTable {
	public:
		dLeftHashTable(const int, const int);
		~dLeftHashTable();
		bool insertFlow(int);
		void printTable();
};

#endif
