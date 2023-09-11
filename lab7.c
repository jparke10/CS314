#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Sum rows is of n X n matrix a
   and store in vector b  */
void sum_rows1(double *a, double *b, long n) 
{
    for (long i = 0; i < n; i++) 
    {
        b[i] = 0;
        for (long j = 0; j < n; j++) 
        {
                b[i] += a[i*n + j];
        }
    }
}

// TODO: optimize by precomputing row index

void sum_rows2(double *a, double *b, long n) 
{
    for (long i = 0; i < n; i++) 
    {
        b[i] = 0;
	long ixn = i*n;
        for (long j = 0; j < n; j++) 
        {
                b[i] += a[ixn + j];
        }
    }
}

// TODO: optimize by precomputing row index

void sum_rows3(double *a, double *b, long n) 
{
    for (long i = 0; i < n; i++) 
    {
        b[i] = 0;
        for (long j = 0; j < n; j++) 
        {
                b[i] += *(a + j);
        }
	a += n;
    }
}

// TODO: optimize b[i] memory access

void sum_rows4(double *a, double *b, long n) 
{
    for (long i = 0; i < n; i++) 
    {
	double rowSum = 0;
        b[i] = 0;
        for (long j = 0; j < n; j++) 
        {
                rowSum += a[i*n + j];
		// b[i] requires:
		// lea
		// mov (read)
		// add
		// mov (write)
        }
	b[i] = rowSum;
    }
}

int main() {
    for (size_t size = 10; size < 101; size += 10)
    {
        double M[size][size];
        double resVect[size];
        for (size_t i = 0; i < size; ++i) 
        {
                for (size_t j = 0; j < size; ++j) 
                {
                        M[i][j] = rand()/(double)RAND_MAX < 0.5 ? 0 : 1;
                }
        }

        // SUM_ROWS1:

        clock_t start = clock();

        // Do this 100,000 times to exaggerate the time taken.
        for (size_t i = 0; i < 100000; ++i) 
        {
                sum_rows1(&M[0][0], resVect, size);
        }

        clock_t end = clock();
        double totalTime1 = ((double) (end - start)) / CLOCKS_PER_SEC;

        // SUM_ROWS2:
        
        start = clock();

        // Do this 100,000 times to exaggerate the time taken.
        for (size_t i = 0; i < 100000; ++i) {
                sum_rows2(&M[0][0], resVect, size);
        }

        end = clock();
        double totalTime2 = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        // SUM_ROWS3:
        
        start = clock();

        // Do this 100,000 times to exaggerate the time taken.
        for (size_t i = 0; i < 100000; ++i) {
                sum_rows3(&M[0][0], resVect, size);
        }

        end = clock();
        double totalTime3 = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        // SUM_ROWS4:
        
        start = clock();

        // Do this 100,000 times to exaggerate the time taken.
        for (size_t i = 0; i < 100000; ++i) {
                sum_rows4(&M[0][0], resVect, size);
        }

        end = clock();
        double totalTime4 = ((double) (end - start)) / CLOCKS_PER_SEC;
        

        printf("size: %d\t", size);
        printf("sum_rows1: %f\t", totalTime1);
        printf("sum_rows2: %f\t", totalTime2);
        printf("sum_rows3: %f\t", totalTime3);
        printf("sum_rows4: %f\n", totalTime4);
	printf("\n");
    }
}
