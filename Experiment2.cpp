#include <iostream>
#include <cmath>

#include "matrix.h"
#include "ODE.h"
#include "vector.h"

vec<2> F(const vec<2>& u) {
	double x = u.x[0];
	double y = u.x[1];
	
	vec<2> v;
	v.x[0] = x;
	v.x[1] = exp(-x * x * x);
	
	return v;
}

vec<2> f(const vec<2>& u) {
	
	double x = u.x[0];
	double y = u.x[1];
	
	vec<2> v;
	v.x[0] = 1;
	v.x[1] = -3*x*x*y;
	
	return v;
}

mat<2,2> df(const vec<2>& u) {
	
	double x = u.x[0];
	double y = u.x[1];
	
	mat<2,2> M;
	M.x[0][0] = 0;		M.x[0][1] = 0;
	M.x[1][1] = -6*x*y;	M.x[1][1] = -3*x*x;
	
	return M;
}
	
int main(int argc, char** argv) {
	
	if(argc < 3) printf("Usage: ./main [stepSize] [stepCount]\n");
	
	vec<2> x0        = {0, 1};
	double stepSize  = std::stod(argv[1]);
	int    stepCount = std::stoi(argv[2]);
	
	vec<2> eTest = forwardEuler(f, x0, stepSize, stepCount);
	vec<2> bTest = backwardEuler(f, x0, stepSize, stepCount, df);
	vec<2> tTest = trapezoidal(f, x0, stepSize, stepCount, df);
	vec<2> solution = F(x0 + stepSize*stepCount);
	
	printf("\n---Parameters---\n");
	std::cout << "x0:        " << x0.toString() << "\n";
	std::cout << "stepSize:  " << stepSize      << "\n";
	std::cout << "stepCount: " << stepCount     << "\n";
	
	printf("\n---Results---\n");
	std::cout << "Solution :          " << F(x0 + stepSize*stepCount).toString() << "\n";

	std::cout << "Forward Euler:      " << eTest.toString() << "Error: " << magnitude(eTest - solution) << "\n";
	std::cout << "Backwards Euler:    " << bTest.toString() << "Error: " << magnitude(bTest - solution) << "\n";
	std::cout << "Trapezoidal Method: " << tTest.toString() << "Error: " << magnitude(tTest - solution) << "\n";
	
	
}