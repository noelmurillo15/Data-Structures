#pragma once

template<typename type>
class BST{

	struct Node{

		type data;
		Node *left;
		Node *right;

		Node(){ data = nullptr; left = nullptr; right = nullptr; }
		Node(type d) { data = d; left = nullptr; right = nullptr; }
	};

	Node *root;

	void case0(Node *c, Node *p);
	void case1(Node *c, Node *p);

public:

	BST();
	~BST();

	BST(const BST &_cpy);
	BST& operator=(const BST &_asn);

	bool findAndRemove(const type &v);
	bool find(const type &v) const;

	void insert(const type &v);
	void inOrder(Node *n) const;
	void postOrder(Node *n);
	void preOrder(Node *n);
	void printInOrder() const;
	void clear();
};

template<typename type>
BST<type>::BST(){
	root = nullptr;
}

template<typename type>
BST<type>::~BST(){
	clear();
	delete root;
}

template<typename type>
BST<type>::BST(const BST &_cpy){
	root = nullptr;
	preOrder(_cpy.root);
}

template<typename type>
BST<type>& BST<type>::operator=(const BST &_asn){

	if (this != &_asn){
		clear();
		root = nullptr;
		preOrder(_asn.root);
	}
	return *this;
}

template<typename type>
void BST<type>::insert(const type& v){

	Node* add = new Node(v);

	if (root == nullptr){
		root = add;
		return;
	}
	Node * curr = root;
	while (curr != nullptr){
		if (add->data < curr->data){ //less
			if (curr->left == nullptr){
				curr->left = add;
				return;
			}
			else{
				curr = curr->left;
			}
		}
		else if (add->data >= curr->data){ //greater
			if (curr->right == nullptr){
				curr->right = add;
				return;
			}
			else{
				curr = curr->right;
			}
		}
	}
}

template<typename type>
bool BST<type>::findAndRemove(const type& v){

	if (find(v)){
		Node *curr = root;
		Node *parent = root;

		if (v > root->data)
			curr = root->right;
		else if (v < root->data)
			curr = root->left;

		while (curr->data != v){
			parent = curr;
			if (v > curr->data){
				curr = curr->right;
			}
			else{
				curr = curr->left;
			}
		}

		if (curr->right != nullptr && curr->left != nullptr){ // case 2
			Node *min = curr->right;
			while (min->left != nullptr){
				parent = min;
				min = min->left;
			}

			curr->data = min->data;
			min->data = v;

			curr = min;

			if (curr->left == nullptr && curr->right == nullptr) // case0
				case0(curr, parent);
			else // case1
				case1(curr, parent);

		}
		else if (curr->right == nullptr && curr->left == nullptr){ // case 0
			case0(curr, parent);
		}
		else { // case 1
			case1(curr, parent);
		}

		return true;
	}
	return false;
}

template<typename type>
bool BST<type>::find(const type& v) const{

	Node* curr = root;

	while (curr != nullptr){
		if (v == curr->data){
			return true;
		}
		else if (v < curr->data){ //less
			curr = curr->left;
		}
		else if (v >= curr->data){ //greater
			curr = curr->right;
		}
	}
	return false;
}

template<typename type>
void BST<type>::clear(){
	postOrder(root);
}

template<typename type>
void BST<type>::postOrder(Node* n){

	if (n)
	{
		postOrder(n->left);
		postOrder(n->right);
		delete n;
	}
	root = nullptr;
}

template<typename type>
void BST<type>::inOrder(Node* n) const{

	if (n)
	{
		inOrder(n->left);
		cout << n->data << ' ';
		inOrder(n->right);
	}
}

template<typename type>
void BST<type>::preOrder(Node* n){

	if (n)
	{
		insert(n->data);
		preOrder(n->left);
		preOrder(n->right);
	}
}

template<typename type>
void BST<type>::printInOrder() const{

	inOrder(root);
	cout << endl;
}

template<typename type>
void BST<type>::case0(Node *c, Node* p){
	if (c == root){
		root = nullptr;
	}
	else if (p->left == c){
		p->left = nullptr;
	}
	else{
		p->right = nullptr;
	}
	delete c;
}

template<typename type>
void BST<type>::case1(Node * c, Node * p){

	if (c == root){
		if (c->right != nullptr)
			root = root->right;
		else
			root = root->left;

		delete c;
	}
	else{
		if (c->left == nullptr){
			if (p->left == c)
				p->left = c->right;
			else
				p->right = c->right;
		}
		else if (c->right == nullptr){
			if (p->right == c)
				p->right = c->right;
			else
				p->left = c->right;
		}
		delete c;
	}
}