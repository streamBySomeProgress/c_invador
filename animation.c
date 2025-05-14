#include "animation.h"

char* Aboom[8];

void onShipDestroyed(char shipShape[10], UPOINT currentMyPos)
{
	Aboom[0] = "i<^>i";
	Aboom[1] = "i(*)i";
	Aboom[2] = "(* *)";
	Aboom[3] = "(** **)";
	Aboom[4] = " (* *) ";
	Aboom[5] = "  (*)  ";
	Aboom[6] = "   *   ";
	Aboom[7] = "       ";

	DWORD         thisTickCount = GetTickCount();
	DWORD         bcount = thisTickCount;

	int frame = 0;
	for (;frame < 8;frame++)
	{
		thisTickCount = GetTickCount();

		if (thisTickCount - bcount > 100)
		{
			gotoxy(currentMyPos);
			printf("%s", Aboom[frame]); // 적의 총알에 맞은 좌표(ptthisMypos)에서 printf 사용하여 폭발 애니메이션 활성화
			bcount = thisTickCount; // 애니메이션 프레임 조절
		}
	}
}