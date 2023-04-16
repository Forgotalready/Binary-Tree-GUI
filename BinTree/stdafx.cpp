#include "stdafx.h"

Node* Bintree::tree(int n, Node *p) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 10);
	if (n == 0) return nullptr;
	Node* q = new Node(dist(mt));
	int nL = (n - 1) / 2, nR = n - 1 - nL;
	q->left = tree(nL, q); q->right = tree(nR, q);
	q->parent = p;
	return q;
}


Bintree::Bintree(std::vector<int> &a, int n) {
	for (const int& x : a) add(x, root);
}

void Bintree::add(int k, Node *p) {
	if (p == nullptr) { root = new Node(k); return; }

	if (p->left == nullptr) {
		Node* q = new Node(k);
		p->left = q;
		q->parent = p;
		return;
	}
	if (p->right == nullptr) {
		Node* q = new Node(k);
		p->right = q;
		q->parent = p;
		return;
	}
	if (rand() % 2 == 0) {
		add(k, p->left);
	}
	else {
		add(k, p->right);
	}
}

void Bintree::del(Node* p) {
	if (p == nullptr) return;

	if (p->left == nullptr && p->right == nullptr) {
		Node* par = p->parent;
		bool isLeft = false;
		if (par->left == p) isLeft = true;
		if (isLeft) par->left = nullptr;
		else par->right = nullptr;
		delete p;
		p = nullptr;
		return;
	}
	Node* temp = p;
	while (temp->left != nullptr || temp->right != nullptr) {
		if (temp->left != nullptr) temp = temp->left;
		else if (temp->right != nullptr) temp = temp->right;
	}
	p->key = temp->key;
	//Говорим родителю, что его ребенок nullptr
	Node* par = temp->parent;
	if (par->left == temp) par->left = nullptr;
	else par->right = nullptr;
	delete temp;
	temp = nullptr;
}

void Bintree::clearTree() {
	if (root == nullptr) return;

	while (root->left != nullptr || root->right != nullptr) {
		if (root->left != nullptr) del(root->left);
		if (root->right != nullptr) del(root->right);
	}
	delete root;
	root = nullptr;
}

Bintree::~Bintree() {
	this->clearTree();
}

void printTree(Graphics ^ gr, Node * q, int L, int R, int y)
{
	int x0 = (L + R) / 2;
	int d = 50;
	Pen^ p = gcnew Pen(Color::Black, 2);
	Brush^ br = gcnew SolidBrush(Color::Yellow);
	int x = x0 - d / 2;
	gr->DrawEllipse(p, x, y, d, d);
	gr->FillEllipse(br, x, y, d, d);

	String^ str = System::Convert::ToString(q->key);
	Font^ f = gcnew Font("Arial", 12);
	Brush^ br2 = gcnew SolidBrush(Color::Black);
	gr->DrawString(str, f, br2, x0, y + d / 2 );

	if (q->left != nullptr) { 
		gr->DrawLine(p, (x0 + L) / 2, y + d + 50, x0, y + d);
		printTree(gr, q->left, L, x0, y + d + 50);
	}
	if (q->right != nullptr) {
		gr->DrawLine(p, (R + x0) / 2, y + d + 50, x0, y + d);
		printTree(gr, q->right, x0, R, y + d + 50);
	}
}
