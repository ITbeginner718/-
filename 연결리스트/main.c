#include "main.h"
//main.c


int main()
{	
	//프로그램 시작
	app_Init();

	//로그인 화면 
	app_Login();

	//프로그램 시작
	eg_Main_Engine();

	//프로그램 종료
	app_Ending();

	return 0;
}

