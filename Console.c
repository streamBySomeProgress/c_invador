#include <stdio.h>
#include "console.h"
#include <curses.h>

//HANDLE hout;

void SetConsoleCursorPosition(int row, int col) {
    // ANSI escape code: \033[<row>;<col>H
    printf("\033[%d;%dH", row, col); // 탈출 구문을 사용하여 일반적인 문자열 출력이 아닌 다른 동작을 수행하도록 함
    fflush(stdout); // Ensure the cursor moves immediately --> 표준 출력 stream(stdout) 과 연관된 버퍼를 비움(출력 처리)
}

void ClearScreen()
{
	int i,j;
	UPOINT pos;

	for(i = 1 ; i < 25 ; i++)
	{
		for(j = 1; j < 80 ; j++)
		{
			pos.x = j;
			pos.y = i;
			gotoxy(pos);
			printf(" ");
		}
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
}

// 본 함수 이하에 커서를 이동시킬 시 작동시키고자 하는 동작을 추가로 작성할수 있다 
void gotoxy(UPOINT pt)
{
	SetConsoleCursorPosition(pt.x, pt.y);
}