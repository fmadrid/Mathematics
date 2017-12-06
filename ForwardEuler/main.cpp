#include <iostream>
#include <cstdio>
#include <cmath>

#include "matrix.h"
#include "vector.h"

// Create the constant vector: u = [-2zx +2x - 4; -4yz + 2y - 6; -x^2 -2y^2 + 1]
double f(const vec<2>& u) {
    
    double y = u.x[1];
    return exp(y);
	
}

// Create the constant matrix: gradient(u) = [dx[0]/dx dx[0]/dy dx[0]/dz]
//                                           [dx[1]/dx dx[1]/dy dx[1]/dz]
//                                           [dx[2]/dx dx[2]/dy dx[2]/dz]
double df(const vec<2>& u) {
    
    double y = u.x[1];
    
    return y;
}

template<int n>
vec<n> newton(vec<n> (*g)(const vec<n>&), mat<n,n> (*dg)(const vec<n>&), const vec<n>& x0, double tol) {
    vec<n> x_n0 = x0;
    for(int i = 0; i < 10; i++) {
        vec<n> x_n1 = x_n0 - (inverse(dg(x_n0)) * g(x_n0));
        x_n0 = x_n1;
    }
    
    return x_n0;
}

template<int n>
vec<n> forwardEuler(vec<n> (*dg)(const vec<n>&), const vec<n>& x0, double t, double h) {
	
	vec<n> x = x0;
	int stepCount = t / h;
	for(int i = 0; i < stepCount; i++)
		x = x + h * dg(x); 
	
    return x;
}

int main() {
	
    vec<2> t0 = {0,1};
	int t = 4;
	double h = 0.001;
    vec<2> tn = forwardEuler(df, t0, t, h);
	vec<2> y = f(t0);
	std::cout << tn.toString() << std::endl;
	std::cout << y.toString() << std::endl;	
    return 0;
}
