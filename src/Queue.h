#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include "BinTree.h"

class QueueNode
{
	private:
		Node* vetrice;
		QueueNode* next_el;
	public:
		QueueNode(Node* vetrice_n) {
			vetrice = vetrice_n;
			next_el = NULL;
		}
		QueueNode* getNext() { return next_el; }
		void setNext(QueueNode* next_n) { next_el = next_n; }
		Node* getVetrice() { return vetrice; }
		void setVetrice(Node* vetrice_n) { vetrice = vetrice_n; }

};

class Queue 
{
	private:
		QueueNode* top_el;
		QueueNode* bottom_el;
	public:
		Queue(Node* top_vetrice) {
			QueueNode* top_n = new QueueNode(top_vetrice);
			top_el = top_n;
			bottom_el = top_n;
		}
		Node* top() {
			Node* res = top_el->getVetrice();
			QueueNode* tmp = top_el;
			top_el = top_el->getNext();
			tmp->setVetrice(NULL);
			tmp->setNext(NULL);
			//delete tmp;
			return res;
		}
		void insert(Node* vetrice_n) {
			QueueNode* bottom_n = new QueueNode(vetrice_n);
			bottom_el->setNext(bottom_n);
			bottom_el = bottom_n;
			if (top_el == NULL)
				top_el = bottom_el;
		}
		bool isEmpty() {
			return (top_el == NULL);
		}
};
#endif
