#ifndef VECTOR_H
#define VECTOR_H

#include <iomanip>
#include <string>
#include <sstream>

template<int n>
struct vec {
    
    double x[n];
    
    // No longer used
    std::string toString() {
        std::ostringstream oss;
		for(int i = 0; i < n; i++)
			oss << std::setprecision(10) << x[i] << " ";
        return oss.str();
    }
    
	vec<n> normalize() {
		
		double mag = magnitude(x);
		double sum = 0;
		
		for(int i = 0; i < n; i++)
			x[i] /= sqrt(sum);
		
		return x;
	}
		
};

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
vec<n> operator-(int c, const vec<n>& u) {
    
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
#endif