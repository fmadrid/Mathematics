#ifndef CALCULUS_H
#define CALCULUS_H

#include <iostream>
#include <functional>
#include "matrix.h"
#include "vector.h"

#define MAX_ITERATIONS 50
#define TOLERANCE 1e-10
template<int n>
vec<n> newton(vec<n> (*g)(const vec<n>&), const vec<n>& x0, mat<n,n> (*dg)(const vec<n>&)) {
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

template<int n>
vec<n> newton(std::function<vec<n>(const vec<n>&)> &g, const vec<n>& x0, std::function<mat<n,n>(const vec<n>&)> &dg) {
	
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


double finitePoisson(std::function<vec<n>(const vec<2>&)> &ddg, std::function<vec<2>(const vec<2>&)> &phi, const vec<2>& x0, double h, int stepCount) {
	
	vec<2> x = x0;
	double sum = 0.0;
	for(int i = 0; i < stepCount; i++)
		for(int j = 0; j < stepCount; i++) {
			vec<2> delta = {i,j};
			sum += dot(ddg(x0 + delta * stepSize), phi(x0 + delta * stepSize));
		}
		
	return sum;
}

#endif