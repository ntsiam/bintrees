#include "RedBlackTree.h"

void printPath(Node* node) {
	std::cout << "Node: " << node->getValue() << " ";
	while (node->getParent()) {
		std::cout << "-> " << node->getParent()->getValue() << " ";
		node = node->getParent();
	}
	std::cout << std::endl;
}


RedBlackTree* RedBlackTree::NewRBTree(std::vector<int> val_n)
{
	void (*insert_ptr)(Node**,int) = RedBlackTree::RBTreeInsert;
	RedBlackTree* tree = new RedBlackTree(&val_n,insert_ptr);
	return tree;
}

void RedBlackTree::LeftRotate(Node* node)
{
	if (node->getParent()) {
		if (node == node->getParent()->getLeftChild()) {
			node->getParent()->setLeftChild(node->getRightChild());
		} else {
			node->getParent()->setRightChild(node->getRightChild());
		}
		Node* tmp = node->getRightChild()->getLeftChild();
		node->getRightChild()->setLeftChild(node);
		node->getRightChild()->setParent(node->getParent());
		node->setParent(node->getRightChild());
		node->setRightChild(tmp);
		if (tmp)
			node->getRightChild()->setParent(node);
	} else {
		Node* tmp = node->getRightChild()->getLeftChild();
		node->getRightChild()->setLeftChild(node);
		node->getRightChild()->setParent(node->getParent());
		node->setParent(node->getRightChild());
		node->setRightChild(tmp);
		if (tmp)
			node->getRightChild()->setParent(node);
	}
}

void RedBlackTree::RightRotate(Node* node)
{
	if (node->getParent()) {
		if (node == node->getParent()->getLeftChild()) {
			node->getParent()->setLeftChild(node->getLeftChild());
		} else {
			node->getParent()->setRightChild(node->getLeftChild());
		}
		Node* tmp = node->getLeftChild()->getRightChild();
		node->getLeftChild()->setRightChild(node);
		node->getLeftChild()->setParent(node->getParent());
		node->setParent(node->getLeftChild());
		node->setLeftChild(tmp);
		if (tmp)
			node->getLeftChild()->setParent(node);
	} else {
		Node* tmp = node->getLeftChild()->getRightChild();
		node->getLeftChild()->setRightChild(node);
		node->getLeftChild()->setParent(node->getParent());
		node->setParent(node->getLeftChild());
		node->setLeftChild(tmp);
		if (tmp)
			node->getLeftChild()->setParent(node);
	}
}

void InsertFix(Node* node)
{
	Node* uncle;
	if (node->getParent() && node->getParent()->getParent()) {

		while(node->getParent() && node->getParent()->isRed()) {
			if (node->getParent() == node->getParent()->getParent()->getLeftChild()) {
				uncle = node->getParent()->getParent()->getRightChild();
				if (uncle && uncle->isRed()) {
					node->getParent()->setRed(false);
					uncle->setRed(false);
					node->getParent()->getParent()->setRed(true);
					node = node->getParent()->getParent();
				} else {
					if (node == node->getParent()->getRightChild()) {
						node = node->getParent();
						RedBlackTree::LeftRotate(node);
					}
					if (node->getParent()) {
						node->getParent()->setRed(false);
						if (node->getParent()->getParent())
							node->getParent()->getParent()->setRed(true);
					}
					RedBlackTree::RightRotate(node->getParent()->getParent());
				}
			} else {
				uncle = node->getParent()->getParent()->getLeftChild();
				if (uncle && uncle->isRed()) {
					node->getParent()->setRed(false);
					uncle->setRed(false);
					node->getParent()->getParent()->setRed(true);
					node = node->getParent()->getParent();
				} else {
					if (node == node->getParent()->getLeftChild()) {
						node = node->getParent();
						RedBlackTree::RightRotate(node);
					}
					node->getParent()->setRed(false);
					if (node->getParent()) {
						node->getParent()->setRed(false);
						if (node->getParent()->getParent())
							node->getParent()->getParent()->setRed(true);
					} 
					RedBlackTree::LeftRotate(node->getParent()->getParent());
				}
			}
		}
	}
}

void RedBlackTree::RBTreeInsert(int val_n)
{
	Node* node = new Node(val_n,NULL,NULL);
	Node* root = this->getRoot();
	node->setRed(true);
	TreeInsert(node);
	if (node->getParent() && node->getParent()->getParent()) {
		InsertFix(node);
	}
	while (root->getParent()) {
		root = root->getParent();
	}
	root->setRed(false);
	this->setRoot(root);
}

void RedBlackTree::RBTreeInsert(Node** root_n, int val_n)
{
	Node* root = *root_n;
	Node* node = new Node(val_n,NULL,NULL);
	node->setRed(true);
	BinTree::TreeInsert(root,node);

	if (node->getParent() && node->getParent()->getParent()) {
		InsertFix(node);
	}
	while (root->getParent()) {
		root = root->getParent();
	}
	root->setRed(false);
	(*root_n) = root;
}

void DeleteFix(Node* node) {
	bool fixed_n = false;
	while (!fixed_n) {
		if (node == node->getParent()->getLeftChild()) {
			if (node->getParent()->getRightChild() && node->getParent()->getRightChild()->isRed()) {
				std::cout << "Child of spliced Node: " << node->getValue() << ", left child with red right sibling" << std::endl;
				RedBlackTree::LeftRotate(node->getParent());
				node->getParent()->setRed(true);
				node->getParent()->getParent()->setRed(false);
			} else if ((node->getParent()->getRightChild() && (!node->getParent()->getRightChild()->isRed()) && (node->getParent()->getRightChild()->getLeftChild()) && (!node->getParent()->getRightChild()->getLeftChild()->isRed()) && (node->getParent()->getRightChild()->getRightChild()) && (!node->getParent()->getRightChild()->getRightChild()->isRed())) || (node->getParent()->getRightChild() && (!node->getParent()->getRightChild()->isRed()) && (!node->getParent()->getRightChild()->getLeftChild()) && (!node->getParent()->getRightChild()->getRightChild()))) {
				std::cout << "Child of spliced Node: " << node->getValue() << ", left child with black right sibling with black children" << std::endl;
				node->getParent()->getRightChild()->setRed(true);
				node = node->getParent();
				if (node->getLeftChild()->getValue() == -1) {
					node->getLeftChild()->setParent(NULL);
					Node* tmp = node->getLeftChild();
					node->setLeftChild(NULL);
					delete(tmp);
				}
				if (node->isRed()) {
					node->setRed(false);
					return;
				}
			} else if (node->getParent()->getRightChild() && (!node->getParent()->getRightChild()->isRed()) && (node->getParent()->getRightChild()->getLeftChild()) && (node->getParent()->getRightChild()->getLeftChild()->isRed()) && (((node->getParent()->getRightChild()->getRightChild()) && (!node->getParent()->getRightChild()->getRightChild()->isRed())) || (!node->getParent()->getRightChild()->getRightChild())))  {
				std::cout << "Child of spliced Node: " << node->getValue() << ", left child with black right sibling with red left child" << std::endl;
				RedBlackTree::RightRotate(node->getParent()->getRightChild());
				node->getParent()->getRightChild()->setRed(false);
				node->getParent()->getRightChild()->getRightChild()->setRed(true);
			} else if (node->getParent()->getRightChild() && (!node->getParent()->getRightChild()->isRed()) && (node->getParent()->getRightChild()->getRightChild()) && (node->getParent()->getRightChild()->getRightChild()->isRed())) {
				std::cout << "Child of spliced Node: " << node->getValue() << ", left child with black right sibling with red right child" << std::endl;
				RedBlackTree::LeftRotate(node->getParent());
				fixed_n = true;
				bool redness = node->getParent()->isRed();
				node->getParent()->setRed(false);
				if (redness)
					node->getParent()->getParent()->setRed(true);
				else 
					node->getParent()->getParent()->setRed(false);
				node->getParent()->getParent()->getRightChild()->setRed(false);
			}
		} else {
			if (node->getParent()->getLeftChild() && node->getParent()->getLeftChild()->isRed()) {
				std::cout << "Child of spliced Node: " << node->getValue() << ", right child with red left sibling" << std::endl;
				RedBlackTree::RightRotate(node->getParent());
				node->getParent()->setRed(true);
				node->getParent()->getParent()->setRed(false);
			} else if ((node->getParent()->getLeftChild() && (!node->getParent()->getLeftChild()->isRed()) && (node->getParent()->getLeftChild()->getRightChild()) && (!node->getParent()->getLeftChild()->getRightChild()->isRed()) && (node->getParent()->getLeftChild()->getLeftChild()) && (!node->getParent()->getLeftChild()->getLeftChild()->isRed())) || (node->getParent()->getLeftChild() && (!node->getParent()->getLeftChild()->isRed()) && (!node->getParent()->getLeftChild()->getRightChild()) && (!node->getParent()->getLeftChild()->getLeftChild()))) {
				std::cout << "Child of spliced Node: " << node->getValue() << ", right child with black left sibling with black children" << std::endl;
				node->getParent()->getLeftChild()->setRed(true);
				node = node->getParent();
				if (node->getRightChild()->getValue() == -1) {
					node->getRightChild()->setParent(NULL);
					Node* tmp = node->getRightChild();
					node->setRightChild(NULL);
					delete(tmp);
				}
				if (node->isRed()) {
					node->setRed(false);
					return;
				}
			} else if (node->getParent() && node->getParent()->getLeftChild() && (!node->getParent()->getLeftChild()->isRed()) && (node->getParent()->getLeftChild()->getRightChild()) && (node->getParent()->getLeftChild()->getRightChild()->isRed()) && (((node->getParent()->getLeftChild()->getLeftChild()) && (!node->getParent()->getLeftChild()->getLeftChild()->isRed())) || (!node->getParent()->getLeftChild()->getLeftChild())))  {
				std::cout << "Child of spliced Node: " << node->getValue() << ", right child with black left sibling with red right child" << std::endl;
				RedBlackTree::LeftRotate(node->getParent()->getLeftChild());
				node->getParent()->getLeftChild()->setRed(false);
				node->getParent()->getLeftChild()->getLeftChild()->setRed(true);
			} else if (node->getParent() && node->getParent()->getLeftChild() && (!node->getParent()->getLeftChild()->isRed()) && (node->getParent()->getLeftChild()->getLeftChild()) && (node->getParent()->getLeftChild()->getLeftChild()->isRed())) {
				std::cout << "Child of spliced Node: " << node->getValue() << ", right child with black left sibling with red left child" << std::endl;
				RedBlackTree::RightRotate(node->getParent());
				fixed_n = true;
				bool redness = node->getParent()->isRed();
				node->getParent()->setRed(false);
				if (redness)
					node->getParent()->getParent()->setRed(true);
				else 
					node->getParent()->getParent()->setRed(false);
				node->getParent()->getParent()->getLeftChild()->setRed(false);
			}

		}
		if (!node->getParent())
			fixed_n = true;
	}
}

void RedBlackTree::RBTreeDelete(int val_n) {
	std::cout << "\nDeleting " << val_n << std::endl;
	Node* child = TreeDeleteReturnNode(val_n);
	if (child) {
		if (!child->isRed()) {
			DeleteFix(child);
		}
		else child->setRed(false);
	}
	if (child->getValue() == -1) {
		if (child == child->getParent()->getLeftChild())
			child->getParent()->setLeftChild(NULL);
		else
			child->getParent()->setRightChild(NULL);
		child->setParent(NULL);
		delete(child);

	}
	while (this->getRoot()->getParent())
		this->setRoot(this->getRoot()->getParent());
}
