#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

template<int m, int n>
struct mat { double x[m][n]; };

// Returns an m-by-m identity matrix. Not used.
template<int m>
mat<m,m> identity() {
	
	mat<m,m> identity;
	for(int row = 0; row < m; row++)
		for(int col = 0; col < m; col++)
			identity.x[row][col] = ((row == col) ? 1: 0);	// 1 if along the diagonal; otherwise, 0
			
	return identity;
}

// Outputs the values of an m-by-n matrix. Not used within the program.
template<int m, int n>
void print(const mat<m,n>& u) {
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++) {
			printf("| %0.10f %0.10f %0.10f|\n", u.x[i][j], u.x[i][j], u.x[i][j]);
		}
		printf("\n");
	}
}

// Matrix-vector multiplication: [m,n] * [n]
template<int m, int n>
vec<n> operator*(const mat<m,n>& M, const vec<n>& u) {

	vec<n> w;
	
	// Initialize vector
	for(int i = 0; i < n; i++) w.x[i] = 0;
	
	for(int row = 0; row < m; row++)
		for(int col = 0; col < n; col++)
			w.x[row] += M.x[row][col] * u.x[col];
	
	return w;

}	

// Finds the first row containing a non-zero element in the specified column. Returns -1 otherwise
template<int m, int n>
int getPivotRow(const mat<m,n>& u, const int col) {
	for(int row = col; row < m; row++)
		if(u.x[row][col] != 0) return row;
	return -1;
}

template<int m, int n>
void normalizeRow(mat<m,n>& u, int row, double val) {
	
	for(int col = 0; col < n; col++)
		u.x[row][col] /= val;
	
}

template<int m, int n>
void swapRows(mat<m,n>& u, int row1, int row2) {
	
	vec<n> temp;
	for(int col = 0; col < m; col++){
		temp.x[col] = u.x[row1][col];
		u.x[row1][col] = u.x[row2][col];
		u.x[row2][col] = temp.x[col];
	}
}
	
template<int m, int n>
void reduceRow(mat<m,n>& u, int pivotRow, int row, double val) {
	for(int col = 0; col < n; col++)
		u.x[row][col] = u.x[pivotRow][col] * val - u.x[row][col];
}

// Calculates the inverse of the matrix u by augmenting u with I and performing Gaussian Elimination.
template<int m>
mat<m,m> inverse(const mat<m,m>& u) {
	
	mat<m,2*m> w;
	
	// Copy u into the left half matrix w 
	for(int row = 0; row < m; row++)
		for(int col = 0; col < m; col++)
			w.x[row][col] = u.x[row][col];
	
	// Augment matrix w with the identity matrix
	for(int row = 0; row < m; row++)
		for(int col = m; col < 2*m; col++)
			w.x[row][col] = ((row == col - m) ? 1: 0);
	
	// For each row in w
	for(int row = 0; row < m; row++) {
		
		int pivotRow = getPivotRow(w, row);
		
		// If the current row is not the pivot row, then swap rows.
		if(row != pivotRow) swapRows(w, row, pivotRow);
		
		// Normalize the current row
		normalizeRow(w, row, w.x[row][row]);
		
		// Reduce each row in the matrix not the current row
		for(int j = 0; j < m; j++)
			if(j != row) reduceRow(w, row, j, w.x[j][row]);
	}
	
	// Normalize each row
	for(int i = 0; i < m; i++) normalizeRow(w, i, w.x[i][i]);
	
	// Copy the augmented half the matrix
	mat<m,m> inv;
	for(int row = 0; row < m; row++)
		for(int col = m; col < 2*m; col++)
			inv.x[row][col-m] = w.x[row][col];
		
	return inv;
	
}

#endif