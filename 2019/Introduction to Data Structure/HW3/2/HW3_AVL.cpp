#include "HW3_AVL.h"

AVL::AVL() {

}

void AVL::insert(const int& key, const double& data) {
	insert(root, key, data);
}

void AVL::remove(const int& key) {
	remove(root, key);
}

int AVL::BF(TreeNode* curr_node) {
	return getLevelFromLeaf(curr_node->left) - getLevelFromLeaf(curr_node->right);
}

void AVL::insert(TreeNode*& curr_node, const int& key, const double& data) {
	if (curr_node == nullptr) {
		curr_node = new TreeNode(key, data);
	}
	else if (key < curr_node->key) {
		insert(curr_node->left, key, data);

		// Left is bigger
		if (BF(curr_node) == 2) {
			if (BF(curr_node->left) == 1) {
				// right
				rotateSingle(curr_node);
			}
			else {
				// left-right
				rotateDouble(curr_node);
			}
		}
	}
	else if (key > curr_node->key) {
		insert(curr_node->right, key, data);

		// Right is bigger
		if (BF(curr_node) == -2) {
			if (BF(curr_node->right) == -1) {
				// left
				rotateSingle(curr_node);
			}
			else {
				// right-left
				rotateDouble(curr_node);
			}
		}
	}
	else if (key == curr_node->key) {
		curr_node->data = data;
	}

	return;
}

void AVL::rotateSingle(TreeNode*& curr_node) {
	// right rotation (left is bigger)
	if (BF(curr_node) > 0) {
		TreeNode* L3 = curr_node->left->right;
		TreeNode* tmp_cur = curr_node;
		curr_node = curr_node->left;
		curr_node->right = tmp_cur;
		tmp_cur->left = L3;
	}
	// left rotation (right is bigger)
	else if (BF(curr_node) < 0) {
		TreeNode* L2 = curr_node->right->left;
		TreeNode* tmp_cur = curr_node;
		curr_node = curr_node->right;
		curr_node->left = tmp_cur;
		tmp_cur->right = L2;
	}
}

void AVL::rotateDouble(TreeNode*& curr_node) {
	// left-right
	if (BF(curr_node) > 0) {
		rotateSingle(curr_node->left);
		rotateSingle(curr_node);
	}
	// right-left
	else if (BF(curr_node) < 0) {
		rotateSingle(curr_node->right);
		rotateSingle(curr_node);
	}
}

void AVL::remove(TreeNode*& curr_node, const int& key) {
	if (curr_node != nullptr) {
		if (key == curr_node->key) {
			doRemoval(curr_node);
		}
		else if (key < curr_node->key) {
			remove(curr_node->left, key);
		}
		else {
			remove(curr_node->right, key);
		}

		if (curr_node != nullptr) {
			if (BF(curr_node) == -2) {
				int tmp_bf = BF(curr_node->right);

				if (tmp_bf == -1 || tmp_bf == 0)
					rotateSingle(curr_node);
				else
					rotateDouble(curr_node);
			}
			else if (BF(curr_node) == 2) {
				int tmp_bf = BF(curr_node->left);

				if (tmp_bf == 1 || tmp_bf == 0)
					rotateSingle(curr_node);
				else
					rotateDouble(curr_node);
			}
		}
	}
}