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
        //printf("--------------------------\n");
        Dictionary B;
        B.setValue("insignia", 100);
        cout << B.pre_string() << endl;
        B.setValue("feather", 20);
        cout << B.pre_string() << endl;
        B.setValue("heat", 15);
        cout << B.pre_string() << endl;
        B.setValue("eradicate", 10);
        cout << B.pre_string() << endl;
        B.setValue("bolstering", 5);
        cout << B.pre_string() << endl;
        B.setValue("abjuration", 1);
        //cout << B.pre_string() << endl;
        //B.remove("a");
        cout << B.pre_string() << endl;

}

