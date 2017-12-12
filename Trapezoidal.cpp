#include <iostream>
#include <cstdio>
#include <cmath>
#include <functional>

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
vec<2> dg(const vec<2>& u) {
	
	double x = u.x[0];
	double y = u.x[1];
	
	vec<2> v;
	v.x[0] = 1;
	v.x[1] = -3*x*x*y;
	
	return v;
}

mat<2,2> ddg(const vec<2>& u) {
	double x = u.x[0];
	double y = u.x[1];
	
	mat<2,2> M;
	M.x[0][0] = 0;      M.x[0][1] = 0;
	M.x[1][0] = -6*x*y; M.x[1][1] = -3*x*x;

	return M;
}

template<int n>
std::function<vec<n>(const vec<n>&)> genF(const vec<n>& u, double deltaT, vec<n> (*dg)(const vec<n>&)) {
	
	auto f = [&u, &deltaT, &dg](const vec<n>& w) -> vec<n> {
			vec<n> v;
			v = w - u - (deltaT / 2) * (dg(w) + dg(u));
			return v;
		};
		
	return f;
}

template<int n>
std::function<mat<n,n>(const vec<n>&)> genDF(double deltaT, mat<n,n> (*dg)(const vec<n>&)) {
	
	auto df = [&deltaT, &dg](const vec<n>& w) -> mat<n,n> {
			mat<n,n> M;
			for(int row = 0; row < n; row++)
				for(int col = 0; col < n; col++)
					M.x[row][col] = ((row == col) ? 1: 0);
            
			M = M - (deltaT / 2) * dg(w);
			return M;
		};
		
	return df;
}

template<int n>
vec<n> newton(std::function<vec<n>(const vec<n>&)> &g, std::function<mat<n,n>(const vec<n>&)> &dg, const vec<n>& x0, double tol) {
	vec<n> x = x0;
	vec<n> delta;
	do {
		delta = (inverse(dg(x)) * g(x));
		x = x - delta;
	} while( !(delta < tol));
	
    return x;
}

template<int n>
vec<n> trapezoidal(vec<n> (*dg)(const vec<n>&), const vec<n>& u0, double deltaT, int stepCount) {
	
	vec<n> u = u0;
	for(int i = 0; i < stepCount; i++){
		
		auto f = genF(u,deltaT, dg);
		auto df = genDF(deltaT, ddg);
		
		vec<n> u_n = newton(f, df, u + deltaT * dg(u), 1e-6);
		
		/*
		vec<n> x = x0;
		vec<n> delta;
		do {
			delta = (inverse(dg(x)) * g(x));
			x = x - delta;
		} while( !(delta < tol));
	*/
	
	}
    return u;
}

int main() {
	
	vec<2> ex = trapezoidal(dg, {0,1}, 0.1, 5);
	std::cout << "Experimental: " << ex.toString() << "\n";
	return 0;
}
