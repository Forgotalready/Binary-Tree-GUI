#pragma once

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <random>
#include <string>
using namespace System;
using namespace System::Drawing;

class Node
{
	int key;
	Node *left, *right, *parent;
public:
	Node(int k = 0, Node *L = 0, Node *R = 0, Node *P = 0)
	{
		key = k; left = L; right = R; parent = P;
	}
	friend class Bintree;
	friend void printTree(Graphics^ gr, Node *q, int L, int R, int y);
};

class Bintree
{
	Node* root;
	Node* tree(int n, Node *p);
public:
	void add(int k, Node *p);
	Bintree() { root = NULL; }
	Bintree(std::vector<int> &a, int n);
	~Bintree();
	void del(Node *p);
	Node* getRoot() { return root; }
	void clearTree();
};

void printTree(Graphics^ gr, Node *q, int L, int R, int y);