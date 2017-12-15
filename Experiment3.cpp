#include <iostream>

#include "matrix.h"
#include "ODE.h"
#include "vector.h"

vec<2> ddf(const vec<2>& u) {
	
    double x = u.x[0], y = u.x[1];
	
    vec<2> w;
    w.x[0] = x*x*x*x;
	w.x[1] = X*y;
	
    return w;
}

vec<2> phi(const vec<2>& u) {
	double x = u.x[0], y = u.x[1];
	
	vec<2> w;
	w.x[0] = 1;
	w.x[1] = 1;
	
	return w;
}

int main(int argc, char** argv) {
	
	if(argc < 3) printf("Usage: ./main [stepSize] [stepCount]\n");
	
	vec<3> x0        = {0.6, 0.8, -2.0};
	double stepSize  = std::stod(argv[1]);
	int    stepCount = std::stoi(argv[2]);
	
	vec<3> eTest = forwardEuler(f, x0, stepSize, stepCount);
	vec<3> bTest = backwardEuler(f, x0, stepSize, stepCount, df);
	vec<3> tTest = trapezoidal(f, x0, stepSize, stepCount, df);
	
	printf("\n---Parameters---\n");
	std::cout << "x0:        " << x0.toString() << "\n";
	std::cout << "stepSize:  " << stepSize      << "\n";
	std::cout << "stepCount: " << stepCount     << "\n";
	
	printf("\n---Results---\n");
	std::cout << "Forward Euler:      " << eTest.toString() << "\n";
	std::cout << "Backwards Euler:    " << bTest.toString() << "\n";
	std::cout << "Trapezoidal Method: " << tTest.toString();
	
}