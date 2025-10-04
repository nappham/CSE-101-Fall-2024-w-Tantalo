//Mandy Lau
//mlau16
//pa5

#define DUMMY 0

#include "List.h"
using namespace std;

List::Node::Node(long x){
   data = x;
   prev = nullptr;
   next = nullptr;
}


// Class Constructors & Destructors ----------------------------------------
   
   // Creates new List in the empty state.
List::List(){

    frontDummy = new Node(DUMMY);
    backDummy = new Node(DUMMY);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;

}

   // Copy constructor.
List::List(const List& L){
    frontDummy = new Node(DUMMY);
    backDummy = new Node(DUMMY);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;

    Node* N = L.frontDummy->next;
    while( N != L.backDummy ){
	int data = N->data;
        this->insertBefore(data);
        N = N->next;
    }
}

   // Destructor
List::~List(){
   this->clear();
   delete(this->frontDummy);
   delete(this->backDummy);
}

// Access functions --------------------------------------------------------

   // length()
   // Returns the length of this List.
int List::length() const{
    return(this->num_elements);
}

   // front()
   // Returns the front element in this List.
   // pre: length()>0
ListElement List::front() const{
    if(num_elements <= 0){
      exit(1);
    }
   
   return(frontDummy->next->data);

}

   // back()
   // Returns the back element in this List.
   // pre: length()>0
ListElement List::back() const{
    if(num_elements <= 0){
      exit(1);
    }
   
   return(backDummy->prev->data);
   
}

   // position()
   // Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{	
   return(this->pos_cursor);

}

   // peekNext()
   // Returns the element after the cursor.
   // pre: position()<length()
ListElement List::peekNext() const{
    if(position() >= length()){
      exit(1);
    }
   
   return(afterCursor->data);
    
}

   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
ListElement List::peekPrev() const{
    if(position() <= 0){
      exit(1);
    }

   return(beforeCursor->data);
}


// Manipulation procedures -------------------------------------------------

   // clear()
   // Deletes all elements in this List, setting it to the empty state.
void List::clear(){
   this->moveFront();
   while(num_elements > 0){
      this->eraseAfter();
   }

}

   // moveFront()
   // Moves cursor to position 0 in this List.
void List::moveFront(){
   beforeCursor = frontDummy;
   afterCursor = beforeCursor->next;
   pos_cursor = 0;
}

   // moveBack()
   // Moves cursor to position length() in this List.
void List::moveBack(){
   afterCursor = backDummy;
   beforeCursor = afterCursor->prev;
   this->pos_cursor = this->num_elements;
}

   // moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<length() 
ListElement List::moveNext(){
   if(this->position() >= this->length()){
      exit(1);
   }
      
   afterCursor = afterCursor->next;
   beforeCursor = beforeCursor->next;

   this->pos_cursor += 1;

   return(this->beforeCursor->data);

   
}

   // movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
ListElement List::movePrev(){
   if(position() <= 0){
      exit(1);
   }

   beforeCursor = beforeCursor->prev;
   afterCursor = afterCursor->prev;

   this->pos_cursor--;
   return this->afterCursor->data;
}

   // insertAfter()
   // Inserts x after cursor.
void List::insertAfter(ListElement x) {
	Node* X = new Node(x);
	X->prev = beforeCursor;
	X->next = afterCursor;
	beforeCursor->next = X;
	afterCursor->prev = X;
	afterCursor = X;
	num_elements ++;
}

   // insertBefore()
   // Inserts x before cursor.
void List::insertBefore(ListElement x){
   Node* X = new Node(x);
   X->prev = beforeCursor;
   X->next = afterCursor;
   beforeCursor->next = X;
   afterCursor->prev = X;
   beforeCursor = X;
   num_elements ++;
   pos_cursor ++;
}

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
void List::setAfter(ListElement x){
   if(position() >= length()){
      exit(1);
   }
   Node* N = this->afterCursor;
   Node* M = new Node(x);

   this->beforeCursor->next = N;
   N->prev = this->beforeCursor;
   N->next = this->afterCursor->next;
   this->afterCursor->next->prev = N;
   this->afterCursor = N;
   delete(M);

}

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
void List::setBefore(ListElement x){
   if(position() <= 0){
      exit(1);
   }
   Node* N = this->beforeCursor;
   this->afterCursor->prev = N;
   N->next = this->afterCursor;
   N->prev = this->beforeCursor->prev;
   this->beforeCursor->prev->next = N;
   this->beforeCursor = N;
   //delete(M);

}

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
void List::eraseAfter(){
   if(position() >= length()){
      exit(1);
   }

   Node* X = afterCursor;
   afterCursor = afterCursor->next;
   afterCursor->prev = beforeCursor;
   beforeCursor->next = afterCursor;
   delete(X);

   num_elements -= 1;


}

   // eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
void List::eraseBefore(){
   if(position() <= 0){
      exit(1);
   }

   Node* X = beforeCursor;
   beforeCursor = beforeCursor->prev;
   beforeCursor->next = afterCursor;
   afterCursor->prev = beforeCursor;

   delete(X);

   this->num_elements --;
   this->pos_cursor --;
}


// Other Functions ---------------------------------------------------------

   // findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of element x. If x
   // is found, places the cursor immediately after the found element, then 
   // returns the final cursor position. If x is not found, places the cursor 
   // at position length(), and returns -1. 
int List::findNext(ListElement x){
   while(position() < length()){
      if(moveNext() == x){
         return(pos_cursor);
      }
      //moveNext();

   }
   return(-1);
}

   // findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of element x. If x
   // is found, places the cursor immediately before the found element, then
   // returns the final cursor position. If x is not found, places the cursor 
   // at position 0, and returns -1. 
int List::findPrev(ListElement x) {
	while(this->pos_cursor != 0) {
		if (this->movePrev() == x) {
			return this->pos_cursor;
		}
	}
	return -1;
}

   // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
   // the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
   Node* N = frontDummy->next;
   int a = 0;
   while(N != backDummy){
      Node* M = N->next;
      int b = a + 1;
      while (M != backDummy){
	 Node *Z = M->next;
         if(N->data == M->data){
            Node* E = M;
            (M->prev)->next = M->next;
            (M->next)->prev = M->prev;
            this->num_elements--;
            delete(E);
	    if (b < pos_cursor) {
	    	pos_cursor--;
	    } 
         }
         M = Z;
	 b++;
      }
      N = N->next;
   }
   int pos = pos_cursor;
   this->moveFront();
   for(int i = 0; i < pos; i++){
      this->moveNext();
   }


}
 
   // concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
   List M;
    Node* A = this->frontDummy->next;
    Node* B = L.frontDummy->next;
    while(A != this->backDummy){
        M.insertBefore(A->data);
        A = A->next;
    }
    while(B != L.backDummy){
        M.insertBefore(B->data);
        B = B->next;
    }
    M.moveFront();
    return M;
}

   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
   std::string s;
   s += "(";
   List::Node* N = this->frontDummy->next;
   while(N != backDummy){
      s += std::to_string(N->data);
      N = N->next;
      if (N != backDummy){
         s += ",";
      }
   }
   s += ")";
   return s;
}

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{

   Node* M = this->frontDummy->next;
   Node* N = R.frontDummy->next;

   if(this->length() != R.length()){
      return false; 
   }

   while(M != backDummy){
      if(M->data != N->data){
         return false;
      }
      M = M->next;
      N = N->next;
   }
   return true;
}


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
   return stream << L.to_string();
}

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
   return A.equals(B);
}

   // operator=()
   // Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
   if( this != &L){
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
