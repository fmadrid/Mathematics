#include <iostream>
#include <cstdio>
#include <cmath>

#include "matrix.h"
#include "vector.h"


template<int n>
vec<n> conjugateGradient(mat<n,n> M, vec<n> b, vec<n> x0) {

	vec<n> x = x0;
	vec<n> r0;
	vec<n> r1 = b - M * x;
	vec<n> p = r1;

	for(int i = 0; i < n; i++){
		
		double alpha = (~r1*r1).toFloat() / (~p*M*p).toFloat();
		x = x + alpha*p;
		r0 = r1;
		r1 = r0 - alpha * M * p;
		double beta = (~r1*r1).toFloat() / (~r0*r0).toFloat();
		p = r1 + beta * p;
		
	}
	
	return x;
	
}

int main() {
    
	mat<2,2> M;
	M.x[0][0] = 4;	M.x[0][1] = 1;
	M.x[1][0] = 1;	M.x[1][1] = 3;
	vec<2> b = {1,2};
	vec<2> x0 = {0,0};
	vec<2> x = conjugateGradient(M, b, x0);

	double error = magnitude(x - inverse(M) * b);
	printf("Error: %f\n", error);

	return 0;
}
