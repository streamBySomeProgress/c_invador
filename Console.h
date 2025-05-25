typedef struct{  
	int x; // column
	int y; // row
} UPOINT;


#ifdef _WIN32
#include <windows.h>
#include <wincon.h>
#else
void moveCursor(int x, int y);
void InitConsole();
void gotoxy(UPOINT pt);
void ClearScreen();
void SetCursorPosition(int row, int col);
#endif