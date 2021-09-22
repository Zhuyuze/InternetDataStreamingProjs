#ifndef MULTIHASHTABLE_H
#define MULTIHASHTABLE_H
#include <iostream>
#include <fstream>
#include "hashTable.h"

using namespace std;
class multiHashTable: public hashTable {
	public:
		multiHashTable(const int, const int);
		~multiHashTable();
		bool insertFlow(int);
		void printTable();
};

#endif
