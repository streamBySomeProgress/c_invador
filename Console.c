#include <stdio.h>
#include "Console.h"
#include <curses.h>

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