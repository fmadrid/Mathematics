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

   double         c;         // Scalar value
   mat<ROW,COL>   M, temp;   // Randomly generated matrix 
   vec<COL>       v;         // Randomly generated vector
   
   mat<ROW, COL> L;   // Temporary actual results

   /////////////////////////////
   // Randomly generate values
   /////////////////////////////

   c = randDouble();

   for(auto& row : M.x)
      for(double& x : row)
         x = randDouble();

   for(double& x : v.x)
      x = randDouble();

   std::cout << "c: " << c << "\n";
   std::cout << "M: " << M << "\n";
   std::cout << "v: " << v << "\n";

   ///////////////////////////////
   // Matrix - Scalar Operations
   ///////////////////////////////

   // Multiplication
   L = M;
   for(auto& row : L.x)
      for(double& x : row) 
         x *= c;

   aout << L << "\n";
   aout << L << "\n";

   eout << c*M << "\n";    // 1. Left
   eout << M*c << "\n";    // 2. Right

   // Addition
   L = M;
   for(auto& row : L.x)
      for(double& x : row) 
         x += c;

   aout << L << "\n";
   aout << L << "\n";

   eout << c + M << "\n";  // 3. Left
   eout << M + c << "\n";  // 4. Right

   // Subtraction
   L = M;
   for(auto& row : L.x)
      for(double& x : row) 
         x -= c;

   aout << L << "\n";
   eout << M - c << "\n";  // Right

   L = M;
   for(auto& row : L.x)
      for(double&x : row) 
         x = c - x;

   aout << L << "\n";
   eout << c - M << "\n";  // Left

   ///////////////////////////////
   // Matrix - Vector Operations
   ///////////////////////////////

   // Multiplication
   eout << M * v << "\n";  // Right

   vec<ROW> u = {}; // Actual vector result

   for(int i = 0; i < 3; i++) {
      vec<COL> temp = M.getRow(i);
      u.x[i] = temp.dot(v);
   }

   aout << u << "\n";

   ///////////////////////////////
   // Matrix - Matrix Operations
   // ////////////////////////////
   
   mat<ROW,COL> N;
   for(auto& row : N.x)
      for(double& x : row)
         x = randDouble();

   // Addition
   for(int i = 0; i < ROW; i++) {
      vec<COL> temp = M.getRow(i);
      temp += N.getRow(i);
      L.setRow(i,temp);
   }
   aout << L << "\n";
   aout << L << "\n";
   aout << L << "\n";

   eout << M + N << "\n";
   eout << (M += N) << "\n";  // Compound Assignment
   eout << M << "\n";         // Confirm assignment

   // Subdtraction

   // Addition
   for(int i = 0; i < ROW; i++) {
      vec<COL> temp = M.getRow(i);
      temp -= N.getRow(i);
      L.setRow(i,temp);
   }
   aout << L << "\n";
   aout << L << "\n";
   aout << L << "\n";

   eout << M - N << "\n";
   eout << (M -= N) << "\n";  // Compound Assignment
   eout << M << "\n";         // Confirm Assignment
   return 0;

}
