#include <iostream>

#include "matrix.h"
#include "ODE.h"
#include "vector.h"

vec<3> f(const vec<3>& u) {
	
    double x = u.x[0], y = u.x[1], z = u.x[2];
	
    vec<3> w;
    w.x[0] = -2*x*z + 2*x -4;
    w.x[1] = -4*y*z + 2*y - 6;
    w.x[2] = -x*x - 2*y*y + 1;
	
    return w;
}

mat<3,3> df(const vec<3>& u) {
	double x = u.x[0], y = u.x[1], z = u.x[2];
	
	mat<3,3> w;
	w.x[0][0] = -2*z + 2; w.x[0][1] = 0;        w.x[0][2] = -2*x; 
	w.x[1][0] = 0;        w.x[1][1] = -4*z + 2; w.x[1][2] = -4*y;
	w.x[2][0] = -2*x;     w.x[2][1] = -4*y;     w.x[2][2] = 0;
	
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