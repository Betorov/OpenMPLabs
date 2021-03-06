// Labs6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;
const int NMAX = 25'990; //Больше не стоит лол кек чебурек 49990 идеально для моего компа

std::bitset<sizeof(int) * 8> ToBits(int value) {
	std::bitset<sizeof(int) * 8> bits(value);
	return bits;;
}

int MultiplierReduction(int **Matrix) {
	int sumOnes = 0, i = 0, j = 0;
	int result = 0;
	double t3 = clock();
#pragma omp parallel shared(Matrix) private(i, j)
	{
#pragma omp for reduction(+:sumOnes)
		for (i = 0; i < NMAX; i++) {
			result = 1;
			for (j = 0; j < NMAX; j++) {
				result *= Matrix[i][j];
				std::bitset<sizeof(int) * 8> bits(result);
				sumOnes += bits.count();
			}
		}
	}
	double t4 = clock();
	cout << "Time with reduction" << "\n" << (t4 - t3) / CLOCKS_PER_SEC << "\n";
	return sumOnes;
}

int MultiplierSectionsWithLocking(int **Matrix) {
	int sumOnes = 0, i = 0, j = 0;
	int result = 0;
	double t3 = clock();
	int threads = 0;
	omp_lock_t lock;
	omp_init_lock(&lock);
#pragma omp parallel shared(Matrix) private(i, j)
	{
#pragma omp for reduction(+:sumOnes)
		for (i = 0; i < NMAX; i++) {
			result = 1;
			omp_set_lock(&lock);
			for (j = 0; j < NMAX; j++) {
				result *= Matrix[i][j];
				std::bitset<sizeof(int) * 8> bits(result);
				sumOnes += bits.count();
			}
			omp_unset_lock(&lock);
		}
		threads++;
	}
	double t4 = clock();
	cout << "Time with lock" << "\n" << (t4 - t3) / CLOCKS_PER_SEC << "\n";
	return sumOnes;
}
int MultipliernotMP(int **Matrix) {
	int sumOnes = 0;
	int result = 0;
	double t3 = clock();
	for (int i = 0; i < NMAX; i++) {
		result = 1;
		for (int j = 0; j < NMAX; j++) {
			result *= Matrix[i][j];
			std::bitset<sizeof(int) * 8> bits(result);
			sumOnes += bits.count();
		}
	}
	double t4 = clock();
	cout << "Time with notMP" << "\n" << (t4 - t3) / CLOCKS_PER_SEC << "\n";
	return sumOnes;
}


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");

	int MaxThread = omp_get_max_threads();
	cout << "Max thread = " << MaxThread << endl;
	cout << "Max procs = " << omp_get_num_procs() << endl;

	int** Matrix = new int *[NMAX];
	for (int i = 0; i < NMAX; i++) {
		Matrix[i] = new int[NMAX];
	}
	int i = 0, j = 0;
#pragma omp parallel shared(Matrix) private(i,j)
	{
#pragma omp for
		for (i = 0; i < NMAX; i++)
			for (j = 0; j < NMAX; j++)
				Matrix[i][j] = rand() % 100;
	}

	cout << "Init" << endl;

	omp_set_dynamic(false);
	//cout << "Sum of Values" << "\n" << MultiplierReduction(Matrix) << "\n";
	omp_set_num_threads(2);
	cout << "Sum of Values with 2 thread" << "\n" << MultiplierSectionsWithLocking(Matrix) << "\n";
	cout << "Sum of Values with 2 thread with reduction " << MultiplierReduction(Matrix) << "\n";
	omp_set_num_threads(4);
	cout << "Sum of Values with 4 thread" << "\n" << MultiplierSectionsWithLocking(Matrix) << "\n";
	cout << "Sum of Values with 4 thread with reduction " << MultiplierReduction(Matrix) << "\n";
	omp_set_num_threads(6);
	cout << "Sum of Values with 6 thread" << "\n" << MultiplierSectionsWithLocking(Matrix) << "\n";
	cout << "Sum of Values with 6 thread with reduction " << MultiplierReduction(Matrix) << "\n";
	omp_set_num_threads(8);
	cout << "Sum of Values with 8 thread" << "\n" << MultiplierSectionsWithLocking(Matrix) << "\n";
	cout << "Sum of Values with 8 thread with reduction " << MultiplierReduction(Matrix) << "\n";
	omp_set_num_threads(16);
	cout << "Sum of Values with 16 thread" << "\n" << MultiplierSectionsWithLocking(Matrix) << "\n";
	cout << "Sum of Values with 16 thread with reduction " << MultiplierReduction(Matrix) << "\n";
	omp_set_num_threads(32);
	cout << "Sum of Values with 32 thread" << "\n" << MultiplierSectionsWithLocking(Matrix) << "\n";
	cout << "Sum of Values with 32 thread with reduction " << MultiplierReduction(Matrix) << "\n";
	omp_set_num_threads(64);
	cout << "Sum of Values with 64 thread" << "\n" << MultiplierSectionsWithLocking(Matrix) << "\n";
	cout << "Sum of Values with 64 thread with reduction " << MultiplierReduction(Matrix) << "\n";
	omp_set_num_threads(128);
	cout << "Sum of Values with 128 thread" << "\n" << MultiplierSectionsWithLocking(Matrix) << "\n";
	cout << "Sum of Values with 128 thread with reduction " << MultiplierReduction(Matrix) << "\n";

	for (int i = 0; i < NMAX; i++) {
		delete[] Matrix[i];
	}
	delete[] Matrix;
	return 0;
}

