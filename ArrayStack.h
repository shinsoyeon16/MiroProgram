#pragma once
#include<iostream>
#include "Node.h"

#define MAX_STACK_SIZE 300
#define DATA Node *

inline void error(const char * msg) {
	printf("%s\n", msg);
	exit(1);
}
class ArrayStack
{
	int top;
	DATA data[MAX_STACK_SIZE];
public:
	ArrayStack() { top = -1; }
	~ArrayStack() {}
	bool isEmpty() {
		return top == -1;
	}
	bool isFull() {
		return top == MAX_STACK_SIZE - 1;
	}

	void push(DATA e) {
		if (isFull()) error("���� ��ȭ ����");
		data[++top] = e;
	}
	DATA pop() {
		if (isEmpty()) error("���� ���� ����");
		return data[top--];
	}
	DATA peek() {
		if (isEmpty()) error("���� ���� ����");
		return data[top];
	}
};