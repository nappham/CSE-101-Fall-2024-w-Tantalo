//---------------------------------------------
// Order.cpp
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 8
//----------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){
    ifstream in;
    ofstream out;

    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }
    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    string s;
    Dictionary D;
    for(int x = 1; getline(in, s); x++){
        D.setValue(s, x);
    }
    out << D.to_string() << endl;
    out << D.pre_string() << endl;
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
