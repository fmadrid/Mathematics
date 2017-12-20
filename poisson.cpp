
#include <iostream>
#include <functional>
#include "matrix.h"
#include "vector.h"

double g(double x) { return -10 * (x*x + 10); }

double f(double x, double y) { return -10 * (x*x + y*y + 10); }

template<int n>
vec<n> poisson1D(std::function<double(double)> g, double h, const vec<1>& t0) {

	mat<n,n> A;
		
	// Diagonal
	for(int col = 1; col < n*n; col++) if(col % n != 0) A.x[col-1][col] = -1;
	for(int row = 0; row < n*n; row++) A.x[row][row] =  2;
	for(int row = 1; row < n*n; row++) if(row % n != 0) A.x[row][row-1] = -1;

	vec<n> b;
	for(int i = 0; i < n; i++)
		b.x[i] = -(h) * g(t0.x[0] + i * h);

	return inverse(A) * b;
	
	;
}

template<int n>
mat<n,n> poisson2D(std::function<double(double,double)> g, double h, const vec<2>& t0) {

	mat<n*n,n*n> A;
		
	// Diagonal
	for(int col = 1; col < n*n; col++) if(col % n != 0) A.x[col-1][col] = -1;
	for(int row = 0; row < n*n; row++) A.x[row][row] =  4;
	for(int row = 1; row < n*n; row++) if(row % n != 0) A.x[row][row-1] = -1;

	// -I
	for(int col = n; col < n*n; col++) A.x[col-n][col] = -1;
	for(int row = n; row < n*n; row++) A.x[row][row-n] = -1;

	vec<n*n> b;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			b.x[i * n + j] = -(h * h) * g(t0.x[0] + j * h, t0.x[1] + i * h);

	vec<n*n> u = inverse(A) * b;
	
	mat<n,n> M;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			M.x[i][j] = u.x[i * n + j];
		
	return M;
}

int main() {

	double h = 1;
	vec<1> t1 = {1};
	//vec<2> p1D = poisson1D<2>(g, h, t1);
	
	vec<2> t2 = {1,1};
	mat<4,4> p2D = poisson2D<4>(f, h, t2);

	//std::cout << p1D << "\n";
	std::cout << p2D << "\n";
	return 0;
}
