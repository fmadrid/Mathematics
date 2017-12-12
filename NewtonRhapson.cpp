#include <iostream>
#include <cstdio>
#include <cmath>

#include "matrix.h"
#include "vector.h"

vec<3> f(const vec<3>& u) {
	
    double x = u.x[0], y = u.x[1], z = u.x[2];
	
    vec<3> w;
    w.x[0] = -2*x*z + 2*x -4;
    w.x[1] = -4*y*z + 2*y - 6;
    w.x[2] = -x*x - 2*y*y + 1;
	
    return w;
}

mat<3,3> df(const vec<3>& u) {
	
	double x = u.x[0], y = u.x[1], z = u.x[2];
	
	mat<3,3> w;
	w.x[0][0] = -2*z + 2; w.x[0][1] = 0;        w.x[0][2] = -2*x; 
	w.x[1][0] = 0;        w.x[1][1] = -4*z + 2; w.x[1][2] = -4*y;
	w.x[2][0] = -2*x;     w.x[2][1] = -4*y;     w.x[2][2] = 0;
	
	return w;
}



// y(t) = -3yt^2
mat<1,1> dg(const vec<1>& u) {
	
	double y = u.x[0];
	double t = 0.0;
	mat<1,1> v;
	v.x[0][0] = 2*y;
	
	return v;
}

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

int main() {
	
    double tol = 1e-10;
    vec<3> x0 = {0.6,0.8,-2.0};
    vec<3> x = newton(f, df, x0, tol);
    vec<3> err = f(x);

    printf("Error: %g Tolerance: %g\n", magnitude(err), tol);

	 vec<1> w = newton(g, dg, {0 + 0.1}, tol);
	 std::cout << w.toString() << "\n";
    return 0;
}
