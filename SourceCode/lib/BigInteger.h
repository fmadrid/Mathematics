#ifndef BIG_INTEGER_H
#define BIG_INTEGER

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

using std::string;

class BigInteger {
	
	
	
	public:
	
	std::string value = "0";
	bool isNegative   = false;
	
	const static BigInteger ZERO;
	
	// Constructors
	BigInteger();
	BigInteger(const long long&);
	BigInteger(const BigInteger&);
	BigInteger(string);
	
	// Assignment Operators
	BigInteger& operator =  (const BigInteger&);
	BigInteger& operator += (const BigInteger&);
	BigInteger& operator -= (const BigInteger&);
	BigInteger& operator *= (const BigInteger&);
	
	//Unary Operators
	BigInteger operator-() const;
	
	// Indexing
	char& operator [] (const int&);
	char operator [] (const int&) const;
	void replace(const int& index, const int& n);
	
	// Conversion
	long long   toLongLong() const;
	
	// Streams
	friend std::ostream& operator << (std::ostream&, const BigInteger&);
	friend std::istream& operator >> (std::istream&, const BigInteger&);
	
	// Relational Operators
	friend bool operator <  (const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator >  (const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator == (const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator != (const BigInteger& lhs, const BigInteger& rhs);
};


// Binary Operators
BigInteger operator + (BigInteger lhs, const BigInteger& rhs);
BigInteger operator - (BigInteger lhs, BigInteger rhs);
BigInteger operator * (const BigInteger& lhs, const BigInteger& rhs);

BigInteger abs(BigInteger);

BigInteger power(const BigInteger&, int);
#endif