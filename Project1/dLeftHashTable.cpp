#include <iostream>
#include <fstream>
#include "dLeftHashTable.h"
dLeftHashTable::dLeftHashTable(const int tableEntries, const int hashes) {
	this->tableEntries = tableEntries;
	this->hashes = hashes;
	this->randomValues = new int[hashes];
	for (int i = 0; i < hashes; i++) randomValues[i] = rand();
	this->table = new int*[tableEntries];
	for (int i = 0; i < tableEntries; i++) {
		table[i] = new int[2];
		table[i][0] = -1, table[i][1] = -1;
	} 
	success = 0;
	failure = 0;
	occupied = 0;
}
dLeftHashTable::~dLeftHashTable() {
	delete[] this->randomValues;
	for (int i = 0; i < this->tableEntries; i++) delete[] this->table[i];
	delete[] this->table;
}
bool dLeftHashTable::insertFlow(int fid) {
	int groupAmount = this->tableEntries / this->hashes;
	for (int i = 0; i < this->hashes; i++) {
		int entry = hashFunction(fid ^ randomValues[i]) % groupAmount + groupAmount * i;
		if (table[entry][0] == -1) {
			table[entry][0] = fid;
			table[entry][1] = 1;
			success++;
			occupied++;
			return true;
		} else if (table[entry][0] == fid) {
			table[entry][1]++;
			success++;
			return true;
		}
	}
	failure++;
	return false;
}

void dLeftHashTable::printTable() {
	cout << "D-Left Success: " << success << "\t" << "Failure: " << failure << "\t" << "Occupied: " << occupied << endl;
	ofstream output;
	output.open("dLeftHashTableOutput", ios::out);
	output << success << " " << occupied << endl;
	for (int i = 0; i < this->tableEntries; i++) {
		//cout << table[i][0] << "\t" << table[i][1] << endl;
		output << table[i][0] << "\t" << table[i][1] << endl;
	}
}
