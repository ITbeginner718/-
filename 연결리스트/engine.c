#include "main.h"
//engine.c

//���� ȭ�� ���� 
void eg_Main_Engine()
{
	//�޸� �Ҵ�(�л�, ����, ����)
	con_MemoryAllocation();

	while (1)
	{
		//ȭ�� �ʱ�ȭ
		system("cls");

		//���� ���ε�(�л�, ����, ����) 
		con_FILE_All_Load();

		//�л� ���� ���
		stu_PrintStuInfo();

		char menu = eg_SelectMainMenu();
		//���α׷� ����
		if (menu == 27)
			return;
		switch (menu)
		{
		case '1':
			//�л� ���� �Է�
			stu_InputStuInfo();
			break;

		case '2':
			//�л� ���� ����
			stu_StuInfoCorrect();
			break;

		case '3':
			//���н�û
			stu_LeaveOfAbsenceRequest();
			break;

		case'4':
			//���� ���� ȭ��
			eg_Scholarship();
			break;

		case'5':
			//���� ����
			app_GradeGuide();
			//���� ȭ������ �̵�
			eg_GradeEngine();
			break;

		case '6':
			//��� ������ �ʱ�ȭ
			con_AllDataReset();
			break;

		default:
			printf("�ٽ� �Է�!\n");
			break;
		}

		//���� ���(�л�, ����, ����)
		con_FILE_All_Down();
		//���� Ŭ����
		con_clearBuffer();
		//�� �� ����
		system("pause");
	}

	//������ �Ҹ�
	free(head); free(stu); free(ship);
}

//���� ȭ�� �޴� ����
char eg_SelectMainMenu()
{
	printf("\nMENU [ESC:���α׷� ����]\n");
	printf("================================================\n");
	printf("1. �л� ���� �Է�\t"); printf("2. �л� ���� ����\n");
	printf("------------------------------------------------\n");
	printf("3. ���� ��û(1��)\t"); printf("4. [���� ���� ȭ��]\n");
	printf("------------------------------------------------\n");
	printf("5. [���� ���� ȭ��]\t"); printf("6. �ص����� �ʱ�ȭ��\n");
	printf("================================================\n\n");
	
	printf(">>�޴� �Է�:");
	char menu = _getch();
	printf("\n");
	return menu;
}

//���� ���� ���� 
void eg_Scholarship()
{
	while (1)
	{
		system("cls");

		//���� ������ �������� 
		stu_Scholarship_Info_Load();

		//���� ���� 
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
			printf("���� ȭ������ �̵��մϴ�. \n");
			return;

		default:
			printf("�ٽ� �Է�!\n");
			break;
		}

		//���� ������ ���� 
		stu_Scholarship_Info_Print();

		con_clearBuffer();
		system("pause");
	}
	
}

//���� ���� �޴� ���� 
char eg_ScholarshipSelectMenu()
{
	printf("\nFUNCTION\n");
	printf("==========================================\n");
	printf("1. ���� ���� �Է�\t"); printf("2. ���� ���� ����\n");
	printf("------------------------------------------\n");
	printf("[ESC]���� ȭ������ �̵� \n");
	printf("==========================================\n");

	printf("�޴� �Է�:");
	char menu = _getch();

	return menu;
}

//���� ȭ�� ����
void eg_GradeEngine()
{
	while (1)
	{
		system("cls");

		//���� ���� ���ε�
		con_NodeFileUp();

		//���� �Ϻ� ���� ȭ��
		app_GradeWindowPrint();

		char menu = eg_GradeInfoSelectMenu();

		switch (menu)
		{
		case '1':
			//�б� �߰�
			eg_GradeWindowSemester_OR_Grade(1, "�߰��� �б�");
			break;
		case '2':
			//�б� ����
			eg_GradeWindowSemester_OR_Grade(2, "������ �б�");
			break;
		case '3':
			//���б� ���� �Է�
			eg_GradeWindowSemester_OR_Grade(3, "������ ���б�");
			break;
		case '4':
			//���б� ���� �Է�
			eg_GradeWindowSemester_OR_Grade(4, "������ �Է��� ���б�");
			break;
		case '5':
			//������ �б� �Է�
			eg_GradeWindowSemester_OR_Grade(5, "������ ������ ���б�");
			break;
		case '6':
			//���� ���� ���
			eg_GradeWindowSemester_OR_Grade(6, "������ ����� ���б�");
			break;
		case '7':
			//���� ��ü ���
			app_GradeWindowAllPrint();
			break;
		case '8':
			//�� 
			con_DeleteSubject();
			break;

		case (int)27:
			printf("���� ȭ������ �̵��մϴ�. \n");
			return;

		default:
			printf("�ٽ� �Է�\n");
			break;
		}

		//��� ���� ���� ����
		con_NodeFileDown();

		//���� Ŭ����
		con_clearBuffer();
		system("pause");
	}
}

//���� ȭ�� �޴� ����
char eg_GradeInfoSelectMenu()
{
	printf("\nMENU([1.1 ~ 1.4][2.1 ~ 2.4][3.1 ~ 3.4][4.1 ~ 4.4])\n");
	printf("==========================================================================\n");
	printf("1. �б� ������ [�߰�]\t"); printf("2. �б� ������ [����]\t"); printf("3. ���б� [����]\n");
	printf("--------------------------------------------------------------------------\n");
	printf("4. *�б� ���� [�Է�]\t"); printf("5. �б� ���� [����]\t"); printf("6. ���б� ���� [���� ���]\n");
	printf("--------------------------------------------------------------------------\n");
	printf("7. ��� ���� [���]\t"); printf("8. ���� ��\t");	printf("[ESC]���� ȭ������ �̵�\n");
	printf("===========================================================================\n\n");
	printf(">>�޴� �Է�:");
	char menu = _getch();
	printf("\n");
	return menu;
}

//�б�(����Ʈ)�Է� �� ���� OR ���� �Է�, ����, ����
void eg_GradeWindowSemester_OR_Grade(int value, const char* notice)
{
	app_ListPrint();
	//�б� �Է�
	float semester = 0.0;
	printf("%s �Է�:", notice);
	scanf_s("%f", &semester);
	
	switch (value)
	{
	case 1:
		//�б� ����
		con_insertList(semester);
		break;
	case 2:
		//�б� ����
		con_deleteList(semester);
		break;
	case 3:
		//���б� ���� �Է�
		con_InputSubjectName(semester);
		break;
	case 4:
		//�б� ���� �Է�
		con_InputGrade(semester);
		break;
	case 5:
		//���� ����
		app_CorectSemester(semester);
		break;
	case 6:
		//���� ���(����)
		printf("\n");
		app_GradeSelectPrint(semester);
		break;

	default:
		printf("�ٽ� �Է�");
		break;
	}

}