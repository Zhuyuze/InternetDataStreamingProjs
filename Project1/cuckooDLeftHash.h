#ifndef CUCKOODLEFTHASH_H
#define CUCKOODLEFTHASH_H
#include <iostream>
#include <fstream>
#include "hashTable.h"

using namespace std;
class cuckooDLeftHash: public hashTable {
	public:
		cuckooDLeftHash(const int, const int, const int);
		~cuckooDLeftHash();
		bool insertFlow(int);
		void printTable();
		bool move(int, int);
	private:
		int steps;
};

#endif
