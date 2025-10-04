//Mandy Lau
//mlau16
//pa6

#include"BigInteger.h"
#include <string>
#include <sstream>

const long BASE = 1000000000;
const int POWER = 9;

using namespace std;

// Class Constructors & Destructors ----------------------------------------

   // BigInteger()
   // Constructor that creates a new BigInteger in the zero state: 
   // signum=0, digits=().
   BigInteger::BigInteger(){
        signum = 0;
        digits = List();
   }

   // BigInteger()
   // Constructor that creates a new BigInteger from the string s.
   // Pre: s is a non-empty string consisting of (at least one) base 10 digit
   // {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
   BigInteger::BigInteger(std::string s){
        if(s.length() == 0){
            throw std::invalid_argument("BigIntg Constructor: empty string");
	    }
	    if((s.substr(0,1) != "-" && s.substr(0,1) != "+") && (s.substr(0,1) > "9" || s.substr(0,1) < "0")) {
		    throw std::invalid_argument("BigIntg Constructor: non-numeric string");
	    }
	    for (int x = 1; x < (int)s.length(); x++) {
		    if (s[x] > '9' || s[x] < '0') {
			    throw std::invalid_argument("BigIntg Constructor: non-numeric string");
		    }
	    }
	    if (s == "0") {
		    return;
	    }

	    if(s.substr(0,1) == "-") {
		    this->signum = -1;
		    s = s.substr(1);
	    } else if(s.substr(0,1) == "+") {
		    this->signum = 1;
		    s = s.substr(1);
	    } else {
		    this->signum = 1;
	    }
	    while (s.length() > 0) {
		    int length = s.length() - POWER;
		    if (length < 0) {
			    string num_str = s;
			    long num = std::stol(num_str);
			    this->digits.insertAfter(num);
			    break;
		    }
		    string num_str = s.substr(length);
		    s = s.substr(0, length);

		    long num = std::stol(num_str);
		    this->digits.insertAfter(num);
	    }

   }

   // BigInteger()
   // Constructor that creates a copy of N.
   BigInteger::BigInteger(const BigInteger& N){
        this->signum = N.signum;
        this->digits = N.digits;
   }

   // Optional Destuctor
   // ~BigInteger()
   // ~BigInteger();

    // Access functions --------------------------------------------------------

   // sign()
   // Returns -1, 1 or 0 according to whether this BigInteger is positive, 
   // negative or 0, respectively.
   int BigInteger::sign() const{
        return signum;
   }

   // compare()
   // Returns -1, 1 or 0 according to whether this BigInteger is less than N,
   // greater than N or equal to N, respectively.
   int BigInteger::compare(const BigInteger& N) const{
    BigInteger result = this->sub(N);
    return result.sign();
   }


   // Manipulation procedures -------------------------------------------------

   // makeZero()
   // Re-sets this BigInteger to the zero state.
   void BigInteger::makeZero(){
    this->signum = 0;
    this->digits.clear();
   }

   // negate()
   // If this BigInteger is zero, does nothing, otherwise reverses the sign of 
   // this BigInteger positive <--> negative. 
   void BigInteger::negate(){
    this->signum *= -1;
   }

   // BigInteger Arithmetic operations ----------------------------------------

   // add()
   // Returns a BigInteger representing the sum of this and N.
   BigInteger BigInteger::add(const BigInteger& N) const{
        BigInteger A(*this);
	    BigInteger B(N);
	    BigInteger result;
        List Alist = A.digits;
        List Blist = B.digits;
        if (A.sign() != B.sign()) {
            if(A.sign() > 0) {
                B.signum *= -1;
                return A.sub(B);
            } else if (A.sign() < 0) {
                A.signum *= -1;
                return B.sub(A);
            }
        }
        result.signum = A.signum;
        List resultList;
        Alist.moveBack();
        Blist.moveBack();
        long carry = 0;
        while (Alist.position() > 0 && Blist.position() > 0) {
            long a = Alist.movePrev();
            long b = Blist.movePrev();
            long add = a + b + carry;
            carry = 0;
            if (add >= 1000000000) {
                carry = add / 1000000000;
                            add = add - carry * 1000000000;
            }
            resultList.insertAfter(add);
        }
        while (Alist.position() > 0) {
            long a = Alist.movePrev() + carry;
            carry = 0;
            while (a >= 1000000000) {
                a -= 1000000000;
                carry += 1;
            }
            resultList.insertAfter(a);
        }
        while (Blist.position() > 0) {
            long b = Blist.movePrev() + carry;
                    carry = 0;
                    if (b >= 1000000000) {
                            carry = b / 1000000000;
                            b = b - carry * 1000000000;
                    }
            resultList.insertAfter(b);
        } 
        while (resultList.length() > 0 && resultList.front() == 0) {
            resultList.moveFront();
            resultList.eraseAfter();
        }
        result.digits = resultList;
        return result;
   }

   // sub()
   // Returns a BigInteger representing the difference of this and N.
   BigInteger BigInteger::sub(const BigInteger& N) const{
        BigInteger A(*this);
        BigInteger B(N);
        while (B.digits.length() > 0 && B.digits.front() == 0) {
                    B.digits.moveFront();
                    B.digits.eraseAfter();
            }
        List Alist = A.digits;
        List Blist = B.digits;
        BigInteger result;
        if (A.digits.length() == 0 && B.digits.length() == 0) {
            return result;	
        } else if (A.digits.length() == 0) {
            return B;
        } else if (B.digits.length() == 0) {
            return A;
        }
        if(A.sign() != B.sign()) {
            B.signum *= -1;
            return A.add(B);
        } else if (B.digits.length() > A.digits.length()) {
            result = B.sub(A);
            result.signum *= -1;
            return result;
        } else if (B.digits.length() == A.digits.length()) {
            B.digits.moveFront();
            A.digits.moveFront();
            while(B.digits.position() < B.digits.length()) {
                long c = A.digits.moveNext();
                long d = B.digits.moveNext();
                if (d > c) {
                    result = B.sub(A);
                    result.signum *= -1;
                    return result;
                } else if (c > d) {
                    break;
                }
            }
        }
        result.signum = A.signum;
        List resultlist;
        Alist.moveBack();
        Blist.moveBack();
        long carry = 0;
        while (Alist.position() > 0 && Blist.position() > 0) {
            long a = Alist.movePrev();
            long b = Blist.movePrev();
            long sub = a - b - carry;
            carry = 0;
            while (sub < 0) {
                sub += 1000000000;
                carry += 1;
            }
            resultlist.insertAfter(sub);
        }

        while (Alist.position() > 0) {
            long a = Alist.movePrev();
            long sub = a - carry;
            carry = 0;
            while (sub < 0) {
                sub += 1000000000;
                carry += 1;
                
            }
            resultlist.insertAfter(a);
        }

        while (Blist.position() > 0) {
            long b = Blist.movePrev();
            long sub = b - carry;
            carry = 0;
            while (sub < 0) {
                sub += 1000000000;
                carry += 1;
            }
            resultlist.insertAfter(b);
        }
        resultlist.moveFront();
        while(resultlist.position() < resultlist.length()) {
            if (resultlist.moveNext() == 0) {
                resultlist.eraseBefore();
                resultlist.moveFront();
            } else {
                break;
            }
        }
        if (resultlist.length() == 0) {
            result.signum = 0;
        }
        while (resultlist.length() > 0 && resultlist.front() == 0) {
                    resultlist.moveFront();
                    resultlist.eraseAfter();
            }
        result.digits = resultlist;
        return result;
   }

   // mult()
   // Returns a BigInteger representing the product of this and N. 
   BigInteger BigInteger::mult(const BigInteger& N) const{
        BigInteger A(*this);
        BigInteger B(N);
	    BigInteger C;
        BigInteger result("0");
        if (A.digits.length() == 0 || B.digits.length() == 0) {
            result.signum = 0;
            return result;
        }

        if (A.sign() != B.sign()) {
            result.signum = -1;
        } else {
            result.signum = 1;
        }
        A.signum = result.signum;
        B.signum = result.signum;
        C.signum = result.signum;
        List Alist = A.digits;
        List Blist = B.digits;
        List resultList;
        Blist.moveBack();
        int carry = 0;
        int count = -1;
        int count2= 0;
        while(Blist.position() > 0) {
            long b = Blist.movePrev();
            Alist.moveBack();
            count++;
            count2 = count;
            while (Alist.position() > 0) {
                carry = 0;
                C.digits.clear();
                long a = Alist.movePrev();
                C.digits.moveFront();
                long c = a * b;
                if (c >= 1000000000) {
                    carry = c / 1000000000;
                    c = c - carry * 1000000000;
                }
                C.digits.insertAfter(c);
                C.digits.insertAfter(carry);
                for (int x = 0; x < count2; x++) {
                    C.digits.moveBack();
                    C.digits.insertBefore(0);
                }
                count2++;
	        result = result.add(C);	
            }
    	}

	    return result;
   }

    // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this BigInteger consisting of its
   // base 10 digits. If this BigInteger is negative, the returned string 
   // will begin with a negative sign '-'. If this BigInteger is zero, the
   // returned string will consist of the character '0' only.
   std::string BigInteger::to_string(){
        std::string s = "";
        digits.moveFront();
        while (digits.position() < digits.length()) {
                printf("%d < %d\n", digits.position(), digits.length());
		long num = digits.moveNext();
		if (num == 0) {
			s += "000000000";
		} else {
			std::string num_str = std::to_string(num);
                	while (num_str.length() < 9) {
				num_str = "0" + num_str;
			}
			s += num_str;
		}
        }
	while (s.substr(0,1) == "0") {
		s = s.substr(1);
	}
	if (this->signum == -1) {
		s = "-" + s;
	}
        return s;
   }


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of N into stream.
   std::ostream& operator<<( std::ostream& stream, BigInteger N ){
        return stream << N.to_string();
   }

   // operator==()
   // Returns true if and only if A equals B. 
   bool operator==( const BigInteger& A, const BigInteger& B ){
        return A.compare(B) == 0;
   }

   // operator<()
   // Returns true if and only if A is less than B. 
   bool operator<( const BigInteger& A, const BigInteger& B ){
    return A.compare(B) < 0;
   }

   // operator<=()
   // Returns true if and only if A is less than or equal to B. 
   bool operator<=( const BigInteger& A, const BigInteger& B ){
        return A.compare(B) <= 0;
   }

   // operator>()
   // Returns true if and only if A is greater than B. 
   bool operator>( const BigInteger& A, const BigInteger& B ){
        return A.compare(B) > 0;
   }

   // operator>=()
   // Returns true if and only if A is greater than or equal to B. 
   bool operator>=( const BigInteger& A, const BigInteger& B ){
        return A.compare(B) >= 0;
   }

   // operator+()
   // Returns the sum A+B. 
   BigInteger operator+( const BigInteger& A, const BigInteger& B ){
        return A.add(B);
   }

   // operator+=()
   // Overwrites A with the sum A+B. 
   BigInteger operator+=( BigInteger& A, const BigInteger& B ){
        A = A.add(B);
        return(A);
   }

   // operator-()
   // Returns the difference A-B. 
   BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
   }

   // operator-=()
   // Overwrites A with the difference A-B. 
   BigInteger operator-=( BigInteger& A, const BigInteger& B ){
        A = A.sub(B);
        return(A);
   }

   // operator*()
   // Returns the product A*B. 
   BigInteger operator*( const BigInteger& A, const BigInteger& B ){
        return A.mult(B);
   }

   // operator*=()
   // Overwrites A with the product A*B. 
   BigInteger operator*=( BigInteger& A, const BigInteger& B ){
        A = A.mult(B);
        return(A);
   }
