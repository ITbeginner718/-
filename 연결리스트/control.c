#include "main.h"
//control.c 

//버퍼 비우기 
void con_clearBuffer() { while (getchar() != '\n'); } //scanf_s()는 스페이스 바 OR 엔터키를 '\n'으로 설정  

//메모리 할당
void con_MemoryAllocation()
{
	//학생 정보  
	stu = malloc(sizeof(student));

	//학점 정보
	if ((head = malloc(sizeof(Node))) == 0)
		return;
	head->next = NULL;

	//장학 정보  
	if ((ship = malloc(sizeof(scholarship))) == NULL)
		return;
	ship->Next = NULL;

}

//모든 파일 업로드(학생, 학점, 장학)
void con_FILE_All_Load()
{
	//학생 정보 업로드 
	stu_FileLoad();
	//노드 정보 업로드
	con_NodeFileUp();
	//장학 정보 업로드 
	stu_Scholarship_Info_Load();
}

//모든 파일 저장(학생, 학점, 장학)
void con_FILE_All_Down()
{
	//학생 정보 파일 저장 
	stu_FilePrint();
	//노드 정보 파일 저장
	con_NodeFileDown();
	//데이터 저장 
	stu_Scholarship_Info_Print();
}

//노드 데이터(학기, 학점) 저장하기(다운로드)
void con_NodeFileDown()
{
	FILE* List;
	fopen_s(&List, "list.bin", "wb");//노드(학기) 파일 생성
	if (List == NULL)//예외 처리 
	{
		printf("List 에러\n"); return;
	}

	FILE* Grade;
	fopen_s(&Grade, "Grade.bin", "wb");//성적(학점) 파일 생성 
	if (Grade == NULL)//예외 처리 
	{
		printf("Grade 에러\n"); return;
	}

	Node* curr = head->next;//데이터 순환
	//"노드(학기)데이터"와 노드데이터에 들어 있는 "성적(학점)데이터"를 따로 저장
	while (curr != NULL)
	{	//학점이 저장된 학기( 1 )와 수강 중인 학기(-1)를 저장  
		if (curr->Key == 1 || curr->Key == -1)
		{	//노드데이터에 들어 있는 성적(학점) 데이터 저장
			for (int i = 0; i < curr->SubNum; i++)
				fwrite(&(curr->cj[i]), sizeof(coljumsu), 1, Grade);
		}
		fwrite(curr, sizeof(Node), 1, List);//노드(학기) 데이터 저장 
		curr = curr->next;//다음 노드(학기)로 이동 
	}

	free(curr);//데이터 소멸 
	fclose(List);//파일 닫기
	fclose(Grade);
}

//노드 데이터(학기, 학점) 가져오기(업로드) 
void con_NodeFileUp()
{
	//학기 리스트
	FILE* List;
	fopen_s(&List, "list.bin", "rb");//노드 파일 생성 
	if (List == NULL)
		return;

	//성적(학점) 파일
	FILE* Grade;
	fopen_s(&Grade, "Grade.bin", "rb");//성적(학점) 파일 생성 
	if (Grade == NULL)
		return;

	//노드 초기화
	Node* curr = head->next;//데이터 순환
	Node* delete;//노드 초기화 

	while (curr != NULL)
	{
		delete = curr;//초기화 할 노드(학기)
		curr = curr->next;//다음 노드로 이동 
		free(delete);
	}

	//노드 헤더 파일 초기화 
	head->next = NULL;

	while (1)
	{	//노드 생성
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL)
			return;
		//파일에 데이터가 있는지 체크 
		int Check = fread(newNode, sizeof(Node), 1, List);

		//파일의 끝에 도달했을 때(업로드할 정보가 없으면) 반복문 탈출(숫자 0 반환)
		if (!(Check)) { free(newNode); break; }

		if (head->next == NULL)	//해당 노드가 처음인 경우 가장 처음 부분에 삽입 
			head->next = newNode;

		else//해당 노드가 처음이 아닌 경우  
		{
			Node* curr2 = head->next;//데이터 순환 
			//마지막 노드에 연결하기위한 마지막 노드 탐색
			while (curr2->next != NULL)
				curr2 = curr2->next;//마지막 노드의 다음 노드가 NULL이면 다음 노드에 삽입 

			curr2->next = newNode;
		}

		//만약 학점이 저장된 학기(1)와 수강 중인 학기(-1)가 있다면 정보 업로드  
		if (newNode->Key == 1 || newNode->Key == -1)
		{
			newNode->cj = malloc(sizeof(coljumsu) * newNode->SubNum);
			if (newNode->cj == 0)
				return;
			for (int i = 0; i < newNode->SubNum; i++)//학점 정보 추가 
				fread(&(newNode->cj[i]), sizeof(coljumsu), 1, Grade);//학점(성적)이 저장된 파일(Grade)에서 업로드 
		}

		/*파일에서 데이터를 갖고 올 때 해당 노드의 다음 노드(Next)가
		NULL이 아니면 Next에는 임의의 노드의 주소 값이 존재하므로에러 발생*/
		newNode->next = NULL;	//중요! 무조건 next에 NULL를 설정해야함
	}

	//파일 닫기 
	fclose(List);
	fclose(Grade);
}

//학기(리스트) 생성 
void con_insertList(float semester)
{
	//
	//학기 예외 처리(1.1 ~ 1.4, 2.1 ~ 2.4, 3.1 ~ 3.4, 4.1 ~ 4.4)
	if (semester > 1.099999 && semester < 4.5)
	{
		float Check = semester - (int)semester;
		//학기 예외 처리
		if (Check < 0.0999999 || Check>0.4000001)//소수점은 정확한 비교를 할 수 없으므로 오차 범위로 비교해야 함
		{	//0.1보다 작거나 0.4보다 크면 리턴
			printf("학기 오류->다시 입력\n");
			return;
		}

	}

	else
	{
		printf("학기오류->다시 입력\n"); return;
	}

	Node* curr = head->next;
	//학기 데이터 중복 체크 
	while (curr != NULL)
	{
		if (curr->Semester == semester)
		{
			printf("실패->학기 데이터 중복!\n");
			return;
		}
		curr = curr->next;
	}

	//새로운 노드 할당
	Node* newNode = malloc(sizeof(Node));
	if (newNode == 0)
		return;

	//데이터 초기화 
	newNode->next = NULL; //필수 
	newNode->Total_Credit = 0;
	newNode->Aver_Grade = 0.0;
	newNode->Key = 0;
	newNode->Semester = semester;

	//노드 삽입
	if (head->next == NULL)//노드가 없으면 처음 헤더 노드에 삽입 
		head->next = newNode;

	else
	{
		Node* curr = head->next;
		while (curr->next != NULL)//마지막 노드 탐색 
			curr = curr->next;
		curr->next = newNode;
	}

	//데이터 재 정렬 
	con_ArrayNode();
}

//학기 정렬 
void con_ArrayNode()
{
	if (head->next == NULL)
		return;

	Node* temp;//정렬에 사용되는 참조 변수 
	//데이터 순환 
	Node* curr = head->next;

	int count = 0;//현재 학기 수 
	int index = 0;//정렬에 사용되는 인덱스 변수 
	
	
	//노드(학기) 수 체크
	while (curr != NULL)
	{
		count++; curr = curr->next;
	}

	Node** Array = malloc(sizeof(Node) * count);//정렬를 하기 위한 포인터 배열 생성 

	if (Array == NULL)
		return;

	curr = head->next;//데이터 순환 

	for (int i = 0; i < count; i++)
	{
		Array[i] = curr;//2차 배열에 Node를 복사 
		curr = curr->next;
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
	Node* newNode = Array[0];
	head->next = newNode;
	newNode->next = NULL;

	for (int i = 1; i < count; i++)
	{
		curr = head->next;
		Node* newNode = Array[i];

		while (curr->next != NULL)//마지막 노드를 찾기 위한 데이터 탐색 
			curr = curr->next;

		curr->next = newNode;

		newNode->next = NULL;
	}
}

//리스트 삭제
void con_deleteList(float semester)
{
	Node* curr = head->next;
	Node* pre = curr;//이전 노드 생성 

	while (curr != NULL)
	{
		if (curr->Semester == semester)
		{	//삭제 노드가 헤더 노드에 위치한 경우 
			if (curr == head->next)
			{
				if (curr->next == NULL)//헤더 노드의 다음 노드가 없는 경우 
					head->next = NULL;//헤더 노드 NULL로 변환 
				else					//헤더 노드의 다음 노드가 있는 경우 
					head->next = curr->next;//다음 노드로 이동 
			}

			//맨 마지막인 경우
			else if (curr->next == NULL)
				pre->next = NULL;

			//중간인 경우 
			else
				pre->next = curr->next;

			free(curr);//노드 삭제
			return;
		}

		else
		{
			pre = curr;//현재 노드를 이전 노드에 저장
			curr = curr->next;//현재 노드는 다음 노드로 이동 
		}
	}
	printf("해당 데이터는 존재하지 않습니다.\n");
}

//학기 데이터 확인 
int con_CheckSemester(float semester)
{
	Node* curr = head->next;

	while (curr != NULL)
	{
		if (curr->Semester == semester)
		{
			//학점 데이터가 없는 경우
			if (curr->Key == 0)
				return 1;

			//수강 중인 학기 인 경우
			if (curr->Key == -1)
				return -1;

			//학점 데이터가 있는 경우
			else
				return 0;
		}
		else
			curr = curr->next;
	}

	return -10;//해당 학기가 존재하지 않음
}

//당학기 학점 입력(학기 데이터 확인 메소드 사용)
void con_InputGrade(float semester)  
{
	if (con_CheckSemester(semester) == 1 || con_CheckSemester(semester) == -1);
	else if (con_CheckSemester(semester) == 0) { printf("학점 데이터 존재함 \n"); return; }
	else { printf("해당 학기가 존재하지 않음\n"); return; }

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

	int num = 0; //과목 수 입력 변수

	if (curr->Key == 0)//학점 정보가 없다면(0)
	{
		printf("\n과목 수 입력:");
		scanf_s("%d", &(curr->SubNum));

		//학점을 입력을 위한 메모리 동적 할당, calloc 연산자를 사용 
		curr->cj = (coljumsu*)calloc(curr->SubNum, sizeof(coljumsu));
	}

	num = curr->SubNum;
	struct coljumsu* cj = curr->cj;//새로운 cj참조 변수에 참조값 대입 
	if (cj == NULL)
		return;

	con_clearBuffer();//버퍼 클리어

	//학점 입력
	//(num+1) : 저장된 학점을 전부다 보여주긴 위해선 모든 학점을 입력하고 한 번더 순환 해야함
	for (int i = 0; i < num + 1; i++)
	{	//반복문 처음 
		system("cls");
		//학점 입력 방법
		app_PrintGradeInfo(num);
		//학점 정보 출력
		app_GradeInputInfo(cj, num);
		
		if (i == num)
			break;

		if (curr->Key == 0)//학점 정보가 없으면( 0 ) 과목명, 이수학점 입력
		{
			//과목명 변수 생성
			char SubName[60] = { 0 };
			//노드에 저장된 과목명 변수 초기화: 이수 학점 및 학점 입력 과정에서 오류가 생기면
			//다시 입력해야 함으로 초기화 과목명을 초기화 
			cj[i].SubName[0] = '\0';

			printf("\n->%d 번째 정보 입력\n",i+1);
			printf("----------------------------------\n");
			printf("*과목 이름*을 입력: "); gets_s(SubName, sizeof(SubName));

			//과목 명 공백 제거 알고리즘
			strcpy_s(SubName, sizeof(SubName), con_RemoveBlank(SubName));

			//과목 명 공백 및 중복 체크 
			if ((int)strlen(SubName) <= 0 || con_CheckSubName(SubName) == 1)
			{
				printf("과목 명이 같거나 없습니다.\n");
				i--;
				system("pause");
				continue;
			}

			//과목명 데이터 저장
			strcpy_s(cj[i].SubName, sizeof(cj[i].SubName), SubName);

			//뒤로 가기 기능: 잘못 입력 시 뒤로 가기로 다시 입력  
			if (cj[i].SubName[0] == '0')
			{
				cj[i].SubName[0] = '\0';
				cj[i - 1].SubName[0] = '\0';

				//첫 번째 인덱스는 뒤로 갈 수 없게 설정 
				if (i == 0) { i--; continue; }

				cj[i - 1].key = 0;
				i--; i--;//두 번 뒤로 가기 
				continue;
			}

			//이수 학점 
			printf("----------------------------------\n");
			printf("이수 학점(1~20): "); scanf_s("%d", &cj[i].Credit);

			//이수 학점 확인 유무
			if (cj[i].Credit >= 20 || cj[i].Credit <= 0)//예외 처리 
			{
				printf("오류:입력한 학점은 존재하지 않습니다.(다시 입력)\n");
				system("pause");
				con_clearBuffer();
				i--;
				continue;
			}
		}

		//평점 입력
		printf("----------------------------------\n");
		printf("A+ ~ D0 / F / P(NP)\n");
		printf("(소문자 가능)평점: ");
		scanf_s("%s", cj[i].Jumsu, sizeof(cj[i].Jumsu)); //Enter or space bar 입력 시 데이터 저장 

		//소문자->대문자 변경 알고리즘 (수정)
		for (int j = 0; j < (int)strlen(cj[i].Jumsu); j++)//글자 수 만큼 
		{
			if (cj[i].Jumsu[j] >= 97 && cj[j].Jumsu[0] <= 122)// a ~ z
			{
				char s_char = cj[i].Jumsu[j];
				s_char = s_char - 32;
				cj[i].Jumsu[j] = s_char;
			}
		}

		//평점 확인 유무
		if (con_DiviJumsu(cj[i].Jumsu) == 0)
		{
			printf("해당 평점은 존재하지 않습니다(다시 입력).\n\n");
			system("pause");
			con_clearBuffer();
			i--;
			continue;
		}

		//학점이 입력되었으므로 학점이 입력된 과목(1)으로 표시
		cj[i].key = 1;

		con_clearBuffer();//버퍼 클리어 

	}//반복문 마지막

	con_ColAverJumsu(curr, num);//학점 연산 

	printf("학점이 저장되었습니다.\n");
}

//학점 연산 기능 
void con_ColAverJumsu(struct Node* curr, int size)
{
	float EachJumsu; //ex) A+ =>> 4.5
	float EachJumsu2;	//ex) 4.5*이수 학점
	float TotalJumsu = 0.0;	//EachJumsu2를 합한 값
	int TotalCredit = 0;	//총 이수 학점
	int ToCreExclu_P = 0;	//P학점을 제외한 경우

	struct coljumsu* cj = curr->cj;
	if (cj == NULL)
		return;

	//평점 부여!!
	/*
	* A+ ~ D0 까지 학점을 부여하며
	* P(N/P)와 F는 학점이 0.0을 부여하며 P(N/P)는 학점 계산에 포함되지 않는다.
	*/
	for (int i = 0; i < size; i++)
	{
		EachJumsu = 4.0;
		//아스키 코드를 이용한 학점 연산 알고리즘
		for (char Grade = 65; Grade <= 68; Grade++)//A~D학점 
		{

			if (cj[i].Jumsu[0] == Grade)
			{
				if (cj[i].Jumsu[1] == '+')
				{
					EachJumsu += 0.5;
					break;
				}
				break;
			}
			EachJumsu -= 1.0;
		}

		//학점 연산(F OR P(N/P)는 0점으로 처리) 
		EachJumsu2 = EachJumsu * cj[i].Credit;
		TotalJumsu += EachJumsu2;

		// 총 이수 학점 계산 (단,N/P는 이수 학점을 받지 못함)
		if (strcmp(cj[i].Jumsu, "NP") != 0)
			TotalCredit += cj[i].Credit;

		// P(N/P)학점을 제외한 평점 연산을 위한 이수학점 계산
		if (strcmp(cj[i].Jumsu, "P") != 0 && strcmp(cj[i].Jumsu, "NP") != 0)
			ToCreExclu_P += cj[i].Credit;//학점을 계산할 때는 P(N/P)학점은 제외하고 계산해야 함 
	}
	
	//f학점은 평점 연산에는 포함되지만 <학점 이수>는 할 수가 없기 때문에
	//다시 f를 받은 과목의 이수 학점은 다시 제외해야함 
	int Credit_F = 0;//F평점 이수학점
	
	for (int i = 0; i < size; i++)
		if (strcmp(cj[i].Jumsu, "F") == 0)
			Credit_F += cj[i].Credit;

	curr->Aver_Grade = (TotalJumsu / ToCreExclu_P);//P(N/P)학점을 제외한 총 학점 
	curr->Total_Credit = (TotalCredit - Credit_F);//F평점을 받은 과목의 이수 학점은 다시 제외해야 함.

	//출력
	printf("총 이수 학점:%d \n", curr->Total_Credit);

	if (isnan(curr->Aver_Grade) != 0)//PASS인 경우(숫자가 아닌 경우) 0이 아닌 수를 반환 
		printf("PASS(N/P)\n");
	else
		printf("평균 평점:%.2f\n", curr->Aver_Grade);

	curr->Key = 1;//학점이 입력된 학기( 1 )로 설정 
}

//평점 확인 유무
int con_DiviJumsu(const char* name)
{
	char Grade[3];
	strcpy_s(Grade, sizeof(Grade), name);

	if (Grade[0] >= 65 && Grade[0] <= 68)//아스키 코드를 (A~D) 이용하여 예외 체크 
		if (Grade[1] == '0' || Grade[1] == '+' || Grade[1] == 0)
			return 1;

	if (strcmp(name, "P") == 0 || strcmp(name, "NP") == 0 || strcmp(name, "F") == 0)
		return 1;

	else
		return 0;//해당 평점이 존재하지 않으면 0을 반환 
}

//데이터 초기화
void con_AllDataReset()
{	
	if (stu->key != 1 && head->next == NULL && ship->Name == NULL)
	{printf("\n 초기화할 데이터가 존재하지 않습니다.\n"); return;}
	
	system("cls");
	//데이터 초기화 설명 
	app_IntroReset();

	char select; //메뉴 변수 
	printf("\n초기화 데이터 선택:");
	scanf_s("%c", &select, 1);

	if (select != '1' && select != '2' && select != '3' && select != '4')
	{ printf("\n취소하였습니다. \n"); return; }

	if (select == '1' || select == '4')
	{		
		//학생 데이터 초기화
		free(stu);
		stu = malloc(sizeof(student));//노드 재생성
		if (stu == NULL)
			return;
	}

	if (select == '2' || select == '4')
	{	
		//학점 데이터 초기화 
		Node* curr = head->next;
		Node* delete;

		while (curr != NULL)
		{
			delete = curr;
			curr = curr->next;
			free(delete);
		}
		head->next = NULL;
	}

	if (select == '3' || select == '4')
	{
		//장학 데이터 초기화 
		scholarship* curr = ship->Next;
		scholarship* delete;
		while (curr != NULL)
		{
			delete = curr;
			curr = curr->Next;
			free(delete);
		}
		ship->Next = NULL;
	}

	//시간 딜레이
	app_TimeDelay(select);
	con_clearBuffer();
	printf("\n초기화 되었습니다.\n");
}

//당학기 반환
double con_ReturnSemester()
{
	Node* curr = head->next;
	double Max = 0.0;

	//가장 큰 학기가 현재 수강 중 OR 이수한 학기로 판별 
	while (curr != NULL)
	{
		//초기 Max값 설정 
		if (curr == head->next)
		{
			Max = curr->Semester;
			curr = curr->next;
			continue;
		}
		//가장 큰 학기 고르기 
		if (curr->Semester > Max)
			Max = curr->Semester;

		curr = curr->next;
	}

	//0.1->0.3->0.2->0.4 당학기로 출력 
	//만약 2학기가(0.2)존재 한다면 0.3(여름학기) 대신 2학기를 출력
	double check = Max - (int)Max;

	//프로그램상 소수점을 100% 정확하게 비교할 수 없으므로 [해당 값에 대한 오차 범위]로 비교 해야함.
	if (check > 0.28 && check < 0.32) //해당 학기가 .3(여름학기)라면 
	{	//2학기가 있는지 체크하기 위한 알고리즘 
		double check2 = Max - 0.13; // *.17
		double check3 = Max - 0.02;	// *.28

		curr = head->next;

		while (curr != NULL)
		{
			if (curr->Semester > check2 && curr->Semester < check3)//만약 .2(2학기)가 존재하면 2학기를 반환 
				return curr->Semester;

			curr = curr->next;
		}
		return Max;//2학기가 없다면 여름학기 반환 
	}
	else//해당 학기가 .3(여름학기)가 아니라면 반환 
		return Max;
}

//과목 폐강 
void con_DeleteSubject()
{
	if (head->next == NULL)
	{
		printf("현재 어떠한 학기도 존재하지 않습니다.\n");
		return;
	}

	printf("주의※ 폐강을 할 때는 폐강 과목을 정확히 기제 해주셔야 합니다.\n");
	printf("주의※ 한 번 폐강된 과목은 절대로 복구할 수 없습니다.\n\n");
	printf("폐강할 과목을 선택하세요:");

	char Name[30] = { 0 };

	gets_s(Name, sizeof(Name));
	//과목명 공백 제거 알고리즘 
	strcpy_s(Name, sizeof(Name), con_RemoveBlank(Name));

	Node* curr = head->next;

	while (curr != NULL)
	{	//학점이 입력되지 않은 수강 과목 및 학점이 입력된 과목
		if (curr->Key == -1 || curr->Key == 1)
		{
			for (int i = 0; i < curr->SubNum; i++)
			{	//폐강을 찾은 경우 
				if (strcmp((curr->cj[i].SubName), Name) == 0)
				{	//과목이 단 한개가 존재하는 경우
					printf("\n -폐강 과목:[%s]\n", curr->cj[i].SubName);

					if (curr->SubNum <= 1)
					{
						printf("[%s] 과목이 하나 밖에 없습니다.\n\n", curr->cj[i].SubName);
						printf("이 경우 학기를 삭제 합니다. 하시겠습니까? (삭제:\'1\', 취소:아무키)\n");
						printf("입력:");
						char Select;
						scanf_s("%c", &Select, 1);

						if (Select == '1')
						{
							con_deleteList(curr->Semester);
							printf("삭제 하였습니다.\n");
							return;
						}
						else
						{
							printf("취소하였습니다.\n"); return;
						}
					}

					//여러 과목이 존재하는 경우
					else
					{
						//수강 과목인 경우
						if (curr->Key == -1)
							curr->Total_Credit = 0;//총 이수 학점 초기화

						//해당 과목 폐강 
						curr->cj[i].key = 0;//해당 폐강 과목 키를 0으로 설정
						curr->SubNum -= 1;//과목 수를 1개 감소

						//과목 수를 1개 감소하고 이를 반영할 새로운 학점 노드 생성
						struct coljumsu* cj = calloc((curr->SubNum), sizeof(struct coljumsu));
						if (cj == NULL)
							return;

						int j = 0;//새로운 학점 노드에 사용될 인덱션 변수

						for (int i = 0; i < (curr->SubNum + 1); i++)
						{	//폐강될 과목을 구별하기 위한 조건문, 수강 중인 과목( -1 ), 학점이 입력된 과목( 1 ) 
							if (curr->cj[i].key == 1 || curr->cj[i].key == -1)
							{
								//기존 학점 노드에 있는 데이터 정보를 새로운 학점 노드로 옮기는 알고리즘 
								cj[j].Credit = curr->cj[i].Credit;
								strcpy_s(cj[j].Jumsu, sizeof(cj[j].Jumsu), curr->cj[i].Jumsu);
								strcpy_s(cj[j].SubName, sizeof(cj[j].SubName), curr->cj[i].SubName);

								//학점 과목인 경우
								if (curr->cj[i].key == 1)
									cj[j].key = 1;

								//수강 과목인 경우 
								if (curr->cj[i].key == -1)
								{	//총 이수 학점 재 설정
									curr->Total_Credit += cj[j].Credit;
									cj[j].key = -1;
								}
								//새로운 학점 노드 인덱스를 다음 인덱스로 이동 
								j++;
							}
						}
						//기존의 학점 노드 삭제 
						struct coljumsu* delete = curr->cj;
						//새로운 학점 노드를 삽입 
						curr->cj = cj;
						free(delete);
						//만약 폐강된 과목의 학기가 학점이 입력된 학기( 1 )라면 학점을 재연산 해야 함.
						if (curr->Key == 1)
							con_ColAverJumsu(curr, curr->SubNum);

						printf("\n과목 폐강 되었습니다.\n");
						return;
					}
				}
			}
		}
		curr = curr->next;
	}

	printf("해당 과목은 존재 하지 않습니다. 제대로 입력해주세요.\n");
}

//전체 학점 평균
float con_AllGradeAver()
{
	if (head->next == NULL)
		return 0.0;
	
	Node* curr = head->next;
	int Credit = 0;			//총 이수 학점
	float Grade = 0.0;		//EX) A+ == 4.5 
	float EachJumsu = 0.0;	//이수 학점 * 평점 

	//전체 순환하여 모든 과목들의 이수 학점과 평점을 더하여 연산
	//단, P(N/P)학점의 이수학점과 평점은 제외
	while (curr != NULL)
	{
		if (curr->Key == 1)
		{
			struct coljumsu* cj = curr->cj;

			for (int i = 0; i < curr->SubNum; i++)
			{
				EachJumsu = 4.0;

				for (char Grade = 65; Grade <= 68; Grade++)
				{

					if (cj[i].Jumsu[0] == Grade)
					{
						if (cj[i].Jumsu[1] == '+')
						{
							EachJumsu += 0.5;
							break;
						}
						break;
					}
					EachJumsu -= 1.0;
				}

				Grade += (EachJumsu * cj[i].Credit);

				//학점 연산은 P(N/P)학점은 제외하고 연산
				if (strcmp(cj[i].Jumsu, "P") != 0 && strcmp(cj[i].Jumsu, "NP") != 0)
					Credit += cj[i].Credit;
			}
		}
		curr = curr->next;
	}
	return (Grade / Credit);
}

//당학기 수강 입력
void con_InputSubjectName(float semester)
{
	if (con_CheckSemester(semester) == 1);//학점 데이터가 없는 경우
	else if (con_CheckSemester(semester) == 0) { printf("학점 데이터 존재함 \n"); return; }
	else if (con_CheckSemester(semester) == -1) { printf("현재 수강 중 입니다. \n"); return; }
	else { printf("해당 학기가 존재하지 않음\n"); return; }

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

	printf("\n수강 중인 과목 이름과 이수 학점만 입력(수강 중에는 학점을 입력할 수 없습니다.)\n");

	int num = 0; //과목 수 변수 
	//과목 수 입력
	printf("\n현재 수강 [과목 수]를 입력하세요:");

	scanf_s("%d", &num);

	curr->cj = (coljumsu*)calloc(num, sizeof(coljumsu));
	coljumsu* cj = curr->cj;//학점 참조 변수에 학기 노드에 있는 학점 참조값을 대입 
	curr->SubNum = num;

	int Total_credit = 0;//총 이수 학점 변수 
	con_clearBuffer();//버퍼 클리어

	for (int i = 0; i < num + 1; i++)
	{
		system("cls");
		//학점 입력 방법
		app_PrintGradeInfo(num);
		//학점 정보 출력
		app_GradeInputInfo(cj, num);

		if (i == num)
			break;

		printf("%d 번째 정보 입력 (학점 입력 X)\n", (i + 1));

		//노드에 저장된 과목명 변수 초기화: 이수 학점 및 학점 입력 과정에서 오류가 생기면
		//다시 입력해야 함으로 초기화 과목명을 초기화 
		cj[i].SubName[0] = '\0';

		//과목명 변수 생성
		char SubName[60] = { 0 };
		printf("----------------------------------\n");
		printf("[과목 이름] 입력: ");
		gets_s(SubName, sizeof(SubName));

		//과목 명 공백 제거 알고리즘
		strcpy_s(SubName, sizeof(SubName), con_RemoveBlank(SubName));

		//과목 명 공백 및 중복 체크 
		if ((int)strlen(SubName) <= 0 || con_CheckSubName(SubName) == 1)
		{
			printf("과목 명이 같거나 없습니다.\n");
			i--;
			system("pause");
			continue;
		}

		//과목명 데이터 저장
		strcpy_s(cj[i].SubName, sizeof(cj[i].SubName), SubName);

		//뒤로 가기 기능: 잘못 입력 시 뒤로 가기로 다시 입력  
		if (cj[i].SubName[0] == '0')
		{
			cj[i].SubName[0] = '\0';
			cj[i - 1].SubName[0] = '\0';

			//첫 번째 인덱스는 뒤로 갈 수 없게 설정 
			if (i == 0) { i--; continue; }

			cj[i - 1].key = 0;
			i--; i--;//두 번 뒤로 가기 
			continue;
		}

		printf("----------------------------------\n");
		printf("[이수 학점](1 ~ 20):");
		scanf_s("%d", &cj[i].Credit);

		//이수 학점 확인 유무
		if (cj[i].Credit >= 20 || cj[i].Credit <= 0)//예외 처리 
		{
			printf("오류:입력한 학점은 존재하지 않습니다.(다시 입력)\n");
			system("pause");
			con_clearBuffer();
			i--;
			continue;
		}

		Total_credit += cj[i].Credit;
		cj[i].key = -1; //과목이름과 이수 학점만 저장되어 있고 학점이 저장되어 있지 않을 시 -1로 설정
		con_clearBuffer();//버퍼 제거 
	}

	curr->Total_Credit = Total_credit;//총 이수학점 저장 
	curr->Key = -1;//키 저장

	printf("저장되었습니다. \n");
}

//공백 제거 알고리즘
char* con_RemoveBlank(char* Name)
{
	char Name1[60] = { 0 };
	strcpy_s(Name1, sizeof(Name1), Name);//배열에 대입

	//스택 메모리를 사용하면 함수 종료될 때 소멸되므로 문자열을 반환할 때 경고(Warning)발생 
	char* Name2 = malloc(sizeof(char) * 60);	//Heap 메모리를 사용
	if (Name2 == NULL)
		return "에러";

	int num = strlen(Name1);//공백을 제외한 문자 길이 반환

	int j = 0;

	for (int i = 0; i < num + 1; i++)
	{
		//공백이 아닐 시...
		if (Name1[i] != 32)//32:아스키코드(공백) 
		{
			Name2[j] = Name1[i];
			j++;
		}
	}

	Name2[j] = 0;//마지막 NULL값 
	//strcpy_s(Name1, sizeof(Name1), Name2); 보류(잘못 작성된 코드로 판정됨) 
	return Name2;
}

//과목 명 중복 체그 
int con_CheckSubName(const char* name)
{
	Node* curr = head->next;

	while (curr != NULL)
	{
		for (int i = 0; i < curr->SubNum; i++)
		{
			if (strcmp(curr->cj[i].SubName, name) == 0)
			{
				printf("%s == ", name);
				printf("[%.1f] - %s\n", curr->Semester, curr->cj[i].SubName);
				return 1;
			}

		}

		curr = curr->next;
	}
	return 0;
}