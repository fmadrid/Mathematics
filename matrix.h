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
  
  // Replaces block [x0,x0+r) x [y0,y0+c) with the contents of M
  template<int r, int c>
  mat<m,n> replaceBlock(const mat<r,c> M, int x0, int y0) {
    assert(x0 + r <- m && y0 + c <= n && x0 >= 0 && y0 >= 0);
    for(int i = 0; i < r; i++)
      for(int j = 0; j < c; j++)
        x[x0+i][y0+j] = M.x[i][j];
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& out, const mat<m,n>& M) {
    out << "[";
    for(int i = 0; i < m; i++) {
      for(int j = 0; j < n; j++) {
        out << M.x[i][j];
        if(j != n-1) out << ", ";
    }
      if(i != m-1) out <<"; ";
    }
    out << "]";

    return out;
  }
  
};

//////////////////////////////
// Matrix Operations
//////////////////////////////


// Finds the first r containing a non-zero element in the specified cumn. Returns -1 otherwise
template<int m, int n>
int getPivotRow(const mat<m,n>& u, const int c) {
    for(int r = c; r < m; r++)
        if(u.x[r][c] != 0) return r;
    return -1;
}

template<int m, int n>
void normalizeRow(mat<m,n>& u, int r, double val) {
    for(int c = 0; c < n; c++)
        u.x[r][c] /= val;
}

template<int m, int n>
void swapRows(mat<m,n>& u, int r1, int r2) {
    vec<n> temp;
    for(int c = 0; c < m; c++){
        temp.x[c] = u.x[r1][c];
        u.x[r1][c] = u.x[r2][c];
        u.x[r2][c] = temp.x[c];
    }
}
    
template<int m, int n>
void reduceRow(mat<m,n>& u, int pivotRow, int r, double val) {
    for(int c = 0; c < n; c++)
        u.x[r][c] = u.x[pivotRow][c] * val - u.x[r][c];
}

// Calculates the inverse of the matrix u by augmenting u with I and performing Gaussian Elimination.
template<int m>
mat<m,m> inverse(const mat<m,m>& u) {
    
    mat<m,2*m> w;
    
    // Copy u into the left half matrix w 
    for(int r = 0; r < m; r++)
        for(int c = 0; c < m; c++)
            w.x[r][c] = u.x[r][c];
    
    // Augment matrix w with the identity matrix
    for(int r = 0; r < m; r++)
        for(int c = m; c < 2*m; c++)
            w.x[r][c] = ((r == c - m) ? 1: 0);
    
    // For each r in w
    for(int r = 0; r < m; r++) {
        
        int pivotRow = getPivotRow(w, r);
        
        // If the current r is not the pivot r, then swap rs.
        if(r != pivotRow) swapRows(w, r, pivotRow);
        
        // Normalize the current r
        normalizeRow(w, r, w.x[r][r]);
        
        // Reduce each r in the matrix not the current r
        for(int j = 0; j < m; j++)
            if(j != r) reduceRow(w, r, j, w.x[j][r]);
    }
    
    // Normalize each r
    for(int i = 0; i < m; i++) normalizeRow(w, i, w.x[i][i]);
    
    // Copy the augmented half the matrix
    mat<m,m> inv;
    for(int r = 0; r < m; r++)
        for(int c = m; c < 2*m; c++)
            inv.x[r][c-m] = w.x[r][c];
        
    return inv;
    
}

//////////////////////////////
// Matrix-Matrix Operations
//////////////////////////////
// Addition
template<int m, int n>
mat<m,n> operator+(const mat<m,n>& M, const mat<m,n>& N) {

    mat<m,n> R;
    
    for(int r = 0; r < m; r++)
        for(int c = 0; c < n; c++)
            R.x[r][c] = M.x[r][c] + N.x[r][c];
    
    return R;

}

template<int m, int n>
mat<m,n> operator-(const mat<m,n>& M, const mat<m,n>& N) { 


    mat<m,n> R;
    
    for(int r = 0; r < m; r++)
        for(int c = 0; c < n; c++)
            R.x[r][c] = M.x[r][c] - N.x[r][c];
    
    return R;

}

template<int m, int n>
mat<m,n> operator-=(mat<m,n>& M, const mat<m,n>& N) {

    for(int r = 0; r < m; r++)
        for(int c = 0; c < n; c++)
            M.x[r][c] -= N.x[r][c];
    
    return M;

}

template<int m, int n, int p>
mat<m,p> operator*(const mat<m,n>& M, const mat<n,p> N) {
  
  mat<m,p> P;
  
  for(int r = 0; r < m; r++)
    for(int c = 0; c < p; c++)
      P.x[r][c] = 0;
    
  for(int r = 0; r < m; r++)
    for(int c = 0; c < p; c++)
      for(int i = 0; i < n; i++)
        P.x[r][c] += M.x[r][i] * N.x[i][c];
  return P;
}

//////////////////////////////
// Matrix-Scalar Operations
//////////////////////////////

template<int m, int n>
mat<m,n> operator*(double c, const mat<m,n>& M) {

    mat<m,n> N;
    
    for(int r = 0; r < m; r++)
        for(int c = 0; c < n; c++)
            N.x[r][c] = c * M.x[r][c];
    
    return N;

}  

template<int m, int n>
mat<m,n> operator*(const mat<m,n>& M, double c) { return c * M; }

//////////////////////////////
// Matrix-Vector Operations
//////////////////////////////

// Multiplication: [m,n] * [n] = [m]
template<int m, int n>
vec<m> operator*(const mat<m,n>& M, const vec<n>& u) {

    vec<m> v;
    
    // Initialize vector
    for(int i = 0; i < m; i++) v.x[i] = 0;
    
    for(int r = 0; r < m; r++)
        for(int c = 0; c < n; c++)
            v.x[r] += M.x[r][c] * u.x[c];
    
    return v;

}   

#endif
