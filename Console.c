#include <stdio.h>
#include "Console.h"



void ClearScreen()
{
	int i,j;
	UPOINT pos;

	for( i =1 ; i < 25 ; i++)
	{
		for( j = 1; j < 80 ; j++)
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
	
}

void gotoxy(UPOINT pt)
{
	
}