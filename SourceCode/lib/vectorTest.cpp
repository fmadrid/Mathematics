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

	string op;	// Operation name
	
   /////////////////////////////
   // Randomly generate values
   /////////////////////////////
   
   c = randDouble();

   for(double&x : v.x) x = randDouble();
   for(double&x : w.x) x = randDouble();
	
	temp = v;
	op = "";
	
   std::cout << "c: " << c << "\n";
   std::cout << "v: " << v << "\n";
   std::cout << "w: " << w << "\n";

	/////////////////
	// Unit Testing
	/////////////////

	double sum = 0.0;
	for(double x : v.x) sum += x * x;
	
	op = "Magnitude_Squared";
	aout << op << " " << sum << "\n";
	eout << op << " " << magnitude_squared(v);
	
	op = "Magnitude";
	aout << op << " " << std::sqrt(sum) << "\n";
	eout << op << " " << magnitude(v) << "\n";
	
	u = v;
	for(double&x : u.x) x += c;
	
	op = "Scalar-Vector: Addition (Left)"
	aout << op << " " << u << "\n";
	eout << op << " " << c + v << "\n";
	
	op = "Scalar-Vector: Addition (Right)";
	aout << op << " " << u << "\n";
	eout << op << " " << v + c << "\n";
		
	
   u = v;
	for(double&x : u.x)
	   x = c - x;
	
	op = "Scalar-Vector: Subtraction (Left)";
   aout << op << " " << u << "\n";
   eout << op << " " << c - v << "\n";
	
   for(double&x : u.x)
	   x *= -1;
	
	op = "Scalar-Vector: Subtraction (Right)";
   aout << op << " " << u << "\n";
   eout << op << " " << v - c << "\n";

   u = v;
   for(double&x : u.x)
	   x *= c;
	
	op = "Scalar-Vector: Multiplication (Left)";
   aout << op << " " << u << "\n";
	eout << op << " " << c * v << "\n";
	
	op = "Scalar-Vector: Multiplication (Right)";
   aout << op << " " << u << "\n";
   eout << op << " " << v * c << "\n";
	
   for(int i = 0; i < N; i++)
	   u.x[i] = v.x[i] + w.x[i];
	
	op = "Vector-Vector: Addition";
   aout << op << " " << u << "\n";
	eout << op << " " << v + w << "\n";
	
	op = "Vector-Vector: Compound Addition";
   aout << op << " " << u << "\n";
	eout << op << " " << (v += w) << "\n";
	
	op = "Vector-Vector: Compound Assignment";
   aout << op << " " << u << "\n";
   eout << op << " " << v << "\n";
   
   v = temp;   // Reset v

   for(int i = 0; i < N; i++)
	   u.x[i] = v.x[i] - w.x[i];
	
	op = "Vector-Vector: Subtraction";
   aout << op << " " << u << "\n";
	eout << op << " " << v - w << "\n";
	
	op = "Vector-Vector: Compound Subtraction";
   aout << op << " " << u << "\n";
	eout << op << " " << (v -= w) << "\n";  // Compound Assignment: Subtraction

   v = temp;   // Reset v

	for(int i = 0; i < N; i++)
	   u.x[i] = v.x[i] * w.x[i];
	
	op = "Vector-Vector: Multiplication (Component)";
   aout << op << " " << u << "\n";
	eout << op << " " << v * w << "\n";
	
   // Dot Product
   double sum = 0.0;
   for(int i = 0; i < N; i++)
	   sum += v.x[i] * w.x[i];
   
	op = "Vector-Vector: Dot Product";
   aout << op << " " << sum << "\n";
	eout << op << " " << dot(v,w) << "\n";
	
	op = "Vector-Vector: Dot Product (Member Function)";
   aout << op << " " << sum << "\n";
   eout << op << " " << v.dot(w) << "\n";

   eout.close();
   aout.close();

   return 0;

}
