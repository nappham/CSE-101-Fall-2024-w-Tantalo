//---------------------------------------------
// BigInteger.cpp
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 6
//----------------------------------------------

#include"BigInteger.h"
#include<string>
#include<sstream>

const long BASE = 1000000000;
const int POWER = 9;

using namespace std;

BigInteger::BigInteger() {
	signum = 0;
	digits = List();
}

BigInteger::BigInteger(std::string s) {
	if(s.length() == 0) {
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}
	if((s.substr(0,1) != "-" && s.substr(0,1) != "+") && (s.substr(0,1) > "9" || s.substr(0,1) < "0")) {
		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
	}
	for (int x = 1; x < (int)s.length(); x++) {
		if (s[x] > '9' || s[x] < '0') {
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
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
			//cout << "s: " << s << endl;
			this->digits.insertAfter(num);
			break;
		}
		string num_str = s.substr(length);
		s = s.substr(0, length);
		//cout << "num_str: " << num_str << endl;
		long num = std::stol(num_str);
		this->digits.insertAfter(num);
	}
}

BigInteger::BigInteger(const BigInteger& N) {
	this->signum = N.signum;	
	this->digits = N.digits;
}

int BigInteger::sign() const {
	return signum;
}

int BigInteger::compare(const BigInteger& N) const {
	BigInteger results = this->sub(N);
	return results.sign();
}

void BigInteger::makeZero() {
	this->signum = 0;
	this->digits.clear();
}

void BigInteger::negate() {
	this->signum *= -1;
}

BigInteger BigInteger::add(const BigInteger& N) const {
	BigInteger A(*this);
	BigInteger B(N);
	BigInteger result;
        List Alist = A.digits;
        List Blist = B.digits;
	//printf("-----------------------------------------------------------------\n");	
	//printf("A.sign(): %d\nB.sign(): %d\n", A.sign(), B.sign());
	if (A.sign() != B.sign()) {
		if(A.sign() > 0) {
			B.signum *= -1;
			//printf("A.sub(B)\n");
			return A.sub(B);
		} else if (A.sign() < 0) {
			A.signum *= -1;
			//printf("B.sub(A)\n");
			return B.sub(A);
		}
	}
	//printf("B2\n");
	result.signum = A.signum;
	List resultList;
	Alist.moveBack();
	Blist.moveBack();
	long carry = 0;
	//printf("B3\n");
	while (Alist.position() > 0 && Blist.position() > 0) {
		long a = Alist.movePrev();
		long b = Blist.movePrev();
		long add = a + b + carry;
		//printf("Add A: %ld\n", a);
		//printf("Add B: %ld\n", b);
		//printf("Add: %ld\n", add);
		carry = 0;
		if (add >= 1000000000) {
			carry = add / 1000000000;
                        add = add - carry * 1000000000;
		}
		resultList.insertAfter(add);
	}
	//printf("B4\n");
	while (Alist.position() > 0) {
		long a = Alist.movePrev() + carry;
		carry = 0;
		while (a >= 1000000000) {
			a -= 1000000000;
			carry += 1;
		}
		resultList.insertAfter(a);
	}
	//printf("B5\n");
	//cout << B.to_string() << endl;
	while (Blist.position() > 0) {
		long b = Blist.movePrev() + carry;
		//printf("B before carry: %ld\n", b);
                carry = 0;
                if (b >= 1000000000) {
                        carry = b / 1000000000;
                        b = b - carry * 1000000000;
                }
		//printf("Adding only B: %ld\n", b);
		resultList.insertAfter(b);
	} 
	//printf("--------------------------------------------\n");
	while (resultList.length() > 0 && resultList.front() == 0) {
		resultList.moveFront();
		resultList.eraseAfter();
	}
	//cout << "Finish Adding: " << resultList.to_string() << endl;
	result.digits = resultList;
	//cout << "Double checking: " << result.digits.to_string() << endl;
	return result;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
	BigInteger A(*this);
	BigInteger B(N);
	while (B.digits.length() > 0 && B.digits.front() == 0) {
                B.digits.moveFront();
                B.digits.eraseAfter();
        }
	List Alist = A.digits;
        List Blist = B.digits;
	//cout << "B: " << B.digits.to_string() << endl;
	//cout << "A: " << A.digits.to_string() << endl;
	//printf("B.digits.length(): %d\nA.digits.length(): %d\n", B.digits.length(), A.digits.length());

	BigInteger result;
	//printf("-------------------------------------------------------------\n");
	if (A.digits.length() == 0 && B.digits.length() == 0) {
		return result;	
	} else if (A.digits.length() == 0) {
		return B;
	} else if (B.digits.length() == 0) {
		return A;
	}
	if(A.sign() != B.sign()) {
		B.signum *= -1;
		//printf("Sub->Add");
		return A.add(B);
	} else if (B.digits.length() > A.digits.length()) {
		//printf("1 Swapping!\n");
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
				//printf("2 Swapping!\n");
				result = B.sub(A);
				result.signum *= -1;
				return result;
			} else if (c > d) {
				break;
			}
		}
	}
	//printf("C3\n");
	result.signum = A.signum;
	List resultlist;
	Alist.moveBack();
	Blist.moveBack();
	long carry = 0;
	while (Alist.position() > 0 && Blist.position() > 0) {
		long a = Alist.movePrev();
		long b = Blist.movePrev();
		long sub = a - b - carry;
		//printf("A: %ld\n", a);
                //printf("B: %ld\n", b);		
		//printf("Carry: %ld\n", carry);
                //printf("Sub: %ld\n", sub);
		carry = 0;
		while (sub < 0) {
			//printf("Negative number detected\n");	
			sub += 1000000000;
			carry += 1;
			//printf("New Sub: %ld\n", sub);
			//printf("New Carry: %ld\n", carry);
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
        //while (A.digits.length() > 0 && A.digits.front() == 0) {
        //        A.digits.moveFront();
        //        A.digits.eraseAfter();
        //}

        //while (B.digits.length() > 0 && B.digits.front() == 0) {
        //        B.digits.moveFront();
        //        B.digits.eraseAfter();
        //}
	List Alist = A.digits;
	List Blist = B.digits;
	List resultList;
	Blist.moveBack();
	int carry = 0;
	int counter = -1;
	int counter2= 0;
	while(Blist.position() > 0) {
		long b = Blist.movePrev();
		Alist.moveBack();
		counter++;
		counter2 = counter;
		//printf("Counter: %d\n", counter);	
		while (Alist.position() > 0) {
			carry = 0;
			C.digits.clear();
			long a = Alist.movePrev();
			//printf("Multiplication A: %ld\n", a);
			//printf("Multiplication B: %ld\n", b);
			C.digits.moveFront();
			long c = a * b;
			if (c >= 1000000000) {
				carry = c / 1000000000;
				c = c - carry * 1000000000;
			}
			C.digits.insertAfter(c);
			C.digits.insertAfter(carry);
			for (int x = 0; x < counter2; x++) {
				C.digits.moveBack();
				C.digits.insertBefore(0);
			}
			//cout << "a * b: " << C.digits.to_string() << endl;
			//printf("Counter: %d\n", counter);
			//cout << "Adding zeros: " << C.digits.to_string() << endl;
			counter2++;
	
                        //cout << "List being added: " << C.digits.to_string() << endl;	
			//printf("Adding!\n");	
			result = result.add(C);
			//cout << "Mult Result: " << result.to_string() << endl;
			
		}
	}
		
	//result.digits = resultList;
	return result;
}


std::string BigInteger::to_string() {
        //if (this->signum == 0) {
        //        return "0";
        //}
        std::string s = "";
        digits.moveFront();
        while (digits.position() < digits.length()) { 
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
	while (s.substr(0, 1) == "0") {
		s = s.substr(1);
	}
	while (s.substr(s.length() - 1, 1) == "0") {
		s = s.substr(0, s.length() - 1);
	}
	if (this->signum == -1) {
		s = "-" + s;
	}
        return s;


}

//Overloaded Operators -------------------------------------------------------

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

