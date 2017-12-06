#include <iostream>
#include <cstdio>
#include <cmath>

#include "../matrix.h"
#include "../vector.h"

#define DEBUG true


template<int n>
vec<n> conjugateGradient(mat<n,n> M, vec<n> b, vec<n> x0) {

	vec<n> r = b - M * x0;
	
	float a = (transpose(r) * r).toFloat() / (transpose(r) * M * r).toFloat();
	std::cout << (M*x0).toString() << std::endl;
	return r;
	
}

int main() {
    
    mat<2,2> M;
	M.x[0][0] = 4;	M.x[0][1] = 1;
	M.x[1][0] = 1;	M.x[1][1] = 3;
	vec<2> b = {1,2};
	vec<2> x0 = {2,1};
	vec<2> x = conjugateGradient(M, b, x0);
	
	std::cout << x.toString() << std::endl;

    return 0;
}
