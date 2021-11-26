#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>


using namespace std;


class virtualBitmap {
	int bSize;
	bool *data;
	int vbSize;
	int* randomValues;
	std::hash<int> hashFunc;
	int totalZ;
	public:
		virtualBitmap(int bits, int vbl) {
			bSize = bits;
			data = new bool[bSize];
			for (int i = 0; i < bSize; i++) data[i] = false;
			vbSize = vbl;
			randomValues = new int[vbSize];
			for (int i = 0; i < vbSize; i++) randomValues[i] = (rand() << 16) + rand();
			totalZ = 0;
		}
		~virtualBitmap() {
			delete[] data;
			delete[] randomValues;
		}
		void record(int fid, int nOF) {
			for (int i = 0; i < nOF; i++) {
				int r = rand() % vbSize;
				data[hashFunc(fid ^ randomValues[r]) % bSize] = true;
			}
		}
		void countZ() {
			totalZ = 0;
			for (int i = 0; i < bSize; i++) {
				if (!data[i]) totalZ++;
			}
		}
		int query(int fid) {
			int noZ = 0;
			for (int i = 0; i < vbSize; i++) {
				if (!data[hashFunc(fid ^ randomValues[i]) % bSize]) noZ++;
			}
			double u1 = noZ, m1 = vbSize, u2 = totalZ, m2 = bSize;
			int output = m1 * (log(u2 / m2) - log(u1 / m1));
			return output;
		}
};


int main() {
	srand(time(NULL));
	std::hash<string> hashFunc;
	ifstream input;
	// Change input file name here
	string name = "project4input.txt";
	input.open(name, ios::in);
	int count = 0;
	input >> count;
	cout << count << endl;
	int data[count][3];
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
	
	// Change bitmap scale here
	int m = 500000, vbi = 500;
	virtualBitmap myVirtualBitmap(m, vbi);
	for (int i = 0; i < count; i++) myVirtualBitmap.record(data[i][0], data[i][1]);
	myVirtualBitmap.countZ();
	for (int i = 0; i < count; i++) data[i][2] = myVirtualBitmap.query(data[i][0]);
	
	
	ofstream out;
	out.open("data.txt", ios::out);
	for (int i = 0; i < count; i++) {
		if (data[i][0] >= 0) {
			//cout << (data[i][0] >> 24) % 256 << "." << (data[i][0] >> 16) % 256 << ".";
			//cout << (data[i][0] >> 8) % 256 << "." << (data[i][0]) % 256 << "\t";
		} else {
			//cout << (((data[i][0] >> 1) - (1 << 31)) >> 23) % 256 << "." << (((data[i][0] >> 1) - (1 << 31)) >> 15) % 256 << ".";
			//cout << (((data[i][0] >> 1) - (1 << 31)) >> 7) % 256 << "." << (data[i][0] - (1 << 31)) % 256 << "\t";
		}
		//cout << data[i][1] << "\t" << data[i][2] << endl;
		out << data[i][1] << "\t" << data[i][2] << endl;
	}
	out.close();
	
	
	return 0;
}
