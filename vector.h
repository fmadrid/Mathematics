#ifndef VECTOR_H
#define VECTOR_H

#include <iomanip>	// std::setprecision
#include <string>	// std::string
#include <sstream>	// std:ostringstream	
#include <cmath>	// std::sqrt

template<int n>
struct vec {

	double x[n];
	friend std::ostream& operator << (std::ostream &out, const vec<n>& u) {
		out << "[";
		for(int i = 0; i < n; i++) {
			out << std::fixed << std::setprecision(10) << u.x[i];
			if(i != n-1) out << " ";
		}
		out << "]";
		return out;

	}

};


//////////////////////////////
// Vector Operations
//////////////////////////////

template<int n>
double magnitude(const vec<n>& v) { return std::sqrt(dot(v,v));}

template<int n>
double magnitude_squared(const vec<n>& v) { return dot(v,v); }

//////////////////////////////
// Vector-Vector Operations
//////////////////////////////

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
vec<n> operator-(const vec<n>& u, const vec<n>& v) {
	vec<n> w;
	for(int i = 0; i < n; i++)
		w.x[i] = u.x[i] - v.x[i];
	return w;
}

template<int n>
double dot(const vec<n>& u, const vec<n>&v) { return innerProduct(u,v); }

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

template<int n>
vec<n> operator-(const double c, const vec<n>& v) { return (-1) * c + v; }

template<int n>
vec<n> operator-(const vec<n>& v, const double c) { return (-1) * c + v; }

template<int n>
vec<n> operator*(double c, const vec<n>& u) {
	vec<n> w;
	for(int i = 0; i < n; i++)
		w.x[i] = u.x[i] * c;
	return w;
}

template<int n>
vec<n> operator*(const vec<n>& u, double c) { return c * u; }

template<int n>
double maxDistance(const vec<n>& u) {
  double max = u.x[1];
  for(int i = 2; i < n; i++)
    max = (max < u.x[i]) ? u.x[i] : max;
  return max;
}

#endif

