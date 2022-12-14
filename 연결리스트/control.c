#include "main.h"
//control.c 

//���� ���� 
void con_clearBuffer() { while (getchar() != '\n'); } //scanf_s()�� �����̽� �� OR ����Ű�� '\n'���� ����  

//�޸� �Ҵ�
void con_MemoryAllocation()
{
	//�л� ����  
	stu = malloc(sizeof(student));

	//���� ����
	if ((head = malloc(sizeof(Node))) == 0)
		return;
	head->next = NULL;

	//���� ����  
	if ((ship = malloc(sizeof(scholarship))) == NULL)
		return;
	ship->Next = NULL;

}

//��� ���� ���ε�(�л�, ����, ����)
void con_FILE_All_Load()
{
	//�л� ���� ���ε� 
	stu_FileLoad();
	//��� ���� ���ε�
	con_NodeFileUp();
	//���� ���� ���ε� 
	stu_Scholarship_Info_Load();
}

//��� ���� ����(�л�, ����, ����)
void con_FILE_All_Down()
{
	//�л� ���� ���� ���� 
	stu_FilePrint();
	//��� ���� ���� ����
	con_NodeFileDown();
	//������ ���� 
	stu_Scholarship_Info_Print();
}

//��� ������(�б�, ����) �����ϱ�(�ٿ�ε�)
void con_NodeFileDown()
{
	FILE* List;
	fopen_s(&List, "list.bin", "wb");//���(�б�) ���� ����
	if (List == NULL)//���� ó�� 
	{
		printf("List ����\n"); return;
	}

	FILE* Grade;
	fopen_s(&Grade, "Grade.bin", "wb");//����(����) ���� ���� 
	if (Grade == NULL)//���� ó�� 
	{
		printf("Grade ����\n"); return;
	}

	Node* curr = head->next;//������ ��ȯ
	//"���(�б�)������"�� ��嵥���Ϳ� ��� �ִ� "����(����)������"�� ���� ����
	while (curr != NULL)
	{	//������ ����� �б�( 1 )�� ���� ���� �б�(-1)�� ����  
		if (curr->Key == 1 || curr->Key == -1)
		{	//��嵥���Ϳ� ��� �ִ� ����(����) ������ ����
			for (int i = 0; i < curr->SubNum; i++)
				fwrite(&(curr->cj[i]), sizeof(coljumsu), 1, Grade);
		}
		fwrite(curr, sizeof(Node), 1, List);//���(�б�) ������ ���� 
		curr = curr->next;//���� ���(�б�)�� �̵� 
	}

	free(curr);//������ �Ҹ� 
	fclose(List);//���� �ݱ�
	fclose(Grade);
}

//��� ������(�б�, ����) ��������(���ε�) 
void con_NodeFileUp()
{
	//�б� ����Ʈ
	FILE* List;
	fopen_s(&List, "list.bin", "rb");//��� ���� ���� 
	if (List == NULL)
		return;

	//����(����) ����
	FILE* Grade;
	fopen_s(&Grade, "Grade.bin", "rb");//����(����) ���� ���� 
	if (Grade == NULL)
		return;

	//��� �ʱ�ȭ
	Node* curr = head->next;//������ ��ȯ
	Node* delete;//��� �ʱ�ȭ 

	while (curr != NULL)
	{
		delete = curr;//�ʱ�ȭ �� ���(�б�)
		curr = curr->next;//���� ���� �̵� 
		free(delete);
	}

	//��� ��� ���� �ʱ�ȭ 
	head->next = NULL;

	while (1)
	{	//��� ����
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL)
			return;
		//���Ͽ� �����Ͱ� �ִ��� üũ 
		int Check = fread(newNode, sizeof(Node), 1, List);

		//������ ���� �������� ��(���ε��� ������ ������) �ݺ��� Ż��(���� 0 ��ȯ)
		if (!(Check)) { free(newNode); break; }

		if (head->next == NULL)	//�ش� ��尡 ó���� ��� ���� ó�� �κп� ���� 
			head->next = newNode;

		else//�ش� ��尡 ó���� �ƴ� ���  
		{
			Node* curr2 = head->next;//������ ��ȯ 
			//������ ��忡 �����ϱ����� ������ ��� Ž��
			while (curr2->next != NULL)
				curr2 = curr2->next;//������ ����� ���� ��尡 NULL�̸� ���� ��忡 ���� 

			curr2->next = newNode;
		}

		//���� ������ ����� �б�(1)�� ���� ���� �б�(-1)�� �ִٸ� ���� ���ε�  
		if (newNode->Key == 1 || newNode->Key == -1)
		{
			newNode->cj = malloc(sizeof(coljumsu) * newNode->SubNum);
			if (newNode->cj == 0)
				return;
			for (int i = 0; i < newNode->SubNum; i++)//���� ���� �߰� 
				fread(&(newNode->cj[i]), sizeof(coljumsu), 1, Grade);//����(����)�� ����� ����(Grade)���� ���ε� 
		}

		/*���Ͽ��� �����͸� ���� �� �� �ش� ����� ���� ���(Next)��
		NULL�� �ƴϸ� Next���� ������ ����� �ּ� ���� �����ϹǷο��� �߻�*/
		newNode->next = NULL;	//�߿�! ������ next�� NULL�� �����ؾ���
	}

	//���� �ݱ� 
	fclose(List);
	fclose(Grade);
}

//�б�(����Ʈ) ���� 
void con_insertList(float semester)
{
	//
	//�б� ���� ó��(1.1 ~ 1.4, 2.1 ~ 2.4, 3.1 ~ 3.4, 4.1 ~ 4.4)
	if (semester > 1.099999 && semester < 4.5)
	{
		float Check = semester - (int)semester;
		//�б� ���� ó��
		if (Check < 0.0999999 || Check>0.4000001)//�Ҽ����� ��Ȯ�� �񱳸� �� �� �����Ƿ� ���� ������ ���ؾ� ��
		{	//0.1���� �۰ų� 0.4���� ũ�� ����
			printf("�б� ����->�ٽ� �Է�\n");
			return;
		}

	}

	else
	{
		printf("�б����->�ٽ� �Է�\n"); return;
	}

	Node* curr = head->next;
	//�б� ������ �ߺ� üũ 
	while (curr != NULL)
	{
		if (curr->Semester == semester)
		{
			printf("����->�б� ������ �ߺ�!\n");
			return;
		}
		curr = curr->next;
	}

	//���ο� ��� �Ҵ�
	Node* newNode = malloc(sizeof(Node));
	if (newNode == 0)
		return;

	//������ �ʱ�ȭ 
	newNode->next = NULL; //�ʼ� 
	newNode->Total_Credit = 0;
	newNode->Aver_Grade = 0.0;
	newNode->Key = 0;
	newNode->Semester = semester;

	//��� ����
	if (head->next == NULL)//��尡 ������ ó�� ��� ��忡 ���� 
		head->next = newNode;

	else
	{
		Node* curr = head->next;
		while (curr->next != NULL)//������ ��� Ž�� 
			curr = curr->next;
		curr->next = newNode;
	}

	//������ �� ���� 
	con_ArrayNode();
}

//�б� ���� 
void con_ArrayNode()
{
	if (head->next == NULL)
		return;

	Node* temp;//���Ŀ� ���Ǵ� ���� ���� 
	//������ ��ȯ 
	Node* curr = head->next;

	int count = 0;//���� �б� �� 
	int index = 0;//���Ŀ� ���Ǵ� �ε��� ���� 
	
	
	//���(�б�) �� üũ
	while (curr != NULL)
	{
		count++; curr = curr->next;
	}

	Node** Array = malloc(sizeof(Node) * count);//���ĸ� �ϱ� ���� ������ �迭 ���� 

	if (Array == NULL)
		return;

	curr = head->next;//������ ��ȯ 

	for (int i = 0; i < count; i++)
	{
		Array[i] = curr;//2�� �迭�� Node�� ���� 
		curr = curr->next;
	}

	//���� �˰���:�б⸦ �������� ������������ ���� 
	for (int i = 0; i < count; i++)
	{
		index = i;
		for (int j = i + 1; j < count; j++)
		{
			if (Array[index]->Semester > Array[j]->Semester)//�б� �� 
				index = j;
		}
		temp = Array[i];
		Array[i] = Array[index];
		Array[index] = temp;
	}

	//���ĵ� ������ �� ��ġ 
	Node* newNode = Array[0];
	head->next = newNode;
	newNode->next = NULL;

	for (int i = 1; i < count; i++)
	{
		curr = head->next;
		Node* newNode = Array[i];

		while (curr->next != NULL)//������ ��带 ã�� ���� ������ Ž�� 
			curr = curr->next;

		curr->next = newNode;

		newNode->next = NULL;
	}
}

//����Ʈ ����
void con_deleteList(float semester)
{
	Node* curr = head->next;
	Node* pre = curr;//���� ��� ���� 

	while (curr != NULL)
	{
		if (curr->Semester == semester)
		{	//���� ��尡 ��� ��忡 ��ġ�� ��� 
			if (curr == head->next)
			{
				if (curr->next == NULL)//��� ����� ���� ��尡 ���� ��� 
					head->next = NULL;//��� ��� NULL�� ��ȯ 
				else					//��� ����� ���� ��尡 �ִ� ��� 
					head->next = curr->next;//���� ���� �̵� 
			}

			//�� �������� ���
			else if (curr->next == NULL)
				pre->next = NULL;

			//�߰��� ��� 
			else
				pre->next = curr->next;

			free(curr);//��� ����
			return;
		}

		else
		{
			pre = curr;//���� ��带 ���� ��忡 ����
			curr = curr->next;//���� ���� ���� ���� �̵� 
		}
	}
	printf("�ش� �����ʹ� �������� �ʽ��ϴ�.\n");
}

//�б� ������ Ȯ�� 
int con_CheckSemester(float semester)
{
	Node* curr = head->next;

	while (curr != NULL)
	{
		if (curr->Semester == semester)
		{
			//���� �����Ͱ� ���� ���
			if (curr->Key == 0)
				return 1;

			//���� ���� �б� �� ���
			if (curr->Key == -1)
				return -1;

			//���� �����Ͱ� �ִ� ���
			else
				return 0;
		}
		else
			curr = curr->next;
	}

	return -10;//�ش� �бⰡ �������� ����
}

//���б� ���� �Է�(�б� ������ Ȯ�� �޼ҵ� ���)
void con_InputGrade(float semester)  
{
	if (con_CheckSemester(semester) == 1 || con_CheckSemester(semester) == -1);
	else if (con_CheckSemester(semester) == 0) { printf("���� ������ ������ \n"); return; }
	else { printf("�ش� �бⰡ �������� ����\n"); return; }

	//������ ��ȸ 
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

	int num = 0; //���� �� �Է� ����

	if (curr->Key == 0)//���� ������ ���ٸ�(0)
	{
		printf("\n���� �� �Է�:");
		scanf_s("%d", &(curr->SubNum));

		//������ �Է��� ���� �޸� ���� �Ҵ�, calloc �����ڸ� ��� 
		curr->cj = (coljumsu*)calloc(curr->SubNum, sizeof(coljumsu));
	}

	num = curr->SubNum;
	struct coljumsu* cj = curr->cj;//���ο� cj���� ������ ������ ���� 
	if (cj == NULL)
		return;

	con_clearBuffer();//���� Ŭ����

	//���� �Է�
	//(num+1) : ����� ������ ���δ� �����ֱ� ���ؼ� ��� ������ �Է��ϰ� �� ���� ��ȯ �ؾ���
	for (int i = 0; i < num + 1; i++)
	{	//�ݺ��� ó�� 
		system("cls");
		//���� �Է� ���
		app_PrintGradeInfo(num);
		//���� ���� ���
		app_GradeInputInfo(cj, num);
		
		if (i == num)
			break;

		if (curr->Key == 0)//���� ������ ������( 0 ) �����, �̼����� �Է�
		{
			//����� ���� ����
			char SubName[60] = { 0 };
			//��忡 ����� ����� ���� �ʱ�ȭ: �̼� ���� �� ���� �Է� �������� ������ �����
			//�ٽ� �Է��ؾ� ������ �ʱ�ȭ ������� �ʱ�ȭ 
			cj[i].SubName[0] = '\0';

			printf("\n->%d ��° ���� �Է�\n",i+1);
			printf("----------------------------------\n");
			printf("*���� �̸�*�� �Է�: "); gets_s(SubName, sizeof(SubName));

			//���� �� ���� ���� �˰���
			strcpy_s(SubName, sizeof(SubName), con_RemoveBlank(SubName));

			//���� �� ���� �� �ߺ� üũ 
			if ((int)strlen(SubName) <= 0 || con_CheckSubName(SubName) == 1)
			{
				printf("���� ���� ���ų� �����ϴ�.\n");
				i--;
				system("pause");
				continue;
			}

			//����� ������ ����
			strcpy_s(cj[i].SubName, sizeof(cj[i].SubName), SubName);

			//�ڷ� ���� ���: �߸� �Է� �� �ڷ� ����� �ٽ� �Է�  
			if (cj[i].SubName[0] == '0')
			{
				cj[i].SubName[0] = '\0';
				cj[i - 1].SubName[0] = '\0';

				//ù ��° �ε����� �ڷ� �� �� ���� ���� 
				if (i == 0) { i--; continue; }

				cj[i - 1].key = 0;
				i--; i--;//�� �� �ڷ� ���� 
				continue;
			}

			//�̼� ���� 
			printf("----------------------------------\n");
			printf("�̼� ����(1~20): "); scanf_s("%d", &cj[i].Credit);

			//�̼� ���� Ȯ�� ����
			if (cj[i].Credit >= 20 || cj[i].Credit <= 0)//���� ó�� 
			{
				printf("����:�Է��� ������ �������� �ʽ��ϴ�.(�ٽ� �Է�)\n");
				system("pause");
				con_clearBuffer();
				i--;
				continue;
			}
		}

		//���� �Է�
		printf("----------------------------------\n");
		printf("A+ ~ D0 / F / P(NP)\n");
		printf("(�ҹ��� ����)����: ");
		scanf_s("%s", cj[i].Jumsu, sizeof(cj[i].Jumsu)); //Enter or space bar �Է� �� ������ ���� 

		//�ҹ���->�빮�� ���� �˰��� (����)
		for (int j = 0; j < (int)strlen(cj[i].Jumsu); j++)//���� �� ��ŭ 
		{
			if (cj[i].Jumsu[j] >= 97 && cj[j].Jumsu[0] <= 122)// a ~ z
			{
				char s_char = cj[i].Jumsu[j];
				s_char = s_char - 32;
				cj[i].Jumsu[j] = s_char;
			}
		}

		//���� Ȯ�� ����
		if (con_DiviJumsu(cj[i].Jumsu) == 0)
		{
			printf("�ش� ������ �������� �ʽ��ϴ�(�ٽ� �Է�).\n\n");
			system("pause");
			con_clearBuffer();
			i--;
			continue;
		}

		//������ �ԷµǾ����Ƿ� ������ �Էµ� ����(1)���� ǥ��
		cj[i].key = 1;

		con_clearBuffer();//���� Ŭ���� 

	}//�ݺ��� ������

	con_ColAverJumsu(curr, num);//���� ���� 

	printf("������ ����Ǿ����ϴ�.\n");
}

//���� ���� ��� 
void con_ColAverJumsu(struct Node* curr, int size)
{
	float EachJumsu; //ex) A+ =>> 4.5
	float EachJumsu2;	//ex) 4.5*�̼� ����
	float TotalJumsu = 0.0;	//EachJumsu2�� ���� ��
	int TotalCredit = 0;	//�� �̼� ����
	int ToCreExclu_P = 0;	//P������ ������ ���

	struct coljumsu* cj = curr->cj;
	if (cj == NULL)
		return;

	//���� �ο�!!
	/*
	* A+ ~ D0 ���� ������ �ο��ϸ�
	* P(N/P)�� F�� ������ 0.0�� �ο��ϸ� P(N/P)�� ���� ��꿡 ���Ե��� �ʴ´�.
	*/
	for (int i = 0; i < size; i++)
	{
		EachJumsu = 4.0;
		//�ƽ�Ű �ڵ带 �̿��� ���� ���� �˰���
		for (char Grade = 65; Grade <= 68; Grade++)//A~D���� 
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

		//���� ����(F OR P(N/P)�� 0������ ó��) 
		EachJumsu2 = EachJumsu * cj[i].Credit;
		TotalJumsu += EachJumsu2;

		// �� �̼� ���� ��� (��,N/P�� �̼� ������ ���� ����)
		if (strcmp(cj[i].Jumsu, "NP") != 0)
			TotalCredit += cj[i].Credit;

		// P(N/P)������ ������ ���� ������ ���� �̼����� ���
		if (strcmp(cj[i].Jumsu, "P") != 0 && strcmp(cj[i].Jumsu, "NP") != 0)
			ToCreExclu_P += cj[i].Credit;//������ ����� ���� P(N/P)������ �����ϰ� ����ؾ� �� 
	}
	
	//f������ ���� ���꿡�� ���Ե����� <���� �̼�>�� �� ���� ���� ������
	//�ٽ� f�� ���� ������ �̼� ������ �ٽ� �����ؾ��� 
	int Credit_F = 0;//F���� �̼�����
	
	for (int i = 0; i < size; i++)
		if (strcmp(cj[i].Jumsu, "F") == 0)
			Credit_F += cj[i].Credit;

	curr->Aver_Grade = (TotalJumsu / ToCreExclu_P);//P(N/P)������ ������ �� ���� 
	curr->Total_Credit = (TotalCredit - Credit_F);//F������ ���� ������ �̼� ������ �ٽ� �����ؾ� ��.

	//���
	printf("�� �̼� ����:%d \n", curr->Total_Credit);

	if (isnan(curr->Aver_Grade) != 0)//PASS�� ���(���ڰ� �ƴ� ���) 0�� �ƴ� ���� ��ȯ 
		printf("PASS(N/P)\n");
	else
		printf("��� ����:%.2f\n", curr->Aver_Grade);

	curr->Key = 1;//������ �Էµ� �б�( 1 )�� ���� 
}

//���� Ȯ�� ����
int con_DiviJumsu(const char* name)
{
	char Grade[3];
	strcpy_s(Grade, sizeof(Grade), name);

	if (Grade[0] >= 65 && Grade[0] <= 68)//�ƽ�Ű �ڵ带 (A~D) �̿��Ͽ� ���� üũ 
		if (Grade[1] == '0' || Grade[1] == '+' || Grade[1] == 0)
			return 1;

	if (strcmp(name, "P") == 0 || strcmp(name, "NP") == 0 || strcmp(name, "F") == 0)
		return 1;

	else
		return 0;//�ش� ������ �������� ������ 0�� ��ȯ 
}

//������ �ʱ�ȭ
void con_AllDataReset()
{	
	if (stu->key != 1 && head->next == NULL && ship->Name == NULL)
	{printf("\n �ʱ�ȭ�� �����Ͱ� �������� �ʽ��ϴ�.\n"); return;}
	
	system("cls");
	//������ �ʱ�ȭ ���� 
	app_IntroReset();

	char select; //�޴� ���� 
	printf("\n�ʱ�ȭ ������ ����:");
	scanf_s("%c", &select, 1);

	if (select != '1' && select != '2' && select != '3' && select != '4')
	{ printf("\n����Ͽ����ϴ�. \n"); return; }

	if (select == '1' || select == '4')
	{		
		//�л� ������ �ʱ�ȭ
		free(stu);
		stu = malloc(sizeof(student));//��� �����
		if (stu == NULL)
			return;
	}

	if (select == '2' || select == '4')
	{	
		//���� ������ �ʱ�ȭ 
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
		//���� ������ �ʱ�ȭ 
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

	//�ð� ������
	app_TimeDelay(select);
	con_clearBuffer();
	printf("\n�ʱ�ȭ �Ǿ����ϴ�.\n");
}

//���б� ��ȯ
double con_ReturnSemester()
{
	Node* curr = head->next;
	double Max = 0.0;

	//���� ū �бⰡ ���� ���� �� OR �̼��� �б�� �Ǻ� 
	while (curr != NULL)
	{
		//�ʱ� Max�� ���� 
		if (curr == head->next)
		{
			Max = curr->Semester;
			curr = curr->next;
			continue;
		}
		//���� ū �б� ���� 
		if (curr->Semester > Max)
			Max = curr->Semester;

		curr = curr->next;
	}

	//0.1->0.3->0.2->0.4 ���б�� ��� 
	//���� 2�бⰡ(0.2)���� �Ѵٸ� 0.3(�����б�) ��� 2�б⸦ ���
	double check = Max - (int)Max;

	//���α׷��� �Ҽ����� 100% ��Ȯ�ϰ� ���� �� �����Ƿ� [�ش� ���� ���� ���� ����]�� �� �ؾ���.
	if (check > 0.28 && check < 0.32) //�ش� �бⰡ .3(�����б�)��� 
	{	//2�бⰡ �ִ��� üũ�ϱ� ���� �˰��� 
		double check2 = Max - 0.13; // *.17
		double check3 = Max - 0.02;	// *.28

		curr = head->next;

		while (curr != NULL)
		{
			if (curr->Semester > check2 && curr->Semester < check3)//���� .2(2�б�)�� �����ϸ� 2�б⸦ ��ȯ 
				return curr->Semester;

			curr = curr->next;
		}
		return Max;//2�бⰡ ���ٸ� �����б� ��ȯ 
	}
	else//�ش� �бⰡ .3(�����б�)�� �ƴ϶�� ��ȯ 
		return Max;
}

//���� �� 
void con_DeleteSubject()
{
	if (head->next == NULL)
	{
		printf("���� ��� �б⵵ �������� �ʽ��ϴ�.\n");
		return;
	}

	printf("���ǡ� ���� �� ���� �� ������ ��Ȯ�� ���� ���ּž� �մϴ�.\n");
	printf("���ǡ� �� �� �󰭵� ������ ����� ������ �� �����ϴ�.\n\n");
	printf("���� ������ �����ϼ���:");

	char Name[30] = { 0 };

	gets_s(Name, sizeof(Name));
	//����� ���� ���� �˰��� 
	strcpy_s(Name, sizeof(Name), con_RemoveBlank(Name));

	Node* curr = head->next;

	while (curr != NULL)
	{	//������ �Էµ��� ���� ���� ���� �� ������ �Էµ� ����
		if (curr->Key == -1 || curr->Key == 1)
		{
			for (int i = 0; i < curr->SubNum; i++)
			{	//���� ã�� ��� 
				if (strcmp((curr->cj[i].SubName), Name) == 0)
				{	//������ �� �Ѱ��� �����ϴ� ���
					printf("\n -�� ����:[%s]\n", curr->cj[i].SubName);

					if (curr->SubNum <= 1)
					{
						printf("[%s] ������ �ϳ� �ۿ� �����ϴ�.\n\n", curr->cj[i].SubName);
						printf("�� ��� �б⸦ ���� �մϴ�. �Ͻðڽ��ϱ�? (����:\'1\', ���:�ƹ�Ű)\n");
						printf("�Է�:");
						char Select;
						scanf_s("%c", &Select, 1);

						if (Select == '1')
						{
							con_deleteList(curr->Semester);
							printf("���� �Ͽ����ϴ�.\n");
							return;
						}
						else
						{
							printf("����Ͽ����ϴ�.\n"); return;
						}
					}

					//���� ������ �����ϴ� ���
					else
					{
						//���� ������ ���
						if (curr->Key == -1)
							curr->Total_Credit = 0;//�� �̼� ���� �ʱ�ȭ

						//�ش� ���� �� 
						curr->cj[i].key = 0;//�ش� �� ���� Ű�� 0���� ����
						curr->SubNum -= 1;//���� ���� 1�� ����

						//���� ���� 1�� �����ϰ� �̸� �ݿ��� ���ο� ���� ��� ����
						struct coljumsu* cj = calloc((curr->SubNum), sizeof(struct coljumsu));
						if (cj == NULL)
							return;

						int j = 0;//���ο� ���� ��忡 ���� �ε��� ����

						for (int i = 0; i < (curr->SubNum + 1); i++)
						{	//�󰭵� ������ �����ϱ� ���� ���ǹ�, ���� ���� ����( -1 ), ������ �Էµ� ����( 1 ) 
							if (curr->cj[i].key == 1 || curr->cj[i].key == -1)
							{
								//���� ���� ��忡 �ִ� ������ ������ ���ο� ���� ���� �ű�� �˰��� 
								cj[j].Credit = curr->cj[i].Credit;
								strcpy_s(cj[j].Jumsu, sizeof(cj[j].Jumsu), curr->cj[i].Jumsu);
								strcpy_s(cj[j].SubName, sizeof(cj[j].SubName), curr->cj[i].SubName);

								//���� ������ ���
								if (curr->cj[i].key == 1)
									cj[j].key = 1;

								//���� ������ ��� 
								if (curr->cj[i].key == -1)
								{	//�� �̼� ���� �� ����
									curr->Total_Credit += cj[j].Credit;
									cj[j].key = -1;
								}
								//���ο� ���� ��� �ε����� ���� �ε����� �̵� 
								j++;
							}
						}
						//������ ���� ��� ���� 
						struct coljumsu* delete = curr->cj;
						//���ο� ���� ��带 ���� 
						curr->cj = cj;
						free(delete);
						//���� �󰭵� ������ �бⰡ ������ �Էµ� �б�( 1 )��� ������ �翬�� �ؾ� ��.
						if (curr->Key == 1)
							con_ColAverJumsu(curr, curr->SubNum);

						printf("\n���� �� �Ǿ����ϴ�.\n");
						return;
					}
				}
			}
		}
		curr = curr->next;
	}

	printf("�ش� ������ ���� ���� �ʽ��ϴ�. ����� �Է����ּ���.\n");
}

//��ü ���� ���
float con_AllGradeAver()
{
	if (head->next == NULL)
		return 0.0;
	
	Node* curr = head->next;
	int Credit = 0;			//�� �̼� ����
	float Grade = 0.0;		//EX) A+ == 4.5 
	float EachJumsu = 0.0;	//�̼� ���� * ���� 

	//��ü ��ȯ�Ͽ� ��� ������� �̼� ������ ������ ���Ͽ� ����
	//��, P(N/P)������ �̼������� ������ ����
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

				//���� ������ P(N/P)������ �����ϰ� ����
				if (strcmp(cj[i].Jumsu, "P") != 0 && strcmp(cj[i].Jumsu, "NP") != 0)
					Credit += cj[i].Credit;
			}
		}
		curr = curr->next;
	}
	return (Grade / Credit);
}

//���б� ���� �Է�
void con_InputSubjectName(float semester)
{
	if (con_CheckSemester(semester) == 1);//���� �����Ͱ� ���� ���
	else if (con_CheckSemester(semester) == 0) { printf("���� ������ ������ \n"); return; }
	else if (con_CheckSemester(semester) == -1) { printf("���� ���� �� �Դϴ�. \n"); return; }
	else { printf("�ش� �бⰡ �������� ����\n"); return; }

	//������ ��ȸ 
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

	printf("\n���� ���� ���� �̸��� �̼� ������ �Է�(���� �߿��� ������ �Է��� �� �����ϴ�.)\n");

	int num = 0; //���� �� ���� 
	//���� �� �Է�
	printf("\n���� ���� [���� ��]�� �Է��ϼ���:");

	scanf_s("%d", &num);

	curr->cj = (coljumsu*)calloc(num, sizeof(coljumsu));
	coljumsu* cj = curr->cj;//���� ���� ������ �б� ��忡 �ִ� ���� �������� ���� 
	curr->SubNum = num;

	int Total_credit = 0;//�� �̼� ���� ���� 
	con_clearBuffer();//���� Ŭ����

	for (int i = 0; i < num + 1; i++)
	{
		system("cls");
		//���� �Է� ���
		app_PrintGradeInfo(num);
		//���� ���� ���
		app_GradeInputInfo(cj, num);

		if (i == num)
			break;

		printf("%d ��° ���� �Է� (���� �Է� X)\n", (i + 1));

		//��忡 ����� ����� ���� �ʱ�ȭ: �̼� ���� �� ���� �Է� �������� ������ �����
		//�ٽ� �Է��ؾ� ������ �ʱ�ȭ ������� �ʱ�ȭ 
		cj[i].SubName[0] = '\0';

		//����� ���� ����
		char SubName[60] = { 0 };
		printf("----------------------------------\n");
		printf("[���� �̸�] �Է�: ");
		gets_s(SubName, sizeof(SubName));

		//���� �� ���� ���� �˰���
		strcpy_s(SubName, sizeof(SubName), con_RemoveBlank(SubName));

		//���� �� ���� �� �ߺ� üũ 
		if ((int)strlen(SubName) <= 0 || con_CheckSubName(SubName) == 1)
		{
			printf("���� ���� ���ų� �����ϴ�.\n");
			i--;
			system("pause");
			continue;
		}

		//����� ������ ����
		strcpy_s(cj[i].SubName, sizeof(cj[i].SubName), SubName);

		//�ڷ� ���� ���: �߸� �Է� �� �ڷ� ����� �ٽ� �Է�  
		if (cj[i].SubName[0] == '0')
		{
			cj[i].SubName[0] = '\0';
			cj[i - 1].SubName[0] = '\0';

			//ù ��° �ε����� �ڷ� �� �� ���� ���� 
			if (i == 0) { i--; continue; }

			cj[i - 1].key = 0;
			i--; i--;//�� �� �ڷ� ���� 
			continue;
		}

		printf("----------------------------------\n");
		printf("[�̼� ����](1 ~ 20):");
		scanf_s("%d", &cj[i].Credit);

		//�̼� ���� Ȯ�� ����
		if (cj[i].Credit >= 20 || cj[i].Credit <= 0)//���� ó�� 
		{
			printf("����:�Է��� ������ �������� �ʽ��ϴ�.(�ٽ� �Է�)\n");
			system("pause");
			con_clearBuffer();
			i--;
			continue;
		}

		Total_credit += cj[i].Credit;
		cj[i].key = -1; //�����̸��� �̼� ������ ����Ǿ� �ְ� ������ ����Ǿ� ���� ���� �� -1�� ����
		con_clearBuffer();//���� ���� 
	}

	curr->Total_Credit = Total_credit;//�� �̼����� ���� 
	curr->Key = -1;//Ű ����

	printf("����Ǿ����ϴ�. \n");
}

//���� ���� �˰���
char* con_RemoveBlank(char* Name)
{
	char Name1[60] = { 0 };
	strcpy_s(Name1, sizeof(Name1), Name);//�迭�� ����

	//���� �޸𸮸� ����ϸ� �Լ� ����� �� �Ҹ�ǹǷ� ���ڿ��� ��ȯ�� �� ���(Warning)�߻� 
	char* Name2 = malloc(sizeof(char) * 60);	//Heap �޸𸮸� ���
	if (Name2 == NULL)
		return "����";

	int num = strlen(Name1);//������ ������ ���� ���� ��ȯ

	int j = 0;

	for (int i = 0; i < num + 1; i++)
	{
		//������ �ƴ� ��...
		if (Name1[i] != 32)//32:�ƽ�Ű�ڵ�(����) 
		{
			Name2[j] = Name1[i];
			j++;
		}
	}

	Name2[j] = 0;//������ NULL�� 
	//strcpy_s(Name1, sizeof(Name1), Name2); ����(�߸� �ۼ��� �ڵ�� ������) 
	return Name2;
}

//���� �� �ߺ� ü�� 
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