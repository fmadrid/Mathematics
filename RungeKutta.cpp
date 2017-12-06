#include <iostream>
#include <cstdio>
#include <cmath>

#include "matrix.h"
#include "vector.h"

double df(double t, double y) {
    return 3 * t * t * y;
}

vec<2> rungeKutta(double (*dg)(double, double), vec<2> u, double h) {

	double t = u.x[0];
	double y = u.x[1];
	
	double k1 = dg(t,y);
	double k2 = dg(t + h/2, y + h/2 * k1);
	double k3 = dg(t + h/2, y + h/2 * k2);
	double k4 = dg(t + h  , y + h   * k3);
	
	vec<2> v = {x + h, y + h/6 * (k1 + 2*k2 + 2*k3 + k4)}; 
	
	return v;
}

int main() {
    
	vec<2> x0 = {1,2};
	double h = 0.1;
	vec<2> x = rungeKutta(df, x0, h);

	std::cout << x.x[1] << std::endl;

	return 0;
}
