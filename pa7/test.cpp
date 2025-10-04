//---------------------------------------------
// Dictionary.cpp
// Nathan Pham
// UserID: nappham
// Student ID: 2069891
// Assignment: 7
//----------------------------------------------

#include<iostream>
#include<string>
#include"Dictionary.h"

using namespace std;

Dictionary::Node::Node(keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}
Dictionary::Dictionary() {
	nil = new Node("NIL", -1);
	root = nullptr;
	current = nil;
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
	nil = new Node("NIL", -1);
	root = nullptr;
	num_pairs = 0;
	current = nil;
	preOrderCopy(D.root, nullptr);
}

Dictionary::~Dictionary() {
	postOrderDelete(root);
	delete nil;
}

void Dictionary::inOrderString(std::string& s, Node* R) const {
	if (R == nullptr) {
		return;
	}	
	inOrderString(s, R->left);
	s += R->key + " : " + std::to_string(R->val) + "\n";
	inOrderString(s, R->right);
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
	if (R == nullptr) {
		return;
	}
	s += R->key + "\n";
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
	if (R == nullptr) {
		return;
	}
	postOrderDelete(R->left);
	postOrderDelete(R->right);
	delete R;
	//current = nil;
	num_pairs--;
}

Dictionary::Node* Dictionary::findMin(Node* R) {
	if (R == nullptr) {
		return nil;
	}
	Node* N = R;
	while (N->left != nullptr) {
		N = N->left;
	}	
	return N;
}

Dictionary::Node* Dictionary::findMax(Node *R) {
	if (R == nullptr) {
		return nil;
	}
	while (R->right != nullptr) {
		R = R->right;
	}
	return R;
}

Dictionary::Node* Dictionary::findNext(Node *N) {
	if (N == nil || N == nullptr) {
		return nil;
	}
	if (N->right != nil) {
		return findMin(N->right);
	}
	Node* M = N->parent;
	while (M != nullptr && M == M->right) {
		N = M;
		M = M->parent;
	}
	return M == nullptr ? nil : M;
}

Dictionary::Node* Dictionary::findPrev(Node *N) {
	if (N == nullptr || N == nil || N == findMin(root)) {
		return nil;
	}
	if (N->left != nullptr) {
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
	num_pairs++;
	//if (num_pairs == 1) {
	//	root = insertion;
	//	return;
	//}
	Node* parse = this->root;
	Node* parent = nullptr;
	while(parse != nullptr) {
		parent = parse;
		if(insertion->key < parse->key) {
			parse = parse->left;
		} else if (insertion->key > parse->key) {
			parse = parse->right;
		} else if (insertion->key == parse->key) {
			num_pairs--;
			parse->val = v;
			return;
		}
	}
	insertion->parent = parent;
	if (parent == nil) {
		root = insertion;
		return;
	} else if (insertion->key < parent->key) {
		parent->left = insertion;
		return;
	} else {
		parent->right = insertion;
		return;
	}
}

void Dictionary::remove(keyType k) {
	Node* removal = search(root, k);
	if (removal == nil || removal == nullptr) {
		throw std::logic_error("Removal(): Keytype doesn't exist");;
	}

	if(current == removal) {
		current = nil;
	}
	num_pairs--;
	if (removal->left == nullptr && removal->right == nullptr) {
		if (removal->parent == nullptr) {
			root = nil;
			delete removal;
			return;
		} else if (removal->parent->left == removal) {
			removal->parent->left = nullptr;
			delete removal;
			return;
		} else {
			removal->parent->right = nullptr;
			delete removal;
			return;
		}
	} 
	if (removal->left == nullptr) {
		if (removal->parent == nullptr) {
			removal->right = root;
			removal->right->parent = nullptr;
			delete removal;
			return;
		} else if (removal->parent->right == removal) {
			removal->parent->right = removal->right;
			removal->right->parent = removal->parent;
			delete removal;
			return;
		} else if (removal->parent->left == removal) {
			removal->parent->left = removal->right;
			removal->right->parent = removal->parent;
			delete removal;
			return;
		}
	} else if (removal->right == nullptr) {
		if (removal->parent == nullptr) {
			removal->left = root;
			removal->left->parent = nullptr;
			delete removal;
			return;
		} else if (removal->parent->right == removal) {
			removal->parent->right = removal->left;
			removal->left->parent = removal->parent;
			delete removal;
			return;
		} else if (removal->parent->left == removal) {
			removal->parent->left = removal->left;
			removal->left->parent = removal->parent;
			delete removal;
			return;
		}
	}
	Node* min = findMin(removal->right);
	keyType temp = min->key;
	num_pairs++;
	remove(temp);
	removal->key = temp;
	removal->val = min->val;

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
	Dictionary D = *this;
       	inOrderString(s, D.root);
	return s;       
}

std::string Dictionary::pre_string() const{
	Dictionary D = *this;
	std::string s = "";
	preOrderString(s, root);
	return s;
}

bool Dictionary::equals(const Dictionary& D) const{ 
	if (to_string() == D.to_string()) {
		printf("True\n");
		return true;
	} else {
		printf("False\n");
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
 

