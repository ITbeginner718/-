#pragma once
//node.h
//���� ����ü 
typedef struct coljumsu
{
	int Credit;			//�� �̼�����						
	char Jumsu[3];		//�� ����
	char SubName[60];	//�� ���� �̸�
	int key;			//Ű : <����Ʈ:0>, <���� �Է� ��:1>, <���� ��:-1> 
}coljumsu;

//�б� ����ü 
typedef struct Node
{
	struct Node* next;		//���� ���
	int data;				//�ӽ� ������
	int Total_Credit;		//�� �̼� ����
	float Aver_Grade;		//��� ���� 
	int SubNum;				//���� ��
	float Semester;			//�б�
	coljumsu* cj;			//�б⺰ ���� 
	int Key;				//���� �Է� Ȯ�� Ű : <����Ʈ:0>, <���� �Է� ��:1>, <���� ��:-1> 
}Node;

//�б� ��� ����
/***********************************************/
Node* head;
/***********************************************/