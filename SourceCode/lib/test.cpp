#include <iostream>
#include "BigInteger.h"

int main() {
	
	BigInteger a(2);
	BigInteger b = power(a,7);
	
	std::cout << a << " * " << b << "\n";
	
	return 0;
	
}