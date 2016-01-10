#ifndef NODE_H 
#define NODE_H 
#include <iostream>
#include <vector>

class Node {
	private:
		int val;
		Node* left;
		Node* right;
		Node* parent;

		// Only for Red-Black trees
		bool red;
	public:
		// Construct a new Node by providing a value and its children
		Node(int val_n,Node* left_n,Node* right_n,bool red_n=false)
		{
			val = val_n;
			left = left_n;
			right = right_n;
			if (left_n) left_n->setParent(this);
			if (right_n) right_n->setParent(this);
			parent = NULL;

			// Only for Red-Black trees
			red = red_n;
		}
		Node* getLeftChild() { return this->left; }
		void setLeftChild(Node* left_n) { this->left = left_n; }
		Node* getRightChild() { return this->right; }
		void setRightChild(Node* right_n) { this->right = right_n; }
		Node* getParent() { return this->parent; } 
		void setParent(Node* parent_n) { this->parent = parent_n; }
		int getValue() { return this->val; }
		void setValue(int val_n) { this->val = val_n; }

		// Only used in Red-Black trees
		bool isRed() { return red; }
		void setRed(bool redness) { red = redness; }
};

#endif
