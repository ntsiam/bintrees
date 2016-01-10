#ifndef RED_BLACK_H
#define RED_BLACK_H
#include "BinTree.h"

class RedBlackTree: public BinTree
{
	public:
		// New RedBlackTree with only root
		RedBlackTree(int val_n) : BinTree(val_n) {};
		RedBlackTree(Node* root_n) : BinTree(root_n) {};

		// New RedBlackTree with multiple nodes - use NewRBTree()
		RedBlackTree(std::vector<int>* val_n, void (*insertFunction)(Node** root_n,int val_n)) : BinTree(val_n,insertFunction) {};
		
		// Function to construct a new RedBlackTree
		static RedBlackTree* NewRBTree(std::vector<int> val_n);

		//void InsertManyRBTree(std::vector<int>* val_n);
		bool isRed() { return this->getRoot()->isRed(); }
		void setRed(bool redness) { this->getRoot()->setRed(redness); }
		void RBTreeInsert(int val_n);
		void RBTreeDelete(int val_n);
		static void RBTreeInsert(Node** root, int val_n);
		static void LeftRotate(Node* node);
		static void RightRotate(Node* node);

};
#endif
