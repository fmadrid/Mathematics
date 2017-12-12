#include <iostream>
#include <cstdio>
#include <cmath>

#include "matrix.h"
#include "vector.h"


// F'(x,y,z) = [1; -2xz + 3y^2; -3(1-y)z^2
vec<3> f(const vec<3>& u) {
	
	double x = u.x[0];
	double y = u.x[1];
	double z = u.x[2];
	
	vec<3> v;
	v.x[0] = 1;
	v.x[1] = -2*x*z + 3*y*y;
	v.x[2] = -3*z*z*(1-y);
	
	return v;
}

// F'(x,y) = [1; -3yx^2]
vec<2> g(const vec<2>& u) {
	
	double x = u.x[0];
	double y = u.x[1];
	
	vec<2> v;
	v.x[0] = 1;
	v.x[1] = -3*x*x*y;
	
	return v;
}

vec<2> h(const vec<2>& u, const vec<2>& u_n, double stepSize) {
	
	vec<2> v = u - u_n - (stepSize / 2) * (dg(u) + dg(u_n));
	return v;	
}

mat<2,2> dh(const vec<2>& u) {
	
	mat<2,2> m = identity(2) - 
	
	
}

template<int n>
vec<n> trapezoidal(vec<n> (*dg)(const vec<n>&), const vec<n>& u0, double deltaT, int stepCount) {
	
	vec<n> u = u0;
	for(int i = 0; i < stepCount; i++){
		
		
		vec<n> x = x0;
		vec<n> delta;
		do {
			delta = (inverse(dg(x)) * g(x));
			x = x - delta;
		} while( !(delta < tol));
	
	}
    return u;
}

int main() {
	
	vec<3> f = forwardEuler(df, {0,-1,2}, 0.1, 2);
	vec<2> g = forwardEuler(dg, {0,1}, 0.1, 5);
	std::cout << "Experimental: " << f.toString() << "\n";
	std::cout << "Experimental: " << g.toString() << "\n";
	return 0;
}
