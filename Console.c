#include <stdio.h>
#include "console.h"

//HANDLE hout;

// void moveCursor(int x, int y) {
//     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//         fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
//         return;
//     }

//     SDL_WarpMouseGlobal(x, y);
//     SDL_Quit();
// }

void setCursorPosition(int row, int col) {
    // ANSI escape code: \033[<row>;<col>H
    printf("\033[%d;%dH", row, col);
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
	// todo macos 에서 구동 가능하도록 수정할 것
	CONSOLE_CURSOR_INFO coninfo;

	coninfo.bVisible = FALSE;
	coninfo.dwSize = 1;

	hout = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorInfo(hout, &coninfo);
}

void gotoxy(UPOINT pt)
{

	setCursorPosition(pt.x, pt.y);
}