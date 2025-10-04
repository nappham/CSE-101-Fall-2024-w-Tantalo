//---------------------------------------------
// BigIntegerTest.cpp
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 6
//----------------------------------------------

#include"BigInteger.h"
#include<string>
#include<fstream>
#include<iostream>
#include<iomanip>

using namespace std;

int main() {
	BigInteger A("111122223333");
	BigInteger B("111122223333");
	BigInteger C = A * B;
	BigInteger D("12348148518469628889");
	cout << C.to_string() << endl;
	cout << D.to_string() << endl;
}

