#include "main.h"
//stu.c

//���� ���� ���
void stu_ScholarshipInfo()
{
	scholarship* curr = ship->Next;

	printf("\n[Scholarship Information windows]\n\n");
	
	printf("%s %-2s %-2s %s \t","[��ȣ]","�б�","�ݾ�(����:õ)","���б�����");
	printf("%s %-2s %-2s %s \n","[��ȣ]","�б�","�ݾ�(����:õ)","���б�����");
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
	printf("=> �� ���� �ݾ�:");

	int total = 0;// �� ���� �ݾ�
	curr = ship->Next;

	while (curr != NULL)
	{
		total += curr->Amount;
		curr = curr->Next;
	}
	total *= 1000;

	char total_s[10];       // ��ȯ�� ���ڿ��� ������ �迭
	sprintf_s(total_s,sizeof(total_s), "%d", total);    // %d�� �����Ͽ� ������ ���ڿ��� ����

	char* p = total_s;
	int length = strlen(total_s);

	for (int i = length; i > 0;)
	{
		printf("%c", *p++); i--;

		if (i > 0 && (i % 3) == 0)
			printf(",");
	}
	printf("��\n");
}

//���� ��� �����ϱ� 
void stu_deleteScholarshipNode()
{
	printf("\n������ ��ȣ(Key)�� �Է�:"); 
	
	int key;
	scanf_s("%d", &key);
	
	scholarship* curr = ship->Next;
	scholarship* pre = curr;

	while (curr != NULL)
	{
		if (curr->key == key)
		{	//���� ��尡 ��� ��忡 ��ġ�� ��� 
			if (curr == ship->Next)
			{
				if (curr->Next == NULL)//��� ����� ���� ��尡 ���� ��� 
					ship->Next = NULL;//��� ��� NULL�� ��ȯ 
				else					//��� ����� ���� ��尡 �ִ� ��� 
					ship->Next = curr->Next;//���� ���� �̵� 
			}

			//�� �������� ���
			else if (curr->Next == NULL)
				pre->Next = NULL;

			//�߰��� ��� 
			else
				pre->Next = curr->Next;

			free(curr);//��� ����
			return;
		}

		else
		{
			pre = curr;//���� ��带 ���� ��忡 ����
			curr = curr->Next;//���� ���� ���� ���� �̵� 
		}
	}
	printf("�ش� �����ʹ� �������� �ʽ��ϴ�.\n");
}

//���� ���� ���� ��������
void stu_Scholarship_Info_Load()
{
	//�б� ����Ʈ
	FILE* Ship;
	fopen_s(&Ship, "Ship.bin", "rb");//��� ���� ���� 
	if (Ship == NULL)
		return;

	//��� �ʱ�ȭ
	scholarship* curr = ship->Next;//������ ��ȯ
	scholarship* delete;//��� �ʱ�ȭ 

	while (curr != NULL)
	{
		delete = curr;//�ʱ�ȭ �� ���(�б�)
		curr = curr->Next;//���� ���� �̵� 
		free(delete);
	}

	//��� ��� ���� �ʱ�ȭ 
	ship->Next = NULL;

	while (1)
	{	//��� ����
		scholarship* newNode = malloc(sizeof(scholarship));
		if (newNode == NULL)
			return;

		//���Ͽ� �����Ͱ� �ִ��� üũ 
		int Check = fread(newNode, sizeof(scholarship), 1, Ship);

		//������ ���� �������� ��(���ε��� ������ ������) �ݺ��� Ż��(���� 0 ��ȯ)
		if (!(Check)) { free(newNode); break; }

		if (ship->Next == NULL)	//�ش� ��尡 ó���� ��� ���� ó�� �κп� ���� 
			ship->Next = newNode;

		else//�ش� ��尡 ó���� �ƴ� ���  
		{
			scholarship* curr2 = ship->Next;//������ ��ȯ 
			//������ ��忡 �����ϱ����� ������ ��� Ž��
			while (curr2->Next != NULL)
				curr2 = curr2->Next;//������ ����� ���� ��尡 NULL�̸� ���� ��忡 ���� 

			curr2->Next = newNode;
		}

		/*���Ͽ��� �����͸� ���� �� �� �ش� ����� ���� ���(Next)��
		NULL�� �ƴϸ� Next���� ������ ����� �ּ� ���� �����ϹǷο��� �߻�*/
		newNode->Next = NULL; //�߿�! ������ next�� NULL�� �����ؾ���
	}
	fclose(Ship);
}

//���� ���� ���� �����ϱ�
void stu_Scholarship_Info_Print()
{
	FILE* Ship;
	fopen_s(&Ship, "Ship.bin", "wb");//���(�б�) ���� ����

	if (Ship == NULL)//���� ó�� 
	{
		printf("Ship ����\n"); return;
	}

	scholarship* curr = ship->Next;//������ ��ȯ
	//"���(�б�)������"�� ��嵥���Ϳ� ��� �ִ� "����(����)������"�� ���� ����

	while (curr != NULL)
	{
		fwrite(curr, sizeof(scholarship), 1, Ship);//���(�б�) ������ ���� 
		curr = curr->Next;//���� ���(�б�)�� �̵� 
	}

	free(curr);//������ �Ҹ� 
	fclose(Ship);//���� �ݱ�
}

//���� ���� �Է� 
void stu_InputScholoarship() 
{
	system("cls");
	float Semester;		//�б�
	char Name[30];		//���б� ���� 
	int Amount;			//�ݾ�
	
	app_ListPrint();
	printf("\n�б� �Է� �� ���а����� ����(1 ~ 50) �ڵ� ����\n");
	printf("���б� �Է¡�:");
	scanf_s("%f", &Semester);

	if (con_CheckSemester(Semester) == -10)
	{
		printf("�ش� �бⰡ ���ų� ���� �����ͳ� �����ϴ�.\n");
		return;
	}

	con_clearBuffer();

	while (1)
	{
		printf("\n�̸��� �ִ� [5����]�� ��µǹǷ� �ǵ��� �����ϰ� �ۼ� EX)\"�������\",\"��������\" \n");
		printf("\n���б� �̸�(�����ϰ� �Է�):");
		gets_s(Name, sizeof(Name));

		//���� �� ���� ���� �˰���
		strcpy_s(Name, sizeof(Name), con_RemoveBlank(Name));

		//���� �� ���� �� �ߺ� üũ 
		if ((int)strlen(Name) <= 0)
		{
			printf("���� ����,�ٽ� �Է��ϼ���\n\n");
			system("pause"); continue;
		}
		break;
	}
	
	while (1)
	{
		printf("\n�ݾ��� �Է�(����:õ):");
		scanf_s("%d", &Amount);

		if (Amount <= 0)
		{
			printf("�ݾ� ����, �ٽ� �Է��ϼ���\n\n");
			system("pause"); continue;
		}
		break;
	}

	stu_InsertShipNode(Semester, Name, Amount);
}

//���� ��� ���� 
void stu_ArraySchoralshipNode()
{
	if (ship->Next == NULL)
		return;

	scholarship* temp;//���Ŀ� ���Ǵ� ���� ���� 
	//������ ��ȯ 
	scholarship* curr = ship->Next;

	int count = 0;//���� �б� �� 
	int index = 0;//���Ŀ� ���Ǵ� �ε��� ���� 


	//���(�б�) �� üũ
	while (curr != NULL)
	{
		count++; curr = curr->Next;
	}

	scholarship** Array = malloc(sizeof(scholarship) * count);//���ĸ� �ϱ� ���� ������ �迭 ���� 

	if (Array == NULL)
		return;

	curr = ship->Next;//������ ��ȯ 

	for (int i = 0; i < count; i++)
	{
		Array[i] = curr;//2�� �迭�� Node�� ���� 
		curr = curr->Next;
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
	scholarship* newNode = Array[0];
	ship->Next = newNode;
	newNode->Next = NULL;

	for (int i = 1; i < count; i++)
	{
		curr = ship->Next;
		scholarship* newNode = Array[i];

		while (curr->Next != NULL)//������ ��带 ã�� ���� ������ Ž�� 
			curr = curr->Next;

		curr->Next = newNode;

		newNode->Next = NULL;
	}
}

//���� ��� �߰� 
void stu_InsertShipNode(float Semester, char*Name, int Amount)
{
	scholarship* newNode = malloc(sizeof(scholarship));
	
	if (newNode == NULL)
		return;

	//��� �ʱ�ȭ
	newNode->Semester = Semester;
	newNode->Amount = Amount;
	strcpy_s(newNode->Name, sizeof(newNode->Name), Name);
	
	//���� ���� ���� 
	int Rand = 0;

	while (1)
	{
		Rand = (rand() % 50) + 1;
		scholarship* curr = ship->Next;
		int check = 0;

		while (curr!=NULL)
		{
			//1~99���� ������ �����ϰ� ���� �ߺ��� üũ 
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

	//��� ����
	if (ship->Next == NULL)//��尡 ������ ó�� ��� ��忡 ���� 
		ship->Next = newNode;

	else
	{
		scholarship* curr = ship->Next;
		while (curr->Next != NULL)//������ ��� Ž�� 
			curr = curr->Next;
		curr->Next = newNode;
	}
	//����
	stu_ArraySchoralshipNode();
}

//�л� ������ ����
void stu_FilePrint()
{
	FILE* FO;

	fopen_s(&FO, "stu.bin", "wb");
	
	if (FO == NULL)
		return;

	fwrite(stu, sizeof(student), 1, FO);
	fclose(FO);
}

//�л� ������ �������� 
void stu_FileLoad()
{
	FILE* FI;

	fopen_s(&FI, "stu.bin", "rb");
	if (FI == NULL)
		return;

	fread(stu, sizeof(student), 1, FI);

	fclose(FI);
}

//�л� ���� �Է�
void stu_InputStuInfo()
{
	if (stu->key == 1)
	{
		printf("�л� �����Ͱ� �����մϴ�. ������ �����ϰ� �������ֽñ� �ٶ��ϴ�.\n");
		return;
	}
	system("cls");
	char college[30];		//�ܰ� ����
	char major[50];			//�а�
	char id[20];			//�й�
	char name[20];			//�̸�
	int grade=0;			//�г�
	char gender;			//����
	char callnum[20];		//��ȭ ��ȣ

	printf("<�л� ���� �Է�>\n\n");
	printf("---------------------------------\n");
	printf(">>�̸� �Է�:");
	scanf_s("%s", name, sizeof(name));

	con_clearBuffer();
	printf("---------------------------------\n");
	printf(">>���� m(����) or w(����) �Է�:");
	scanf_s("%c", &gender, sizeof(gender));

	con_clearBuffer();
	printf("---------------------------------\n");
	printf(">>�Ҽ� �ܰ����� �Է�:");
	gets_s(college, sizeof(college));
	con_RemoveBlank(college);
	strcpy_s(college, sizeof(college), con_RemoveBlank(college));

	printf("---------------------------------\n");
	printf(">>�Ҽ� �а� �Է�:");
	gets_s(major, sizeof(major));
	strcpy_s(major, sizeof(major), con_RemoveBlank(major));

	printf("---------------------------------\n");
	while (1)
	{
		printf(">>�г� �Է�(1~4):");
		scanf_s("%d", &grade);
		if (grade >= 1 && grade <= 4)
			break;

		else
		{
			printf("�г� �ٽ� �Է�\n\n");
			continue;
		}
	}

	printf("---------------------------------\n");
	printf(">>�й� �Է�:");
	scanf_s("%s", id, sizeof(id));

	printf("---------------------------------\n");
	con_clearBuffer();

	while (1)
	{
		int check = 0;

		printf("��ȭ��ȣ�� \'-\'�� �����ϰ� ���ڸ��� �Է�\n");
		printf(">>��ȭ��ȣ �Է�(010-):");
		gets_s(callnum, sizeof(callnum));

		if (callnum[7] != 0 && callnum[8] == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				if (callnum[i] < 48 || callnum[i]>57)
				{
					check= 1;
					printf("���� 8�ڸ��� �Է��ϼ���.(�ٽ� �Է�)\n\n");
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
			printf("8�ڸ��� �ٽ� �Է�\n\n");
			continue;
		}
	}

	stu_InsertStuInfo(college, major, id, name, grade, gender, callnum);

	printf("�л� ���� ���� �Ϸ�\n");
}

//������ ���� 
void stu_InsertStuInfo(const char* college, const char* major, const char* id, const char* name,
				   int grade, char gender, const char* callnum)
{
	
	//������ ����
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
//�л� ���� ���
void stu_PrintStuInfo()
{
	printf("[Student Management Program]\n");
	if (stu->key != 1)
	{ printf(">>�л� ������ �����ϴ�.\n"); return; }

	printf("\n�л� ���� (%s",stu->Name);
	if (stu->Gender == 'm')
		printf("/����)\n");
	else
		printf("/����)\n");
	printf("==============================\n");
	char EnterYear[5] = { '\0' };//���г⵵ ���� 
	for (int i = 0; i < 4; i++)
		EnterYear[i] = stu->Id[i];

	//���� �⵵ ��� atoi():ASCII string to integer
	printf(">>���� / ���� :%s / %d\n", EnterYear, atoi(EnterYear) + 4 + stu->LeaveOfAbsence);
	printf("-----------------------------\n");
	printf(">>����(����:��):%d\n", stu->LeaveOfAbsence);
	printf("-----------------------------\n");
	printf(">>�й�/(�г�) : %s/(%d)\n", stu->Id, stu->StuGrade);
	printf("-----------------------------\n");
	printf(">>%s/%s\n", stu->College, stu->Major);
	printf("-----------------------------\n");
	printf(">>��ȭ��ȣ:%s", "010-");
	for (int i = 0; i < 8; i++)
	{
		printf("%c", stu->CallNum[i]);
		if (i == 3)
			printf("-");
	}
	printf("\n==============================\n\n");

	printf("[�ֱ� �б� ����]\n");
	double semester = con_ReturnSemester();

	if (semester == 0.0)
	{
		printf("���� �б� �����Ͱ� �����ϴ�.\n");
		return;
	}

	Node* curr = head->next;
	while (curr != NULL)
	{
		if (curr->Semester == semester)
		{
			printf("���б�:%.1f - ����(�̼�����):%.2f(%d)��", curr->Semester, curr->Aver_Grade, curr->Total_Credit);
			
			if (curr->Key == 1)
				printf("\n");
			else if (curr->Key == -1)
				printf("->���� ���� �� �Դϴ�.\n");
			else
				printf("->���� ���� ������ �������� �ʽ��ϴ�.\n");

			break;
		}
		curr = curr->next;
	}

}

//�л� ���� ���� 
void stu_StuInfoCorrect()
{
	char name[10] = { '\0' };		//�̸�
	char gender;					//����
	char callnum[12] = { '\0' };	//��ȭ��ȣ

	char id[20] = { '\0' };			//�й�
	int grade;						//�г�
	char college[20] = { '\0' };	//�ܰ�����
	char major[40] = { '\0' };		//�а�
	
	while (1)
	{
		
		system("cls");
		//�л� ���� ���
		stu_PrintStuInfo();

		printf("\n\n>>�л� ���� ���� ��ȣ�� ��������. (ESC:���� �Ϸ�)\n");
		printf("=========================================\n");
		printf("1.�̸�, 2.����, 3.��ȭ��ȣ, 4.�й�,\n");
		printf("-----------------------------------------\n");
		printf("5.�г�, 6.�ܰ�����, 7.�а�, <8>.��ü ����\n");
		printf("=========================================\n");

		printf("�Է�:");
		char Menu=_getch();
		printf("\n");
		switch (Menu)
		{
		case '1':
			printf(">>�̸� ���Է�:");
			scanf_s("%s", name, sizeof(name));
			strcpy_s(stu->Name, sizeof(stu->Name), name);
			break;

		case '2':
			printf(">>���� �� �Է� m(����) OR w(����):");
			scanf_s("%c", &gender, sizeof(gender));
			stu->Gender = gender;
			break;

		case '3':
			while (1)
			{
				printf("��ȭ��ȣ�� \'-\'�� �����ϰ� ���ڸ��� �Է�\n");
				printf(">>��ȭ��ȣ �� �Է�(010-):");
				gets_s(callnum, sizeof(callnum));
				
				int check=0;//üũ ���� 
				if (callnum[7] != 0 && callnum[8] == 0)
				{
					for (int i = 0; i < 8; i++)
					{
						if (callnum[i] < 48 || callnum[i]>57)
						{
							printf("���� 8�ڸ��� �Է��ϼ���.(�ٽ� �Է�)\n\n");
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
					printf("8�ڸ��� �ٽ� �Է�\n\n");
					continue;
				}
			}
			strcpy_s(stu->CallNum, sizeof(stu->CallNum), callnum);
			break;

		case '4':
			printf(">>�й� �� �Է�:");
			scanf_s("%s", id, sizeof(id));
			strcpy_s(stu->Id, sizeof(stu->Id), id);
			break;

		case '5':
			while (1)
			{
				printf(">>�г� �� �Է�(1~4):");
				scanf_s("%d", &grade);
				if (grade >= 1 && grade <= 4)
					break;

				else
				{
					printf("�г� �ٽ� �Է�\n\n");
					continue;
				}
			}

			stu->StuGrade = grade;
			break;

		case '6':
			printf(">>�ܰ����� �� �Է�:");
			gets_s(college, sizeof(college));
			//���� ���� �˰���
			strcpy_s(college, sizeof(college), con_RemoveBlank(college));
			strcpy_s(stu->College, sizeof(stu->College), college);
			break;

		case '7':
			printf(">>�а� �� �Է�:");
			gets_s(major, sizeof(major));
			//���� ���� �˰���
			strcpy_s(major, sizeof(major), con_RemoveBlank(major));
			strcpy_s(stu->Major, sizeof(stu->Major), major);
		
			break;

		case '8':
			stu->key = 0;
			stu_InputStuInfo();
			return;

		case (int)27:
			printf("���� �Ϸ�!\n");
			return;

		case '10':
			printf("�� �Է�\n");
			system("pause");
			break;
		}
		con_clearBuffer();
	}
}

//���� ��û
void stu_LeaveOfAbsenceRequest()
{
	char select=0;
	printf("=============================================================\n");
	printf("���� ��û�� 1�� ������ �����մϴ�.\n");
	printf("���� ������ ���� �� ��û�ϸ� ��û�� ��ŭ ������ ���̰� �˴ϴ�.\n");
	printf("=============================================================\n");
	printf("������ ��û �ϰڽ��ϱ�?(Yes:y Or No:�ƹ� Ű):");
	scanf_s("%c", &select,1);
	
	if (select == 'y'||select=='Y')
	{
		stu->LeaveOfAbsence += 1;
		printf("ó���Ǿ����ϴ�.\n");
	}
	else
		printf("��ҵǾ����ϴ�.\n");
}
