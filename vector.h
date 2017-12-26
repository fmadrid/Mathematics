#ifndef VECTOR_H
#define VECTOR_H

#include <iomanip>	// std::setprecision
#include <string>	// std::string
#include <sstream>	// std:ostringstream	
#include <cmath>	// std::sqrt

template<int n>
struct vec {

   double x[n];

   double dot(const vec<n>& v) const { return dot(*this, v); }

   double dot(const vec<n>& u, const vec<n>&v) const {
      double sum = 0.0;
      for(int i = 0; i < n; i++)
         sum += u.x[i] * v.x[i];
      return sum;
   }
};


//////////////////////////////
// Vector Operations
//////////////////////////////

template<int n>
std::ostream& operator << (std::ostream &out, const vec<n>& u) {
   out << "[";
   for(int i = 0; i < n; i++) {
      out << std::fixed << std::setprecision(10) << u.x[i];
      if(i != n-1) out << " ";
   }
   out << "]";
   return out;

}
template<int n>
double magnitude(const vec<n>& v) { return std::sqrt(dot(v,v));}

template<int n>
double magnitude_squared(const vec<n>& v) { return dot(v,v); }

//////////////////////////////
// Vector-Vector Operations
//////////////////////////////

template<int n>
vec<n> operator+(const vec<n>& u, const vec<n>& v) {
   vec<n> w;
   for(int i = 0; i < n; i++)
      w.x[i] = u.x[i] + v.x[i];
   return w;
}

template<int n>
vec<n>& operator+=(vec<n>& lhs, const vec<n>& rhs) {
   for(int i = 0; i < n; i++)
      lhs.x[i] += rhs.x[i];
   return lhs;
}

// Subtraction
template<int n>
vec<n> operator-(const vec<n>& u, const vec<n>& v) {
   vec<n> w;
   for(int i = 0; i < n; i++)
      w.x[i] = u.x[i] - v.x[i];
   return w;
}

// Component-wise Multiplication
template<int n>
vec<n> operator*(const vec<n>& u, const vec<n>& v) {
   vec<n> w;
   for(int i = 0; i < n; i++)
      w.x[i] = u.x[i] * v.x[i];
   return w;
}

template<int n>
vec<n> operator-=(vec<n>& lhs, const vec<n>& rhs) {
   for(int i = 0; i < n; i++)
      lhs.x[i] -= rhs.x[i];
   return lhs;
}

template<int n>
double dot(const vec<n>& u, const vec<n>&v) {
   double sum = 0.0;
   for(int i = 0; i < n; i++)
      sum += u.x[i] * v.x[i];
   return sum;
}

//////////////////////////////////////////////////
// Constant-Vector / Vector-Constant Operations
//////////////////////////////////////////////////

// Component Addition
template<int n>
vec<n> operator+(const double c, const vec<n>& v) {
   vec<n> u;
   for(int i = 0; i < n; i++) 
      u.x[i] = v.x[i] + c;
   return u;
}

template<int n>
vec<n> operator+(const vec<n>& v, const double c) { return c + v; }

// Component Subtraction (Left)
template<int n>
vec<n> operator-(const double c, const vec<n>& v) { 
   vec<n> u = v;
   for(double&x : u.x)
      x = c - x;
   return u;
}

// Component Subtraction (Right)
template<int n>
vec<n> operator-(const vec<n>& v, const double c) { return (-1) * c + v; }

// Component Multiplication (Left)
template<int n>
vec<n> operator*(double c, const vec<n>& u) {
   vec<n> w;
   for(int i = 0; i < n; i++)
      w.x[i] = u.x[i] * c;
   return w;
}

// Multiplication (Right)
template<int n>
vec<n> operator*(const vec<n>& u, double c) { return c * u; }

template<int n>
double maxDistance(const vec<n>& u) {
   double max = std::abs(u.x[1]);
   for(int i = 2; i < n; i++)
      max = (max < std::abs(u.x[i])) ? std::abs(u.x[i]) : max;
   return max;
}

#endif

