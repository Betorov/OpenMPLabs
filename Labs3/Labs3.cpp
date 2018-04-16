// Labs3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
const int N = 10*100'000'000;

int *InitializeMatrix() {
	int *Matrix = new int[N];
	int i = 0;
#pragma omp parallel private(i)
	{
#pragma omp for
		for (i = 0; i < N; i++)
			Matrix[i] = rand() % 400;
	}
	return Matrix;
}

int main(int arg,char *argv[])
{
	srand((unsigned)time(NULL));
	int *A = InitializeMatrix();
	int *B = InitializeMatrix();
	int *C = new int[N];
	long long total = 0;
	//lab parallel 3 variant
	long time1 = clock();
#pragma omp parallel
	{
#pragma omp for reduction(+:total)
		for (int i = 0; i < N; i++)
		{
			
			if (A[i] < B[i]) {
				C[i] = B[i];
				total += C[i];
			}
			else {
				C[i] = A[i];
				total += C[i];
			}
		}					
	}
	long time2 = clock();

	long long total2 = 0;
	delete[] C;
	int *F = new int[N];

	//lab normal
	long time3 = clock();
	for (int i = 0; i < N; i++)
	{
		if (A[i] < B[i]) {
			F[i] = B[i];
			total2 += F[i];
		}
		else {
			F[i] = A[i];
			total2 += F[i];
		}
	}
	long time4 = clock();

	cout << " time parallel it by " << ((double) (time2 - time1)) / CLOCKS_PER_SEC << " Total : " << total << endl;
	cout << " time normal it by " << (double) (time4 - time3) / CLOCKS_PER_SEC << " Total : " << total2 << endl;
	//cout << "total = " << total << endl;
	std::cout << std::boolalpha << (total == total2) << '\n';
	delete[] F;
	delete[] A;
	delete[] B;
	system("pause");
    return 0;
}

/*
#include <omp.h>
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
srand((unsigned)time(NULL));
int N = 2;
cout << "input N ";
cin >> N;
int *A = new int[N], *B = new int[N], *C = new int[N];

for (int i = 0; i < N; i++) {
A[i] = rand() % 100;
B[i] = rand() % 100;
C[i] = rand() % 100;
}

//for (int i = 0; i < N; i++) {
//	cout << A[i] << " " << B[i] << " " << C[i] << endl;
//}
long long total = 1;

//start parallel
long time1 = clock();

//lab parallel
#pragma omp parallel
{
#pragma omp for reduction(*:total)
for (int i = 0; i < N; i++) {
if (A[i] % 2 == 0) {
if (B[i] != 0 && C[i] != 0 && (B[i] / C[i]) != 0) {
total *= B[i] / C[i];
}
}
else {
if ((B[i] + A[i]) != 0) {
total *= (B[i] + A[i]);
}
}
}
}

//finish parallel
long time2 = clock();

total = 1;

//start normal
long time3 = clock();

//lab normal
for (int i = 0; i < N; i++) {
if (A[i] % 2 == 0) {
if (B[i] != 0 && C[i] != 0 && (B[i] / C[i]) != 0) {
total *= B[i] / C[i];
}
}
else {
if ((B[i] + A[i]) != 0) {
total *= (B[i] + A[i]);
}
}
}

//finish normal
long time4 = clock();

cout << " time parallel " << (time2 - time1) << endl;
cout << " time normal " << (time4 - time3) << endl;
//cout << "total = " << total << endl;
system("pause");
}
*/