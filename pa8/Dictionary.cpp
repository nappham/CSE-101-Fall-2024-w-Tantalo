//---------------------------------------------
// Dictionary.cpp
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 8
//----------------------------------------------

#include<iostream>
#include<string>
#include"Dictionary.h"

#define BLACK 1
#define RED 2  

using namespace std;

Dictionary::Node::Node(keyType k, valType v) {	
	key = k;
	val = v;
	color = RED;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}


Dictionary::Dictionary() {
	nil = new Node("NIL", BLACK);
	nil->color = BLACK;
	nil->left = nil->right = nil;
	root = nullptr;
	current = nil;
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
	nil = new Node("NIL", BLACK);
	nil->color = BLACK;
	nil->left = nil->right = nil;
	root = nullptr;
	num_pairs = 0;
	current = nil;
	preOrderCopy(D.root, nullptr);
}

Dictionary::~Dictionary() {
	postOrderDelete(root);
	delete nil;
}

int Dictionary::getColor(Node *R) {
	return R->color;
}
void Dictionary::inOrderString(std::string& s, Node* R) const {
	if (R == nullptr || R->key == nil->key) {
		return;
	}	
	inOrderString(s, R->left);
	s += R->key + " : " + std::to_string(R->val) + "\n";
	inOrderString(s, R->right);
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
	if (R == nullptr || R->key == nil->key) {
		return;
	}
	if (R->color == RED) {
		s += R->key + " (RED)\n";
	} else {
		s += R->key + "\n";
	}
	preOrderString(s, R->left);
	preOrderString(s, R->right);
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
	if (R == N || R == nil || R == nullptr) {
		return;
	}
	setValue(R->key, R->val);
	preOrderCopy(R->left, N);
	preOrderCopy(R->right, N);
}

void Dictionary::postOrderDelete(Node* R) {
	if (R == nullptr || R == nil) {
		return;
	}
	postOrderDelete(R->left);
	postOrderDelete(R->right);
	delete R;
	num_pairs--;
}

Dictionary::Node* Dictionary::findMin(Node* R) {
	if (R == nullptr) {
		return nil;
	}
	Node* N = R;
	while (N->left != nil) {
		N = N->left;
	}	
	return N;
}

Dictionary::Node* Dictionary::findMax(Node *R) {
	if (R == nullptr) {
		return nil;
	}
	Node *N = R;
	while (N->right != nil) {
		N = N->right;
	}
	return N;
}

Dictionary::Node* Dictionary::findNext(Node *N) {
	if (N == nil || N == nullptr || N == findMax(root)) {
		return nil;
	}
	if (N->right != nil) {
		return findMin(N->right);
	}
	Node* M = N->parent;
	while (M != nil && M == M->right) {
		N = M;
		M = M->parent;
	}
	return M == nullptr ? nil : M;
}

Dictionary::Node* Dictionary::findPrev(Node *N) {
	if (N == nullptr || N == nil || N == findMin(root)) {
		return nil;
	}
	if (N->left != nil) {
		return findMax(N->left);
	}
	Node* M = N->parent;
	while(M != nullptr && M->left == N) {
		N = M;
		M = M->parent;
	}
	return M;
}

int Dictionary::size() const {
	return num_pairs;
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
	if (R == nullptr || R == nil) {
		return R;
	} else if (R->key == k) {
		return R;
	} else if (R->key > k) {
		return search(R->left, k);
	} else {
		return search(R->right, k);
	}
}

bool Dictionary::contains(keyType k) const {
	Node* N = search(root, k);
	if (N == nullptr || N == nil) {
		return false;
	} else {
		return true;
	}
}

bool Dictionary::hasCurrent() const {
	return current != nil;
}

keyType Dictionary::currentKey() const {
	if (!hasCurrent()) {
		throw std::logic_error("Dictionary: currentKey(): current undefined.");
	}
	return current->key;
}

valType& Dictionary::currentVal() const {
	if (!hasCurrent()) {
		throw std::logic_error("Dictionary: currentVal(): current undefined.");
	}
	return current->val;
}

void Dictionary::clear() {
	postOrderDelete(root);
	current = nil;
	root = nil;
	num_pairs = 0;
}

valType& Dictionary::getValue(keyType k) const {
    Node* N = search(root, k);
    if (N == nil) {
        throw std::invalid_argument("Dictionary: getValue(): key does not exist.");
    }
    return N->val;
}


void Dictionary::setValue(keyType k, valType v) {
	Node* insertion = new Node(k, v);
	insertion->left = nil;
	insertion->right = nil;
	num_pairs++;
	if (num_pairs == 1) {
		insertion->color = BLACK;
		root = insertion;
		return;
	}
	Node* parse = this->root;
	Node* guardian = nullptr;
	while(parse != nil && parse != nullptr) {
		guardian = parse;
		if(k < parse->key) {
			parse = parse->left;
		} else if (k > parse->key) {
			parse = parse->right;
		} else if (k == parse->key) {
			num_pairs--;
			parse->val = insertion->val;
			delete insertion;
			return;
		}
		
	}

	insertion->parent = guardian;
	if (insertion->key < guardian->key) {
		guardian->left = insertion;
	} else if (insertion->key > guardian->key) {
		guardian->right = insertion;
	}
	RB_InsertFixUp(insertion);	
}

void Dictionary::RB_InsertFixUp(Node* Z) {
	if (Z->parent == nullptr) {
		return;
	} else if (Z->parent->parent == nullptr) {
		return;
	}
	
	while (Z->parent->color == RED) {
		if (Z->parent == Z->parent->parent->left) {
			Node* Y = Z->parent->parent->right;
			if (Y == nil || Y->color == BLACK) { 
				if (Z == Z->parent->right) {
					Z = Z->parent;
					LeftRotate(Z);
				}
				Z->parent->color = BLACK;
				Z->parent->parent->color = RED;
				RightRotate(Z->parent->parent);
			} else {
				Z->parent->color = BLACK;
				Y->color = BLACK;
				Z->parent->parent->color = RED;
				Z = Z->parent->parent;
			}
		} else {
			Node* Y = Z->parent->parent->left;	
			if (Y->color == RED) {
				Z->parent->color = BLACK;
				Y->color = BLACK;
				Z->parent->parent->color = RED;
				Z = Z->parent->parent;
			} else {
				if (Z == Z->parent->left) {
					Z = Z->parent;
					RightRotate(Z);
				}
				Z->parent->color = BLACK;
				Z->parent->parent->color = RED;
				LeftRotate(Z->parent->parent);
			}
		}
		root->color = BLACK;
	        if (Z->parent == nullptr || Z->parent->parent == nullptr) {
                	return;
		}
	}
}

void Dictionary::LeftRotate(Node* N) {
	Node* M = N->right;
	N->right = M->left;
	if (M->right != nil) {
		N->right->parent = N;
	}
	M->parent = N->parent;
	if (N->parent == nullptr) {
		root = M;
	} else if (N->parent->left == N) {
		N->parent->left = M;
	} else {
		N->parent->right = M;
	}
	N->parent = M;
	M->left = N;
}

void Dictionary::RightRotate(Node* N) {
	Node* M = N->left;
	N->left = M->right;
	if (N->left != nil) {
		N->left->parent = N;
	}
	M->parent = N->parent;
	if (M->parent == nullptr) {
		root = M;
	} else if (N == N->parent->right) {
		N->parent->right =  M;
	} else {
		N->parent->left = M;
	}
	N->parent = M;
	M->right = N;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
	if (u->parent == nil || u->parent == nullptr) {
		root = v;
	} else if (u == u->parent->left) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N) {
	while (N != root && N->color == BLACK) {
		if (N == N->parent->left) {
			Node* W = N->parent->right;
			if (W->color == RED) {
				W->color = BLACK;
				N->parent->color = RED;
				LeftRotate(N->parent);
				W = N->parent->right;
			}
			if (W->left->color == BLACK && W->right->color == BLACK) {
				W->color = RED;
				N = N->parent;
			} else {
				if (W->right->color == BLACK) {
					W->left->color = BLACK;
					W->color = RED;
					RightRotate(W);
					W = N->parent->right;
				}
				W->color = N->parent->color;
				N->parent->color = BLACK;
				W->right->color = BLACK;
				LeftRotate(N->parent);
				N = root;
			}
		} else {
			Node* W = N->parent->left;
			if (W->color == RED) {
				W->color = BLACK;
				N->parent->color = RED;
				RightRotate(N->parent);
				W = N->parent->left;
			}
			if (W->right->color == BLACK && W->left->color == BLACK) {
				W->color = RED;
				N = N->parent;
			} else {
				if (W->left->color == BLACK) {
					W->right->color = BLACK;
					W->color = RED;
					LeftRotate(W);
					W = N->parent->left;
				}
				W->color = N->parent->color;
				N->parent->color = BLACK;
				W->left->color = BLACK;
				RightRotate(N->parent);
				N = root;
			}			
		}
	}
	N->color = BLACK;
}

void Dictionary::remove(keyType k) {
	Node * N = search(root, k);
	if (N == nil || N == nullptr) {
		throw std::logic_error("Error\n");
	}
	RB_Delete(N);
	if (N == current) {
		current = nil;
	}
	delete N;
	num_pairs--;

}

void Dictionary::RB_Delete(Node* N) {
	Node* Y = N;
	Node* X = nullptr;
        int originalColor = Y->color;
        if (N->left == nil) {
                X = N->right;
                RB_Transplant(N, N->right);
        } else if (N->right == nil) {
                X = N->left;
                RB_Transplant(N, N->left);
        } else {
                Y = findMin(N->right);
                originalColor = Y->color;
                X = Y->right;
                if (Y->parent == N) {
                        X->parent = Y;
                } else {
                        RB_Transplant(Y, Y->right);
                        Y->right = N->right;
                        Y->right->parent = Y;
                }
                RB_Transplant(N, Y);
                Y->left = N->left;
                Y->left->parent = Y;
                Y->color = N->color;
        }
        if (originalColor == BLACK) {
                RB_DeleteFixUp(X);
        }

}

void Dictionary::begin() {
	if (root == nil || root == nullptr) {
		return;
	} else {
		current = findMin(root);
	}
}

void Dictionary::end() {
	if (root == nil || root == nullptr) {
		return;
	} else {
		current = findMax(root);
	}
}

void Dictionary::next() {
	current = findNext(current);
}

void Dictionary::prev() {
	current = findPrev(current);
}

std::string Dictionary::to_string() const{
	string s = "";
       	inOrderString(s, root);
	return s;       
}

std::string Dictionary::pre_string() const{
	string s = "";
	preOrderString(s, root);
	return s;
}

bool Dictionary::equals(const Dictionary& D) const{ 
	if (to_string() == D.to_string()) {
		return true;
	} else {
		return false;
	}
}

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
return stream << D.to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
if (this != &D) {
	clear();
	if (D.root != D.nil) {
		preOrderCopy(D.root, nil);
	}
}
return *this;
}
 



