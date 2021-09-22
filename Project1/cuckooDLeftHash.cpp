#include <iostream>
#include <fstream>
#include "cuckooDLeftHash.h"
cuckooDLeftHash::cuckooDLeftHash(const int tableEntries, const int hashes, const int steps) {
	this->tableEntries = tableEntries;
	this->hashes = hashes;
	this->steps = steps;
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
cuckooDLeftHash::~cuckooDLeftHash() {
	delete[] this->randomValues;
	for (int i = 0; i < this->tableEntries; i++) delete[] this->table[i];
	delete[] this->table;
}
bool cuckooDLeftHash::move(int position, int steps) {
	int fToMove = table[position][0];
	for (int i = 0; i < this->hashes; i++) {
		int entry = hashFunction(fToMove ^ randomValues[i]) % this->tableEntries;
		if (entry != position && table[entry][0] == -1) {
			table[entry][0] = fToMove;
			table[entry][1] = table[position][1];
			return true;
		}
	}
	if (steps >=1) {
		for (int i = 0; i < this->hashes; i++) {
			int entry = hashFunction(fToMove ^ randomValues[i]) % this->tableEntries;
			if (entry != position && move(entry, steps-1)) {
				table[entry][0] = fToMove;
				table[entry][1] = table[position][1];
				return true;
			}
		}
	}
	return false;	
}
bool cuckooDLeftHash::insertFlow(int fid) {
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
	for (int i = 0; i < 3; i++) {
		int entry = hashFunction(fid ^ randomValues[i]) % groupAmount + groupAmount * i;
		if (move(entry, this->steps)) {
			table[entry][0] = fid;
			table[entry][1] = 1;
			success++;
			occupied++;
			return true;
		}
	}
	failure++;
	return false;
}

void cuckooDLeftHash::printTable() {
	cout << "cuckoo&DLeft Success: " << success << "\t" << "Failure: " << failure << "\t" << "Occupied: " << occupied << endl;
	ofstream output;
	output.open("cuckooDLeftHashTableOutput", ios::out);
	output << success << " " << occupied << endl;
	for (int i = 0; i < this->tableEntries; i++) {
		//cout << table[i][0] << "\t" << table[i][1] << endl;
		output << table[i][0] << "\t" << table[i][1] << endl;
	}
}
