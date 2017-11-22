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
		oss << std::setprecision(10) << x[0] << " " << x[1] << " " << x[2];
		return oss.str();
	}
	
};

// Vector subtraction
vec<3> operator-(const vec<3>& u, const vec<3>& v) {
	
	vec<3> w;
	for(int i = 0; i < 3; i++)
		w.x[i] = u.x[i] - v.x[i];
	
	return w;
}

#endif