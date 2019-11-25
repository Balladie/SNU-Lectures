#include "BST.h"

BST::BST() {
	root = nullptr;
}

bool BST::isEmpty() {
	return root == nullptr;
}

int BST::getLevelFromLeaf(TreeNode* curr_node) {
	return (curr_node == nullptr) ?
		-1 : __max(getLevelFromLeaf(curr_node->left),
			getLevelFromLeaf(curr_node->right)) + 1;
}

int BST::getHeight() {
	return (root == nullptr) ? -1 : getLevelFromLeaf(root);
}

TreeNode* BST::find(TreeNode*& curr_node, const int& key) {
	if (curr_node == nullptr) return nullptr;
	else if (curr_node->key == key) return curr_node;
	else if (key < curr_node->key)
		return find(curr_node->left, key);
	else
		return find(curr_node->right, key);
}

double BST::find(const int& key) {
	if (find(root, key) == nullptr)
		return -1;
	else
		return find(root, key)->data;
}

void BST::insert(TreeNode*& curr_node, const int& key,
	const double& data) {
	if (curr_node == nullptr)
		curr_node = new TreeNode(key, data);
	else if (curr_node->key == key)
		curr_node->data = data;
	else if (key < curr_node->key)
		insert(curr_node->left, key, data);
	else
		insert(curr_node->right, key, data);
}

void BST::insert(const int& key, const double& data) {
	insert(root, key, data);
}

TreeNode*& BST::rightMostChild(TreeNode*& curr_node) {
	return (curr_node->right != nullptr) ?
		rightMostChild(curr_node->right) : curr_node;
}

void BST::remove(TreeNode*& curr_node, const int& key) {
	if (curr_node != nullptr) {
		if (key == curr_node->key)
			doRemoval(curr_node);
		else if (key < curr_node->key)
			remove(curr_node->left, key);
		else
			remove(curr_node->right, key);
	}
}

void BST::doRemoval(TreeNode*& curr_node) {
	if ((curr_node->left == nullptr) &&
		(curr_node->right == nullptr))
		noChildRemove(curr_node);
	else if ((curr_node->left != nullptr)
		&& (curr_node->right != nullptr))
		twoChildRemove(curr_node);
	else
		oneChildRemove(curr_node);
}

void BST::remove(const int& key) {
	remove(root, key);
}

void BST::noChildRemove(TreeNode*& curr_node)
{
	delete curr_node;
	curr_node = nullptr;
}

void BST::oneChildRemove(TreeNode*& curr_node)
{
	TreeNode* tmp;

	if (curr_node->left != nullptr)
		tmp = curr_node->left;
	else
		tmp = curr_node->right;

	delete curr_node;
	curr_node = tmp;
}

void BST::twoChildRemove(TreeNode*& curr_node)
{
	TreeNode*& pred = rightMostChild(curr_node->left);
	curr_node->key = pred->key;
	curr_node->data = pred->data;
	doRemoval(pred);
}

void BST::inorder()
{
	inorder(root);
	cout << endl;
}

void BST::inorder(TreeNode* curr_node)
{
	if (curr_node->left != nullptr)
		inorder(curr_node->left);

	cout << "[" << curr_node->key << ", " << curr_node->data << "] ";

	if (curr_node->right != nullptr)
		inorder(curr_node->right);
}