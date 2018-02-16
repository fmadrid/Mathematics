#include <algorithm>

// Employs the inclusion-exclusion principle to calculate the sum of the multiples of the
// elements in mult. 
// Example: sumMultiples(17, {3,5}) -> (3 + 6 + 9 + 12 + 15) + (5 + 10 + 15) - (15) = 60)
long long sumMultiples(const long long n, int* mult, int SIZE) {
	
	long long sum  = 0;
	
	for(int i = 0; i < SIZE; i++) {
		
		// Generate an array ending with 'i' 1's
		int* pArray = new int[SIZE];
		for(int j = 0; j < i; j++) pArray[j] = 0;
		for(int j = i; j < SIZE; j++) pArray[j] = 1;
		
		// Cycle through each permutation of the array
		do {
			
			int m = 1;
			for(int j = 0; j < SIZE; j++)
				if(pArray[j] == 1) {
					m *= mult[j];
					if(m > n) break;
				}
				
			if(m > n) continue;
			
			long long tempSum = m * ( (n/m) * ((n/m) + 1)) / 2;
			if(i % 2 == 1) sum += tempSum;
			else           sum -= tempSum;
			
		} while(std::next_permutation(pArray, pArray + SIZE));
		
		delete[] pArray;
	}
	
	return sum;
	
}

long long nCk(long long n, long long k) {
	
	int a,b;
	if(n-k>k) {
		a = n-k;
		b = k;
	} else {
		a = k;
		b = n-k;
	}
	
	long long result = 1;
	long long i = a+1;
	long long j = 1;
	while(i <= n && j <= b) {
		
		if(i <= n) result *= (i++);
		if(j <= b && result % j == 0) result /= (j++);
			
	}
	
	return result;
	
}