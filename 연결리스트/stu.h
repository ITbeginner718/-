#pragma once

//학생 관리 구조체 
typedef struct
{
	char College[30];	//단과대학
	char Major[50];		//학과
	char Id[20];		//학번
	char Name[15];		//이름
	int StuGrade;		//학년
	char Gender;		//성별
	char CallNum[20];	//전화번호
	int LeaveOfAbsence;	//휴학 
	int key;			//키 
}student;


//장학 관리 구조체
typedef struct scholarship
{
	struct scholarship* Next;	//다음 노드 
	float Semester;		//학기
	char Name[30];		//장학금 유형 
	int Amount;			//금액
	int key;			//키(1~50)
	
}scholarship;

//생성 
student* stu;
scholarship* ship;

/*********************************************************************************/
//파일_I.O
void stu_FilePrint();
void stu_FileLoad();

//stu
void stu_InputStuInfo();
void stu_InsertStuInfo(const char* college, const char* major, const char* id, const char* name, int grade, char gender, const char* callnum);
void stu_PrintStuInfo();
void stu_StuInfoCorrect();
void stu_LeaveOfAbsenceRequest();

//장학정보
void stu_ScholarshipInfo();
void stu_InsertShipNode(float Smester, char* Name, int Amount);
void stu_Scholarship_Info_Load();
void stu_Scholarship_Info_Print();
void stu_InputScholoarship();
void stu_deleteScholarshipNode();
void stu_ArraySchoralshipNode();