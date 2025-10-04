//---------------------------------------------
// BigInteger.cpp
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 6
//----------------------------------------------

#include"BigInteger.h"
#include"List.h"
#include<string>
#include<sstream>

const int POWER = 9;

const long BASE = 1000000000;

using namespace std;

BigInteger::BigInteger() {
	signum = 0;
	digits = new List();	
}

BigInteger::BigInteger(std::string s) {
	if (s[0] == "-") {
		signum = -1;
		s = s.substr(1);
	} else if (s[0] == "+") {
		signum = 1;
		s = s.substr(1);
	} else {
		signum = 1;
	}
	while (s.length() > 0) {
		string num_str;
		int start = s.length() - POWER;
		if (start > 0) {
			num_str = s.substr(start);
			s = s.substr(0, start);
		} else {
			num_str = s;
			s = s.substr(0, 0);
		}
		long num = std::stol(num_str);
		this->digits.insertAfter(num);
	}

}

BigInteger::BigInteger(const BigInteger& N) {
	this->signum = N.signum;
	this->digits = List(N.digits);
}

// Access Functions

int BigInteger::sign() const {
	return signum;
}

int BigInteger::compare(const BigInteger& N) const {
	BigInteger test = this->sub(N);
	return test.signum;
}

// Manipulation

void BigInteger::makeZero() {
	this->signum = 0;
	this->digits.clear();
}

void BigInteger::negate() {
	this->signum *= -1;
}

// Arithmetic

BigInteger BigInteger::add(const BigInteger& N) const {
	BigInteger nM(*this);
	BigInteger nN(N);
	if (nM.sign() != nN.sign()) {
		if (nM.sign() > 0) {
			nM.signum = 1;
			return nN.sub(nM);
		} else {
			nN.signum = 1;
			return nM.sub(nN);
		}
	}
	BigInteger result;
	result.signum = N.sign();
	List dR;
	List dN;
	List dM;
	dN.moveBack();
	dM.moveBack();
	while (dN.position() > 0 && dM.position() > 0) {
		long n = dN.movePrev();
		long m = dM.movePrev();
		dR.insertAfter(n + m);
	}

	while (dN.position() > 0) {
		dR.insertAfter(dN.movePrev());
	}


	while (dM.position() > 0) {
		dR.insertAfter(dM.movePrev());
	}
	result.digits = dR;
	return result;


}

BigInteger BigInteger::sub(const BigInteger& N) const {
	BigInteger nM(*this);
	BigInteger nN(N);
	if (nM.sign() != nN.sign()) {
		nN.signum *= -1;
		return nM.add(nN);
	}
	return nM;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
	BigInteger nM(*this);
	BigInteger nN(N);
	BigInteger result;

	if (nM.sign() != nN.sign()) {
		result.signum = -1;
	} else {
		result.signum = 1;
	}

	List dM = nM.digits;
	List dN = nN.digits;
	return nM;
}

std::string BigInteger::to_string() {
	if (this->signum == 0) {
		return "0";
	}
	std::string s = "";
	if (this->signum == -1) {
		s += "-";
	}
	digits.moveFront();
	while (digits.position() < digits.length()) {
		long num = digits.moveNext();
		std::string num_str = std::to_string(num);
		while (num_str.length() < POWER) {
			num_str = '0' + num_str;
		}
		s += num_str;
	}
	return s;


}

// Overloaded Operators

std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    return stream << N.to_string();
}

bool operator==(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 0;
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) < 0;
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) <= 0;
}

bool operator>(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) > 0;
}

bool operator>=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) >= 0;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
    return A.add(B);
}

BigInteger operator+=(BigInteger& A, const BigInteger& B) {
    A = A.add(B);
    return A;
}

BigInteger operator-(const BigInteger& A, const BigInteger& B) {
    return A.sub(B);
}

BigInteger operator-=(BigInteger& A, const BigInteger& B) {
    A = A.sub(B);
    return A;
}

BigInteger operator*(const BigInteger& A, const BigInteger& B) {
    return A.mult(B);
}

BigInteger operator*=(BigInteger& A, const BigInteger& B) {
    A = A.mult(B);
    return A;
}


