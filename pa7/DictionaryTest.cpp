// DictionaryTest.cpp
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 5
//----------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

int main(){
	Dictionary D;
	D.setValue("a", 3);
	D.setValue("b", 1);
	D.setValue("c", 2);
	cout << D.to_string() << endl;
}

