#include <SDL2/SDL.h>


typedef struct{  
	int x;
	int y;
} UPOINT;

void moveCursor(int x, int y);

void InitConsole();
void gotoxy(UPOINT pt);
void ClearScreen();