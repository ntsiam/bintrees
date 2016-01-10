#include "src/BinTree.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "src/RedBlackTree.h"
#define NODES 20 

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "Usage: './main i' for interactive mode or './main s' for standard mode\n";

	} else if (strcmp(argv[1],"s") == 0) {
		//Node* a = new Node(5,NULL,NULL);
		//Node* c = new Node(7,a,NULL);
		//BinTree* g = new BinTree(c);
		//g->printPreOrder();

		std::cout << std::endl;

		std::vector<int> values;
		values.reserve(NODES);
		std::srand(std::time(NULL));
		std::cout << "Values: \n";
		for (int cnt=0;cnt<NODES;cnt++) {
			values.push_back(std::rand() % (10*NODES));
			//values.push_back(cnt);
			//std::cout << values[cnt] << ", ";
		}
		std::cout << std::endl;
		static const int arr[] = { 43, 6, 4, 31 , 7, 81 , 76, 42, 58, 86, 14 , 70 , 12, 4, 63, 32, 66, 27,18, 77 };
		//static const int arr[] = { 25, 13, 30, 6, 21, 27, 48, 3, 9, 16, 23, 26, 29, 43, 50, 0, 5, 7, 11, 14, 19, 22, 24, 41, 47, 49, 55, 12, 17, 20, 42 };
		std::vector<int> values1(arr, arr + sizeof(arr) / sizeof(arr[0]));

		BinTree* tree = BinTree::NewBinTree(values1);
		tree->ShowTree();
		//Node* node = tree->BinTree::TreeDeleteReturnNode(25);
		//tree->BinTree::TreeDelete(25);
		//if (node)
		//	std::cout << "Result Node: " << node->getValue() << std::endl;
		//else std::cout << "Result Node: NULL\n";
		//tree->ShowTree();
		RedBlackTree* rbtree1 = RedBlackTree::NewRBTree(values1);

		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(27);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(14);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(18);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(7);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(12);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(6);
		rbtree1->ShowTree(true);
		//rbtree1->RBTreeDelete(42);
		rbtree1->RBTreeDelete(58);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(32);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(43);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(42);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(31);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(4);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(4);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(63);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(66);
		rbtree1->ShowTree(true);
		rbtree1->RBTreeDelete(70);
		rbtree1->ShowTree(true);
	} else {
		int choice;
		int val_n;
		std::cout << "Interactive mode, press CTRL-C to quit\n";
		std::cout << "Create a BinTree (1) or a RedBlackTree (2) : ";
		std::cin >> choice;
		std::cout << "Trees are shown with the value of the nodes for each level from right to left. NULL nodes are represented as nodes with -1 value.\n";
		if (choice == 2)
			std::cout << "RedBlackTrees are shown as <node value> [<color>], where color is 0 for black and 1 for red. E.g. 4 [1], means node with value 4 and color red\n";
		std::cout << "New node value: ";
		std::cin >> val_n;
		if (choice != 1 && choice !=2) return 0;
		BinTree* bintree = new BinTree(val_n);
		RedBlackTree* rbtree = new RedBlackTree(val_n);
		if (choice == 1) {
			bintree->ShowTree();
		} else if (choice == 2) {
			rbtree->ShowTree(true);
		}
		while(1) {
			std::cout << "New node value: ";
			std::cin >> val_n;
			if (choice == 1) {
				bintree->TreeInsert(val_n);		
				bintree->ShowTree();
			} else {
				rbtree->RBTreeInsert(val_n);
				rbtree->ShowTree(true);
			}

		}

	}
	return 0;
}
