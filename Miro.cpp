#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include<fstream>
#include "LocationStack.h"
#include "LinkedList.h"
#include "ArrayStack.h"
#include "Node.h"
using namespace std;

const int MAZE_ROW_SIZE = 20;//미로의 행 개수
const int MAZE_COL_SIZE = 31;//미로의 열 개수
char miro[MAZE_ROW_SIZE][MAZE_COL_SIZE]; //미로를 저장하는 2차원 배열

void LoadMiro() { //파일의 미로를 2차원배열에 저장하는 함수 //벽은1 공간은0, 입구는(1,0), 출구는 x여야 돌아감
	FILE* fp;
	fopen_s(&fp,"Maze_3.txt", "rt");
	if (fp == NULL) {
		cout << "파일 입출력 에러" << endl;
		exit(1);
	}

	//배열에 미로 저장하기
	for (int i = 0; i < MAZE_ROW_SIZE; i++) {
		for (int j = 0; j < MAZE_COL_SIZE; j++) {
			miro[i][j] = fgetc(fp);
		}
	}
	miro[2][0] = 'e'; //입구설정
	fclose(fp);
}
void print() //미로를 화면에 출력
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
				cout << "■";
			}
			else if (miro[i][j] == '.')
			{
				cout << "□";
			}
			else if (miro[i][j] == 'x')
			{
				cout << "◎";
			}
			else if (miro[i][j] == 'e')
			{
				cout << "○";
			}
		}
		cout << endl;
	}
	cout << endl;
}

bool isValidLoc(int r, int c) //미로정보를 탐색하는 함수
{
	//유효하지 않은 미로 좌표일경우 false반환
	if (r < 0 || c < 0 || r >= MAZE_ROW_SIZE || c >= MAZE_COL_SIZE) 
		return false; 
	// 탐색할 수 있는 미로인지 검사 후 반환
	else 
		return miro[r][c] == '0' || miro[r][c] == 'x';
}
bool isValidLocOnly(int r, int c) //미로정보를 탐색하는 함수
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
	LinkedList total_path; //전체 경로를 저장하기 위한 연결리스트
	LinkedStack list; //분기점의 정보를 저장하기 위한 연결리스트
	ArrayStack stack; //현재 분기점 탐색을 위한 스택 설정

	list.push(entry); //연결리스트의 초기값 저장하기

	while (list.isEmpty() == false) //)//스택이 비어있지 않다면 반복해라 //연결리스트에 데이터가 없을때까지 반복하는 반복문
	{
		if (total_path.isEmpty() == false) {
			cout << "\n현재경로: ";
			total_path.display(); //현재까지의 경로 출력
			print();
		}

		Node* next = list.pop();
		stack.push(next);
		while (stack.isEmpty() == false) {
			Node* here = stack.pop(); //좌표  이동 
			total_path.enqueue(here);

			int r = here->getRow();
			int c = here->getCol();

			//현재위치가 미로의 출구라면 메인함수에 true 리턴
			if (miro[r][c] == 'x') {
				cout << "\n\n전체경로: " << endl;
				total_path.display(); //전체경로 출력
				cout << "미로 탐색 성공!!" << endl;
				print();
				return;
			}

			//출구가 아니라면 미로 탐색
			else { 
				miro[r][c] = '.'; //지나온 자리 확인을 위해 변경

				 //현재 분기는 스택에 추가하여 탐색
				if (isValidLocOnly(r, c)) {
					if (isValidLoc(r - 1, c)) stack.push(new Node(r - 1, c));//좌
					else if (isValidLoc(r + 1, c)) stack.push(new Node(r + 1, c));//우
					else if (isValidLoc(r, c - 1)) stack.push(new Node(r, c - 1));//상
					else stack.push(new Node(r, c + 1));//하
				}

				//다른 분기는 연결리스트에 추가
				else {
					if (isValidLoc(r, c - 1)) list.push(new Node(r, c - 1));//좌
					if (isValidLoc(r, c + 1)) list.push(new Node(r, c + 1));//우
					if (isValidLoc(r - 1, c)) list.push(new Node(r - 1, c));//상
					if (isValidLoc(r + 1, c)) list.push(new Node(r + 1, c));//하
				}
			}
		}
	}
	cout << "미로 탐색 실패" << endl;
}

int main() {
	LoadMiro(); //미로을 불러오는 함수 호출
	print();//미로를 출력하는 함수 호출

	MiroSearch(new Node(2, 0)); //입구를 전달하여 미로탐색하는 함수를 호출합니다

	return 0;
}