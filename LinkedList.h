#pragma once
#include<iostream>
#include "Node.h"

class LinkedList {
	Node * front;
	Node * rear;
public:
	LinkedList() { front = NULL; rear = NULL; }
	~LinkedList() { while (!isEmpty()) delete dequeue(); }
	bool isEmpty() { return front == NULL; }
	void enqueue (Node*p) { 
		if (isEmpty()) front = rear = p;
		else {
			rear->setLink(p);
			rear = p;
		}
	}
	Node*dequeue() {
		if (isEmpty()) return NULL;
		Node* p = front;
		front = front->getLink();
		if (front == NULL) rear = NULL;
		return p;
	}
	Node*peek() { return front; }
	void display() {
		for (Node*p = front; p != NULL; p = p->getLink())
			p->display();
		printf("\n");
	}
};