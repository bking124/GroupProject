#include "SplayTree.h"

using namespace std;

void SplayNode::printPreorder(ostream &os, string indent) const{
	if (this != NULL) {
		os << indent << this->data << endl;
		this->left->printPreorder(os, indent + "  ");
		this->right->printPreorder(os, indent + "  ");
	}
	else
		os << indent << "NULL" << endl;
}

SplayNode* SplayNode::minNode(){
	SplayNode* temp = this;
	if (temp != NULL) {
		while (temp->left != NULL)
			temp = temp->left;
	}
	return temp;
}

SplayNode* SplayTree::find(int data){
	SplayNode* temp = root;
	//Default return value if not found
	SplayNode* result = NULL;
	while (temp != NULL && result != temp) {
		if (data > temp->data)
			temp = temp->right;
		else if (data < temp->data)
			temp = temp->left;
		else
			result = temp;
	}
	return result;
}

void SplayTree::swap(SplayNode* old, SplayNode* newer){
	if (old->par == NULL)
		root = newer;
	else if (old == old->par->left)
		old->par->left = newer;
	else
		old->par->right = newer;
	if (newer != NULL)
		newer->par = old->par;
}

void SplayTree::search(int data){
	SplayNode* temp = find(data);
	if (temp != NULL)
		splay(temp);
	else {
		SplayNode* temp = root;
		while (temp != NULL) {
			if (data > temp->data)
				temp = temp->right;
			else if (data < temp->data)
				temp = temp->left;
		}
		splay(temp->par);
	}
}

void SplayTree::insertNode(int data){
	if (root == NULL)
		root = new SplayNode(data);
	else {
		SplayNode* temp = root;
		bool insert = false;

		//Find place to insert and create node
		while (!insert && data != temp->data) {

			//Insert to the left
			if (data < temp->data) {
				if (temp->left == NULL) {
					temp->left = new SplayNode(data);
					temp->left->par = temp;
					splay(temp->left);
					insert = true;
				}
				else
					temp = temp->left;
			}

			//Insert to the right
			else if (data > temp->data){
				if (temp->right == NULL) {
					temp->right = new SplayNode(data);
					temp->right->par = temp;
					splay(temp->right);
					insert = true;
				}
				else
					temp = temp->right;
			}
		}
		if (!insert)
			splay(temp);
	}
}

void SplayTree::deleteNode(int data){
	SplayNode* temp = find(data);
	SplayNode* parent = NULL;

	if (temp != NULL) {

		//Leaf Node; simply delete the node
		if (temp->left == NULL && temp->right == NULL) {
			parent = temp->par;
			swap(temp, NULL);
			temp->par = NULL;
			delete temp;
		}

		//Node to be deleted has two children
		//Idea: Store leftmost child of the right subtree, then remove that data
		//Set child's data equal to the stored value
		//The actual delete will be handled by one of the other two cases
		else if (temp->left != NULL && temp->right != NULL) {
			int min = temp->right->minNode()->data;
			deleteNode(min);
			temp->data = min;
		}
		//Node to be deleted has only one child
		else {
			parent = temp->par;
			if (temp->left == NULL){
				swap(temp, temp->right);
				temp->right = NULL;
			}
			else if (temp->right == NULL){
				swap(temp, temp->left);
				temp->left = NULL;
			}
			temp->par = NULL;
			delete temp;
		}

		splay(parent);
	}
}

void SplayTree::splay(SplayNode* cur){
	//Repeat until cur == root
	while (cur->par != NULL){

		//One rotation needed (simple zig)
		if (cur->par->par == NULL){
			if (cur->par->left == cur)
				rotateRight(cur->par);
			else
				rotateLeft(cur->par);
		}

		//Zig-Zig Rotation in left subtree of cur->par->par
		else if ( cur->par->left == cur && cur->par->par->left == cur->par) {
			rotateRight(cur->par->par);
			rotateRight(cur->par);
		}

		//Zig-Zig Rotation in right subtree of cur->par->par
		else if (cur->par->right == cur && cur->par->par->right == cur->par) {
			rotateLeft(cur->par->par);
			rotateLeft(cur->par);
		}

		//Zig-Zag Rotation in right subtree of cur->par->par
		else if (cur->par->left == cur && cur->par->par->right == cur->par) {
			rotateRight(cur->par);
			rotateLeft(cur->par);
		}

		//Only other option: Zig-Zag Rotation in left subtree of cur->par->par
		else {
			rotateLeft(cur->par);
			rotateRight(cur->par);
		}
	}
}

void SplayTree::rotateLeft(SplayNode* cur){
	SplayNode* temp = cur->right;

	//Perform rotations by moving around left and right pointers
	if (temp != NULL){
		cur->right = temp->left;
		if (temp->left != NULL)
			temp->left->par = cur;
		temp->par = cur->par;
		temp->left = cur;
	}

	//Fix parent pointers
	if (cur->par == NULL)
		root = temp;
	else if (cur == cur->par->left)
		cur->par->left = temp;
	else
		cur->par->right = temp;
	cur->par = temp;
}

void SplayTree::rotateRight(SplayNode* cur){
	SplayNode* temp = cur->left;

	//Perform rotations by moving around left and right pointers
	if (temp != NULL){
		cur->left = temp->right;
		if (temp->right != NULL)
			temp->right->par = cur;
		temp->par = cur->par;
		temp->right = cur;
	}

	//Fix parent pointers (same as in leftRotate)
	if (cur->par == NULL)
		root = temp;
	else if (cur == cur->par->left)
		cur->par->left = temp;
	else
		cur->par->right = temp;
	cur->par = temp;
}
