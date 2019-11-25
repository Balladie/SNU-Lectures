#ifndef HW3_BST_H
#define HW3_BST_H

#include <iostream>

using namespace std;

class TreeNode {
public:
	int key;
	double data;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int k, double d) {
		key = k;
		data = d;
		left = nullptr;
		right = nullptr;
	}
};

class BST {
protected:
	TreeNode* root;

	int getLevelFromLeaf(TreeNode*);

	TreeNode* find(TreeNode*&, const int&);

	virtual void insert(TreeNode*&, const int&, const double&);

	TreeNode*& rightMostChild(TreeNode*&);

	void remove(TreeNode*&, const int&);
	void doRemoval(TreeNode*&);

	void noChildRemove(TreeNode*&);
	void oneChildRemove(TreeNode*&);
	void twoChildRemove(TreeNode*&);
	void inorder(TreeNode*);

public:
	BST();
	bool isEmpty();
	int getHeight();
	double find(const int&);
	virtual void insert(const int&, const double&);
	virtual void remove(const int&);
	void inorder();
};

#endif