#include <iostream>
#include <map>
#include <vector>

#include "primes.h"
using namespace std;

template<class T1, class T2>
ostream& operator<< (ostream& out, map<T1, T2> m) {
	
	for(auto it = m.begin(); it != m.end(); it++)
		out << "[" << it->first << "] -> " << it->second << '\n';
	
	return out;
}

template<class T>
ostream& operator<< (ostream& out,vector<T> v) {
	
	for(int i = 0; i < v.size(); i++) out << v[i] << ' ';
	
	return out;
}

int main() {
	
	cout << sieve(100) << "\n";
	segmentedSieve(100);
	cout << incrementalSieve(5) << "\n";
	
	cout << primeFactorization(500);
	return 0;
	
}