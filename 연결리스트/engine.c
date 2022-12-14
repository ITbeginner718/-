#include "main.h"
//engine.c

//메인 화면 엔진 
void eg_Main_Engine()
{
	//메모리 할당(학생, 학점, 장학)
	con_MemoryAllocation();

	while (1)
	{
		//화면 초기화
		system("cls");

		//파일 업로드(학생, 학점, 장학) 
		con_FILE_All_Load();

		//학생 정보 출력
		stu_PrintStuInfo();

		char menu = eg_SelectMainMenu();
		//프로그램 종료
		if (menu == 27)
			return;
		switch (menu)
		{
		case '1':
			//학생 정보 입력
			stu_InputStuInfo();
			break;

		case '2':
			//학생 정보 수정
			stu_StuInfoCorrect();
			break;

		case '3':
			//휴학신청
			stu_LeaveOfAbsenceRequest();
			break;

		case'4':
			//장학 정보 화면
			eg_Scholarship();
			break;

		case'5':
			//학점 설명
			app_GradeGuide();
			//학점 화면으로 이동
			eg_GradeEngine();
			break;

		case '6':
			//모든 데이터 초기화
			con_AllDataReset();
			break;

		default:
			printf("다시 입력!\n");
			break;
		}

		//파일 출력(학생, 학점, 장학)
		con_FILE_All_Down();
		//버퍼 클리어
		con_clearBuffer();
		//한 번 멈춤
		system("pause");
	}

	//데이터 소멸
	free(head); free(stu); free(ship);
}

//메인 화면 메뉴 선택
char eg_SelectMainMenu()
{
	printf("\nMENU [ESC:프로그램 종료]\n");
	printf("================================================\n");
	printf("1. 학생 정보 입력\t"); printf("2. 학생 정보 수정\n");
	printf("------------------------------------------------\n");
	printf("3. 휴학 신청(1년)\t"); printf("4. [장학 정보 화면]\n");
	printf("------------------------------------------------\n");
	printf("5. [학점 정보 화면]\t"); printf("6. ※데이터 초기화※\n");
	printf("================================================\n\n");
	
	printf(">>메뉴 입력:");
	char menu = _getch();
	printf("\n");
	return menu;
}

//장학 정보 엔진 
void eg_Scholarship()
{
	while (1)
	{
		system("cls");

		//장학 데이터 가져오기 
		stu_Scholarship_Info_Load();

		//장학 정보 
		stu_ScholarshipInfo();

		char menu = eg_ScholarshipSelectMenu();
		printf("\n");
		switch (menu)
		{
		case '1':
			stu_InputScholoarship();
			break;

		case '2':
			stu_deleteScholarshipNode();
			break;

		case (int)27:
			printf("메인 화면으로 이동합니다. \n");
			return;

		default:
			printf("다시 입력!\n");
			break;
		}

		//장학 데이터 저장 
		stu_Scholarship_Info_Print();

		con_clearBuffer();
		system("pause");
	}
	
}

//장학 정보 메뉴 선택 
char eg_ScholarshipSelectMenu()
{
	printf("\nFUNCTION\n");
	printf("==========================================\n");
	printf("1. 장학 정보 입력\t"); printf("2. 장학 정보 삭제\n");
	printf("------------------------------------------\n");
	printf("[ESC]메인 화면으로 이동 \n");
	printf("==========================================\n");

	printf("메뉴 입력:");
	char menu = _getch();

	return menu;
}

//학점 화면 엔진
void eg_GradeEngine()
{
	while (1)
	{
		system("cls");

		//학점 정보 업로드
		con_NodeFileUp();

		//학점 일부 정보 화면
		app_GradeWindowPrint();

		char menu = eg_GradeInfoSelectMenu();

		switch (menu)
		{
		case '1':
			//학기 추가
			eg_GradeWindowSemester_OR_Grade(1, "추가할 학기");
			break;
		case '2':
			//학기 삭제
			eg_GradeWindowSemester_OR_Grade(2, "삭제할 학기");
			break;
		case '3':
			//당학기 과목만 입력
			eg_GradeWindowSemester_OR_Grade(3, "수강할 당학기");
			break;
		case '4':
			//당학기 학점 입력
			eg_GradeWindowSemester_OR_Grade(4, "학점을 입력할 당학기");
			break;
		case '5':
			//수정할 학기 입력
			eg_GradeWindowSemester_OR_Grade(5, "학점을 수정할 당학기");
			break;
		case '6':
			//학점 선택 출력
			eg_GradeWindowSemester_OR_Grade(6, "학점을 출력할 당학기");
			break;
		case '7':
			//학점 전체 출력
			app_GradeWindowAllPrint();
			break;
		case '8':
			//폐강 
			con_DeleteSubject();
			break;

		case (int)27:
			printf("메인 화면으로 이동합니다. \n");
			return;

		default:
			printf("다시 입력\n");
			break;
		}

		//노드 정보 파일 저장
		con_NodeFileDown();

		//버퍼 클리어
		con_clearBuffer();
		system("pause");
	}
}

//학점 화면 메뉴 선택
char eg_GradeInfoSelectMenu()
{
	printf("\nMENU([1.1 ~ 1.4][2.1 ~ 2.4][3.1 ~ 3.4][4.1 ~ 4.4])\n");
	printf("==========================================================================\n");
	printf("1. 학기 데이터 [추가]\t"); printf("2. 학기 데이터 [삭제]\t"); printf("3. 당학기 [수강]\n");
	printf("--------------------------------------------------------------------------\n");
	printf("4. *학기 학점 [입력]\t"); printf("5. 학기 학점 [수정]\t"); printf("6. 당학기 학점 [선택 출력]\n");
	printf("--------------------------------------------------------------------------\n");
	printf("7. 모든 학점 [출력]\t"); printf("8. 과목 폐강\t");	printf("[ESC]메인 화면으로 이동\n");
	printf("===========================================================================\n\n");
	printf(">>메뉴 입력:");
	char menu = _getch();
	printf("\n");
	return menu;
}

//학기(리스트)입력 및 삭제 OR 학점 입력, 삭제, 수정
void eg_GradeWindowSemester_OR_Grade(int value, const char* notice)
{
	app_ListPrint();
	//학기 입력
	float semester = 0.0;
	printf("%s 입력:", notice);
	scanf_s("%f", &semester);
	
	switch (value)
	{
	case 1:
		//학기 삽입
		con_insertList(semester);
		break;
	case 2:
		//학기 삭제
		con_deleteList(semester);
		break;
	case 3:
		//당학기 과목만 입력
		con_InputSubjectName(semester);
		break;
	case 4:
		//학기 학점 입력
		con_InputGrade(semester);
		break;
	case 5:
		//학점 수정
		app_CorectSemester(semester);
		break;
	case 6:
		//학점 출력(선택)
		printf("\n");
		app_GradeSelectPrint(semester);
		break;

	default:
		printf("다시 입력");
		break;
	}

}