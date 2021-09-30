#include <iostream>
#include <fstream>
using namespace std;


class bloomFilter {
	public:
		bloomFilter(int numOfBits, int hashes) {
			this->nOBInFilter = numOfBits;
			this->hashes = hashes;
			this->randomValues = new int[hashes];
			for (int i = 0; i < hashes; i++) randomValues[i] = rand();
			this->filter = new bool[numOfBits];
			for (int i = 0; i < numOfBits; i++) filter[i] = false;
		}
		~bloomFilter() {
			delete[] filter;
			delete[] randomValues;
		}
		void encodeElement(int e) {
			for (int i = 0; i < this->hashes; i++) {
				int entry = hashFunction(e ^ randomValues[i]) % this->nOBInFilter;
				filter[entry] = true;
			}
		}
		bool lookUpElement(int e) {
			for (int i = 0; i < this->hashes; i++) {
				int entry = hashFunction(e ^ randomValues[i]) % this->nOBInFilter;
				if (!filter[entry]) return false;
			}
			return true;
		}
	private:
		int nOBInFilter;
		bool* filter;
		int hashes;
		int* randomValues;
		std::hash<int> hashFunction;
};


class countingBloomFilter {
	public:
		countingBloomFilter(int numOfCounters, int hashes) {
			this->nOCInFilter = numOfCounters;
			this->hashes = hashes;
			this->randomValues = new int[hashes];
			for (int i = 0; i < hashes; i++) randomValues[i] = rand();
			this->filter = new int[numOfCounters];
			for (int i = 0; i < numOfCounters; i++) filter[i] = 0;
		}
		~countingBloomFilter() {
			delete[] filter;
			delete[] randomValues;
		}
		void encodeElement(int e) {
			for (int i = 0; i < this->hashes; i++) {
				int entry = hashFunction(e ^ randomValues[i]) % this->nOCInFilter;
				filter[entry]++;
			}
		}
		void removeElement(int e) {
			for (int i = 0; i < this->hashes; i++) {
				int entry = hashFunction(e ^ randomValues[i]) % this->nOCInFilter;
				filter[entry]--;
			}
		}
		bool lookUpElement(int e) {
			for (int i = 0; i < this->hashes; i++) {
				int entry = hashFunction(e ^ randomValues[i]) % this->nOCInFilter;
				if (filter[entry] <= 0) return false;
			}
			return true;
		}
	private:
		int nOCInFilter;
		int* filter;
		int hashes;
		int* randomValues;
		std::hash<int> hashFunction;
};


class codedBloomFilter {
	public:
		codedBloomFilter(int numOfFilters, int numOfBits, int numOfHashes) {
			this->nOF = numOfFilters;
			this->nOBInFilter = numOfBits;
			this->hashes = numOfHashes;
			this->filter = new bloomFilter*[numOfFilters];
			for (int i = 0; i < numOfFilters; i++) filter[i] = new bloomFilter(numOfBits, numOfHashes);
		}
		~codedBloomFilter() {
			for (int i = 0; i < this->nOF; i++) delete filter[i];
			delete[] filter;
		}
		void encodeElement(int e, int s) {
			int count = 0;
			while (s > 0) {
				if (s % 2 == 1) {
					filter[count]->encodeElement(e);
				}
				s = s >> 1;
				count++;
			}
		}
		int lookUpElement(int e) {
			int output = 0;
			for (int i = this->nOF - 1; i >= 0; i--) {
				output = output << 1;
				if (filter[i]->lookUpElement(e)) output++;
			}
			return output;
		}
	private:
		int nOF;
		int nOBInFilter;
		int hashes;
		bloomFilter** filter;
		std::hash<int> hashFunction;
};


int main() {
	// change input for Bloom Filter here
	int numOfElementsBF = 1000, numOfBitsBF = 10000, numOfHashesBF = 7;
	bloomFilter myBloomFilter(numOfBitsBF, numOfHashesBF);
	ofstream outputBF;
	outputBF.open("bloomFilter.txt", ios::out);
	int ABF[numOfElementsBF];
	for (int i = 0; i < numOfElementsBF; i++) {
		ABF[i] = rand();
		myBloomFilter.encodeElement(ABF[i]);
	}
	int counter = 0;
	for (int i = 0; i < numOfElementsBF; i++) {
		if (myBloomFilter.lookUpElement(ABF[i])) counter++;
	}
	cout << counter << " ";
	outputBF << counter << endl;
	counter = 0;
	for (int i = 0; i < numOfElementsBF; i++) {
		if (myBloomFilter.lookUpElement(rand())) counter++;
	}
	cout << counter << endl;
	outputBF << counter << endl;
	
	// change input for Counting Bloom Filter here
	int numOfElementsCBF = 1000, numOfRemovalCBF = 500, numOfAddCBF = 500, numOfCountersCBF = 10000, numOfHashesCBF = 7;
	countingBloomFilter myCountingBloomFilter(numOfCountersCBF, numOfHashesCBF);
	ofstream outputCBF;
	outputCBF.open("countingBloomFilter.txt", ios::out);
	int ACBF[numOfElementsCBF];
	for (int i = 0; i < numOfElementsCBF; i++) {
		ACBF[i] = rand();
		myCountingBloomFilter.encodeElement(ACBF[i]);
	}
	for (int i = 0; i < numOfRemovalCBF; i++) {
		myCountingBloomFilter.removeElement(ACBF[i]);
	}
	for (int i = 0; i < numOfAddCBF; i++) {
		myCountingBloomFilter.encodeElement(rand());
	}
	counter = 0;
	for (int i = 0; i < numOfElementsCBF; i++) {
		if (myCountingBloomFilter.lookUpElement(ACBF[i])) counter++;
	}
	cout << counter << endl;
	outputCBF << counter << endl;
	
	// change input for Coded Bloom Filter here
	int numOfSetsCDBF = 7, numOfElementsCDBF = 1000, numOfFiltersCDBF = 3, numOfBitsCDBF = 30000, numOfHashesCDBF = 7;
	codedBloomFilter myCodedBloomFilter(numOfFiltersCDBF, numOfBitsCDBF, numOfHashesCDBF);
	ofstream outputCDBF;
	outputCDBF.open("codedBloomFilter.txt", ios::out);
	int ACDBF[numOfSetsCDBF][numOfElementsCDBF];
	for (int i = 0; i < numOfSetsCDBF; i++) {
		for (int j = 0; j < numOfElementsCDBF; j++) {
			ACDBF[i][j] = rand();
			myCodedBloomFilter.encodeElement(ACDBF[i][j], i+1);
		}	
	}
	counter = 0;
	for (int i = 0; i < numOfSetsCDBF; i++) {
		for (int j = 0; j < numOfElementsCDBF; j++) {
			if (myCodedBloomFilter.lookUpElement(ACDBF[i][j]) == i + 1) counter++;
		}	
	}
	cout << counter << endl;
	outputCDBF << counter << endl;
	
	return 0;
}
