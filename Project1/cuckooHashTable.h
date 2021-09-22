#ifndef CUCKOOHASHTABLE_H
#define CUCKOOHASHTABLE_H
#include <iostream>
#include <fstream>
#include "hashTable.h"

using namespace std;
class cuckooHashTable: public hashTable {
	public:
		cuckooHashTable(const int, const int, const int);
		~cuckooHashTable();
		bool insertFlow(int);
		void printTable();
		bool move(int, int);
	private:
		int steps;
};

#endif
