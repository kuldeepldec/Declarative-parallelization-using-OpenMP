/* openmp.cpp : This file is about declarative parallelization using OpenMP(pragma) . 
To enable open mp right click on openmp file and in C/C++ language subfolder enable openmp

*/

#include "stdafx.h"
#include<iostream>
#include<chrono>
#include<cstdio>
#include<omp.h>
#include<vector>

using namespace std;

void hello_openmp() {
	omp_set_num_threads(8);  // This will set 8 threads

	#pragma omp parallel          //it will show how many cores in the pc
	{
	#pragma omp critical           // to correctly show threads in order we have to use critical

		cout << "hello,openmp "<<omp_get_thread_num()<<"/"<<omp_get_num_threads()<<endl; // show number of threads

	}
}

void pfor() {                   // to parallelize for loop with an aray
	const int length = 1024 * 1024 * 64;
	float *a = new float[length],
		*b = new float[length],
		*c = new float[length],
		*result = new float[length];
#pragma omp parallel for            // for loop will parallelize the operation of result 
	for (int i = 0; i < length; i++) {
		result[i] = a[i] + b[i] * erff(c[i]);
		
	}
	delete [] a;
	delete[] b;
	delete[] c;
	delete[] result;

}

void sections()// to parallel compute particular part of sections in the program
{  
	#pragma omp parallel sections // header for parallel operation, if we remove the parallel keyword it will do sequential
	{ 

		#pragma omp section         //Section1 calculation
		{
				for (int i = 0; i < 1000; i++) {
					cout << i;
				}
		}
		#pragma omp section         // section2 calculation
		{
				for (int i = 0; i < 1000; i++) {
					cout << static_cast<char>('a' + (i % 26));
				}
		}

	}

}

void single_master() // using single master thread for parallelization
{
	#pragma omp parallel
	{
    # pragma omp single
		printf("Gathering input: %d\n", omp_get_thread_num());
		printf("In parallel: %d\n", omp_get_thread_num());
    #pragma omp barrier      // barrier for correct output to execute single first and master second
    #pragma omp master
		printf("Output on: %d\n", omp_get_thread_num());

	}


}

void sync() {

	printf("\nAtomic\n");
	int sum = 0;
    #pragma omp parallel for num_threads(128)      //parallel operation using 128 threads
	for (int i = 0; i < 100; i++) {
#pragma omp atomic                                 // atomic operation
		++sum;
	}
	cout << sum<<endl;

	cout << "Ordered operation";
	vector<int>square;
#pragma omp parallel for ordered                      // to order operation during parallelization
	for (int i = 0; i < 20; i++) {
		printf("%d: %d\t", omp_get_thread_num(),i);
		int j = i*i;
#pragma omp ordered
		square.push_back(j);
	}
	printf("\n");
	for (auto v : square)printf("%d\t", v);


}

void data_sharing() {
	int i = 10;
#pragma omp parallel for firstprivate(i)   //firstprivate will help in initializing value of i in the loop below
	for (int a = 0; a < 10; a++) {
		printf("thread %d i=%d\n", omp_get_thread_num(), i);
		i = 1000 + omp_get_thread_num();
	}



}


int main()
{
	//hello_openmp();
	//pfor();
	//sections();
	//single_master();
	//sync();
	data_sharing();
	system("Pause");
    return 0;
}

