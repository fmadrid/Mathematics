#include <iostream>
#include <cstdio>
#include <cmath>

#include "matrix.h"
#include "vector.h"

double f(double y) {
	double val = exp(y);	//f(x,y) = e^y
	return val;		
}

double df(const vec<2>& u) {
	double y = u.x[1];
	double val = y;	// f'(x,y) = y
	return val;
}

template<int n>
vec<n> forwardEuler(double (*dg)(const vec<n>&), const vec<n>& x0, double t, double h) {
	
	vec<2> x = x0;
	int stepCount = t / h;
	for(int i = x0.x[0]; i < stepCount; i++)
		x.x[1] = x.x[1] + h * dg(x); 
    return x;
}

int main() {
	
	vec<2> t0 = {0,1};
	double t = 4;
	double h = 0.001;
	vec<2> tn = forwardEuler(df, t0, t, h);
	
	
	double error = abs(tn.x[1] - f(t));
	printf("Error: %0.10f\n", error);
	
	return 0;
}
