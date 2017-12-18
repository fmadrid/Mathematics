#ifndef ODE_H
#define ODE_H

#include <iostream>

#include "calculus.h"
#include "matrix.h"
#include "vector.h"


////////////////////
// BackwardsEuler
////////////////////
template<int n>
std::function<vec<n>(const vec<n>&)> backwardEulerF(const vec<n>& u, double h, vec<n> (*g)(const vec<n>&)) {
	
	auto f = [u, h, g](const vec<n>& x) -> vec<n> {
		return x - u - h * (g(u) + g(x));
	};
		
	return f;
}

template<int n>
std::function<mat<n,n>(const vec<n>&)> backwardEulerDF(double& h, mat<n,n> (*dg)(const vec<n>&)) {
	
	auto df = [h, dg](const vec<n>& x) -> mat<n,n> {
			mat<n,n> M;
			for(int row = 0; row < n; row++)
				for(int col = 0; col < n; col++)
					M.x[row][col] = ((row == col) ? 1: 0);
		
			M = M - h * dg(x);
			
			return M;
		};
		
	return df;
}

template<int n>
vec<n> backwardEuler(vec<n> (*g)(const vec<n>&), const vec<n>& y0, double h, int stepCount, mat<n,n> (*dg)(const vec<n>&)) {
	
	vec<n> y = y0;
	for(int i = 0; i < stepCount; i++){
		auto f = backwardEulerF(y,h,g);
		auto df = backwardEulerDF(h,dg);
		y = y + h * g(newton(f, y + h * g(y), df));
	}
	
    return y;
}

////////////////////
// Trapezoidal
////////////////////
template<int n>
std::function<vec<n>(const vec<n>&)> trapezoidalF(const vec<n>& u, double h, vec<n> (*g)(const vec<n>&)) {
	
	auto f = [u, h, g](const vec<n>& x) -> vec<n> {
		return x - u - (h / 2) * (g(u) + g(x));
	};
		
	return f;
}

template<int n>
std::function<mat<n,n>(const vec<n>&)> trapezoidalDF(double& h, mat<n,n> (*dg)(const vec<n>&)) {
	
	auto df = [h, dg](const vec<n>& x) -> mat<n,n> {
			mat<n,n> M;
			for(int row = 0; row < n; row++)
				for(int col = 0; col < n; col++)
					M.x[row][col] = ((row == col) ? 1: 0);
		
			M = M - (h / 2) * dg(x);
			
			return M;
		};
		
	return df;
}

template<int n>
vec<n> trapezoidal(vec<n> (*g)(const vec<n>&), const vec<n>& y0, double h, int stepCount, mat<n,n> (*dg)(const vec<n>&)) {
	
	vec<n> y = y0;
	for(int i = 0; i < stepCount; i++){
		auto f = trapezoidalF(y,h,g);
		auto df = trapezoidalDF(h,dg);
		y = y + (h/2)*(g(y) + g(newton(f,y + h * g(y), df)));
	}
	
    return y;
}

////////////////////
// ForwardEuler
////////////////////
template<int n>
vec<n> forwardEuler(vec<n> (*g)(const vec<n>&), const vec<n>& y0, double h, int stepCount) {
	vec<n> y = y0;
	for(int i = 0; i < stepCount; i++)
		y = y + h * g(y);
    return y;
}

#endif