// Labs4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


using namespace std;
const int NMAX = 100'000'00; //Больше не стоит лол кек чебурек

int main() {

	srand(time(NULL));
	setlocale(LC_ALL, "Rus");

	
	int *a = new int[NMAX];
	int *b = new int[NMAX];
	int *c = new int[NMAX];
	for (int i = 0; i < NMAX; i++)
	{
		a[i] = rand() % 100;
		b[i] = rand() % 100;
		c[i] = rand() % 100;
	}

	//CriticalSection
	int total = 0;
	int i = 0;
	double t3 = clock();
#pragma omp parallel shared(a, b, c,total) private(i) 
	{
#pragma omp for
		for (i = 0; i < NMAX; i++)
		{
			if (a[i] < b[i]) {
				c[i] = b[i];		
			}
			else {
				c[i] = a[i];
			}
#pragma omp critical
				total += c[i];
		}
	}
	cout << "Sum of Values" << "\n" << total << "\n";
	double t4 = clock();
	cout << "Time with critical section" << "\n" << (t4 - t3) / CLOCKS_PER_SEC << "\n";

	//Reduction
	long time1 = clock();
	i = 0; total = 0;
#pragma omp parallel
	{
#pragma omp for reduction(+:total)
		for (i = 0; i < NMAX; i++)
		{

			if (a[i] < b[i]) {
				c[i] = b[i];
				total += c[i];
			}
			else {
				c[i] = a[i];
				total += c[i];
			}
		}
	}
	long time2 = clock();
	cout << "Sum of Values" << "\n" << total << "\n";
	cout << "Time with reduction" << "\n" << ((double)(time2 - time1)) / CLOCKS_PER_SEC << "\n";

	//Atomic
	time1 = clock();
	i = 0;
	total = 0;
#pragma omp parallel shared(total) private (i)
	{
#pragma omp for
		for (i = 0; i < NMAX; i++)
		{

			if (a[i] < b[i]) {
				c[i] = b[i];
			}
			else {
				c[i] = a[i];
			}
#pragma omp atomic
			total += c[i];
		}
	}
	
	time2 = clock();
	cout << "Sum of Values" << "\n" << total << "\n";
	cout << "Time with atomic" << "\n" << ((double)(time2 - time1)) / CLOCKS_PER_SEC << "\n";

	//without OpenMP
	time1 = clock();
	i = 0;
	total = 0;
	for (i = 0; i < NMAX; i++)
	{

		if (a[i] < b[i]) {
			c[i] = b[i];
			total += c[i];
		}
		else {
			c[i] = a[i];
			total += c[i];
		}
	}
	time2 = clock();
	cout << "Sum of Values" << "\n" << total << "\n";
	cout << "Time withoutOpenMP" << "\n" << ((double)(time2 - time1)) / CLOCKS_PER_SEC << "\n";
	return 0;
}






