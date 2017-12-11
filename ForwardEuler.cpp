#include <iostream>
#include <cstdio>
#include <cmath>

#include "matrix.h"
#include "vector.h"

vec<2> f(double t) {

	vec<2> u;
	u.x[0] = exp(2*t);
	u.x[1] = 3*exp(t);
	
	return u;		
}

vec<2> df(const vec<2>& u) {
	
	double x = u.x[0];
	double y = u.x[1];
	
	vec<2> v;
	v.x[0] = 2*x;
	v.x[1] = y;
	
	return v;
}

template<int n>
vec<n> forwardEuler(vec<n> (*dg)(const vec<n>&), const vec<n>& t0, double deltaT, int stepCount) {
	
	vec<2> t = t0;
	for(int i = 1; i <= stepCount; i++)
		t = t + deltaT * dg(t);
	
    return t;
}

int main() {
	
	float  ti        = 0;
	vec<2> t0        = f(ti);
	double deltaT    = 0.0125;
	int    stepCount = 320;
	
	vec<2> predicted = forwardEuler(df, t0, deltaT, stepCount);
	vec<2> actual = f(ti + deltaT * stepCount);
	
	double error = magnitude(predicted - actual);
	
	std::cout << "Actual:       " << actual.toString()    << "\n";
	std::cout << "Experimental: " << predicted.toString() << "\n";
	
	printf("Error: %0.10f\n", error);
	
	return 0;
}
