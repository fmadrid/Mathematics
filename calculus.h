#ifndef CALCULUS_H
#define CALCULUS_H

#include <iostream>
#include <functional>
#include "matrix.h"
#include "vector.h"

template<int n>
vec<n> newton(std::function<vec<n>(const vec<n>&)> &g, const vec<n>& x0, std::function<mat<n,n>(const vec<n>&)> &dg, int MAX_ITERATIONS = 50, double TOLERANCE = 1e-10) {
	
	vec<n> x = x0;
	vec<n> delta;
	
	int iterations = 0;
	do {
		delta = (inverse(dg(x)) * g(x));
		x = x - delta;
		
		if(++iterations >= MAX_ITERATIONS) {
			std::cout << "[NEWTON] Warning: Reached MAXIMUM_ITERATIONS. delta = " << delta.toString() << "\n";
			break;
		}
		
	} while( !(delta < TOLERANCE));
	
    return x;
}


#endif