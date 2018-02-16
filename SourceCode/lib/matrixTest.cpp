/* Title:         MatrixTest.cpp
 * Author:        Frank Madrid
 *
 * Description:   This program serves as a unit test to the matrix header file usingly randomly generated scalars, vectors,
 *                and matrices. Three outputs are generated:
 *                   1) Experimental (eout) - matrix header file results
 *                   2) Actual (aout) - manually calculated results
 *                   3) Test Information (cout) - SEED and randomly generated values
 *
 * Usage:         ./matrixTest FILENAME_EXP FILENAME_ACT
 *                DIFF = diff FILENAME_EXP FILENAME_ACT
 *                $DIFF = "" 
 * 
 * */

#include <iostream>  // std::cout
#include <cstdlib>   // rand, srand
#include <fstream>   // ofstream
#include <ctime>     // time

#include "matrix.h"


// Randomly generates a double between 0.0 and 1.0
double randDouble() { return (double) rand() / RAND_MAX; }

int main(int argc, char** argv) {

   // Input Verification
   if(argc < 3) {
      std::cout << "Usage: ./matrixTest FILENAME_EXP FILENAME_ACT\n";
      return 1;
   }

   // Initialization
   std::ofstream eout(argv[1]);  // Experimental
   std::ofstream aout(argv[2]);  // Actual 

   time_t      SEED = time(NULL);   // srand(SEED)
   const int   ROW = 3;             // Matrix Dimension
   const int   COL = 5;             // Matrix Dimenstion

   srand(SEED);
   std::cout << "Seed: " << SEED << "\n";

   double         c;   			// Scalar value
   mat<ROW,COL>   M,N,temp;	// Randomly generated matrix 
   vec<COL>       v;   			// Randomly generated vector
   
   mat<ROW, COL> L;   		// Temporary actual results
	vec<ROW>      u = {}; 	// Temporary actual results
	
	string op;	// Operation name
	
   /////////////////////////////
   // Randomly generate values
   /////////////////////////////

   c = randDouble();

   for(auto& row : M.x)
      for(double& x : row)
         x = randDouble();
		
	for(auto& row : N.x)
      for(double& x : row)
         x = randDouble();

   for(double& x : v.x)
      x = randDouble();

	temp = M;
	op   = "";
	
   std::cout << "c: " << c << "\n";
   std::cout << "M: " << M << "\n";
   std::cout << "v: " << v << "\n";

   /////////////////
   // Unit Testing
   /////////////////
	
	// TO-DO: mat<n,m>::getRow, mat<n,m> setRow
	// To-DO: Matrix: upperTriangular, getPivotRow, normalizeRow, swapRows, reduceRow, inverse
	// TO-DO: Matrix-Matrix Multiplication
	
	L = M;
   for(auto& row : L.x)
      for(double& x : row) 
         x += c;
		
	op = "Scalar-Matrix Addition (Component)"
   aout << op << " " << L << "\n";
	eout << op << " " << c + M << "\n";  // Left
	
	op = "Matrix-Scalar Addition (Component)"
   aout << op << " " << L << "\n";
   eout << op << " " << M + c << "\n";  // Right
	
	L = M;
   for(auto& row : L.x)
      for(double&x : row) 
         x = c - x;
		
	op = "Scalar-Matrix Subtraction (Component)"
   aout << op << " " << L << "\n";
   eout << op << " " << c - M << "\n";  // Left
	
   L = M;
   for(auto& row : L.x)
      for(double& x : row) 
         x -= c;
		
	op = "Matrix-Scalar Subtraction (Component)"
   aout << op << " " << L << "\n";
   eout << op << " " << M - c << "\n";  // Right

   L = M;
   for(auto& row : L.x)
      for(double& x : row) 
         x *= c;

	op = "Scalar-Matrix Multiplication (Component)"
   aout << op << " " << L << "\n";
	eout << op << " " << c*M << "\n";    // Left
	
	op = "Matrix-Scalar Multiplication (Component)"
   aout << op << " " << L << "\n";
   eout << op << " " << M*c << "\n";    // Right

   
	for(int i = 0; i < 3; i++) {
		vec<COL> temp = M.getRow(i);
		u.x[i] = temp.dot(v);
	}

	op = "Matrix-Vector Multiplication"
   eout << op << " " << M * v << "\n";
   aout << op << " " << u << "\n";

   for(int i = 0; i < ROW; i++) {
      vec<COL> temp = M.getRow(i);
      temp += N.getRow(i);
      L.setRow(i,temp);
   }
	
	op = "Matrix-Matrix Addition"
   aout << op << " " << L << "\n";
	eout << op << " " << M + N << "\n";
	
	op = "Matrix-Matrix Compound Addition"
   aout << op << " " << L << "\n";
	eout << op << " " << (M += N) << "\n";
   
	M = temp;
	
   for(int i = 0; i < ROW; i++) {
      vec<COL> temp = M.getRow(i);
      temp -= N.getRow(i);
      L.setRow(i,temp);
   }
	
	op = "Matrix-Matrix Subtraction"
   aout << op << " " << L << "\n";
	eout << op << " " << M - N << "\n";
	
	op = "Matrix-Matrix Compound Subtraction"
   aout << op << " " << L << "\n";
	eout << op << " " << (M -= N) << "\n";
	
	M = temp;
	
	
	
   return 0;

}
