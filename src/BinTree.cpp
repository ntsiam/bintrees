#include "BinTree.h"
#include "Queue.h"

BinTree::BinTree(int val_n)
{
	Node* root_n = new Node(val_n,NULL,NULL);
	this->root = root_n;
}

BinTree::BinTree(Node* root_n) {
	this->root = root_n;
}

BinTree::BinTree(std::vector<int>* val_n,void (*insertFunction)(Node** root_n,int val_n)) {
	if ((val_n)) {
		Node* root_n = new Node((*val_n)[0],NULL,NULL);
		this->root = root_n;
	}
	for (unsigned long i=1;i<val_n->size();i++) {
		(*insertFunction)(&(this->root),(*val_n)[i]);
		//this->TreeInsert((*val_n)[i]);
	}

}

BinTree* BinTree::NewBinTree(std::vector<int> val_n) {
	void (*insert_ptr)(Node**,int) = BinTree::TreeInsert;
	BinTree* tree = new BinTree(&val_n,insert_ptr);
	return tree;
}

Node* BinTree::getRoot() {
	return this->root;
}

void BinTree::setRoot(Node* root_n) {
	this->root = root_n;
}

void printHelper(Node* root) 
{
	std::cout << root->getValue() << ", ";
	if (root->getLeftChild() != NULL)
		printHelper(root->getLeftChild());
	if (root->getRightChild() != NULL)
		printHelper(root->getRightChild());
}

void BinTree::printPreOrder()
{
	Node* root = this->getRoot();
	if (!root) return;
	std::cout << std::endl << "Tree Preorder is: " << std::endl;
	printHelper(root);
	std::cout << std::endl;
	std::cout << "---------------------------------------\n";
}

void SearchHelper(Node** node, int k)
{
	if (!(*node) || (*node)->getValue() == k)
		return;
	if (k < (*node)->getValue()) {
		(*node) = (*node)->getLeftChild();
		SearchHelper(node,k);
	}
	else {
		(*node) = (*node)->getRightChild();
		SearchHelper(node,k);
	}
}

Node* BinTree::TreeSearch(int k)
{
	Node* tmp = this->getRoot();
	SearchHelper(&tmp,k);
	return tmp;
}

void DeleteHelper(BinTree* root,Node* node)
{
	Node* child;
	Node* splice_n;
	if (!node) return;
	if (!node->getLeftChild() || !node->getRightChild())
		splice_n = node;
	else splice_n = root->TreeSucc(node);
	if (splice_n->getLeftChild())
		child = splice_n->getLeftChild();
	else child = splice_n->getRightChild();
	if (child) {
		child->setParent(splice_n->getParent()); 
	}
	if (!splice_n->getParent()) {
		root->setRoot(child);
		return;
	} else {
		if (splice_n == splice_n->getParent()->getLeftChild()) {
			splice_n->getParent()->setLeftChild(child);
		} else {
			splice_n->getParent()->setRightChild(child);
		}
	}
	if (splice_n != node)
		node->setValue(splice_n->getValue());
	return;
}

Node* DeleteHelperReturnNode(BinTree* root,Node* node,bool* fix)
{
	Node* child;
	Node* splice_n;
	if (!node) return NULL;
	if (!node->getLeftChild() || !node->getRightChild())
		splice_n = node;
	else splice_n = root->TreeSucc(node);
	if (!splice_n->isRed()) *fix = true;
	if (splice_n->getLeftChild())
		child = splice_n->getLeftChild();
	else child = splice_n->getRightChild();
	if (child) {
		child->setParent(splice_n->getParent()); 
	} else {
		// ADDED THIS BLOCK (?)
		child = new Node(-1,NULL,NULL);
		child->setParent(splice_n->getParent());
		if (child->getParent()) {
			if (splice_n == splice_n->getParent()->getLeftChild())
				child->getParent()->setLeftChild(child);
			else
				child->getParent()->setRightChild(child);
		}
		if (splice_n != node) {
			node->setValue(splice_n->getValue());
		}
		return child;
	}
	if (!splice_n->getParent()) {
		root->setRoot(child);
		return child;
	} else {
		if (splice_n == splice_n->getParent()->getLeftChild()) {
			splice_n->getParent()->setLeftChild(child);
		} else {
			splice_n->getParent()->setRightChild(child);
		}
	}
	if (splice_n != node) {
		node->setValue(splice_n->getValue());
	}
	return child;
}

void BinTree::TreeDelete(int val_n)
{
	Node* node;
	node = TreeSearch(val_n);
	if (node == this->getRoot() && !this->getRoot()->getRightChild() && !this->getRoot()->getLeftChild()) {
		this->setRoot(NULL);
		return;
	}
	DeleteHelper(this,node);
}

Node* BinTree::TreeDeleteReturnNode(int val_n)
{
	Node* node;
	node = TreeSearch(val_n);
	if (node == this->getRoot() && !this->getRoot()->getRightChild() && !this->getRoot()->getLeftChild()) {
		this->setRoot(NULL);
		return NULL;
	}
	bool needsfix = false;
	node = DeleteHelperReturnNode(this,node,&needsfix);
	if (!needsfix && node) node->setRed(true);
	std::cout << "Needs fix: " << needsfix << std::endl;
	return node;
}

void BinTree::TreeDelete(Node* node)
{
	if (node == this->getRoot() && !this->getRoot()->getRightChild() && !this->getRoot()->getLeftChild()) {
		this->setRoot(NULL);
		return;
	}
	DeleteHelper(this,node);
}

Node* MinHelper(Node* root)
{
	if (!root) return NULL;
	if (root->getLeftChild() == NULL)
		return root;
	return MinHelper(root->getLeftChild());
}

Node* BinTree::TreeMin()
{
	Node* tmp = this->root;
	return MinHelper(tmp);
}

Node* BinTree::TreeSucc(Node* node)
{
	if (node->getRightChild()) {
		BinTree* tmp = new BinTree(node->getRightChild());
		return tmp->TreeMin();
	}
	Node* par = node->getParent();
	while (par && node == par->getRightChild()) {
		node = par;
		par = node->getParent();
	}
	return par;
}

void InsertHelper(Node* root, Node* node)
{
	if (!root) {
		root = node;
		root->setParent(NULL);
		return;
	}
	if (root->getValue() > node->getValue()) {
		if (!root->getLeftChild()){
			root->setLeftChild(node);
			node->setParent(root);
		} else {
			InsertHelper(root->getLeftChild(),node);
		}
	} else {
		if (!root->getRightChild()) {
			root->setRightChild(node);
			node->setParent(root);
		} else {
			InsertHelper(root->getRightChild(),node);
		}
	}
}

void BinTree::TreeInsert(Node* node)
{
	InsertHelper(this->root,node);
}

void BinTree::TreeInsert(Node** root, int val_n)
{
	Node* tmp = *root;
	Node* node = new Node(val_n,NULL,NULL);
	InsertHelper(tmp,node);
}

void BinTree::TreeInsert(Node* root, Node* node)
{
	Node* tmp = root;
	InsertHelper(tmp,node);
}

void BinTree::TreeInsert(int val_n)
{
	Node* tmp = this->root;
	Node* node = new Node(val_n,NULL,NULL);
	InsertHelper(tmp,node);
}

void ElementsPerLevelHelper(Node* root,std::vector<int> *res,unsigned long lvl)
{
	if (res->size()	< lvl)
		res->push_back(1);
	else (*res)[lvl-1]++;
	if (root->getLeftChild())
		ElementsPerLevelHelper(root->getLeftChild(),res,lvl+1);
	else {
		if (res->size()	< lvl+1)
			res->push_back(1);
		else (*res)[lvl]++;
	}
	if (root->getRightChild())
		ElementsPerLevelHelper(root->getRightChild(),res,lvl+1);
	else {
		if (res->size()	< lvl+1)
			res->push_back(1);
		else (*res)[lvl]++;
	}
}

std::vector<int> BinTree::ElementsPerLevel()
{
	Node* tmp = this->root;
	std::vector<int> vec;
	ElementsPerLevelHelper(tmp,&vec,1); 
	return vec;
}

void printTree(std::vector<int> node_stack,std::vector<int> sizes,bool RBTree) 
{
	for (int i=sizes.size()-1;i>=0;i--) {
		std::cout << "Level: " << i << ", nodes: ";
		if (!RBTree) {
			for (int j=0;j<sizes[i];j++) {
				if (node_stack.back() != -1) {
					std::cout << node_stack.back() << ", ";
					node_stack.pop_back();
					node_stack.pop_back();
				} else {
					std::cout << node_stack.back() << ", ";
					node_stack.pop_back();
				}
			}
		} else {
			for (int j=0;j<sizes[i];j++) {
				if (node_stack.back() != -1) {
					std::cout << node_stack.back() << " [";
					node_stack.pop_back();
					std::cout << node_stack.back() << "], ";
					node_stack.pop_back();
				} else {
					std::cout << node_stack.back() << ", ";
					node_stack.pop_back();
				}
			}
		}
		std::cout << std::endl;
	}

}

void createStack(BinTree* tree,std::vector<int>* node_stack)
{
	Node* root = tree->getRoot();
	Queue* nodes = new Queue(root);
	node_stack->push_back(root->getValue());
	while(!nodes->isEmpty()) {
		Node* curr = nodes->top();
		if (curr->getLeftChild()) {
			nodes->insert(curr->getLeftChild());
			node_stack->push_back(curr->getLeftChild()->isRed());
			node_stack->push_back(curr->getLeftChild()->getValue());
		} else { 
			node_stack->push_back(-1);
		}
		if (curr->getRightChild()) {
			nodes->insert(curr->getRightChild());
			node_stack->push_back(curr->getRightChild()->isRed());
			node_stack->push_back(curr->getRightChild()->getValue());
		} else { 
			node_stack->push_back(-1);
		}
	}
}

//Print the structure of the tree starting from the leaves. Print -1 for NULL nodes.
void BinTree::ShowTree(bool RBTree) {
	BinTree* tmp = this;
	std::cout << "Tree: \n";
	std::vector<int> vec;
	vec = ElementsPerLevel(); 
	std::vector<int> node_stack; 
	createStack(tmp,&node_stack);
	printTree(node_stack,vec,RBTree);
	std::cout << "------------------------------------\n";
}
