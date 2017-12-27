#include "matrix.h"
#include "vector.h"

template<int n>
vec<n> solveLinearSystem(const mat<n,n>& A, const vec<n>& b) {

   vec<n>   v = {};
   mat<n,n> U = upperTriangular(A);

   for(int i = n-1; i >= 0; i--) {
      vec<n> temp = U.getRow(i);
      v.x[i] = (b - temp.dot(v)) / M.x[i][i];
   }

   return v;

}

