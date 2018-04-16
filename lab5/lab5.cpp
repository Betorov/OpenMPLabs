// lab5.cpp: определяет точку входа для консольного приложения.
//

/*
Задание. 
Модифицировать программы, составленные в Л.Р. №№3,4, распределив вычислительную нагрузку по секциям (как минимум двумя способами). 
Измерять время работы программы для тех же значений параметров, что были использованы при выполнении Л.Р. №3. 
Результаты сравнить и занести в отчёт.
//6 лаба удалить битсет
*/

#include "stdafx.h"
using namespace std;
const int NMAX = 25'990; //Больше не стоит лол кек чебурек 49990 идеально для моего компа

std::bitset<sizeof(int) * 8> ToBits(int value) {
	std::bitset<sizeof(int) * 8> bits(value);
	return bits;;
}

int MultiplierSectionsWithLocking(int **Matrix) {
	int sumOnes = 0, i = 0, j = 0;
	int result = 0;
	double t3 = clock();
	int* sums = new int[4];
	sums[0] = 0; sums[1] = 0, sums[2] = 0, sums[3] = 0;
#pragma omp parallel shared(Matrix) private(i, j)
	{
#pragma omp sections reduction (+ : sumOnes)
		{
#pragma omp section
			{
				for (i = 0; i < NMAX / 4; i++) {
					result = 1;
					for (j = 0; j < NMAX; j++) {
						result *= Matrix[i][j];
						std::bitset<sizeof(int) * 8> bits(result);
						sumOnes += bits.count();
					}
				}
			}
#pragma omp section
			{
				for (i = NMAX / 4; i < NMAX / 2; i++) {
					result = 1;
					for (j = 0; j < NMAX; j++) {
						result *= Matrix[i][j];
						std::bitset<sizeof(int) * 8> bits(result);
						sumOnes += bits.count();
					}
				}
			}
#pragma omp section
			{
				for (i = NMAX / 2; i < 3 * (NMAX / 4); i++) {
					result = 1;
					for (j = 0; j < NMAX; j++) {
						result *= Matrix[i][j];
						std::bitset<sizeof(int) * 8> bits(result);
						sumOnes += bits.count();
					}
				}
			}
#pragma omp section
			{
				for (i = 3 * (NMAX / 4); i < NMAX; i++) {
					result = 1;
					for (j = 0; j < NMAX; j++) {
						result *= Matrix[i][j];
						std::bitset<sizeof(int) * 8> bits(result);
						sumOnes += bits.count();
					}
				}
			}
		}
	}
	//sumOnes = sums[0] + sums[1] + sums[2] + sums[3];
	delete[] sums;
	double t4 = clock();
	cout << "Time with 4 Sections" << "\n" << (t4 - t3) / CLOCKS_PER_SEC << "\n";
	return sumOnes;
}

int MultiplierSectionsWithThirdSection(int **Matrix) {
	int sumOnes = 0, i = 0, j = 0;
	int result = 0;
	double t3 = clock();
	int* sums = new int[3];
	sums[0] = 0; sums[1] = 0 , sums[2] = 0;

#pragma omp parallel shared(Matrix) private(i, j)
	{
#pragma omp sections reduction (+ : sumOnes)
		{
#pragma omp section
			{
				for (i = 0; i < NMAX/3; i++) {
					result = 1;
					for (j = 0; j < NMAX; j++) {
						result *= Matrix[i][j];
						std::bitset<sizeof(int) * 8> bits(result);
						sums[0] += bits.count();
					}
				}
			}
#pragma omp section
			{
				for (i = NMAX / 3; i <2 * (NMAX / 3); i++) {
					result = 1;
					for (j = 0; j < NMAX; j++) {
						result *= Matrix[i][j];
						std::bitset<sizeof(int) * 8> bits(result);
						sums[1] += bits.count();
					}
				}
			}
#pragma omp section
			{
				for (i = 2 * (NMAX / 3); i < NMAX ; i++) {
					result = 1;
					for (j = 0; j < NMAX; j++) {
						result *= Matrix[i][j];
						std::bitset<sizeof(int) * 8> bits(result);
						sums[2] += bits.count();
					}
				}
			}
		}
	}
	sumOnes = sums[0] + sums[1] + sums[2];
	delete[] sums;
	double t4 = clock();
	cout << "Time with 3 Sections" << "\n" << (t4 - t3) / CLOCKS_PER_SEC << "\n";
	return sumOnes;
}

int MultiplierSectionsWithTwoSection(int **Matrix) {
	int sumOnes = 0, j = 0, i = 0;
	int result = 0;
	double t3 = clock();
	int* sums = new int[2];
	sums[0] = 0; sums[1] = 0;
#pragma omp parallel shared(Matrix) private(i, j)
	{
#pragma omp sections reduction (+ : sumOnes)
		{
#pragma omp section
			{
				for (i = 0; i < NMAX/2; i++) {
					result = 1;
					for (j = 0; j < NMAX; j++) {
						result *= Matrix[i][j];
						std::bitset<sizeof(int) * 8> bits(result);
						sumOnes += bits.count();
					}
				}
			}
#pragma omp section
			{
				for (i = NMAX/2; i < NMAX ; i++) {
					result = 1;
					for (j = 0; j < NMAX; j++) {
						result *= Matrix[i][j];
						std::bitset<sizeof(int) * 8> bits(result);
						sumOnes += bits.count();
					}
				}
			}
		}
	}
	//sumOnes = sums[0] + sums[1];
	delete[] sums;
	double t4 = clock();
	cout << "Time with 2 Sections" << "\n" << (t4 - t3) / CLOCKS_PER_SEC << "\n";
	return sumOnes;
}

int MultiplierSectionsWithOneSection(int **Matrix) {
	int sumOnes = 0, i = 0, j = 0;
	int result = 0;
	double t3 = clock();
#pragma omp parallel shared(Matrix) private(i, j)
	{
#pragma omp sections reduction (+ : sumOnes)
		{
#pragma omp section
			{
				for (i = 0; i < NMAX; i++) {
					result = 1;
					for (j = 0; j < NMAX; j++) {
						result *= Matrix[i][j];
						std::bitset<sizeof(int) * 8> bits(result);
						sumOnes += bits.count();
					}
				}
			}
		}
	}
	double t4 = clock();
	cout << "Time with 1 Sections" << "\n" << (t4 - t3) / CLOCKS_PER_SEC << "\n";
	return sumOnes;
}

int MultiplierAtomic(int **Matrix) {
	int sumOnes = 0,i = 0,j = 0;
	int result = 0;
	double t3 = clock();
#pragma omp parallel shared(Matrix) private(i, j)
	{
#pragma omp for
		for (i = 0; i < NMAX; i++) {
			result = 1;
			for (j = 0; j < NMAX; j++) {
				result *= Matrix[i][j];
				std::bitset<sizeof(int) * 8> bits(result);
#pragma omp atomic
				sumOnes += bits.count();			
			}
		}
	}
	double t4 = clock();
	cout << "Time with Atomic" << "\n" << (t4 - t3) / CLOCKS_PER_SEC << "\n";
	return sumOnes;
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

int MultiplierCritical(int **Matrix) {
	int sumOnes = 0;
	int result = 0;
	double t3 = clock();
	int i = 0, j = 0;
#pragma omp parallel shared(Matrix) private(i, j)
	{
#pragma omp for 
		for (i = 0; i < NMAX; i++) {
			result = 1;
			for (j = 0; j < NMAX; j++) {
				result *= Matrix[i][j];
				std::bitset<sizeof(int) * 8> bits(result);
#pragma omp critical
				sumOnes += bits.count();
			}
		}
	}
	double t4 = clock();
	cout << "Time with critical" << "\n" << (t4 - t3) / CLOCKS_PER_SEC << "\n";
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

	cout << "Sum of Values" << "\n" << MultiplierReduction(Matrix) << "\n";
	//cout << "Sum of Values" << "\n" << MultiplierCritical(Matrix) << "\n";
	//cout << "Sum of Values" << "\n" << MultiplierAtomic(Matrix) << "\n";
	cout << "Sum of Values" << "\n" << MultipliernotMP(Matrix) << "\n";
	cout << "Sum of Values" << "\n" << MultiplierSectionsWithOneSection(Matrix) << "\n";
	cout << "Sum of Values" << "\n" << MultiplierSectionsWithTwoSection(Matrix) << "\n";
	cout << "Sum of Values" << "\n" << MultiplierSectionsWithThirdSection(Matrix) << "\n";
	cout << "Sum of Values" << "\n" << MultiplierSectionsWithLocking(Matrix) << "\n";

	for (int i = 0; i < NMAX; i++) {
		delete[] Matrix[i];
	}
	delete[] Matrix;
    return 0;
}

