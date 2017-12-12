#ifndef MY_MATH_H
#define MY_MATH_H

#include "vector.h"
#include "matrix.h"

template<int n>
vec<n> newton(vec<n> (*g)(const vec<n>&), mat<n,n> (*dg)(const vec<n>&), const vec<n>& x0, double tol) {
	vec<n> x = x0;
	vec<n> delta;
	do {
		delta = (inverse(dg(x)) * g(x));
		x = x - delta;
	} while( !(delta < tol));
	
    return x;
}


#endif