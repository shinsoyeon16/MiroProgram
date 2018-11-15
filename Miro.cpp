#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include<fstream>
#include "LocationStack.h"
#include "LinkedList.h"
#include "ArrayStack.h"
#include "Node.h"
using namespace std;

const int MAZE_ROW_SIZE = 20;//�̷��� �� ����
const int MAZE_COL_SIZE = 31;//�̷��� �� ����
char miro[MAZE_ROW_SIZE][MAZE_COL_SIZE]; //�̷θ� �����ϴ� 2���� �迭

void LoadMiro() { //������ �̷θ� 2�����迭�� �����ϴ� �Լ� //����1 ������0, �Ա���(1,0), �ⱸ�� x���� ���ư�
	FILE* fp;
	fopen_s(&fp,"Maze_3.txt", "rt");
	if (fp == NULL) {
		cout << "���� ����� ����" << endl;
		exit(1);
	}

	//�迭�� �̷� �����ϱ�
	for (int i = 0; i < MAZE_ROW_SIZE; i++) {
		for (int j = 0; j < MAZE_COL_SIZE; j++) {
			miro[i][j] = fgetc(fp);
		}
	}
	miro[2][0] = 'e'; //�Ա�����
	fclose(fp);
}
void print() //�̷θ� ȭ�鿡 ���
{
	for (int i = 0; i < MAZE_ROW_SIZE; i++)
	{
		for (int j = 0; j < MAZE_COL_SIZE; j++)
		{
			if (miro[i][j] == '0')
			{
				cout << "  ";
			}
			else if (miro[i][j] == '1')
			{
				cout << "��";
			}
			else if (miro[i][j] == '.')
			{
				cout << "��";
			}
			else if (miro[i][j] == 'x')
			{
				cout << "��";
			}
			else if (miro[i][j] == 'e')
			{
				cout << "��";
			}
		}
		cout << endl;
	}
	cout << endl;
}

bool isValidLoc(int r, int c) //�̷������� Ž���ϴ� �Լ�
{
	//��ȿ���� ���� �̷� ��ǥ�ϰ�� false��ȯ
	if (r < 0 || c < 0 || r >= MAZE_ROW_SIZE || c >= MAZE_COL_SIZE) 
		return false; 
	// Ž���� �� �ִ� �̷����� �˻� �� ��ȯ
	else 
		return miro[r][c] == '0' || miro[r][c] == 'x';
}
bool isValidLocOnly(int r, int c) //�̷������� Ž���ϴ� �Լ�
{
	int a = 0;
	if (r < 0 || c < 0 || r >= MAZE_ROW_SIZE || c >= MAZE_COL_SIZE)
		return false;
	else
	{
		if (isValidLoc(r - 1, c)) a++;
		if (isValidLoc(r + 1, c)) a++;
		if (isValidLoc(r, c - 1)) a++;
		if (isValidLoc(r, c + 1)) a++;
		return a==1;
	}
}
void MiroSearch(Node* entry) {
	LinkedList total_path; //��ü ��θ� �����ϱ� ���� ���Ḯ��Ʈ
	LinkedStack list; //�б����� ������ �����ϱ� ���� ���Ḯ��Ʈ
	ArrayStack stack; //���� �б��� Ž���� ���� ���� ����

	list.push(entry); //���Ḯ��Ʈ�� �ʱⰪ �����ϱ�

	while (list.isEmpty() == false) //)//������ ������� �ʴٸ� �ݺ��ض� //���Ḯ��Ʈ�� �����Ͱ� ���������� �ݺ��ϴ� �ݺ���
	{
		if (total_path.isEmpty() == false) {
			cout << "\n������: ";
			total_path.display(); //��������� ��� ���
			print();
		}

		Node* next = list.pop();
		stack.push(next);
		while (stack.isEmpty() == false) {
			Node* here = stack.pop(); //��ǥ  �̵� 
			total_path.enqueue(here);

			int r = here->getRow();
			int c = here->getCol();

			//������ġ�� �̷��� �ⱸ��� �����Լ��� true ����
			if (miro[r][c] == 'x') {
				cout << "\n\n��ü���: " << endl;
				total_path.display(); //��ü��� ���
				cout << "�̷� Ž�� ����!!" << endl;
				print();
				return;
			}

			//�ⱸ�� �ƴ϶�� �̷� Ž��
			else { 
				miro[r][c] = '.'; //������ �ڸ� Ȯ���� ���� ����

				 //���� �б�� ���ÿ� �߰��Ͽ� Ž��
				if (isValidLocOnly(r, c)) {
					if (isValidLoc(r - 1, c)) stack.push(new Node(r - 1, c));//��
					else if (isValidLoc(r + 1, c)) stack.push(new Node(r + 1, c));//��
					else if (isValidLoc(r, c - 1)) stack.push(new Node(r, c - 1));//��
					else stack.push(new Node(r, c + 1));//��
				}

				//�ٸ� �б�� ���Ḯ��Ʈ�� �߰�
				else {
					if (isValidLoc(r, c - 1)) list.push(new Node(r, c - 1));//��
					if (isValidLoc(r, c + 1)) list.push(new Node(r, c + 1));//��
					if (isValidLoc(r - 1, c)) list.push(new Node(r - 1, c));//��
					if (isValidLoc(r + 1, c)) list.push(new Node(r + 1, c));//��
				}
			}
		}
	}
	cout << "�̷� Ž�� ����" << endl;
}

int main() {
	LoadMiro(); //�̷��� �ҷ����� �Լ� ȣ��
	print();//�̷θ� ����ϴ� �Լ� ȣ��

	MiroSearch(new Node(2, 0)); //�Ա��� �����Ͽ� �̷�Ž���ϴ� �Լ��� ȣ���մϴ�

	return 0;
}