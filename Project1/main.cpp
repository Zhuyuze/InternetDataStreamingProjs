#include "multiHashTable.h"
#include "cuckooHashTable.h"
#include "dLeftHashTable.h"
#include "cuckooDLeftHash.h"

using namespace std;

int main(int argc, char* argv[]) {
	int entries = 1000; // set input size
	int tableSize = 1000; // set table size (for all hash tables)
	
	int hashesOfMultiHashTable = 3; // set number of hashes in Multi Hash Table
	
	int hashesOfCuckooHashTable = 3; // set number of hashes in Cuckoo Hash Table
	int cuckooSteps = 2; // set number of cuckoo steps in Cuckoo Hash Table
	
	int segmentsOfDLeftHashTable = 4; // set number of segments in D Left Hash Table
	
	
	multiHashTable myMultiHashTable(tableSize, hashesOfMultiHashTable);
	for (int i = 0; i < entries; i++) {
		myMultiHashTable.insertFlow(rand());
	}
	myMultiHashTable.printTable();
	
	
	cuckooHashTable myCuckooHashTable(tableSize, hashesOfCuckooHashTable, cuckooSteps);
	for (int i = 0; i < entries; i++) {
		myCuckooHashTable.insertFlow(rand());
	}
	myCuckooHashTable.printTable();
	
	
	dLeftHashTable myDLeftHashTable(tableSize, segmentsOfDLeftHashTable);
	for (int i = 0; i < entries; i++) {
		myDLeftHashTable.insertFlow(rand());
	}
	myDLeftHashTable.printTable();
	

	// combination of cuckoo and D Left
	cuckooDLeftHash myCuckooDLeftHashTable(tableSize, 4, 2);
	for (int i = 0; i < entries; i++) {
		myCuckooDLeftHashTable.insertFlow(rand());
	}
	myCuckooDLeftHashTable.printTable();

	return 0;
}
