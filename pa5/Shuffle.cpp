//---------------------------------------------
// List.cpp
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 5
//----------------------------------------------

#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"List.h"

using namespace std;

void shuffle(List& D);

int main(int argc, char * argv[]){
	ifstream in;
	stringstream ss;

   if( argc != 2 ){
      cerr << "Usage: " << argv[0] << " <deck size>" << endl;
      return(EXIT_FAILURE);
   }
   int deck;
   ss << argv[1];
   ss >> deck;
   List L;
   cout << "deck size       shuffle count" << endl;
   cout << "------------------------------" << endl;
   for (int x = 1; x <= deck; x++) {
   	L.insertBefore(x);
	int counter = 0;
	List test = L;
	do {
		shuffle(L);
		counter++;
	} while (!(L.equals(test)));
        cout << setw(5) << x << setw(18) << counter << '\n';	
   }
   in.close();
   return(EXIT_SUCCESS);
}

void shuffle(List& D) {
	List left;
	D.moveFront();
	int length = D.length()/2;
	for (int x = 0; x < length; x++) {
		left.insertBefore(D.moveNext());
		D.eraseBefore();
	}
	left.moveFront();
	while(D.position() < D.length()) {
		D.moveNext();
		if (left.position() < left.length())
			D.insertBefore(left.moveNext());
	}
}
