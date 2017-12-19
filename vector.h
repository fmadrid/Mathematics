#ifndef VECTOR_H
#define VECTOR_H

#include <iomanip>	// std::setprecision
#include <string>	// std::string
#include <sstream>	// std:ostringstream	
#include <cmath>		// std::sqrt

template<int n>
struct vec {

	double x[n];

	std::string toString() const{
		std::ostringstream oss;
		for(int i = 0; i < n; i++)
			oss << std::fixed << std::setprecision(10) << x[i] << " ";
		return oss.str();
	}

	// Should we check for mag != 0? (i.e. |mag| < epsilon)
	vec<n> normalize() {
		double mag = magnitude(x);
		for(int i = 0; i < n; i++)
			x[i] /= mag;
		return x;
	}

};


//////////////////////////////
// Vector Operations
//////////////////////////////

template<int n>
double magnitude(const vec<n>& v) {
	double sum = 0.0;
	for(int i = 0; i < n; i++)
		sum += v.x[i] * v.x[i];
	return std::sqrt(sum);
}



//////////////////////////////
// Vector-Vector Operations
//////////////////////////////

// Addition
template<int n>
vec<n> operator+(const vec<n>& u, const vec<n>& v) {
	vec<n> w;
	for(int i = 0; i < n; i++)
		w.x[i] = u.x[i] + v.x[i];
	return w;
}

template<int n>
vec<n>& operator+=(vec<n>& lhs, const vec<n>& rhs) {
	for(int i = 0; i < n; i++)
		lhs.x[i] += rhs.x[i];
	return lhs;
}
	
// Subtraction
template<int n>
vec<n> operator-(const vec<n>& u, const vec<n>& v) { return u + (-1) * v; }

template<int n>
double innerProduct(const vec<n>& u, const vec<n>&v) {
	double sum = 0.0;
	for(int i = 0; i < n; i++)
		sum += u.x[i] * v.x[i];
	return sum;
}

//////////////////////////////////////////////////
// Constant-Vector / Vector-Constant Operations
//////////////////////////////////////////////////

// Addition
template<int n>
vec<n> operator+(const double c, const vec<n>& v) {
	vec<n> u;
	for(int i = 0; i < n; i++) 
		u.x[i] += c;
	return u;
}

template<int n>
vec<n> operator+(const vec<n>& v, const double c) { return c + v; }

// Subtraction
template<int n>
vec<n> operator-(const double c, const vec<n>& v) { return (-1) * c + v; }

template<int n>
vec<n> operator-(const vec<n>& v, const double c) { return (-1) * c + v; }

// Multiplication
template<int n>
vec<n> operator*(double c, const vec<n>& u) {
	vec<n> w;
	for(int i = 0; i < n; i++)
		w.x[i] = u.x[i] * c;
	return w;
}

template<int n>
vec<n> operator*(const vec<n>& u, double c) { return c * u; }

// Component-wise comparison. Returns true if the abs(x_i) <= tol for all x_i in vector v
template<int n>
bool operator<(const vec<n>& v, const double tol) {
	
	for(int i = 0; i < n; i++) 
		if(std::abs(v.x[i]) >= tol) return false;
	return true;
}


#endif

