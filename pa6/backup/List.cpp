//---------------------------------------------
// List.cpp
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 6
//----------------------------------------------

#include "List.h"

using namespace std;

#define DUMMY 0

List::Node::Node(long x) {
    data = x;
    prev = nullptr;
    next = nullptr;
}

List::List() {
    frontDummy = new Node(DUMMY);
    backDummy = new Node(DUMMY);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List &L) {
    frontDummy = new Node(DUMMY);
    backDummy = new Node(DUMMY);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    Node *N = L.frontDummy->next;
    while (N != L.backDummy) {
        int data = N->data;
	this->insertBefore(data);
	N = N->next;
    }
}

List::~List() {
	this->clear();
	delete this->frontDummy;
	delete this->backDummy;
}

int List::length() const{
	return this->num_elements;
} 

ListElement List::front() const{
	if (this->num_elements <= 0) {
		throw std::length_error("List: front(): empty List");
	}
	return frontDummy->next->data;
}

ListElement List::back() const {
        if (this->num_elements <= 0) {
                throw std::length_error("List: front(): empty List");
        }
	return backDummy->prev->data;
}

ListElement List::peekNext() const {
	if (this->position() >= this->length()) {
		throw std::length_error("List: peakNext(): position >= length");
	}
	return afterCursor->data;
}

ListElement List::peekPrev() const {
	if (this->position() <= 0) {
		throw std::length_error("List: peakPrev(): position <= 0");
	}
	return beforeCursor->data;
}

int List::position() const {
	return this->pos_cursor;
}

void List::moveFront() {
	beforeCursor = frontDummy;
	afterCursor = beforeCursor->next;
	this->pos_cursor = 0;
}

void List::moveBack() {
	afterCursor = backDummy;
	beforeCursor = afterCursor->prev;
	this->pos_cursor = this->num_elements;
}

ListElement List::moveNext() {
	if (this->position() >= this->length()) {
		throw std::length_error("List: moveNext(): position >= length");
	}
	beforeCursor = beforeCursor->next;
	afterCursor = afterCursor->next;
	this->pos_cursor ++;
	return beforeCursor->data;
}

ListElement List::movePrev() {
	if (this->position() <= 0) {
		throw std::length_error("List: movePrev(): position <= 0");
	}
	beforeCursor = beforeCursor->prev;
	afterCursor = afterCursor->prev;
	this->pos_cursor --;
	return afterCursor->data;
}

void List::insertAfter(ListElement x) {
	Node* N = new Node(x);
	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	afterCursor = N;
	num_elements ++;
}

void List::insertBefore(ListElement x) {
	Node* N = new Node(x);
	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	beforeCursor = N;
	num_elements ++;
	pos_cursor ++;
}

void List::setAfter(ListElement x) {
	Node* N = new Node(x);
	Node* M = this->afterCursor;
	this->beforeCursor->next = N;
	N->prev = this->beforeCursor;
	N->next = this->afterCursor->next;
	this->afterCursor->next->prev = N;
	this->afterCursor = N;
	delete M;
}

void List::setBefore(ListElement x) { Node* N = new Node(x);
	
	Node* M = this->beforeCursor;
	this->afterCursor->prev = N;
	N->next = this->afterCursor;
	N->prev = this->beforeCursor->prev;
	this->beforeCursor->prev->next = N;
	this->beforeCursor = N;
	delete M;
}

void List::clear() {
	this->moveFront();
	while(num_elements > 0) {
		this->eraseAfter();
	}
}
void List::eraseAfter() {
	Node* N = afterCursor;
	afterCursor = afterCursor->next;
	afterCursor->prev = beforeCursor;
	beforeCursor->next = afterCursor;
	num_elements --;
	delete N;
}

void List::eraseBefore() {
	Node* N = beforeCursor;
	beforeCursor = beforeCursor->prev;
	beforeCursor->next = afterCursor;
	afterCursor->prev = beforeCursor;
	delete N;
	this->num_elements --;
	this->pos_cursor --;
}

int List::findNext(ListElement x){
	Node *N = this->afterCursor;
	while(N != this->backDummy) {
		if (N->data == x) {
			this->beforeCursor = N;
			this->afterCursor = N->next;
			this->pos_cursor++;
			return this->pos_cursor;
		}
		N = N->next;
		this->pos_cursor ++;
	}
	this->afterCursor = backDummy;
	this->beforeCursor = afterCursor->prev;
	return -1;
}

int List::findPrev(ListElement x) {
	Node *N = this->beforeCursor;
	if (N == this->backDummy) {
		N = N->prev;
		this->pos_cursor --;
	}
	while(N != this->frontDummy) {
		if (N->data == x) {
			this->afterCursor = N;
			this->beforeCursor = N->prev;
			this->pos_cursor--;
			return this->pos_cursor;
		}
		N = N->prev;
		this->pos_cursor --;
	}
	this->pos_cursor = 0;
	this->beforeCursor = frontDummy;
	this->afterCursor = beforeCursor->next;
	return -1;
}

std::string List::to_string() const {
	std::string s;
        s += "(";	
	List::Node* N = this->frontDummy->next;
	while(N != backDummy) {
		s += std::to_string(N->data);
		N = N->next;
		if (N != backDummy) {
		s += ",";
		}
	}
	s += ")";
	return s;
}

void List::cleanup() {
	Node *N = this->frontDummy->next;
	int outer = 0;
	while(N != this->backDummy) {
		Node *M = N->next;
		int inner = outer + 1;
		while (M != this->backDummy) {
			Node *Z = M->next;
			if (N->data == M->data) {
				Node* erase = M;
				(M->prev)->next = M->next;
				(M->next)->prev = M->prev;
				this->num_elements --;
				delete erase;
				if (inner <= pos_cursor) {
					pos_cursor --;
				}
			}
			M = Z;
			inner++;
		}
		outer++;
		N = N->next;
	}
	int position  = this->pos_cursor; 
	this->moveFront();
	for (int x = 0; x < position; x++) {
		this->moveNext();
	}
	
}

List List::concat(const List& L) const {
	List nL;
	nL.moveBack();
	Node* N = this->frontDummy->next;
	while (N != this->backDummy) {
		nL.insertBefore(N->data);
		N = N->next;	
	}
	N = L.frontDummy->next;
	while (N != L.backDummy) {
		nL.insertBefore(N->data);
		N = N->next;
	}
	nL.beforeCursor = nL.frontDummy;
	nL.afterCursor = nL.beforeCursor->next;
	nL.pos_cursor = 0;
	return nL;
}

bool List::equals(const List& R) const {
	if (this->length() != R.length()) {
		return false;
	}
	Node* N = this->frontDummy->next;
	Node* M = R.frontDummy->next;
	while (N != this->backDummy) {
		if (N->data != M->data) {
			return false;
		}
		N = N->next;
		M = M->next;
	}
	return true;
}

std::ostream& operator<<( std::ostream& stream, const List& L) {
	return stream << L.to_string();
}

bool operator==( const List& A, const List& B ) {
	return A.equals(B);
}

List& List::operator = ( const List& L ) {
	if (this != &L){
		List temp = L;
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(pos_cursor, temp.pos_cursor);
		std::swap(num_elements, temp.num_elements);
	}

	return *this;
}
