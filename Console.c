#include <stdio.h>
#include "console.h"

//HANDLE hout;

void moveCursor(int x, int y) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return;
    }

    SDL_WarpMouseGlobal(x, y);
    SDL_Quit();
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
	int i;
}

void gotoxy(UPOINT pt)
{

	moveCursor(pt.x, pt.y);
}