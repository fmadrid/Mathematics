
#include <iostream>
#include <functional>
#include "matrix.h"
#include "vector.h"

double g(double x) { return -10 * (x*x + 10); }

double f(double x, double y) { return -10 * (x*x + y*y + 10); }

// TO-DO: Unit Test
template<int n>
vec<n> poisson1D(std::function<double(double)> g, double h, const vec<1>& t0) {

	mat<n,n> A;
		
	// Diagonal
	for(int c = 1; c < n; c++) if(c % n != 0) A.x[c-1][c] = -1;
	for(int r = 0; r < n; r++) A.x[r][r] =  2;
	for(int r = 1; r < n; r++) if(r % n != 0) A.x[r][r-1] = -1;

	vec<n> b;
	for(int i = 0; i < n; i++)
		b.x[i] = -(h) * g(t0.x[0] + i * h);

	return inverse(A) * b;
}

// TO-DO: Unit Test
template<int n>
mat<n,n> poisson2D(std::function<double(double,double)> g, double h, const vec<2>& t0) {

	mat<n*n,n*n> A;
		
	// Diagonal
	for(int c = 1; c < n*n; c++) if(c % n != 0) A.x[c-1][c] = -1;
	for(int r = 0; r < n*n; r++) A.x[r][r] =  4;
	for(int r = 1; r < n*n; r++) if(r % n != 0) A.x[r][r-1] = -1;

	// -I
	for(int c = n; c < n*n; c++) A.x[c-n][c] = -1;
	for(int r = n; r < n*n; r++) A.x[r][r-n] = -1;

	vec<n*n> b;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			b.x[i * n + j] = -(h * h) * g(t0.x[0] + j * h, t0.x[1] + i * h);

	vec<n*n> u = inverse(A) * b;

  // Un-collapse u into M
	mat<n,n> M;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			M.x[i][j] = u.x[i * n + j];
		
	return M;
}

int main() {

	double h = 1;
	vec<1> t1 = {1};
	vec<2> p1D = poisson1D<2>(g, h, t1);
	
	vec<2> t2 = {1,1};
	mat<2,2> p2D = poisson2D<2>(f, h, t2);

	std::cout << p1D << "\n"; // Unconfirmed
	std::cout << p2D << "\n"; // Confirmed in MatLab
	return 0;
}
