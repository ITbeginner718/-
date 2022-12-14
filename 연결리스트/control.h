#pragma once
//control.h

//FILE_I.O
void con_NodeFileDown();
void con_NodeFileUp();
void con_FILE_All_Load();
void con_FILE_All_Down();

//control
void con_insertList(float semester);
void con_deleteList(float semester);
void con_AllDataReset();
double con_ReturnSemester();
void con_clearBuffer();
char* con_RemoveBlank(char* Name);
void con_MemoryAllocation();

//학점
int con_CheckSemester(float semester);
void con_InputGrade(float semester);
int con_DiviJumsu(const char* name);
void con_ColAverJumsu(struct Node* curr, int size);
void con_DeleteSubject();
float con_AllGradeAver();
void con_InputSubjectName(float semester);
int con_CheckSubName(const char* name);

//학기 정렬 메소드 
void con_ArrayNode();