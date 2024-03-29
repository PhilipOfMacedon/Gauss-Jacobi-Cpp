#include <cstdlib>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void generateInstance(int size, int sparsity) {
	if (size <= 1) {
		cout << "\nInvalid size. Size must be greater than 2.\n\n";
	} else {
		int** matrix = new int*[size];
		for (int i = 0; i < size; i++) {
			matrix[i] = new int[size];
		}
		time_t rawtime = time(nullptr);
		struct tm* timeinfo;
		timeinfo = localtime (&rawtime);
		stringstream ss;
		ss << "instances/matrix_" << put_time(timeinfo, "%Y-%m-%d_%Hh%Mm%Ss") << ".txt";
		string fileName =ss.str();
		ofstream output(fileName.c_str());
		output << size << endl;
		srand(time(NULL));
		for (int i = 0; i < size; i++) {
			int sum = 0;
			for (int j = 0; j < size; j++) {
				if (i != j) {
					int zeroRoulette = rand() % 100;
					if (zeroRoulette < sparsity) {
						matrix[i][j] = 0;
					} else {
						matrix[i][j] = rand() % 60 - 30;
						sum += abs(matrix[i][j]);
					}
				}
			}
			sum += rand() % 15 + 10;
			sum *= (rand() % 10 < 5) ? (-1) : (1);
			matrix[i][i] = sum;
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				output << matrix[i][j] << " ";
			}
			output << size * (rand() % 2000 - 1000) << endl;
		}
		output.close();
		for (int i = 0; i < size; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}
}

void printError(string exeName) {
	cout << "\nUsage:\t" << exeName << " --size [NUMBER OF VARIABLES]" << endl << endl;
}

int main(int argc, char** argv) {
	if (argc > 2) {
		int count = 1;
		int size = 10;
		int sparsity = 50;
		while (count < argc) {
			if (string(argv[count]) == "--size") {
				size = stoi(argv[++count]);
			} else if (argv[count] == "--sparsity") {
				sparsity = stoi(argv[++count]);
			}
			count++;
		}
		generateInstance(size, sparsity);
		return 0;
	}
	printError(string(argv[0]));
	return -1;
}