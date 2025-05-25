#include <stdio.h>
#include "Console.h"
#include <curses.h>

//HANDLE hout;

void ClearScreen()
{
	int i,j;
	UPOINT pos;

	for(i = 1 ; i < 30 ; i++)
	{
		for(j = 1; j < 100 ; j++)
		{
			pos.x = j;
			pos.y = i;
			gotoxy(pos);
			printf(" ");
		}
		printf("\n");
	}
}

void InitConsole()
{
	// // todo macos 에서 구동 가능하도록 수정할 것
	// CONSOLE_CURSOR_INFO coninfo;

	// coninfo.bVisible = FALSE; // 커서가 보이지 않도록 함
	// coninfo.dwSize = 1; // 커서가 좌측 끝단에 위치하도록 함(100일시 전체차지)

	// hout = GetStdHandle(STD_OUTPUT_HANDLE); // 기본 설정인듯 하다

	// SetConsoleCursorInfo(hout, &coninfo);
	printf("\033[2J"); // 터미널 영역에 텍스트 전부 지움
	printf("\033[?25l"); // 커서 감춤
	printf("\033[%d;%dH", 1, 1); // 커서를 좌측 끝단으로 이동
	fflush(stdout);
}

// 본 함수 이하에 커서를 이동시킬 시 작동시키고자 하는 동작을 추가로 작성할수 있다 
void gotoxy(UPOINT pt)
{
	// ANSI escape code: \033[<row>;<col>H
    printf("\033[%d;%dH", pt.y, pt.x); // row, column
	fflush(stdout);
}