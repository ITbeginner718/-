#include "main.h"
//app.c
//���� �׽�Ʈ 
//ó�� ȭ�� 
void app_Init()
{
	printf("====================\n");
	printf("���Ḯ��Ʈ �˰��� �̿��� �ܼ� ���α׷�\n");
	printf("�л� ���� ���� ���α׷�\n");
	printf("2021-02-11\n");
	printf("====================\n");
	
	printf("�α��� ȭ������ �̵��մϴ�.\n\n");
	system("pause");
}

//���� ȭ��
void app_Ending()
{
	system("cls");
	printf("====================\n");
	printf("���Ḯ��Ʈ �˰���\n");
	printf("201910718-�Ǽ�ȣ\n");
	printf("====================\n");
	printf("����\n");
	system("pause");
}

//�α��� ȭ��
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

	if ((check) == -1)//�α��� �����Ͱ� ���� ���
	{
		printf("���� Id/Passwd�� �������� �ʽ��ϴ�.\n");
		printf("�α��� ������ ���� �����մϴ�. ������:�ش� ������ *�ѱ��� ������* ��� ���ڷ� ���� �����մϴ�.\n");

		printf("���̵� �Է�:");
		scanf_s("%s", Id, sizeof(Id));

		printf("��й�ȣ �Է�:");
		scanf_s("%s", Passwd, sizeof(Passwd));

		fclose(loginFile);
		fopen_s(&loginFile, "login.txt", "w");

		if(loginFile==NULL)
			return;

		fprintf(loginFile, "%s %s", Id, Passwd);

		printf("ID/PASSWD�� �����Ǿ����ϴ�.\n");
		system("pause");
	}

	fclose(loginFile);

	//���̵� ��� �Է�
	char inputId[20] = { '\0' };
	char inputPasswd[30];

	while (1)
	{
		system("cls");
		printf("<<�α��� ����>>\n");

		printf("���̵� �Է�:");
		scanf_s("%s", inputId, sizeof(inputId));

		if (strcmp(Id, inputId) == 0)
			break;
		else
			printf("���̵� ����(�ٽ� �ۼ�)\n");

		system("pause");
	}

	while (1)
	{
		int i = 0;
		printf("��й�ȣ �Է�:");
		while (1)
		{
			inputPasswd[i] = _getch();//�Է�

			if (inputPasswd[i] == 13)//����Ű�� ������ ��
			{
				inputPasswd[i] = '\0';//����Ű�� ���� �ε����� NULL�� ���� 
				break;
			}

			else if (inputPasswd[i] == 8)//�齺���̽��� ������ �� �ڷ� ���� 
			{
				if (i == 0)//�ε����� 0�� ���� ��� ���۵� ���� ���� 
					inputPasswd[0] = 0;

				else//�� ���ھ� ���� 
				{	//EX) 5��° �ε���(�Է� �ܰ�)���� �齺���̽��� ������ 5��°�� 4��° �ε����� ������� 
					//4��° �ε������� �ٽ� ����    
					inputPasswd[i] = 0;
					inputPasswd[i - 1] = 0;
					i = (int)strlen(inputPasswd);//���� �� üũ 

					system("cls");
					printf("<<�α��� ����>>\n");
					printf("���̵� �Է�:%s\n", Id);

					printf("��й�ȣ �Է�:");
					for (int i = 0; i < (int)strlen(inputPasswd); i++)//������ ���ڸ� ������ ������ ���� ��� 
						printf("*");
				}
			}
			//����, ���ĺ�, Ư������(ctrl+1 ~ 0) �Է� �� ����ŷ ó�� 
			else if (inputPasswd[i] >= 33 && inputPasswd[i] <= 126)
			{
				printf("*"); i++;
			}
			//�� �� Ư������ �Է½� 
			else
			{
				inputPasswd[i] = 0; continue;
			}
		}

		if (strcmp(Passwd, inputPasswd) == 0)
		{
			printf("\n�α��� ����\n");
			break;
		}

		else
		{
			printf("\n�α��� ����(�ٽ� �Է�)\n");
			system("pause");
			system("cls");
			printf("<<�α��� ����>>\n");
			printf("���̵� �Է�:%s\n", Id);
		}
		
	}
	system("pause");
}

//���� ���� ȭ��
void app_GradeGuide()
{
	system("cls");
	printf("\n<���� ����> ȭ������ �̵��մϴ�. ������ ������ �Ѿ����.\n\n");
	printf("�ڻ�� ���\n");
	printf("��1 - ������ �Է��� ���� �б⸦ ���� �߰��� �� �Է�\n");
	printf("------------------------------------------------------------\n");
	printf("  2 - �б�� \"1.1\" \"2.1\" ó�� �Ҽ������� �б⸦ ���� \n");
	printf("------------------------------------------------------------\n");
	printf("  3 - .1(1�б�) .2(2�б�) .3(���� �б�) .4(�ܿ��б�)�� �Է� \n");
	printf("------------------------------------------------------------\n");
	printf("  4 - ���б� ������ ������ �Է� ���� �ʰ� ����� �̼� ������ �Է¡�\n\n");
	system("pause");
}
/*-----------���� ��� ���------------*/

//���� ���� ȭ��
void app_GradeWindowPrint()
{
	printf("\n[Semester Information Window]\n\n");
	printf("%-9s %-8s %s \t", "�̼�����", "����", "�б�");
	printf("%-9s %-8s %s \n", "�̼�����", "����", "�б�");
	printf("-----------------------------------------------------------\n");

	Node* curr = head->next;
	int count = 0;
	while (curr != NULL)
	{
		if (curr->Key == 1||curr->Key==-1)
		{	//������ P������ �����Ҷ��� PASS�� ��� 
			//->isnan()�� ���� ���ڰ� �ƴ϶��(NaN) 0�� �ƴ� ���� ���, ���ڶ�� 0�� ���  
			if (isnan(curr->Aver_Grade) != 0) //PASS�� P/N ��, ������ ����(0.0) 
				printf("%s %-7d %s %s "," ", curr->Total_Credit,"P(N/P)", " ");
			else
				printf("%s %-7d %-6.2f %s "," ", curr->Total_Credit, curr->Aver_Grade, " ");
		}
		//������ �� �� ������ Key==0
		else
			printf("%-9s %-4s %-4s", "����", "����", " ");

		//���� �б�(0.3), ���� �б�(0.4)�� ����
		float select = curr->Semester - ((int)curr->Semester);

		if (select > 0.29)
		{
			if (select > 0.39)
				printf("%.1f[�ܿ�]", curr->Semester);
			else
				printf("%.1f[����]", curr->Semester);
		}

		else
			printf("%.1f(����)", curr->Semester);
		//¦���� ���� �ٷ� �̵� 
		count++;

		if (curr->Key == -1)
			printf("(�ڼ��� �ߡ�)");
		
		if (count % 2 == 0)
			printf("\n");
		else
			printf("\t");
		
		curr = curr->next;
	}
	if (count % 2 == 1)
		printf("\n");
	printf("-----------------------------------------------------------\n");

	//�� �̼� ���� ��� 
	Node* curr2 = head->next;
	int Total_Credit = 0;//�� �̼� ����
	int Curr_Credit = 0;//���� ���� ����
	
	while (curr2 != NULL)
	{
		if (curr2->Key == 1)//������ �Էµ� ����
			Total_Credit += curr2->Total_Credit;
		if (curr2->Key == -1)//���� ���� ����
			Curr_Credit += curr2->Total_Credit;

		curr2 = curr2->next;
	}

	printf("->��ü ����:��%.2f\n\n", con_AllGradeAver());
	printf("<������������: 132��>\n");
	printf("-------------------------------------\n");
	printf("���� ��/(�� �̼�)/*���� : %d/(%d)/*%d \n", Curr_Credit, Total_Credit, (132 - Total_Credit));
	printf("-------------------------------------\n");
}

//����Ʈ ���(�ܼ� ���� ����Ʈ)
void app_ListPrint()
{
	printf("����� �б�: [");
	Node* curr = head->next;

	while (curr != NULL)
	{
		printf("%.1f", curr->Semester); //�бⰡ ����� ������ ���

		if (curr->next != NULL)
			printf(" -> ");

		curr = curr->next; 
	}
	printf("]\n");
}

//���� ����
void app_CorectSemester(float semester)
{
	if (con_CheckSemester(semester) == -1)
	{ printf("���� ���� �� �Դϴ�. \n"); return; }
	if (con_CheckSemester(semester) == 1)
	{ printf("���� �����Ͱ� �����ϴ�. \n"); return; }
	if (con_CheckSemester(semester) == -10)
	{printf("�ش� �б�� �����ϴ�. \n"); return;}

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

	con_clearBuffer();//���� Ŭ���� 
	
	while (1)
	{
		char Name[60] = { 0 };

		system("cls");
		printf("\n[�б� ���� ����]\n");
		app_GradeSelectPrint(curr->Semester);

		coljumsu* cj = curr->cj;
		printf("�������� ������ �����Ͽ� �Է�â�� ���̼���.��\n");
		printf("�������� �������� ���� \"0\"�� �Է��ϼ��䡹\n\n");

		printf(">������ ������ �Է��Ͻÿ�:");
		gets_s(Name,sizeof(Name));

		//���� ���� �˰���
		strcpy_s(Name, sizeof(Name), con_RemoveBlank(Name));

		//���� ���� 
		if (Name[0] == '0')
			break;

		int check = 0;//���� Ȯ�� ���� 

		for (int i = 0; i < curr->SubNum; i++)//���� Ž��
		{
			//�ش� ���� ���� 
			if (strcmp(Name, cj[i].SubName) == 0)
			{
				check = 1;//���� Ȯ��

				printf("���� �̸� ����:");
				gets_s(cj[i].SubName, sizeof(cj[i].SubName));

				//���� ���� �˰���
				strcpy_s(cj[i].SubName, sizeof(cj[i].SubName), con_RemoveBlank(cj[i].SubName));

				printf("�̼� ���� ����:");
				scanf_s("%d", &cj[i].Credit);

				char Jumsu[3] = { 0 };
				printf("��� ����:");
				scanf_s("%s", Jumsu, sizeof(Jumsu));


				//�ҹ���->�빮�� ���� �˰��� 
				if (Jumsu[0] >= 97 && Jumsu[0] <= 122)
				{
					char s_char = Jumsu[0];
					s_char = s_char - 32;
					Jumsu[0] = s_char;
				}

				//���� Ȯ�� ����
				if (con_DiviJumsu(Jumsu) == 0)
				{
					printf("�ش� ������ �������� �ʽ��ϴ�(�ٽ� �Է�).\n");
					break;//�ݺ��� Ż�� 
				}
				strcpy_s(cj[i].Jumsu, sizeof(cj[i].Jumsu), Jumsu);

				break;//�ݺ��� Ż��
			}
		}

		if (check == 0)
			printf("�ش� ������ �����ϴ�.\n");

		con_clearBuffer();//���� Ŭ���� 
		system("pause");
	}

	//���� �� ����
	con_ColAverJumsu(curr, curr->SubNum);
}

//���� ���� ���
void app_GradeSelectPrint(float semester)
{
	if (con_CheckSemester(semester) == -10)
	{ printf("�ش� �бⰡ �������� ����\n"); return; }
		
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

	printf(">>");
	float select = curr->Semester - ((int)curr->Semester);

	//���� �б�� ���� �б� ���� 
	if (select > 0.29)
	{
		if (select > 0.39)
			printf("%.1f(�ܿ�)", curr->Semester);
		else
			printf("%.1f(����)", curr->Semester);
	}

	else
		printf("%.1f", curr->Semester);

	//������ P������ �����Ҷ��� PASS�� ��� 
	//->isnan()�� ���� ���ڰ� �ƴ϶��(NaN) 0�� �ƴ� ���� ���, ���ڶ�� 0�� ��� 
	if (isnan(curr->Aver_Grade) != 0)
		printf("�б� - �̼�����:%d - ����:PASS(N/P)", curr->Total_Credit);
	else
		printf("�б� - �̼�����:%d - ����:%.2f", curr->Total_Credit, curr->Aver_Grade);

	if (curr->Key == 1 || curr->Key == -1)
	{
		//���� ���� �б�
		if (curr->Key == -1)
			printf("������ ���� �ߡ�\n");

		printf("\n%-11s %-10s %s \n", "<<�̼� ����>>", "<<����>>", "<<�����>>");
		printf("---------------------------------------------\n");

		for (int i = 0; i < curr->SubNum; i++)//�ش� ���� �� ��ŭ �ݺ� 
		{
			printf("-> %-13d %-8s %s", curr->cj[i].Credit, curr->cj[i].Jumsu, curr->cj[i].SubName);
			if (strcmp(curr->cj[i].Jumsu, "F") == 0 || strcmp(curr->cj[i].Jumsu, "NP") == 0)
				printf("(����� ����)\n");
			else
				printf("\n");
			printf("---------------------------------------------\n");
		}
	}

	else
		printf("\n���� ����-> �Է� ���\n");

	printf("\n");

}

//���� ��ü ���
void app_GradeWindowAllPrint()
{
	system("cls");
	printf("���� ��� ���� ���\n\n");

	Node* curr = head->next;
	
	while(curr != NULL)
	{
		app_GradeSelectPrint(curr->Semester);
		curr = curr->next;
	}
}
/*----------------------------------------*/

//�ǽð� �ԷµǴ� ���� ���� 
void app_GradeInputInfo(struct coljumsu* cj, int count)
{
	printf("���� �Է� ����\n");
	printf("=====================\n");
	printf("%-8s%-7s%-7s\n","����", "����","�����\n");
	for (int i = 0; i < count; i++)
	{
		if (cj[i].key == 1)
		{
			printf("*%-6d >>%-4s %s", cj[i].Credit, cj[i].Jumsu, cj[i].SubName);
			//F OR NP�� �����
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

//���� �Է� ��� �Ұ�
void app_PrintGradeInfo(int num)
{
	printf("****���� ��� ����****\n\n");
	printf("[<���� �̸�>�� �����ϰ� ���ڷ� �ۼ��ص� ����]\n");
	printf("[����� <�̼� ����>�� \"1 ~ 20\"�������� �Է�]\n");
	printf("[������ A+, A0(A), B+, B0(B), C+, C0(C), D+, D0(D), P(NP), F �Է�]\n\n");
	

	printf("[���� ������ �߸� �Է� �� -> ���� �̸��� <���� 0>�� �Է��ϸ� �� ������ �̵�]\n");
	printf("\n\n*���� ��:%d*\n", num);
}

//�ð� ������
void app_TimeDelay(char select)
{
	char* name;

	if (select == '1')
		name = "�л�";
	else if (select == '2')
		name = "����";
	else if (select == '3')
		name = "����";
	else
		name = "���[�л�, ����, ����]";

	for (int i = 0; i < 3; i++)
	{
		system("cls");
		printf("         ��%s ������ �ʱ�ȭ��\n",name);
		printf("���� �Էµ� %s �����͸� �ʱ�ȭ�ϰ� �ֽ��ϴ�.\n",name);
		printf("                 ������");
		for (int i = 0; i < 5; i++)
		{
			Sleep(120);
			printf(".");
		}
	}
}

//������ �ʱ�ȭ ���� ȭ�� 
void app_IntroReset()
{
	printf("\n������ �ʱ�ȭ\n");
	printf("=================================\n");
	char* true = "������";
	char* false = "�������� ����";

	//�л� ������ Ȯ��
	printf("�л� ���� ������:");
	
	//�л��� �޸𸮴� ������ �������� ������ �޸𸮴� �Ҵ��� ��
	if (stu ->key == 1)
		printf("%s\n",true);
	else
		printf("%s\n",false);
	printf("---------------------------------\n");
	//���� ������ Ȯ��
	printf("���� ���� ������:");
	if (head->next != NULL)
		printf("%s\n",true);
	else
		printf("%s\n",false);
	printf("---------------------------------\n");
	//���� ���� ������ Ȯ��
	printf("���� ���� ������:");
	if (ship->Next != NULL)
		printf("%s\n", true);
	else
		printf("%s \n", false);
	printf("=================================\n\n");

	printf("MENU(���:<�ƹ� Ű>)\n");

	printf("�л� ����:<1��>, ���� ����:<2��> \n");
	printf("---------------------------------\n");
	printf("���� ����:<3��>, ��� ����:<4��> \n");
}
