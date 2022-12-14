#pragma once
//node.h
//학점 구조체 
typedef struct coljumsu
{
	int Credit;			//각 이수학점						
	char Jumsu[3];		//각 평점
	char SubName[60];	//각 과목 이름
	int key;			//키 : <디폴트:0>, <학점 입력 시:1>, <수강 중:-1> 
}coljumsu;

//학기 구조체 
typedef struct Node
{
	struct Node* next;		//다음 노드
	int data;				//임시 데이터
	int Total_Credit;		//총 이수 학점
	float Aver_Grade;		//평균 평점 
	int SubNum;				//과목 수
	float Semester;			//학기
	coljumsu* cj;			//학기별 과목 
	int Key;				//학점 입력 확인 키 : <디폴트:0>, <학점 입력 시:1>, <수강 중:-1> 
}Node;

//학기 노드 생성
/***********************************************/
Node* head;
/***********************************************/