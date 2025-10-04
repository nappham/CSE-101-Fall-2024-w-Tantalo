//---------------------------------------------
// ListClient.cpp
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 5
//----------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"List.h"

using namespace std;

int main() {
	List A;
	A.insertBefore(34);
    	A.insertBefore(77);
    	A.insertBefore(77);
    	A.insertBefore(1);
    	A.insertBefore(34);
    	A.insertBefore(1);
	A.insertBefore(55);
    	A.insertBefore(77);
	A.findPrev(99);
	A.findPrev(1);
	A.findPrev(1);
	A.findPrev(1);
	cout << A.to_string() << endl;
	A.moveBack();
	A.cleanup();
	cout << A.to_string() << endl;
	int a = A.findPrev(1);
	cout << a << endl;	

}
