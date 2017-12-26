/* Title:         VectorTest.cpp
 * Author:        Frank Madrid
 *
 * Description:   This program serves as a unit test for the vector header file usingly randomly generated scalars and vectors,
 *                Three outputs are generated:
 *                   1) Experimental (eout) - vector header file results
 *                   2) Actual (aout) - manually calculated results
 *                   3) Test Information (cout) - SEED and randomly generated values
 *
 * Usage:         ./vectorTest FILENAME_EXP FILENAME_ACT
 *                DIFF = diff FILENAME_EXP FILENAME_ACT
 *                $DIFF = "" 
 * 
 * */
#include <iostream>  // cout
#include <cstdlib>   // rand, srand
#include <cstdio>    // printf
#include <fstream>   // ofstream
#include <ctime>     // time

#include "vector.h"

// Randomly generates a double between 0.0 and 1.0
double randDouble() { return (double)rand() / RAND_MAX; }

int main(int argc, char** argv) {

   // Input Verification
   if(argc < 3) {
      std::cout << "Usage: ./vectorTest FILENAME_EXP FILENAME_ACT\n";
      return 1;
   }

   // Initialization
   std::ofstream eout(argv[1]);  // Experimental
   std::ofstream aout(argv[2]);  // Actual

   time_t      SEED = time(NULL);
   const int   N    = 3;

   srand(SEED);
   std::cout << "Seed: " << SEED << "\n";
   
   double c;            // Scalar value
   vec<N> v, w, temp;   // Experimental
   vec<N> u;            // Temporary actual results

   /////////////////////////////
   // Randomly generate values
   /////////////////////////////
   //
   c = randDouble();

   for(double&x : v.x)
      x = randDouble();

   for(double&x : w.x)
      x = randDouble();

   std::cout << "c: " << c << "\n";
   std::cout << "v: " << v << "\n";
   std::cout << "w: " << w << "\n";

   ///////////////////////////////
   // Vector - Scalar Operations
   ///////////////////////////////

   // Multiplication
   u = v;
   for(double&x : u.x) x *= c;
   aout << u << "\n";
   aout << u << "\n";

   eout << c*v << "\n"; // 1. Left
   eout << v*c << "\n"; // 2. Right

   // Addition
   u = v;
   for(double&x : u.x) x += c;
   aout << u << "\n";
   aout << u << "\n";

   eout << c + v << "\n";  // 3. Left
   eout << v + c << "\n";  // 4. Right

   // Subtraction
   u = v;
   for(double&x : u.x) x -= c;
   aout << u << "\n";
   eout << v - c << "\n";  // Right

   for(double&x : u.x) x *= -1;
   aout << u << "\n";
   eout << c - v << "\n";  // Left

   ///////////////////////////////
   // Vector - Vector Operations
   // ////////////////////////////
   for(double& x : w.x) x = randDouble();

   // Addition
   for(int i = 0; i < N; i++) u.x[i] = v.x[i] + w.x[i];
   aout << u << "\n";
   aout << u << "\n";
   aout << u << "\n";

   eout << v + w << "\n";     // Addition
   eout << (v += w) << "\n";  // Compound Assignment: Addition
   eout << v << "\n";         // Confirm Assignment
   
   v = temp;   // Reset v

   // Subtraction
   for(int i = 0; i < N; i++) u.x[i] = v.x[i] - w.x[i];
   aout << u << "\n";
   aout << u << "\n";
   aout << u << "\n";

   eout << v - w << "\n";     // Subtraction
   eout << (v -= w) << "\n";  // Compound Assignment: Subtraction
   eout << v << "\n";         // Confirm Assignment
   
   v = temp;   // Reset v

   // Dot Product
   double sum = 0.0;
   for(int i = 0; i < N; i++) sum += v.x[i] * w.x[i];
   aout << sum << "\n";
   aout << sum << "\n";

   eout << dot(v,w) << "\n";
   eout << v.dot(w) << "\n";

   // Component Multiplication
   eout << v * w << "\n";

   for(int i = 0; i < N; i++)
      u.x[i] = v.x[i] * w.x[i];
   
   aout << u << "\n";

   eout.close();
   aout.close();

   return 0;

}
