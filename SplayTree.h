#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>
#include <string>

using namespace std;

class SplayTree;

class SplayNode{
public:
	friend class SplayTree;
	SplayNode(int d = 0, SplayNode *l = NULL, SplayNode *r = NULL, SplayNode *p = NULL) :
		data(d), left(l), right(r), par(p) {}
	~SplayNode() { delete left; delete right; }

	void printPreorder(ostream &os = cout, string indent = "") const;

	int getData() { return data; }
	SplayNode* getLeft() { return left; }
	SplayNode* getRight() { return right; }
	SplayNode* minNode();

protected:
	int data;
	SplayNode* left;
	SplayNode* right;
	SplayNode* par; //parent pointer
};

class SplayTree{
public:
	SplayNode *root;

	SplayTree() : root(NULL) {}
	virtual ~SplayTree() { delete root; }

	void insertNode(int data);
	void deleteNode(int data);
	SplayNode* find(int data);
	void swap(SplayNode* old, SplayNode* newer);
	void search(int data);

	void printPreorder(ostream &os = cout) const
	{
		if (root) root->printPreorder(os);
	}

	SplayNode* getRoot() { return root; }

protected:

	void rotateLeft(SplayNode* current);
	void rotateRight(SplayNode* current);
	void splay(SplayNode* current);
};

#endif // SPLAY_TREE_H
