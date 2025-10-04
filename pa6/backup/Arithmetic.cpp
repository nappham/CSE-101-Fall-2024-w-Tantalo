//---------------------------------------------
// Arithmetic.cpp
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
 
    string line;
    getline(in, line);
    BigInteger A(line);
    getline(in, line);
    getline(in, line);
    BigInteger B(line);
    //BigInteger G("16");
    //BigInteger H("9");
    //out << (A * A * A * A).mult(H) + (B * B * B * B * B).mult(G) << endl << endl;
    out << A << endl << endl;
    out << B << endl << endl;
    out << A + B << endl << endl;
    out << A - B << endl << endl;
    out << "0" << endl << endl;
    BigInteger C("3");
    BigInteger D("2");
    BigInteger E(A.mult(C));
    BigInteger F(B.mult(D));
    out << E - F << endl << endl;
    out << A * B << endl << endl;
    out << A * A << endl << endl;
    out << B * B << endl << endl;
    out << (A * A * A * A).mult(BigInteger("9")) + (B * B * B * B * B).mult(BigInteger("16"))  << endl << endl;
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
