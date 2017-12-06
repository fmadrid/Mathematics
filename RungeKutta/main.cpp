#include <iostream>
#include <cstdio>
#include <cmath>

#include "../matrix.h"
#include "../vector.h"

#define DEBUG true

// Create the constant matrix: gradient(u) = [dx[0]/dx dx[0]/dy dx[0]/dz]
//                                           [dx[1]/dx dx[1]/dy dx[1]/dz]
//                                           [dx[2]/dx dx[2]/dy dx[2]/dz]
double df(double x, double y) {
    
    return 3 * x * x * y;
}


vec<2> rungeKutta(double (*dg)(double, double), vec<2> u, double h) {

	double x = u.x[0];
	double y = u.x[1];
	
	double k1 = dg(x,y);
	double k2 = dg(x + h/2, y + h/2 * k1);
	double k3 = dg(x + h/2, y + h/2 * k2);
	double k4 = dg(x + h  , y + h   * k3);
	
	if(DEBUG) printf("(k1, k2, k3, k4) = (%f, %f, %f, %f)\n", k1, k2, k3, k4);
	
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
