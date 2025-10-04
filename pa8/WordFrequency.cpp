#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {

    ifstream in;
    ofstream out;


    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }


    in.open(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }


    out.open(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    Dictionary D;
    string s;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

    while (getline(in, s)) {
        if (s != "" && s != "\n") {  

            std::size_t len = s.length();
            std::size_t index = s.find_first_not_of(delim, 0); 
            string word;

            while (index != string::npos) {  
                std::size_t endindex = s.find_first_of(delim, index);  

                if (endindex == string::npos) {  
                    endindex = len;
                }

                word = s.substr(index, endindex - index);  
                for (char& c : word) {
                    c = tolower(c); 
                }

              
                if (D.contains(word)) {
                    valType val = D.getValue(word);
                    D.setValue(word, val + 1);
                } else {
                    D.setValue(word, 1);
                }

              
                index = s.find_first_not_of(delim, endindex);
            }
        }
    }
    out << D << endl;

    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
