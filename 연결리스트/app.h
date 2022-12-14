#pragma once
//app.h

//엔진 
void eg_Main_Engine();
char eg_SelectMainMenu();
void eg_GradeWindowSemester_OR_Grade(int value, const char* notice);
char eg_GradeInfoSelectMenu();
void eg_GradeEngine();
void eg_Scholarship();
char eg_ScholarshipSelectMenu();

//app
void app_Init();
void app_Ending();
void app_Login();
void app_ListPrint();
void app_TimeDelay(char select);
void app_GradeGuide();
void app_IntroReset();

//학점
void app_GradeSelectPrint(float semester);
void app_GradeWindowPrint();
void app_GradeWindowAllPrint();
void app_CorectSemester(float semester);
void app_GradeInputInfo(struct coljumsu* cj, int count);
void app_PrintGradeInfo(int num);
