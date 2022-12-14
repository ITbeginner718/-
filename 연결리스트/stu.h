#pragma once

//�л� ���� ����ü 
typedef struct
{
	char College[30];	//�ܰ�����
	char Major[50];		//�а�
	char Id[20];		//�й�
	char Name[15];		//�̸�
	int StuGrade;		//�г�
	char Gender;		//����
	char CallNum[20];	//��ȭ��ȣ
	int LeaveOfAbsence;	//���� 
	int key;			//Ű 
}student;


//���� ���� ����ü
typedef struct scholarship
{
	struct scholarship* Next;	//���� ��� 
	float Semester;		//�б�
	char Name[30];		//���б� ���� 
	int Amount;			//�ݾ�
	int key;			//Ű(1~50)
	
}scholarship;

//���� 
student* stu;
scholarship* ship;

/*********************************************************************************/
//����_I.O
void stu_FilePrint();
void stu_FileLoad();

//stu
void stu_InputStuInfo();
void stu_InsertStuInfo(const char* college, const char* major, const char* id, const char* name, int grade, char gender, const char* callnum);
void stu_PrintStuInfo();
void stu_StuInfoCorrect();
void stu_LeaveOfAbsenceRequest();

//��������
void stu_ScholarshipInfo();
void stu_InsertShipNode(float Smester, char* Name, int Amount);
void stu_Scholarship_Info_Load();
void stu_Scholarship_Info_Print();
void stu_InputScholoarship();
void stu_deleteScholarshipNode();
void stu_ArraySchoralshipNode();