#ifndef VECTOR_H
#define VECTOR_H

#include <iomanip>
#include <string>
#include <sstream>
#include<cmath>
template<int n>
struct vec {

	double x[n];

	std::string toString() const{
		std::ostringstream oss;for(int i = 0; i < n; i++)
		oss << std::fixed << std::setprecision(10) << x[i] << " ";
		return oss.str();
	}

	vec<n> normalize() {
		double mag = magnitude(x);
		for(int i = 0; i < n; i++)
			x[i] /= mag;
		return x;
	}

};

// Vector Addition
template<int n>
vec<n> operator+(const vec<n>& u, const vec<n>& v) {
	vec<n> w;
	for(int i = 0; i < n; i++)
		w.x[i] = u.x[i] + v.x[i];
	return w;
}

// Vector subtraction
template<int n>
vec<n> operator-(const vec<n>& u, const vec<n>& v) {
	vec<n> w;
	for(int i = 0; i < n; i++)
		w.x[i] = u.x[i] - v.x[i];
	return w;
}

// Constant-vector multiplication
template<int n>
vec<n> operator*(double c, const vec<n>& u) {
	vec<n> w;
	for(int i = 0; i < n; i++)
		w.x[i] = u.x[i] * c;
	return w;
}

template<int n>
double magnitude(const vec<n>& v) {
	double sum = 0.0;
	for(int i = 0; i < n; i++)
		sum += v.x[i] * v.x[i];
	return sqrt(sum);
}

template<int n>
double innerProduct(const vec<n>& v, const vec<n>&u) {
	double sum = 0.0;
	for(int i = 0; i< n; i++)
		sum += v.x[i] * u.x[i];
	return sum;
}

// Component-wise comparison. Returns true if the abs(x_i) <= tol for all x_i in vector v
template<int n>
bool operator<(const vec<n>& v, const double tol) {
	
	for(int i = 0; i < n; i++) 
		if(std::abs(v.x[i]) >= tol) return false;
	return true;
}

// Component-wise addition. Returns true if the abs(x_i) <= tol for all x_i in vector v
template<int n>
vec<n> operator+(const vec<n>& v, const double a) {
	vec<n> u;
	for(int i = 0; i < n; i++) 
		u.x[i] += a;
	return u;
}

template<int n>
double dot(const vec<n>& u, const vec<n>& v) {
	double sum = 0.0;
	for(int i = 0; i < n; i++)
		sum += u.x[0] * v.x[0];
	return sum;
#endif

