#include "main.h"
//stu.c

//장학 정보 출력
void stu_ScholarshipInfo()
{
	scholarship* curr = ship->Next;

	printf("\n[Scholarship Information windows]\n\n");
	
	printf("%s %-2s %-2s %s \t","[번호]","학기","금액(단위:천)","장학금유형");
	printf("%s %-2s %-2s %s \n","[번호]","학기","금액(단위:천)","장학금유형");
	printf("==================================================================================\n");
	int count = 0;

	while (curr != NULL)
	{
		float seme = curr->Semester - (int)curr->Semester;
		printf("%s %-5d %.0f-%-5.0f %-10d"," ", curr->key,curr->Semester,(double)seme * 10,curr->Amount);
		
		for (int i = 0; i < 10; i++)
			printf("%c", curr->Name[i]);
		curr = curr->Next;

		count++;
		if (count % 2 == 0)
			printf("\n----------------------------------------------------------------------------------\n");
		else
			printf("\t");
	}
	if (count % 2 == 1)
		printf("\n");
	printf("==================================================================================\n");
	printf("=> 총 장학 금액:");

	int total = 0;// 총 수혜 금액
	curr = ship->Next;

	while (curr != NULL)
	{
		total += curr->Amount;
		curr = curr->Next;
	}
	total *= 1000;

	char total_s[10];       // 변환한 문자열을 저장할 배열
	sprintf_s(total_s,sizeof(total_s), "%d", total);    // %d를 지정하여 정수를 문자열로 저장

	char* p = total_s;
	int length = strlen(total_s);

	for (int i = length; i > 0;)
	{
		printf("%c", *p++); i--;

		if (i > 0 && (i % 3) == 0)
			printf(",");
	}
	printf("원\n");
}

//장학 노드 삭제하기 
void stu_deleteScholarshipNode()
{
	printf("\n삭제할 번호(Key)를 입력:"); 
	
	int key;
	scanf_s("%d", &key);
	
	scholarship* curr = ship->Next;
	scholarship* pre = curr;

	while (curr != NULL)
	{
		if (curr->key == key)
		{	//삭제 노드가 헤더 노드에 위치한 경우 
			if (curr == ship->Next)
			{
				if (curr->Next == NULL)//헤더 노드의 다음 노드가 없는 경우 
					ship->Next = NULL;//헤더 노드 NULL로 변환 
				else					//헤더 노드의 다음 노드가 있는 경우 
					ship->Next = curr->Next;//다음 노드로 이동 
			}

			//맨 마지막인 경우
			else if (curr->Next == NULL)
				pre->Next = NULL;

			//중간인 경우 
			else
				pre->Next = curr->Next;

			free(curr);//노드 삭제
			return;
		}

		else
		{
			pre = curr;//현재 노드를 이전 노드에 저장
			curr = curr->Next;//현재 노드는 다음 노드로 이동 
		}
	}
	printf("해당 데이터는 존재하지 않습니다.\n");
}

//장학 파일 정보 가져오기
void stu_Scholarship_Info_Load()
{
	//학기 리스트
	FILE* Ship;
	fopen_s(&Ship, "Ship.bin", "rb");//노드 파일 생성 
	if (Ship == NULL)
		return;

	//노드 초기화
	scholarship* curr = ship->Next;//데이터 순환
	scholarship* delete;//노드 초기화 

	while (curr != NULL)
	{
		delete = curr;//초기화 할 노드(학기)
		curr = curr->Next;//다음 노드로 이동 
		free(delete);
	}

	//노드 헤더 파일 초기화 
	ship->Next = NULL;

	while (1)
	{	//노드 생성
		scholarship* newNode = malloc(sizeof(scholarship));
		if (newNode == NULL)
			return;

		//파일에 데이터가 있는지 체크 
		int Check = fread(newNode, sizeof(scholarship), 1, Ship);

		//파일의 끝에 도달했을 때(업로드할 정보가 없으면) 반복문 탈출(숫자 0 반환)
		if (!(Check)) { free(newNode); break; }

		if (ship->Next == NULL)	//해당 노드가 처음인 경우 가장 처음 부분에 삽입 
			ship->Next = newNode;

		else//해당 노드가 처음이 아닌 경우  
		{
			scholarship* curr2 = ship->Next;//데이터 순환 
			//마지막 노드에 연결하기위한 마지막 노드 탐색
			while (curr2->Next != NULL)
				curr2 = curr2->Next;//마지막 노드의 다음 노드가 NULL이면 다음 노드에 삽입 

			curr2->Next = newNode;
		}

		/*파일에서 데이터를 갖고 올 때 해당 노드의 다음 노드(Next)가
		NULL이 아니면 Next에는 임의의 노드의 주소 값이 존재하므로에러 발생*/
		newNode->Next = NULL; //중요! 무조건 next에 NULL를 설정해야함
	}
	fclose(Ship);
}

//장학 파일 정보 저장하기
void stu_Scholarship_Info_Print()
{
	FILE* Ship;
	fopen_s(&Ship, "Ship.bin", "wb");//노드(학기) 파일 생성

	if (Ship == NULL)//예외 처리 
	{
		printf("Ship 에러\n"); return;
	}

	scholarship* curr = ship->Next;//데이터 순환
	//"노드(학기)데이터"와 노드데이터에 들어 있는 "성적(학점)데이터"를 따로 저장

	while (curr != NULL)
	{
		fwrite(curr, sizeof(scholarship), 1, Ship);//노드(학기) 데이터 저장 
		curr = curr->Next;//다음 노드(학기)로 이동 
	}

	free(curr);//데이터 소멸 
	fclose(Ship);//파일 닫기
}

//장학 정보 입력 
void stu_InputScholoarship() 
{
	system("cls");
	float Semester;		//학기
	char Name[30];		//장학금 유형 
	int Amount;			//금액
	
	app_ListPrint();
	printf("\n학기 입력 시 구분가능한 난수(1 ~ 50) 자동 생성\n");
	printf("「학기 입력」:");
	scanf_s("%f", &Semester);

	if (con_CheckSemester(Semester) == -10)
	{
		printf("해당 학기가 없거나 학점 데이터나 없습니다.\n");
		return;
	}

	con_clearBuffer();

	while (1)
	{
		printf("\n이름은 최대 [5글자]만 출력되므로 되도록 간략하게 작성 EX)\"성적우수\",\"국가장학\" \n");
		printf("\n장학금 이름(간략하게 입력):");
		gets_s(Name, sizeof(Name));

		//과목 명 공백 제거 알고리즘
		strcpy_s(Name, sizeof(Name), con_RemoveBlank(Name));

		//과목 명 공백 및 중복 체크 
		if ((int)strlen(Name) <= 0)
		{
			printf("오류 공백,다시 입력하세요\n\n");
			system("pause"); continue;
		}
		break;
	}
	
	while (1)
	{
		printf("\n금액을 입력(단위:천):");
		scanf_s("%d", &Amount);

		if (Amount <= 0)
		{
			printf("금액 오류, 다시 입력하세요\n\n");
			system("pause"); continue;
		}
		break;
	}

	stu_InsertShipNode(Semester, Name, Amount);
}

//장학 노드 정렬 
void stu_ArraySchoralshipNode()
{
	if (ship->Next == NULL)
		return;

	scholarship* temp;//정렬에 사용되는 참조 변수 
	//데이터 순환 
	scholarship* curr = ship->Next;

	int count = 0;//현재 학기 수 
	int index = 0;//정렬에 사용되는 인덱스 변수 


	//노드(학기) 수 체크
	while (curr != NULL)
	{
		count++; curr = curr->Next;
	}

	scholarship** Array = malloc(sizeof(scholarship) * count);//정렬를 하기 위한 포인터 배열 생성 

	if (Array == NULL)
		return;

	curr = ship->Next;//데이터 순환 

	for (int i = 0; i < count; i++)
	{
		Array[i] = curr;//2차 배열에 Node를 복사 
		curr = curr->Next;
	}

	//정렬 알고리즘:학기를 기준으로 오름차순으로 정렬 
	for (int i = 0; i < count; i++)
	{
		index = i;
		for (int j = i + 1; j < count; j++)
		{
			if (Array[index]->Semester > Array[j]->Semester)//학기 비교 
				index = j;
		}
		temp = Array[i];
		Array[i] = Array[index];
		Array[index] = temp;
	}

	//정렬된 데이터 재 배치 
	scholarship* newNode = Array[0];
	ship->Next = newNode;
	newNode->Next = NULL;

	for (int i = 1; i < count; i++)
	{
		curr = ship->Next;
		scholarship* newNode = Array[i];

		while (curr->Next != NULL)//마지막 노드를 찾기 위한 데이터 탐색 
			curr = curr->Next;

		curr->Next = newNode;

		newNode->Next = NULL;
	}
}

//장학 노드 추가 
void stu_InsertShipNode(float Semester, char*Name, int Amount)
{
	scholarship* newNode = malloc(sizeof(scholarship));
	
	if (newNode == NULL)
		return;

	//노드 초기화
	newNode->Semester = Semester;
	newNode->Amount = Amount;
	strcpy_s(newNode->Name, sizeof(newNode->Name), Name);
	
	//랜덤 숫자 생성 
	int Rand = 0;

	while (1)
	{
		Rand = (rand() % 50) + 1;
		scholarship* curr = ship->Next;
		int check = 0;

		while (curr!=NULL)
		{
			//1~99까지 난수를 생성하고 난수 중복을 체크 
			if (curr->key == Rand)
			{
				check = 1; break;
			}
			else
				curr = curr->Next;
		}

		if (check == 0)
			break;
	}

	newNode->key = Rand;
	newNode->Next = NULL;

	//노드 삽입
	if (ship->Next == NULL)//노드가 없으면 처음 헤더 노드에 삽입 
		ship->Next = newNode;

	else
	{
		scholarship* curr = ship->Next;
		while (curr->Next != NULL)//마지막 노드 탐색 
			curr = curr->Next;
		curr->Next = newNode;
	}
	//정렬
	stu_ArraySchoralshipNode();
}

//학생 데이터 저장
void stu_FilePrint()
{
	FILE* FO;

	fopen_s(&FO, "stu.bin", "wb");
	
	if (FO == NULL)
		return;

	fwrite(stu, sizeof(student), 1, FO);
	fclose(FO);
}

//학생 데이터 가져오기 
void stu_FileLoad()
{
	FILE* FI;

	fopen_s(&FI, "stu.bin", "rb");
	if (FI == NULL)
		return;

	fread(stu, sizeof(student), 1, FI);

	fclose(FI);
}

//학생 정보 입력
void stu_InputStuInfo()
{
	if (stu->key == 1)
	{
		printf("학생 데이터가 존재합니다. 정보를 삭제하고 실행해주시기 바랍니다.\n");
		return;
	}
	system("cls");
	char college[30];		//단과 대학
	char major[50];			//학과
	char id[20];			//학번
	char name[20];			//이름
	int grade=0;			//학년
	char gender;			//성별
	char callnum[20];		//전화 번호

	printf("<학생 정보 입력>\n\n");
	printf("---------------------------------\n");
	printf(">>이름 입력:");
	scanf_s("%s", name, sizeof(name));

	con_clearBuffer();
	printf("---------------------------------\n");
	printf(">>성별 m(남자) or w(여자) 입력:");
	scanf_s("%c", &gender, sizeof(gender));

	con_clearBuffer();
	printf("---------------------------------\n");
	printf(">>소속 단과대학 입력:");
	gets_s(college, sizeof(college));
	con_RemoveBlank(college);
	strcpy_s(college, sizeof(college), con_RemoveBlank(college));

	printf("---------------------------------\n");
	printf(">>소속 학과 입력:");
	gets_s(major, sizeof(major));
	strcpy_s(major, sizeof(major), con_RemoveBlank(major));

	printf("---------------------------------\n");
	while (1)
	{
		printf(">>학년 입력(1~4):");
		scanf_s("%d", &grade);
		if (grade >= 1 && grade <= 4)
			break;

		else
		{
			printf("학년 다시 입력\n\n");
			continue;
		}
	}

	printf("---------------------------------\n");
	printf(">>학번 입력:");
	scanf_s("%s", id, sizeof(id));

	printf("---------------------------------\n");
	con_clearBuffer();

	while (1)
	{
		int check = 0;

		printf("전화번호는 \'-\'를 제외하고 뒷자리만 입력\n");
		printf(">>전화번호 입력(010-):");
		gets_s(callnum, sizeof(callnum));

		if (callnum[7] != 0 && callnum[8] == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				if (callnum[i] < 48 || callnum[i]>57)
				{
					check= 1;
					printf("숫자 8자리를 입력하세요.(다시 입력)\n\n");
					break;
				}
			}
			if (check == 1)
				continue;
			else
				break;
		}

		else
		{
			printf("8자리로 다시 입력\n\n");
			continue;
		}
	}

	stu_InsertStuInfo(college, major, id, name, grade, gender, callnum);

	printf("학생 정보 저장 완료\n");
}

//데이터 삽입 
void stu_InsertStuInfo(const char* college, const char* major, const char* id, const char* name,
				   int grade, char gender, const char* callnum)
{
	
	//데이터 저장
	strcpy_s(stu->College, sizeof(stu->College), college);
	strcpy_s(stu->Major, sizeof(stu->Major), major);
	strcpy_s(stu->Id, sizeof(stu->Id), id);
	strcpy_s(stu->Name, sizeof(stu->Name), name);
	strcpy_s(stu->CallNum, sizeof(stu->CallNum), callnum);
	stu->Gender = gender;

	stu->StuGrade = grade;
	
	stu->key = 1;
	stu->LeaveOfAbsence = 0;
}
//학생 정보 출력
void stu_PrintStuInfo()
{
	printf("[Student Management Program]\n");
	if (stu->key != 1)
	{ printf(">>학생 정보가 없습니다.\n"); return; }

	printf("\n학생 정보 (%s",stu->Name);
	if (stu->Gender == 'm')
		printf("/남자)\n");
	else
		printf("/여자)\n");
	printf("==============================\n");
	char EnterYear[5] = { '\0' };//입학년도 변수 
	for (int i = 0; i < 4; i++)
		EnterYear[i] = stu->Id[i];

	//졸업 년도 계산 atoi():ASCII string to integer
	printf(">>입학 / 졸업 :%s / %d\n", EnterYear, atoi(EnterYear) + 4 + stu->LeaveOfAbsence);
	printf("-----------------------------\n");
	printf(">>휴학(단위:년):%d\n", stu->LeaveOfAbsence);
	printf("-----------------------------\n");
	printf(">>학번/(학년) : %s/(%d)\n", stu->Id, stu->StuGrade);
	printf("-----------------------------\n");
	printf(">>%s/%s\n", stu->College, stu->Major);
	printf("-----------------------------\n");
	printf(">>전화번호:%s", "010-");
	for (int i = 0; i < 8; i++)
	{
		printf("%c", stu->CallNum[i]);
		if (i == 3)
			printf("-");
	}
	printf("\n==============================\n\n");

	printf("[최근 학기 정보]\n");
	double semester = con_ReturnSemester();

	if (semester == 0.0)
	{
		printf("현재 학기 데이터가 없습니다.\n");
		return;
	}

	Node* curr = head->next;
	while (curr != NULL)
	{
		if (curr->Semester == semester)
		{
			printf("「학기:%.1f - 평점(이수학점):%.2f(%d)」", curr->Semester, curr->Aver_Grade, curr->Total_Credit);
			
			if (curr->Key == 1)
				printf("\n");
			else if (curr->Key == -1)
				printf("->현재 수강 중 입니다.\n");
			else
				printf("->현재 학점 정보가 존재하지 않습니다.\n");

			break;
		}
		curr = curr->next;
	}

}

//학생 정보 수정 
void stu_StuInfoCorrect()
{
	char name[10] = { '\0' };		//이름
	char gender;					//성별
	char callnum[12] = { '\0' };	//전화번호

	char id[20] = { '\0' };			//학번
	int grade;						//학년
	char college[20] = { '\0' };	//단과대학
	char major[40] = { '\0' };		//학과
	
	while (1)
	{
		
		system("cls");
		//학생 정보 출력
		stu_PrintStuInfo();

		printf("\n\n>>학생 정보 수정 번호를 누르세요. (ESC:수정 완료)\n");
		printf("=========================================\n");
		printf("1.이름, 2.성별, 3.전화번호, 4.학번,\n");
		printf("-----------------------------------------\n");
		printf("5.학년, 6.단과대학, 7.학과, <8>.전체 수정\n");
		printf("=========================================\n");

		printf("입력:");
		char Menu=_getch();
		printf("\n");
		switch (Menu)
		{
		case '1':
			printf(">>이름 재입력:");
			scanf_s("%s", name, sizeof(name));
			strcpy_s(stu->Name, sizeof(stu->Name), name);
			break;

		case '2':
			printf(">>성별 재 입력 m(남자) OR w(여자):");
			scanf_s("%c", &gender, sizeof(gender));
			stu->Gender = gender;
			break;

		case '3':
			while (1)
			{
				printf("전화번호는 \'-\'를 제외하고 뒷자리만 입력\n");
				printf(">>전화번호 재 입력(010-):");
				gets_s(callnum, sizeof(callnum));
				
				int check=0;//체크 변수 
				if (callnum[7] != 0 && callnum[8] == 0)
				{
					for (int i = 0; i < 8; i++)
					{
						if (callnum[i] < 48 || callnum[i]>57)
						{
							printf("숫자 8자리를 입력하세요.(다시 입력)\n\n");
							check = 1;
							break;
						}
					}
					if (check == 1)
						continue;
					else
						break;
				}

				else
				{
					printf("8자리로 다시 입력\n\n");
					continue;
				}
			}
			strcpy_s(stu->CallNum, sizeof(stu->CallNum), callnum);
			break;

		case '4':
			printf(">>학번 재 입력:");
			scanf_s("%s", id, sizeof(id));
			strcpy_s(stu->Id, sizeof(stu->Id), id);
			break;

		case '5':
			while (1)
			{
				printf(">>학년 재 입력(1~4):");
				scanf_s("%d", &grade);
				if (grade >= 1 && grade <= 4)
					break;

				else
				{
					printf("학년 다시 입력\n\n");
					continue;
				}
			}

			stu->StuGrade = grade;
			break;

		case '6':
			printf(">>단과대학 재 입력:");
			gets_s(college, sizeof(college));
			//공백 제거 알고리즘
			strcpy_s(college, sizeof(college), con_RemoveBlank(college));
			strcpy_s(stu->College, sizeof(stu->College), college);
			break;

		case '7':
			printf(">>학과 재 입력:");
			gets_s(major, sizeof(major));
			//공백 제거 알고리즘
			strcpy_s(major, sizeof(major), con_RemoveBlank(major));
			strcpy_s(stu->Major, sizeof(stu->Major), major);
		
			break;

		case '8':
			stu->key = 0;
			stu_InputStuInfo();
			return;

		case (int)27:
			printf("수정 완료!\n");
			return;

		case '10':
			printf("재 입력\n");
			system("pause");
			break;
		}
		con_clearBuffer();
	}
}

//휴학 신청
void stu_LeaveOfAbsenceRequest()
{
	char select=0;
	printf("=============================================================\n");
	printf("휴학 신청시 1년 단위로 가능합니다.\n");
	printf("또한 휴학을 여러 번 신청하면 신청한 만큼 연도가 쌓이게 됩니다.\n");
	printf("=============================================================\n");
	printf("휴학을 신청 하겠습니까?(Yes:y Or No:아무 키):");
	scanf_s("%c", &select,1);
	
	if (select == 'y'||select=='Y')
	{
		stu->LeaveOfAbsence += 1;
		printf("처리되었습니다.\n");
	}
	else
		printf("취소되었습니다.\n");
}
