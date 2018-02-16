#include <string>
#include "BigInteger.h"
#include <iostream>

const BigInteger BigInteger::ZERO = BigInteger("0");

BigInteger::BigInteger() { *this = ZERO; }
BigInteger::BigInteger(const long long& v) : BigInteger(std::to_string(v)){}
BigInteger::BigInteger(const BigInteger& b) : value(b.value), isNegative(b.isNegative){}

BigInteger::BigInteger(string str) { 
	
	if(str[0] == '-') this->isNegative = true;
	
	for(int i = 0; i < str.length(); i++)
		if(!isdigit(str[i])) str.erase(i--,1);

	if(str.compare("0") == 0) *this = ZERO;
	else {
		int pos = 0;
		while(str[pos++] == '0');
		this->value = str.substr(pos-1,string::npos);
	}
}

BigInteger& BigInteger::operator=(const BigInteger& rhs) {
	this->value      = rhs.value;
	this->isNegative = rhs.isNegative;
	return *this;
}

BigInteger& BigInteger::operator += (const BigInteger& b) { return *this = *this + b; }
BigInteger& BigInteger::operator -= (const BigInteger& b) { return *this = *this - b; }
BigInteger& BigInteger::operator *= (const BigInteger& b) { return *this = *this * b; }

BigInteger BigInteger::operator-() const{
	BigInteger b = *this;
	b.isNegative = !this->isNegative;
	return b;
}

char& BigInteger::operator [] (const int& index)       { return value[index]; }
char  BigInteger::operator [] (const int& index) const { return value[index]; }

void BigInteger::replace(const int& index, const int& n) {
	value[index] = n + '0';
}

long long BigInteger::toLongLong() const{ return std::stoll(value); }

std::ostream& operator << (std::ostream& os, const BigInteger& b){
	os << ((b.isNegative) ? "-" : "") << b.value;
	return os;
}

std::istream& operator >> (std::istream& is, const BigInteger& b){
	is >> b.value;
	return is;
}

bool operator <  (const BigInteger& lhs, const BigInteger& rhs){
	const std::string lValue = lhs.value;
	const std::string rValue = rhs.value;
	
	if(lhs.isNegative != rhs.isNegative)                      return lhs.isNegative;
	else if(lValue.compare(rValue) == -1  &&  lhs.isNegative) return true;
	else if(lValue.compare(rValue) ==  1  && !lhs.isNegative) return true;
	else                                                      return false;
}

bool operator > (const BigInteger& lhs, const BigInteger& rhs){ return ~ (lhs < rhs); }

bool operator == (const BigInteger& lhs, const BigInteger& rhs){
	std::string lValue = lhs.value;
	std::string rValue = rhs.value;
	
	if(lhs.isNegative != rhs.isNegative == 1) return false;
	else if(lValue.compare(rValue) == 0)      return true;
	else                                      return false;
}

bool operator != (const BigInteger& lhs, const BigInteger& rhs){ return !(lhs == rhs); }

BigInteger operator + (BigInteger lhs, const BigInteger& rhs) {
	
	if(lhs.isNegative != rhs.isNegative) lhs = (lhs.isNegative) ? (rhs - abs(lhs)) : (lhs - abs(rhs));
	else {
	
		std::string val = "";
		
		int carry = 0;
		int i = lhs.value.length();
		int j = rhs.value.length();
		
		while(i > 0 || j > 0) {
			int sum = carry;
			if(i > 0) sum += (lhs[--i] -'0');
			if(j > 0) sum += (rhs[--j] -'0');
			
			val.append(std::to_string(sum % 10));
			carry = sum / 10;
			
		}
		
		if(carry) val.append(std::to_string(carry));
		std::reverse(val.begin(), val.end());
		lhs.value = val;
	}
	
	return lhs;
	
}

BigInteger operator - (BigInteger lhs, BigInteger rhs) {

	if(lhs.isNegative != rhs.isNegative)      return (lhs.isNegative) ? -(abs(lhs) + abs(rhs)) : (abs(lhs) + abs(rhs));
	else if(lhs.isNegative && rhs.isNegative) return abs(rhs) - abs(lhs);

	bool swapped = false;
	if(lhs.value.length() == rhs.value.length()){
		if(abs(lhs) > abs(rhs)) {
			std::swap(lhs.value, rhs.value); 
			swapped = true; 
		}
	}
	else if(lhs.value.length() < rhs.value.length()) {
		std::swap(lhs.value, rhs.value); 
		swapped = true; 
	}
	
	int i, j;
	for(i = lhs.value.length() - rhs.value.length(), j = 0; i < lhs.value.length(); i++,j++) {
		int a = lhs[i] - '0';
		int b = rhs[j] - '0';
		if(a < b) {
			lhs.value[i-1]--;
			a += 10;
		}
		lhs.value[i] = (a - b) + '0';
	}
	

	int pos = 0;
	while(lhs.value[pos++] == '0');
	lhs.value = lhs.value.substr(pos-1,string::npos);
		
	if(lhs.value.length() == 0)
		return BigInteger::ZERO;
	else if(swapped) {
		lhs.isNegative = true;
		return lhs;
	}
	
}

BigInteger operator * (const BigInteger& lhs, const BigInteger& rhs) {
	
	BigInteger ret;
	
	int i = 0;
	for(auto itL = lhs.value.rbegin(); itL != lhs.value.rend(); itL++, i++) {
		
		std::string val = "";
		
		int carry = 0;
		for(auto itR = rhs.value.rbegin(); itR != rhs.value.rend(); itR++) {
			int sum = (*itL - '0') * (*itR - '0') + carry;
			carry = sum / 10;
			val.append(std::to_string(sum%10));
		}
		if(carry) val.append(std::to_string(carry));
		
		std::reverse(val.begin(), val.end());
		std::string zeros(i, '0');
		val.append(zeros);
		
		BigInteger temp(val);
		ret += val;
		
	}
	ret.isNegative = (lhs.isNegative != rhs.isNegative) ? true : false;
	return ret;
	
}

BigInteger abs(BigInteger b) {
	b.isNegative = false;
	return b;
}

BigInteger power(const BigInteger& b, int exponent) {
	
	BigInteger ret = b;
	int i = 1;
	
	while(i * 2 <= exponent) {
		ret *= ret;
		i *= 2;
	}
	if(i == exponent) return ret;
	else return ret * power(b, exponent - i);
	
}
