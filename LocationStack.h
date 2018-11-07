#pragma once
#include "Node.h"

class LinkedStack 
{
	Node* top;
public:
	LinkedStack() { top = NULL; }
	~LinkedStack() { while (!isEmpty()) delete pop(); }
	bool isEmpty() {
		return top == NULL;
	}

	void push(Node * p) {
		if (isEmpty()) top = p;
		else {
			p->setLink(top);
			top = p;
		}
	}
	Node* pop() {
		if (isEmpty()) NULL;
		Node *p = top;
		top = top->getLink();
		return p;
	}
	Node* peek() {
		return top;
	}
	void display() {
		for (Node*p = top; p != NULL; p = p->getLink())
			p->display();
		printf("\n");
	}
};