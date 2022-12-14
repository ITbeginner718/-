#include "main.h"
//app.c
//설정 테스트 
//처음 화면 
void app_Init()
{
	printf("====================\n");
	printf("연결리스트 알고리즘를 이용한 콘솔 프로그램\n");
	printf("학생 정보 관리 프로그램\n");
	printf("2021-02-11\n");
	printf("====================\n");
	
	printf("로그인 화면으로 이동합니다.\n\n");
	system("pause");
}

//종료 화면
void app_Ending()
{
	system("cls");
	printf("====================\n");
	printf("연결리스트 알고리즘\n");
	printf("201910718-권순호\n");
	printf("====================\n");
	printf("종료\n");
	system("pause");
}

//로그인 화면
void app_Login()
{
	system("cls");
	char Id[20] = { 0 };
	char Passwd[20] = { 0 };
	FILE* loginFile;

	fopen_s(&loginFile, "login.txt", "r");
	if (loginFile == NULL)
		return;

	int check = fscanf_s(loginFile, "%s %s", Id, sizeof(Id), Passwd, sizeof(Passwd));

	if ((check) == -1)//로그인 데이터가 없는 경우
	{
		printf("현재 Id/Passwd가 존재하지 않습니다.\n");
		printf("로그인 정보를 새로 생성합니다. ※주의:해당 정보는 *한글을 제외한* 모든 문자로 생성 가능합니다.\n");

		printf("아이디 입력:");
		scanf_s("%s", Id, sizeof(Id));

		printf("비밀번호 입력:");
		scanf_s("%s", Passwd, sizeof(Passwd));

		fclose(loginFile);
		fopen_s(&loginFile, "login.txt", "w");

		if(loginFile==NULL)
			return;

		fprintf(loginFile, "%s %s", Id, Passwd);

		printf("ID/PASSWD가 생성되었습니다.\n");
		system("pause");
	}

	fclose(loginFile);

	//아이디 비번 입력
	char inputId[20] = { '\0' };
	char inputPasswd[30];

	while (1)
	{
		system("cls");
		printf("<<로그인 정보>>\n");

		printf("아이디 입력:");
		scanf_s("%s", inputId, sizeof(inputId));

		if (strcmp(Id, inputId) == 0)
			break;
		else
			printf("아이디 오류(다시 작성)\n");

		system("pause");
	}

	while (1)
	{
		int i = 0;
		printf("비밀번호 입력:");
		while (1)
		{
			inputPasswd[i] = _getch();//입력

			if (inputPasswd[i] == 13)//엔터키를 눌렀을 때
			{
				inputPasswd[i] = '\0';//엔터키를 누른 인덱스에 NULL값 삽입 
				break;
			}

			else if (inputPasswd[i] == 8)//백스페이스를 눌렀을 때 뒤로 가기 
			{
				if (i == 0)//인덱스가 0일 때는 어떠한 동작도 없게 설정 
					inputPasswd[0] = 0;

				else//한 문자씩 삭제 
				{	//EX) 5번째 인덱스(입력 단계)에서 백스페이스를 누르면 5번째와 4번째 인덱스가 사라지고 
					//4번째 인덱스에서 다시 시작    
					inputPasswd[i] = 0;
					inputPasswd[i - 1] = 0;
					i = (int)strlen(inputPasswd);//글자 수 체크 

					system("cls");
					printf("<<로그인 정보>>\n");
					printf("아이디 입력:%s\n", Id);

					printf("비밀번호 입력:");
					for (int i = 0; i < (int)strlen(inputPasswd); i++)//지워진 글자를 제외한 나머지 글자 출력 
						printf("*");
				}
			}
			//숫자, 알파벳, 특수문자(ctrl+1 ~ 0) 입력 시 마스킹 처리 
			else if (inputPasswd[i] >= 33 && inputPasswd[i] <= 126)
			{
				printf("*"); i++;
			}
			//그 외 특수문자 입력시 
			else
			{
				inputPasswd[i] = 0; continue;
			}
		}

		if (strcmp(Passwd, inputPasswd) == 0)
		{
			printf("\n로그인 성공\n");
			break;
		}

		else
		{
			printf("\n로그인 실패(다시 입력)\n");
			system("pause");
			system("cls");
			printf("<<로그인 정보>>\n");
			printf("아이디 입력:%s\n", Id);
		}
		
	}
	system("pause");
}

//학점 설명 화면
void app_GradeGuide()
{
	system("cls");
	printf("\n<학점 정보> 화면으로 이동합니다. 간략한 설명보고 넘어가세요.\n\n");
	printf("★사용 방법\n");
	printf("「1 - 학점을 입력할 때는 학기를 먼저 추가한 후 입력\n");
	printf("------------------------------------------------------------\n");
	printf("  2 - 학기는 \"1.1\" \"2.1\" 처럼 소수점으로 학기를 구별 \n");
	printf("------------------------------------------------------------\n");
	printf("  3 - .1(1학기) .2(2학기) .3(여름 학기) .4(겨울학기)로 입력 \n");
	printf("------------------------------------------------------------\n");
	printf("  4 - 당학기 수강은 평점을 입력 하지 않고 과목과 이수 학점만 입력」\n\n");
	system("pause");
}
/*-----------학점 출력 기능------------*/

//학점 정보 화면
void app_GradeWindowPrint()
{
	printf("\n[Semester Information Window]\n\n");
	printf("%-9s %-8s %s \t", "이수학점", "평점", "학기");
	printf("%-9s %-8s %s \n", "이수학점", "평점", "학기");
	printf("-----------------------------------------------------------\n");

	Node* curr = head->next;
	int count = 0;
	while (curr != NULL)
	{
		if (curr->Key == 1||curr->Key==-1)
		{	//오로지 P학점만 존재할때는 PASS로 출력 
			//->isnan()로 통해 숫자가 아니라면(NaN) 0이 아닌 값을 출력, 숫자라면 0을 출력  
			if (isnan(curr->Aver_Grade) != 0) //PASS는 P/N 즉, 평점이 없음(0.0) 
				printf("%s %-7d %s %s "," ", curr->Total_Credit,"P(N/P)", " ");
			else
				printf("%s %-7d %-6.2f %s "," ", curr->Total_Credit, curr->Aver_Grade, " ");
		}
		//학점이 안 들어가 있으면 Key==0
		else
			printf("%-9s %-4s %-4s", "없음", "없음", " ");

		//여름 학기(0.3), 계절 학기(0.4)를 구별
		float select = curr->Semester - ((int)curr->Semester);

		if (select > 0.29)
		{
			if (select > 0.39)
				printf("%.1f[겨울]", curr->Semester);
			else
				printf("%.1f[여름]", curr->Semester);
		}

		else
			printf("%.1f(정규)", curr->Semester);
		//짝수면 다음 줄로 이동 
		count++;

		if (curr->Key == -1)
			printf("(★수강 중★)");
		
		if (count % 2 == 0)
			printf("\n");
		else
			printf("\t");
		
		curr = curr->next;
	}
	if (count % 2 == 1)
		printf("\n");
	printf("-----------------------------------------------------------\n");

	//총 이수 학점 계산 
	Node* curr2 = head->next;
	int Total_Credit = 0;//총 이수 학점
	int Curr_Credit = 0;//현재 수강 학점
	
	while (curr2 != NULL)
	{
		if (curr2->Key == 1)//학점이 입력된 과목
			Total_Credit += curr2->Total_Credit;
		if (curr2->Key == -1)//수강 중인 과목
			Curr_Credit += curr2->Total_Credit;

		curr2 = curr2->next;
	}

	printf("->전체 평점:★%.2f\n\n", con_AllGradeAver());
	printf("<졸업「학점」: 132점>\n");
	printf("-------------------------------------\n");
	printf("수강 중/(총 이수)/*부족 : %d/(%d)/*%d \n", Curr_Credit, Total_Credit, (132 - Total_Credit));
	printf("-------------------------------------\n");
}

//리스트 출력(단순 연결 리스트)
void app_ListPrint()
{
	printf("저장된 학기: [");
	Node* curr = head->next;

	while (curr != NULL)
	{
		printf("%.1f", curr->Semester); //학기가 저장된 순서로 출력

		if (curr->next != NULL)
			printf(" -> ");

		curr = curr->next; 
	}
	printf("]\n");
}

//학점 수정
void app_CorectSemester(float semester)
{
	if (con_CheckSemester(semester) == -1)
	{ printf("현재 수강 중 입니다. \n"); return; }
	if (con_CheckSemester(semester) == 1)
	{ printf("학점 데이터가 없습니다. \n"); return; }
	if (con_CheckSemester(semester) == -10)
	{printf("해당 학기는 없습니다. \n"); return;}

	Node* curr = head->next;
	while (curr != NULL)
	{
		if (curr->Semester == semester)
			break;
		else
			curr = curr->next;
	}
	if (curr == NULL)
		return;

	con_clearBuffer();//버퍼 클리어 
	
	while (1)
	{
		char Name[60] = { 0 };

		system("cls");
		printf("\n[학기 평점 수정]\n");
		app_GradeSelectPrint(curr->Semester);

		coljumsu* cj = curr->cj;
		printf("「수정할 과목을 복사하여 입력창에 붙이세요.」\n");
		printf("「수정을 끝내려면 숫자 \"0\"을 입력하세요」\n\n");

		printf(">수정할 과목을 입력하시오:");
		gets_s(Name,sizeof(Name));

		//공백 제거 알고리즘
		strcpy_s(Name, sizeof(Name), con_RemoveBlank(Name));

		//수정 종료 
		if (Name[0] == '0')
			break;

		int check = 0;//과목 확인 변수 

		for (int i = 0; i < curr->SubNum; i++)//과목 탐색
		{
			//해당 과목 갱신 
			if (strcmp(Name, cj[i].SubName) == 0)
			{
				check = 1;//변경 확인

				printf("과목 이름 변경:");
				gets_s(cj[i].SubName, sizeof(cj[i].SubName));

				//공백 제거 알고리즘
				strcpy_s(cj[i].SubName, sizeof(cj[i].SubName), con_RemoveBlank(cj[i].SubName));

				printf("이수 학점 변경:");
				scanf_s("%d", &cj[i].Credit);

				char Jumsu[3] = { 0 };
				printf("등급 변경:");
				scanf_s("%s", Jumsu, sizeof(Jumsu));


				//소문자->대문자 변경 알고리즘 
				if (Jumsu[0] >= 97 && Jumsu[0] <= 122)
				{
					char s_char = Jumsu[0];
					s_char = s_char - 32;
					Jumsu[0] = s_char;
				}

				//평점 확인 유무
				if (con_DiviJumsu(Jumsu) == 0)
				{
					printf("해당 평점은 존재하지 않습니다(다시 입력).\n");
					break;//반복문 탈출 
				}
				strcpy_s(cj[i].Jumsu, sizeof(cj[i].Jumsu), Jumsu);

				break;//반복문 탈출
			}
		}

		if (check == 0)
			printf("해당 과목은 없습니다.\n");

		con_clearBuffer();//버퍼 클리어 
		system("pause");
	}

	//학점 재 연산
	con_ColAverJumsu(curr, curr->SubNum);
}

//학점 선택 출력
void app_GradeSelectPrint(float semester)
{
	if (con_CheckSemester(semester) == -10)
	{ printf("해당 학기가 존재하지 않음\n"); return; }
		
	//데이터 순회 
	Node* curr = head->next;

	while (curr != NULL)
	{
		if (curr->Semester == semester)
			break;
		else
			curr = curr->next;
	}

	if (curr == NULL)
		return;

	printf(">>");
	float select = curr->Semester - ((int)curr->Semester);

	//정규 학기와 계절 학기 구분 
	if (select > 0.29)
	{
		if (select > 0.39)
			printf("%.1f(겨울)", curr->Semester);
		else
			printf("%.1f(여름)", curr->Semester);
	}

	else
		printf("%.1f", curr->Semester);

	//오로지 P학점만 존재할때는 PASS로 출력 
	//->isnan()로 통해 숫자가 아니라면(NaN) 0이 아닌 값을 출력, 숫자라면 0을 출력 
	if (isnan(curr->Aver_Grade) != 0)
		printf("학기 - 이수학점:%d - 평점:PASS(N/P)", curr->Total_Credit);
	else
		printf("학기 - 이수학점:%d - 평점:%.2f", curr->Total_Credit, curr->Aver_Grade);

	if (curr->Key == 1 || curr->Key == -1)
	{
		//수강 중인 학기
		if (curr->Key == -1)
			printf("★현재 수강 중★\n");

		printf("\n%-11s %-10s %s \n", "<<이수 학점>>", "<<학점>>", "<<과목명>>");
		printf("---------------------------------------------\n");

		for (int i = 0; i < curr->SubNum; i++)//해당 과목 수 만큼 반복 
		{
			printf("-> %-13d %-8s %s", curr->cj[i].Credit, curr->cj[i].Jumsu, curr->cj[i].SubName);
			if (strcmp(curr->cj[i].Jumsu, "F") == 0 || strcmp(curr->cj[i].Jumsu, "NP") == 0)
				printf("(재수강 과목)\n");
			else
				printf("\n");
			printf("---------------------------------------------\n");
		}
	}

	else
		printf("\n학점 없음-> 입력 요망\n");

	printf("\n");

}

//학점 전체 출력
void app_GradeWindowAllPrint()
{
	system("cls");
	printf("현재 모든 학점 출력\n\n");

	Node* curr = head->next;
	
	while(curr != NULL)
	{
		app_GradeSelectPrint(curr->Semester);
		curr = curr->next;
	}
}
/*----------------------------------------*/

//실시간 입력되는 학점 공개 
void app_GradeInputInfo(struct coljumsu* cj, int count)
{
	printf("학점 입력 정보\n");
	printf("=====================\n");
	printf("%-8s%-7s%-7s\n","학점", "평점","과목명\n");
	for (int i = 0; i < count; i++)
	{
		if (cj[i].key == 1)
		{
			printf("*%-6d >>%-4s %s", cj[i].Credit, cj[i].Jumsu, cj[i].SubName);
			//F OR NP는 재수강
			if (strcmp(cj[i].Jumsu, "F") == 0 || strcmp(cj[i].Jumsu, "NP") == 0)
				printf("(Fail)\n");
			else
				printf("\n");
		}
		else if (cj[i].key == -1)
			printf("*%-6d >>%-4s %-6s\n", cj[i].Credit, cj[i].Jumsu, cj[i].SubName);
	}
	printf("=====================\n");
}

//학점 입력 방법 소개
void app_PrintGradeInfo(int num)
{
	printf("****학점 계산 연산****\n\n");
	printf("[<과목 이름>은 간단하게 숫자로 작성해도 좋음]\n");
	printf("[과목당 <이수 학점>은 \"1 ~ 20\"학점으로 입력]\n");
	printf("[평점은 A+, A0(A), B+, B0(B), C+, C0(C), D+, D0(D), P(NP), F 입력]\n\n");
	

	printf("[만약 정보가 잘못 입력 시 -> 과목 이름에 <숫자 0>을 입력하면 그 전으로 이동]\n");
	printf("\n\n*과목 수:%d*\n", num);
}

//시간 딜레이
void app_TimeDelay(char select)
{
	char* name;

	if (select == '1')
		name = "학생";
	else if (select == '2')
		name = "학점";
	else if (select == '3')
		name = "장학";
	else
		name = "모든[학생, 학점, 장학]";

	for (int i = 0; i < 3; i++)
	{
		system("cls");
		printf("         ★%s 데이터 초기화★\n",name);
		printf("현재 입력된 %s 데이터를 초기화하고 있습니다.\n",name);
		printf("                 삭제중");
		for (int i = 0; i < 5; i++)
		{
			Sleep(120);
			printf(".");
		}
	}
}

//데이터 초기화 설명 화면 
void app_IntroReset()
{
	printf("\n데이터 초기화\n");
	printf("=================================\n");
	char* true = "존재함";
	char* false = "존재하지 않음";

	//학생 데이터 확인
	printf("학생 정보 데이터:");
	
	//학생은 메모리는 정보를 저장하지 않지만 메모리는 할당은 됨
	if (stu ->key == 1)
		printf("%s\n",true);
	else
		printf("%s\n",false);
	printf("---------------------------------\n");
	//학점 데이터 확인
	printf("학점 정보 데이터:");
	if (head->next != NULL)
		printf("%s\n",true);
	else
		printf("%s\n",false);
	printf("---------------------------------\n");
	//장학 정보 데이터 확인
	printf("장학 정보 데이터:");
	if (ship->Next != NULL)
		printf("%s\n", true);
	else
		printf("%s \n", false);
	printf("=================================\n\n");

	printf("MENU(취소:<아무 키>)\n");

	printf("학생 정보:<1번>, 학점 정보:<2번> \n");
	printf("---------------------------------\n");
	printf("장학 정보:<3번>, 모든 정보:<4번> \n");
}
