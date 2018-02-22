#include <iostream>

#include "lib/vector.h"
#include "lib/matrix.h"

double randDouble() { return (double)rand() / RAND_MAX; }

template<int m>
vec<m> f(const vec<m>& u, const vec<m>& v, const int& p, const vec<m>& n) {
    
    vec<m> w = v - p * n;
    double c = 2.0;
    double a = c * magnitude(v - w) / magnitude(u - w);
    return w + a * (u - w);
    
}

template<int m>
vec<m> subf(const vec<m>& u, const vec<m>& v, const int& p, const vec<m>& n) {
    
    
    vec<m> a = v - p*n;
    vec<m> b = v - a;
    vec<m> c = u - a;
    double d = dot(b,b);
    double e = dot(c,c);
    double f = sqrt(d);
    double g = sqrt(e);
    double h = f / g;
    
    return a + 2 * h * c;
    
}

template<int m>
mat<m,m> df(const vec<m>& u, const vec<m>& v, const double& p, const vec<m>& n, 
    const mat<m,m>& du, const mat<m,m>& dv, const double& dp,const mat<m,m>& dn) {
    
    vec<m> a = v - p*n;
    vec<m> b = v - a;
    vec<m> c = u - a;
    double d = dot(b,b);
    double e = dot(c,c);
    double f = sqrt(d);
    double g = sqrt(e);
    double h = f / g;
    
    
     std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";
    std::cout << "c: " << c << "\n";
    std::cout << "d: " << d << "\n";
    std::cout << "e: " << e << "\n";
    std::cout << "f: " << f << "\n";
    std::cout << "g: " << g << "\n";
    std::cout << "h: " << h << "\n";
    
    mat<m,m> a_partial = dv - (dp * n + p * dn);
    mat<m,m> b_partial = dv - a_partial;
    mat<m,m> c_partial = du - a_partial;
    
     std::cout << "aPartial: " << a_partial << "\n";
     std::cout << "bPartial: " << b_partial << "\n";
     std::cout << "cPartial: " << c_partial << "\n";
    
    vec<m> d_partial = 2 * b * b_partial;
    vec<m> e_partial = 2 * c * c_partial;
    
     std::cout << "dPartial: " << d_partial << "\n";
     std::cout << "ePartial: " << e_partial << "\n";
    
    vec<m> f_partial = d_partial / (2 * sqrt(d));
     std::cout << "fPartial: " << f_partial << "\n";
    
    vec<m> g_partial = e_partial / (2 * sqrt(e));
     std::cout << "gPartial: " << g_partial << "\n";
    
    vec<m> h_partial = (f_partial * g - g_partial * f)/(g * g);
    std::cout << "hPartial: " << h_partial << "\n";
    return a_partial + 2 * (h_partial * c + h * c_partial);
    
}


int main() {
    
    vec<3> u = {1,1,1};
    vec<3> v = {1,1,2};
    double p = 1;
    vec<3> n = {1,1,3};
    
    // Parameters
    std::cout << "u: " << u << "\n";
    std::cout << "v: " << v<< "\n";
    std::cout << "p: " << p<< "\n";
    std::cout << "n: " << n << "\n\n";
    
    mat<3,3> du, dv, dn;
    double dp;
    
    // Partial u
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            du.x[i][j] = 1;         
            dv.x[i][j] = 0;
            dn.x[i][j] = 0;
        }
        
    }
    dp = 0;
    
    std::cout << "du: " << du << "\n";
    std::cout << "dv: " << dv<< "\n";
    std::cout << "dp: " << dp<< "\n";
    std::cout << "dn: " << dn << "\n\n";
    
    // Original Function (and substitutions)
    std::cout << "F:    " << f(u,v,p,n) << "\n";
    std::cout << "subF: " << subf(u,v,p,n) << "\n\n";
    std::cout << "Fu: " << df(u,v,p,n, du, dv, dp, dn) << "\n";
    
    return 0;
    
}
    