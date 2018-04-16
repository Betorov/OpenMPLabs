// OpenMpLabs.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

int M = 1000, N = M;
int **InitializeMatrixnotMP() {
	int **Matrix = nullptr;
	Matrix = new int *[M];
	int i = 0, j = 0;

	for (i = 0; i < M; i++) {
		Matrix[i] = new int[N];
	}


	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			Matrix[i][j] = rand() % 15;

	return Matrix;
}
void MultipliernotMP(int **Matrix) {
	int sumOnes = 0;
	int result = 0;
	for (int i = 0; i < M; i++) {
		result = 1;
		for (int j = 0; j < N; j++) {
			result *= Matrix[i][j];
			std::bitset<sizeof(int) * 8> bits(result);
			sumOnes += bits.count();
		}
	}

}

int **InitializeMatrix() {
	int **Matrix = nullptr;
	Matrix = new int *[M];
	int i = 0, j = 0;
#pragma omp parallel private(i)
	{
#pragma omp for
		for (i = 0; i < M; i++) {
			Matrix[i] = new int[N];
		}
	}
#pragma omp parallel private(i,j)
	{
#pragma omp for
		for (i = 0; i < M; i++)
			for (j = 0; j < N; j++)
				Matrix[i][j] = rand() % 15;
	}
	return Matrix;
}

void deleteMatrix(int **Matrix) {
	for (int i = 0; i < M; i++)
		delete Matrix;
}
void Multiplier(int **Matrix) {
	int sumOnes = 0;
	int result = 0;
#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < M; i++) {
			result = 1;
			for (int j = 0; j < N; j++) {
				result *= Matrix[i][j];
				std::bitset<sizeof(int) * 8> bits(result);
				sumOnes += bits.count();
			}
		}
	}
}

std::bitset<sizeof(int) * 8> ToBits(int value) {
	std::bitset<sizeof(int) * 8> bits(value);
	return bits;;
}




int main(int argc, char * argv[]) {
#ifndef _OPENMP
	std::cout << "OpenMP is working\n";
#endif
	srand(time(NULL));
	unsigned int timesNow = clock();
	int **Matrix = InitializeMatrix();
	Multiplier(Matrix);
	std::cout << "Times with MP: " << clock() - timesNow << std::endl;
	timesNow = clock();
	Matrix = InitializeMatrixnotMP();
	MultipliernotMP(Matrix);
	std::cout << "Times not MP: " << clock() - timesNow << std::endl;
	system("pause");
	return 0;
}

/*unsigned int n = 0;
for(int i = 0; i < M; i++){
std::cout<<"\n";
for(int j = 0; j < N; j++)
std::cout << Matrix[i][j] << " ";
}
int size = 141000000;
int *x = new int[size];
int *y = new int[size];
for(int i = 0; i < size; i++){
x[i] = rand()%10;
y[i] = rand()%15;
}
timesNow = clock();
#pragma omp parallel for
for(int i = 1; i < size; ++i)
x[i] = (y[i-1] + y[i+1])/2;

std::cout << "\n" << clock()-timesNow;*/
