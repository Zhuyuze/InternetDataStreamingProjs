#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;


class countMin {
	int nOA, nOC;
	int* randomValues;
	int** counterArrays;
	std::hash<int> hashFunc; 
	public:
		countMin(int numOfArrays, int numOfCounters) {
			this->nOA = numOfArrays;
			this->nOC = numOfCounters;
			this->randomValues = new int[this->nOA];
			for (int i = 0; i < this->nOA; i++) this->randomValues[i] = (rand() << 16) + rand();
			this->counterArrays = new int*[this->nOA];
			for (int i = 0; i < this->nOA; i++) {
				this->counterArrays[i] = new int[this->nOC];
				for (int j = 0; j < this->nOC; j++) this->counterArrays[i][j] = 0;
			}
		}
		~countMin() {
			for (int i = 0; i < this->nOA; i++) delete[] this->counterArrays[i];
			delete[] this->counterArrays;
			delete[] this->randomValues;
		}
		void insert(int fid, int num) {
			for (int i = 0; i < this->nOA; i++) {
				this->counterArrays[i][hashFunc(fid ^ this->randomValues[i]) % this->nOC] += num;
			}
		}
		int query(int fid) {
			int output = 2147483647;
			for (int i = 0; i < this->nOA; i++) {
				if (this->counterArrays[i][hashFunc(fid ^ this->randomValues[i]) % this->nOC] < output) {
					output = this->counterArrays[i][hashFunc(fid ^ this->randomValues[i]) % this->nOC];
				}
				
			}
			return output;
		}	
};


class counterSketch {
	int nOA, nOC;
	int* randomValues;
	int** counterArrays;
	std::hash<int> hashFunc; 
	public:
		counterSketch(int numOfArrays, int numOfCounters) {
			this->nOA = numOfArrays;
			this->nOC = numOfCounters;
			this->randomValues = new int[this->nOA];
			for (int i = 0; i < this->nOA; i++) this->randomValues[i] = (rand() << 16) + rand();
			this->counterArrays = new int*[this->nOA];
			for (int i = 0; i < this->nOA; i++) {
				this->counterArrays[i] = new int[this->nOC];
				for (int j = 0; j < this->nOC; j++) this->counterArrays[i][j] = 0;
			}
		}
		~counterSketch() {
			for (int i = 0; i < this->nOA; i++) delete[] this->counterArrays[i];
			delete[] this->counterArrays;
			delete[] this->randomValues;
		}
		void insert(int fid, int num) {
			for (int i = 0; i < this->nOA; i++) {
				unsigned int hashNum = hashFunc(fid ^ this->randomValues[i]);
				if (hashNum >> 31) this->counterArrays[i][hashNum % this->nOC] += num;
				else this->counterArrays[i][hashNum % this->nOC] -= num;
			}
		}
		int query(int fid) {
			int temp[this->nOA];
			for (int i = 0; i < this->nOA; i++) temp[i] = this->counterArrays[i][hashFunc(fid ^ this->randomValues[i]) % this->nOC];
			sort(temp, temp + this->nOA);
			//for (int i = 0; i < this->nOA; i++) cout << temp[i] << " ";
			//cout << endl;
			if (this->nOA % 2) {
				return temp[this->nOA / 2];
			} else {
				return (temp[this->nOA / 2] + temp[this->nOA / 2 - 1]) / 2;
			}
		}	
};


class activeCounter{
	unsigned short n, e;
	public:
		activeCounter() {
			n = 0;
			e = 0;
		}
		void increaseByOne() {
			if (rand() < RAND_MAX >> e) n++;
			if (n == 65535){
				n = n >> 1;
				e++;
			}
		}
		int value() {
			return n * (1 << e);
		}
};


bool compare(int* i, int* j) {
	return (i[2] > j[2]);
}


int main() {
	srand(time(NULL));
	std::hash<string> hashFunc;
	ifstream input;
	string name = "project3input.txt";
	input.open(name, ios::in);
	int count = 0;
	input >> count;
	cout << count << endl;
	int** data = new int*[count];
	for (int i = 0; i < count; i++) data[i] = new int[3];
	//int data[count][4];
	for (int i = 0; i < count; i++) {
		data[i][0] = 0;
		int temp = 0;
		input >> temp;
		data[i][0] += temp << 24;
		input.get();
		input >> temp;
		data[i][0] += temp << 16;
		input.get();
		input >> temp;
		data[i][0] += temp << 8;
		input.get();
		input >> temp;
		data[i][0] += temp;
		/*
		string tmp;
		input >> tmp;
		data[i][0] = hashFunc(tmp);
		*/
		input >> data[i][1];
		//cout << data[i][0] << "\t" << data[i][1] << endl;	
		data[i][2] = 0;
	}
	
	
	// set countMin scale here
	int nOA_CM = 3, nOC_CM = 3000;
	countMin myCountMin(nOA_CM, nOC_CM);
	for (int i = 0; i < count; i++) myCountMin.insert(data[i][0], data[i][1]);
	int countError = 0;
	long trueSize = 0;
	for (int i = 0; i < count; i++) {
		trueSize += data[i][1];
		data[i][2] = myCountMin.query(data[i][0]);
		countError += data[i][2] - data[i][1];
	}
	cout << countError / count << endl;
	sort(data, data + count, compare);
	ofstream out;
	out << countError / count << endl;
	out.open("CountMin.txt", ios::out);
	for (int i = 0; i < 100; i++) {
		if (data[i][0] >= 0) {
			cout << (data[i][0] >> 24) % 256 << "." << (data[i][0] >> 16) % 256 << ".";
			cout << (data[i][0] >> 8) % 256 << "." << (data[i][0]) % 256 << "\t";
			out << (data[i][0] >> 24) % 256 << "." << (data[i][0] >> 16) % 256 << ".";
			out << (data[i][0] >> 8) % 256 << "." << (data[i][0]) % 256 << "\t";
		} else {
			cout << (((data[i][0] >> 1) - (1 << 31)) >> 23) % 256 << "." << (((data[i][0] >> 1) - (1 << 31)) >> 15) % 256 << ".";
			cout << (((data[i][0] >> 1) - (1 << 31)) >> 7) % 256 << "." << (data[i][0] - (1 << 31)) % 256 << "\t";
			out << (((data[i][0] >> 1) - (1 << 31)) >> 23) % 256 << "." << (((data[i][0] >> 1) - (1 << 31)) >> 15) % 256 << ".";
			out << (((data[i][0] >> 1) - (1 << 31)) >> 7) % 256 << "." << (data[i][0] - (1 << 31)) % 256 << "\t";
		}
		cout << data[i][2] << "\t" << data[i][1] << endl;
		out << data[i][2] << "\t" << data[i][1] << endl;
	}
	out.close();
	//cout << trueSize << endl;
	
	
	// set counterSketch scale here
	int nOA_CS = 3, nOC_CS = 3000;
	counterSketch myCounterSketch(nOA_CS, nOC_CS);
	for (int i = 0; i < count; i++) myCounterSketch.insert(data[i][0], data[i][1]);
	countError = 0;
	for (int i = 0; i < count; i++) {
		data[i][2] = myCounterSketch.query(data[i][0]);
		if (data[i][2] - data[i][1] >= 0) countError += data[i][2] - data[i][1];
		else countError -= data[i][2] - data[i][1];
	}
	cout << countError / count << endl;
	sort(data, data + count, compare);
	out.open("CounterSketch.txt", ios::out);
	out << countError / count << endl;
	for (int i = 0; i < 100; i++) {
		if (data[i][0] >= 0) {
			cout << (data[i][0] >> 24) % 256 << "." << (data[i][0] >> 16) % 256 << ".";
			cout << (data[i][0] >> 8) % 256 << "." << (data[i][0]) % 256 << "\t";
			out << (data[i][0] >> 24) % 256 << "." << (data[i][0] >> 16) % 256 << ".";
			out << (data[i][0] >> 8) % 256 << "." << (data[i][0]) % 256 << "\t";
		} else {
			cout << (((data[i][0] >> 1) - (1 << 31)) >> 23) % 256 << "." << (((data[i][0] >> 1) - (1 << 31)) >> 15) % 256 << ".";
			cout << (((data[i][0] >> 1) - (1 << 31)) >> 7) % 256 << "." << (data[i][0] - (1 << 31)) % 256 << "\t";
			out << (((data[i][0] >> 1) - (1 << 31)) >> 23) % 256 << "." << (((data[i][0] >> 1) - (1 << 31)) >> 15) % 256 << ".";
			out << (((data[i][0] >> 1) - (1 << 31)) >> 7) % 256 << "." << (data[i][0] - (1 << 31)) % 256 << "\t";
		}
		cout << data[i][2] << "\t" << data[i][1] << endl;
		out << data[i][2] << "\t" << data[i][1] << endl;
	}
	out.close();
	
	
	out.open("ActiveCounter.txt", ios::out);
	activeCounter myActiveCounter;
	for (int i = 0; i < 1000000; i++) myActiveCounter.increaseByOne();
	cout << myActiveCounter.value() << endl;
	out << myActiveCounter.value() << endl;
	out.close(); 
	
	
	for (int i = 0; i < count; i++) delete[] data[i];
	delete[] data;
	return 0;
}
