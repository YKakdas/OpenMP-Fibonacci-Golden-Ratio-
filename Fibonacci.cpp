/*
  Yasar Can Kakdas

  I have changed classic fibonacci implementation a little bit to reduce the computation time.
  fibonacci(n-1) is already calculated while finding the fibonacci(n). That's why I returned fibonacci(n) and
  fibonacci(n-1) together as a pair to calculate the golden ratio with only 1 recursive call.

  Example Running Instructions:

  compiling: g++.exe -o fibonacci -fopenmp Fibonacci.cpp
  running: .\fibonacci.exe 25

*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <iomanip>

std::pair<int, int> fib(int n)
{
	std::pair<int, int> i, j;
	if (n < 2)
	{
		return std::make_pair(n - 1, n);
	}

	else
	{
#pragma omp task shared(i) firstprivate(n)
		i = fib(n - 1);

#pragma omp task shared(j) firstprivate(n)
		j = fib(n - 2);

#pragma omp taskwait
		return  std::pair<int, int>(i.second, i.second + j.second);
	}
}

int main(int argc, char** argv)
{
	int n = std::atoi(argv[1]);
	omp_set_num_threads(8);

#pragma omp parallel shared(n)
	{
#pragma omp single
		{
			std::pair<int, int> result = fib(n);
			std::cout << n - 1 << ". fibonacci number is " << result.first << std::endl;
			std::cout << n << ". fibonacci number is " << result.second << std::endl;
			std::cout << "Golden ratio is: " << std::setprecision(10) << (double)result.second / (double)result.first << std::endl;
		}
	}
}