
#include <iostream>
#include <functional>
#include "matrix.h"
#include "vector.h"

double g(double x) { return -10 * (x*x + 10); }

double f(double x, double y) { return -10 * (x*x + y*y + 10); }

template<int n>
void generateLaplace(mat<n,n>& A) {
	
	for(int i = 0; i < n*n; i++)
		for(int j = 0; j < n*n; j++)
			A.x[i][j] = 0;
	// Diagnoal
	for(int col = 1; col < n*n; col++) if(col % n != 0) A.x[col-1][col] = -1;
	for(int row = 0; row < n*n; row++) A.x[row][row] =  4;
	for(int row = 1; row < n*n; row++) if(row % n != 0) A.x[row][row-1] = -1;

	// -I
	for(int col = n; col < n*n; col++) A.x[col-n][col] = -1;
	for(int row = n; row < n*n; row++) A.x[row][row-n] = -1;

	return;
}

template<int n>
vec<n*n> poisson2D(std::function<double(double,double)> g, double h, const vec<n>& t0) {


	mat<n*n,n*n> A;
	generateLaplace(A);

	vec<n*n> b;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			b.x[i * n + j] = -(h * h) * g(t0.x[0] + j * h, t0.x[1] + i * h);

	std::cout << b << "\n";
	return inverse(A) * b;
}

int main() {

	double h = 1;
	vec<2> t0 = {1,1};
	vec<4> p = poisson2D(f, h, t0);

	std::cout << p;

	return 0;
}
