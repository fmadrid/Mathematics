#ifndef PRIMES_H
#define PRIMES_H
#include<algorithm>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <climits>

using std::map;
using std::vector;

// Returns a list of primes from 2..n
vector<int> simpleSieve(long long n) {
	
  const long long SIZE = n + 1;
  bool* isPrime = new bool[SIZE];
  
  for(long long i = 0; i < SIZE; i++) isPrime[i] = true;

  for(long long i = 2; i < SIZE; i++) {
	 if(!isPrime[i]) continue;
    int m = 2;
    while(m*i <= SIZE) isPrime[(m++)*i] = false;
  }

  vector<int> primes;
  for(long long i = 2; i <= SIZE; i++)
    if(isPrime[i]) primes.push_back(i);

  delete isPrime;

  return primes;

}

// Returns the nth prime using a segmented sieve checking ranges with
// a length of SIZE
vector<int> firstPrimes (int n, const int SIZE = 1000) {

  // Initialize our prime list by performing a simpleSieve
	vector<int> primes = simpleSieve(SIZE);
	
	bool* isPrime = new bool[SIZE];
	
	// Indicates the numerical integer represented by isPrime[0] and 
	// isPrime[SIZE-1]
	int iteration = 1;
	long long lValue, rValue;	
	
	// For each subsequence (i.e. [1,sqrt(n)], [sqrt(n)+1,2*sqrt(n)], ...)
	while(primes.size() < n) {
		
		for(int i = 0; i < SIZE; i++) isPrime[i] = true;
		
		lValue = iteration * SIZE;
		rValue = (iteration + 1) * SIZE - 1;
		//std::cout << lValue << "->" << rValue <<"\n";
		// For each prime up to sqrt(maxValue of the array)
		for(int p : primes) {
			//std::cout << "Checking: " << p << "\n";
			if(p > sqrt(rValue)) break;
			
			int m = ceil(lValue / p);
			while(m * p <= rValue) {
				//std::cout << "\tCrossing: " << (m+1) * p << "\n";
				isPrime[(m++) * p - lValue] = false;
			}
		}
		
		for(int i = 0; i < SIZE; i++)
			if(isPrime[i]) primes.push_back(i + lValue);
		
		iteration++;
	} ;
	
	delete[] isPrime;
	
	return primes;
	
}


vector<int> primesUpTo(int n, const int SIZE = 1000) {

	// Initialize our prime list by performing a simpleSieve
	vector<int> primes = simpleSieve(SIZE);
	
	bool* isPrime = new bool[SIZE];
	
	// Indicates the numerical integer represented by isPrime[0] and 
	// isPrime[SIZE-1]
	int iteration = 1;
	long long lValue, rValue;	
	
	// For each subsequence (i.e. [1,sqrt(n)], [sqrt(n)+1,2*sqrt(n)], ...)
	while(primes.size() < n) {
		
		for(int i = 0; i < SIZE; i++) isPrime[i] = true;
		
		lValue = iteration * SIZE;
		rValue = (iteration + 1) * SIZE - 1;
		//std::cout << lValue << "->" << rValue <<"\n";
		// For each prime up to sqrt(maxValue of the array)
		for(int p : primes) {
			//std::cout << "Checking: " << p << "\n";
			if(p > sqrt(rValue)) break;
			
			int m = ceil(lValue / p);
			while(m * p <= rValue) {
				//std::cout << "\tCrossing: " << (m+1) * p << "\n";
				isPrime[(m++) * p - lValue] = false;
			}
		}
		
		for(int i = 0; i < SIZE; i++)
			if(isPrime[i]) primes.push_back(i + lValue);
		
		iteration++;
	} ;
	
	delete[] isPrime;
	
	return primes;
	
}

// A memory-efficient implementation of the Sieve of Eratosthenes which
// finds primes within a range of sqrt(n) elements at a time
vector<int> segmentedSieve(const long long n) {
	
	// Initialize our prime list by performing a simpleSieve
	vector<int> primes = simpleSieve(sqrt(n));
	
	// Analyze subesequences of sqrt(n) elements
	const int SIZE = sqrt(n);
	
	bool* isPrime = new bool[SIZE];
	
	// Indicates the numerical integer represented by isPrime[0] and 
	// isPrime[SIZE-1]
	int iteration = 1;
	int lValue, rValue;	
	
	// For each subsequence (i.e. [1,sqrt(n)], [sqrt(n)+1,2*sqrt(n)], ...)
	do {
		
		for(int i = 0; i < SIZE; i++) isPrime[i] = true;
		
		lValue = iteration * SIZE;
		rValue = (iteration + 1) * SIZE - 1;
		
		// For each prime up to sqrt(maxValue of the array)
		for(int p : primes) {
			
			if(p > sqrt(rValue)) break;
			
			int m = ceil(lValue / p);
			while(m * p < rValue) isPrime[(m++) * p - lValue] = false;
		}
		
		for(int i = 0; i < SIZE; i++)
			if(isPrime[i]) primes.push_back(i + lValue);
		
		
	} while((iteration++) * SIZE < n);
	
	delete[] isPrime;
	
	return primes;
	
}
	
vector<int> sieve(long long n) {

	if(n <= INT_MAX) return simpleSieve(n);
	else return segmentedSieve(n);
	
}

std::map<int, int> primeFactorization(long long n) {

   std::vector<int> primes = sieve(n);
   std::map<int, int> factorization;

   for(int p : primes) {
      if(n % p == 0) {
         factorization[p] = 0;
			int temp = n;
			while(temp % p == 0) {
				factorization[p]++;
				temp /= p;
			}
		}
   }

   return factorization;
}

std::map<int, int> primeFactorization(long long n, vector<int> primes) {

	std::map<int, int> factorization;

	for(int p : primes) {
		if(n % p == 0) {
			factorization[p] = 0;
			while(n % p == 0) {
				factorization[p]++;
				n /= p;
			}
		}
		
		if(n == 1) break;
	}

	return factorization;
}

long long decomposeFactorization(std::map<int,int> f) {

   long long ret = 1;

   for(auto it = f.begin(); it != f.end(); it++) {
      for(int i = 1; i <= it->second; i++)
         ret *= it->first;
   }

   return ret;
}

std::map<int, int> LCM(std::map<int,int> f1, std::map<int,int> f2) {

   for(auto it2 = f2.begin(); it2 != f2.end(); it2++) {
      auto it1 = f1.find(it2->first);
      if(it1 != f1.end()) it1->second = std::max(it1->second, it2->second);
      else f1[it2->first] = it2->second;
   }

   return f1;

}

std::map<int,int> LCM(long long a, long long b) {
   return LCM(primeFactorization(a), primeFactorization(b));
}

std::map<int, int> LCM (long long a, std::map<int,int> f2){ 
   return LCM(primeFactorization(a), f2);
}

#endif
