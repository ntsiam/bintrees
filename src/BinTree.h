#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include <vector>
#include "Node.h"



class BinTree {
	private:
		Node* root;
	public:
		// Construct a new BinTree by providing a value for the root node
		BinTree(int val_n);

		// Construct a new BinTree by providing a root node
		BinTree(Node* root_n);
		 
		// Construct a new BinTree by providing an array of node values - use NewBinTree()
		BinTree(std::vector<int>* val_n,void (*insertFunction)(Node** root_n,int val_n));

		// Construct a new BinTree by providing an array of node values
		static BinTree* NewBinTree(std::vector<int> val_n);

		Node* getRoot();
		void setRoot(Node* root_n);

		// Print the tree contents in a pre-order fashion
		void printPreOrder();

		// Print the tree structure by level, bottom-up
		// Ignore RBTree parameter if BinTree, set it to "true" if Red-Black Tree
		void ShowTree(bool RBTree = false);

		// Search for a specific value in the tree. Returns NULL if not found.
		Node* TreeSearch(int k);

		// Find the minimum value in the tree
		Node* TreeMin();

		// Find the successor of a specific node (successor: the node with the 
		// smallest value greater than the current)
		Node* TreeSucc(Node* node_n);

		// Insert new node in the tree, providing an existing node
		void TreeInsert(Node* node);

		// Static Equivalent of above
		static void TreeInsert(Node* root,Node* node);

		// Insert a new node in the tree, providing a value
		void TreeInsert(int val_n);

		// The static equivalent of TreeInsert
		static void TreeInsert(Node** root, int val_n);

		// Delete a node from the tree by value
		void TreeDelete(int val_n);

		// Delete a node and return the child of the spliced node, which took its place
		Node* TreeDeleteReturnNode(int val_n);

		// Delete a node from the tree by node pointer
		void TreeDelete(Node* node_n);

		// Get the number of nodes contained in each level. The function returns
		// a vector, where each index contains the number of nodes in the 
		// corresponding level. E.g. vector[2] = 4, means that on level 2 there are
		// 4 nodes. Levels start from 0 to vector.size().
		std::vector<int> ElementsPerLevel(); 
};

#endif
