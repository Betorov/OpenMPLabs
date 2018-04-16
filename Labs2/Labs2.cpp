// Labs2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

const int NMAX = 60000; 
const int LIMIT = 50000;
int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	int i, j;  
	float sum;   
	float **a = new float*[NMAX];
	for (int i = 0; i < NMAX; i++)
		a[i] = new float[NMAX];
	for (i = 0; i < NMAX; i++)    
		for (j = 0; j < NMAX; j++)     
			a[i][j] = i + j;
	double times = clock();
#pragma omp parallel shared(a) if (NMAX>LIMIT) 
	{    
#pragma omp for private(sum)      
		for ( int i=0; i < NMAX; i++)     
		{      
			sum = 0;       
			for (int j=0; j < NMAX; j++)       
				sum += a[i][j];            
		}  
	}
	std::cout << clock() - times;
	/* Завершение параллельного фрагмента */
	system("pause");
    return 0;
}

