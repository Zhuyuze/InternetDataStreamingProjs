#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
class hashTable {
	public:
		virtual bool insertFlow(int) = 0;
		virtual void printTable() = 0;
	protected:
		int tableEntries;
		int** table;
		int hashes;
		int* randomValues;
		std::hash<int> hashFunction;
		int success;
		int failure;
		int occupied;
};

#endif
