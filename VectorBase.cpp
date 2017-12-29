#include <initializer_list>
#include <iostream>
#include <iomanip>

struct VectorBase { 

	int size;
	
	VectorBase(int s) : size(s){}
	
	virtual double* getX() {}
	int getSize() { return size; }
	
};

template<int n>
struct FixedVector : VectorBase {
	
	double x[n];
	
	double* getX() { return x; }
	
	FixedVector(double a[]) : VectorBase(n) {
		for(int i = 0; i < n; i++) x[i] = a[i];
	}
	
};

struct DynamicVector : VectorBase {
	
	double* x;
	
	DynamicVector(double* a, int size) : VectorBase(size) {
		x = new double[size];
		for(int i = 0; i < size; i++)
			x[i] = a[i];
	}

	DynamicVector(std::initializer_list<double> il) : VectorBase(il.size()) {
		
		x = new double[il.size()];
		int i = 0;
		for(auto it = il.begin(); it != il.end(); it++)
			
			x[i++] = *it;
	}
	
	~DynamicVector() { delete[] x; }
	
	double* getX() { return x; }
};

std::ostream& operator << (std::ostream &out, VectorBase& u) {
   out << "[";
   for(int i = 0; i < u.getSize(); i++) {
      out << std::fixed << std::setprecision(10) << u.getX()[i];
      if(i != u.getSize()-1) out << " ";
   }
   out << "]";
   return out;

}

int main() {
	
	double a[3] = {1,2,3};
	FixedVector<3> fV(a);
	DynamicVector dV({1,2,3});
	DynamicVector dV2(a,3);
	std::cout << fV << "\n" << dV << "\n";
	
	return 0;
	
}

