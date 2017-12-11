#ifndef VECTOR_H
#define VECTOR_H

#include <iomanip>
#include <string>
#include <sstream>

template<int n>
struct vec {

	double x[n];

	std::string toString() {
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

#endif