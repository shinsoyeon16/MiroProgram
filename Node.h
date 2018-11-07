#pragma once
#include <cstdio>
class Node 
{
	int row;
	int col;
	Node * link;
public:
	Node(int r = 0, int c = 0) { row = r; col = c; link = NULL; }
	~Node() { delete this; }
	bool isNeighbor(Node&p)
	{
		return ((row == p.row && (col == p.col - 1 || col == p.col + 1))
			|| (col == p.col && (col == p.row - 1 || row == p.row + 1)));
	}
	Node* getLink() { return link; }
	void setLink(	Node * p) {link = p; }
	int getRow() { return row; }
	void setRow(int r) { row = r; }
	int getCol() { return col; }
	void setCol(int c) { col=c; }
	void display() {
		printf("(%d, %d) ", this->row, this->col);
	}
	bool operator==(Node&p) { return row == p.row&& col == p.col; }
};