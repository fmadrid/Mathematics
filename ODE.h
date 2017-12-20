/*
Author: 		Frank Madrid
Description:	Contains implementations for first-order numerical procedures for solving ordinary differential equations
              with a given initial value.
Last Edited:	12/18/2017

TO-DO:
(1) Move functions [methodname]F and [methodname]DF into function [methodname] as anonymous functions
*/

#ifndef ODE_H
#define ODE_H

#include <iostream>		// std::cout

#include "rootApprox.h"	// newton
#include "matrix.h"		// Matrix definition and associated operations
#include "vector.h"		// Vector definition and associated operations


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
    for(int i = 0; i < n; i++)
      M.x[i][i] = 1;
		
    M = M - h * dg(x);

		return M;
	};

	return df;
}

// Uses Newton's Method to find an approximation to the function f(y_{n+1}) = y_{n+1} - y_{n} - h * g(y_{n+1}) using the initial approximation (y_{n} + h * f(y_{n}))
template<int n>
vec<n> backwardEuler(vec<n> (*g)(const vec<n>&), const vec<n>& y0, double h, int stepCount, mat<n,n> (*dg)(const vec<n>&)) {

	vec<n> y = y0;
	for(int i = 0; i < stepCount; i++) {
		auto f  = backwardEulerF(y,h,g);				// Defines the function: f(y_{n+1}) = y_{n+1} - y_{n} + h * g(y_{n}) such that y_{N} = y.
		auto df = backwardEulerDF(h,dg);				// Defines the function: df(y_{n+1}) = 1 - h * f'(y_{n+1});  
		y += h * g(newton(f, y + h * g(y), df));		// Solves the function f(y_{n+1}) = 0 with initial guess y_{n+1} = y + h * g(y)
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
		y += (h/2)*(g(y) + g(newton(f,y + h * g(y), df)));
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
		y += h * g(y);
	return y;
}


////////////////////
// RungeKutta
////////////////////
template<int n>
vec<n> rungeKutta(double (*dg)(double, const vec<n>&), vec<n> u, double h, double t0) {

	vec<n> k1 = dg(t0, u);
	vec<n> k2 = dg(t0 + h/2, u + h/2 * k1);
	vec<n> k3 = dg(t0 + h/2, u + h/2 * k2);
	vec<n> k4 = dg(t0 + h  , u + h   * k3);

	return {t0 + h, u + h/6 * (k1 + 2*k2 + 2*k3 + k4)}; 
}


#endif
