#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include <iostream>
#include "vector.h"

template<int m, int n>
struct mat { 
   double x[m][n]; 

   mat() {
      for(int i = 0; i < m; i++)
         for(int j = 0; j < n; j++)
            x[i][j] = 0;
   }

   vec<n> getRow(const int& row) const {
      vec<n> v;
      for(int i = 0; i < n; i++)
         v.x[i] = x[row][i];
      return v;
   }

   void setRow(const int& row, const vec<n>& v) {
      for(int col = 0; col < n; col++)
         x[row][col] = v.x[col];
      return;
   }

};

//////////////////////////////
// Matrix Operations
//////////////////////////////

// Not unit tested
template<int n>
mat<n,n> upperTriangular(const mat<n,n>& M) {
   mat<n,n> U = M;

   for(int i = 0; i < n; i++) {
      int row = getPivotRow(U,i);
      if(row != i) swapRows(U,i,row);

      for(int j = 0; j < n; j++)
         if(i != j)
            reduceRow(U, row, j, U.x[row][i]);
   }
   return U;
}

template<int m, int n>
std::ostream& operator<<(std::ostream& out, const mat<m,n>& M) {
   out << "[";
   for(int row = 0; row < m; row++) {
      for(int col = 0; col < n; col++) {
         out << M.x[row][col];
         if(col != n-1) out << ", ";
      }
      if(row != m-1) out <<"; ";
   }
   out << "]";

   return out;
}

// Finds the first row containing a non-zero element in the specified column. Returns -1 otherwise
template<int m, int n>
int getPivotRow(const mat<m,n>& u, const int c) {
   for(int row = c; row < m; row++)
      if(u.x[row][c] != 0) return row;
   return -1;
}

template<int m, int n>
void normalizeRow(mat<m,n>& u, int row, double val) {
   for(int col = 0; col < n; col++)
      u.x[row][col] /= val;
}

template<int m, int n>
void swapRows(mat<m,n>& M, int row1, int row2) {
   vec<m> temp = M.getRow(row1);
   M.setRow(row1, M.getRow(row2));
   M.setRow(row2, temp);
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

      // If the current r is not the pivot r, then swap rs.
      if(row != pivotRow) swapRows(w, row, pivotRow);

      // Normalize the current r
      normalizeRow(w, row, w.x[row][row]);

      // Reduce each r in the matrix not the current r
      for(int j = 0; j < m; j++)
         if(j != row) reduceRow(w, row, j, w.x[j][row]);
   }

   // Normalize each r
   for(int i = 0; i < m; i++) normalizeRow(w, i, w.x[i][i]);

   // Copy the augmented half the matrix
   mat<m,m> inv;
   for(int row = 0; row < m; row++)
      for(int col = m; col < 2*m; col++)
         inv.x[row][col-m] = w.x[row][col];

   return inv;

}

//////////////////////////////
// Matrix-Scalar Operations
//////////////////////////////

// Component-wise Addition (Left)
template<int m, int n>
mat<m,n> operator+(const mat<m,n>& M, const double& c) { return c + M; }

// Component-wise Addition (Right)
template<int m, int n>
mat<m,n> operator+(const double& c, const mat<m,n>& M) {
   mat<m,n> N;
   for(int row = 0; row < m; row++)
      for(int col = 0; col < n; col++)
         N.x[row][col] = M.x[row][col] + c;
   return N;
}

// Component-wise Subtraction (Left)
template<int m, int n>
mat<m,n> operator-(const double& c, const mat<m,n>& M) {
   mat<m,n> N;
   for(int row = 0; row < m; row++)
      for(int col = 0; col < n; col++)
         N.x[row][col] = c - M.x[row][col];
   return N;
}

// Component wise Subtraction (Right)
template<int m, int n>
mat<m,n> operator-(const mat<m,n>& M, const double&c) { return M + (-1) * c; }

// Component-wise Multiplication (Left)
template<int m, int n>
mat<m,n> operator*(double c, const mat<m,n>& M) {
   mat<m,n> N;
   for(int row = 0; row < m; row++)
      for(int col = 0; col < n; col++)
         N.x[row][col] = c * M.x[row][col];
   return N;
}  

// Component-wise Multiplication (Right)
template<int m, int n>
mat<m,n> operator*(const mat<m,n>& M, double c) { return c * M; }

//////////////////////////////
// Matrix-Vector Operations
//////////////////////////////

// Multiplication: [m,n] * [n] = [m]
template<int m, int n>
vec<m> operator*(const mat<m,n>& M, const vec<n>& u) {
   vec<m> v;
   for(int row = 0; row < m; row++)
      v.x[row] = dot(M.getRow(row), u);
   return v;
}   

//////////////////////////////
// Matrix-Matrix Operations
//////////////////////////////

template<int m, int n>
mat<m,n> operator+(const mat<m,n>& M, const mat<m,n>& N) {
   mat<m,n> R;
   for(int row = 0; row < m; row++)
      for(int col = 0; col < n; col++)
         R.x[row][col] = M.x[row][col] + N.x[row][col];
   return R;
}

template<int m, int n>
mat<m,n> operator+=(mat<m,n>& lhs, const mat<m,n>& rhs) {
   for(int row = 0; row < m; row++)
      for(int col = 0; col < n; col++)
         lhs.x[row][col] += rhs.x[row][col];
   return lhs;
}

template<int m, int n>
mat<m,n> operator-(const mat<m,n>& M, const mat<m,n>& N) { 
   mat<m,n> R;
   for(int row = 0; row < m; row++)
      for(int col = 0; col < n; col++)
         R.x[row][col] = M.x[row][col] - N.x[row][col];
   return R;
}

template<int m, int n>
mat<m,n> operator-=(mat<m,n>& M, const mat<m,n>& N) {
   for(int row = 0; row < m; row++)
      for(int col = 0; col < n; col++)
         M.x[row][col] -= N.x[row][col];
   return M;
}

// Not Unit-Tested
template<int m, int n, int p>
mat<m,p> operator*(const mat<m,n>& M, const mat<n,p> N) {
   mat<m,p> P={};
   for(int row = 0; row < m; row++)
      for(int col = 0; col < p; col++)
         for(int i = 0; i < n; i++)
            P.x[row][col] += M.x[row][i] * N.x[i][col];
   return P;
}

#endif
