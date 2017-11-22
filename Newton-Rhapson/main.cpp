#include <iostream>
#include <cstdio>
#include <cmath>

#include "matrix.h"
#include "vector.h"

// Create the constant vector: u = [-2zx +2x - 4; -4yz + 2y - 6; -x^2 -2y^2 + 1]
vec<3> f(const vec<3>& u) {
	
    double x = u.x[0], y = u.x[1], z = u.x[2];
	
    vec<3> w;
    w.x[0] = -2*x*z + 2*x -4;
    w.x[1] = -4*y*z + 2*y - 6;
    w.x[2] = -x*x - 2*y*y + 1;
	
    return w;
}

// Create the constant matrix: gradient(u) = [dx[0]/dx dx[0]/dy dx[0]/dz]
//											 [dx[1]/dx dx[1]/dy dx[1]/dz]
//											 [dx[2]/dx dx[2]/dy dx[2]/dz]
mat<3,3> df(const vec<3>& u) {
	
	double x = u.x[0], y = u.x[1], z = u.x[2];
	
	mat<3,3> w;
	w.x[0][0] = -2*z + 2; w.x[0][1] = 0;        w.x[0][2] = -2*x; 
	w.x[1][0] = 0;        w.x[1][1] = -4*z + 2; w.x[1][2] = -4*y;
	w.x[2][0] = -2*x;     w.x[2][1] = -4*y;     w.x[2][2] = 0;
	
	return w;
}

template<int n>
vec<n> newton(vec<n> (*g)(const vec<n>&), mat<n,n> (*dg)(const vec<n>&), const vec<n>& x0, double tol) {
    // Use newton's method to solve g(x)=0.
    // Initial guess = x0
    // tolerance = tol
	vec<n> x_n0 = x0;
	for(int i = 0; i < 10; i++) {
		vec<n> x_n1 = x_n0 - (inverse(dg(x_n0)) * g(x_n0));
		x_n0 = x_n1;
	}
	
    return x_n0;
}

int main() {
	
    double tol = 1e-10;
    vec<3> x0 = {0.6,0.8,-2.0};
    vec<3> x = newton(f, df, x0, tol);
    vec<3> err = f(x);
    double mag = sqrt(err.x[0]*err.x[0]+err.x[1]*err.x[1]+err.x[2]*err.x[2]);

    printf("Error: %g Tolerance: %g\n",mag, tol);

    return 0;
}
