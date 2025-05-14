/*
    전투기 게임 소스코드 본문
	일정 시간 단위로 키보드 입력을 받거나 동기화 로직을 작동시키는 방식으로 게임이 진행된다.
	단순 반복문 내에서 클럭 수를 저장하는 long 변수 값을 사용한 조건문을 차용함으로서 구현하는 중
*/

#include "Main.h" // 기타 라이브러리들은 Main 해더에 할당

#define SPEED_CONTROL 50 // 1초당 1000클럭임에 유념하여 값 설정하기

UPOINT ptCurrentMypos; // 기존 ptthisMypos 대체
int timeflag = FALSE;
int score,hiscore =2000, killnum;

//, 의존성 존재 가능성이 있으니 디버깅
/*UPOINT ptthisMypos;
int    timeflag = FALSE;
int    score,hiscore =2000, killnum;
char   *Aboom[8];
int yes_or_no = 0 ;*/


int main(void)
{
    UPOINT ptend = {MYSHIP_BASE_POSX,MYSHIP_BASE_POSY};

    int yes_or_no = 0 ;
	int	loop = 1;

    char   *Aboom[8];
	Aboom[0] = "i<^>i";
	Aboom[1] = "i(*)i";
	Aboom[2] = "(* *)";
	Aboom[3] = "(** **)";
	Aboom[4] = " (* *) ";
	Aboom[5] = "  (*)  ";
	Aboom[6] = "   *   ";
	Aboom[7] = "       ";

	//ptend.x = 36;
	//ptend.y = 12;

	while(loop)
	{
		// 본동작 이전 초기화 영역
		int bp = 0;
		ptCurrentMypos = {MYSHIP_BASE_POSX,MYSHIP_BASE_POSY};

		play(); // 본동작

        // play() 함수 종료될 때(게임이 끝나고 제어권이 main 함수로 돌아올 때) 이하 폭발 애니메이션 실행
		while(true)
		{
			if (timeflag == FALSE)
			{
				long thisClockCount = clock(); // 초당 1000 (clock)
		        long bcount = thisClockCount;
				//thisClockCount = clock();

                // 폭발 애니메이션 프레임 속도 조절
				if (thisClockCount - bcount > 100 / SPEED_CONTROL)
				{
					gotoXY(ptCurrentMypos);
					printf("%s",Aboom[bp]);
					bp++;

					if(bp > 7)
					   break;

					bcount = thisClockCount;
				}
			}
			else
			    break;
		}

		/*gotoXY(ptend);
		printf("58line ");
		ptend.y +=1;*/

		gotoXY(ptend);
		printf("do you wanna try again? (y/n)\n");

        // scanf 사용?
		Dasi:
		yes_or_no = getch();

		if (yes_or_no == 'y')
		{
			// 게임을 다시 시작
			ClearScreen();
			bp = 0;
			killnum = 0;
			timeflag = 0;
			ptend.x = MYSHIP_BASE_POSX;
			ptend.y = MYSHIP_BASE_POSY;
			loop = 1;
		}
		else if (yes_or_no == 'n')
			loop = 0;
		else
			goto Dasi; // 유효한 값이 아닐 경우 재질의
	}

	return 0;
}

void play()
{
	static UPOINT ptMyoldpos;
	long         clockCount = clock();
	long         gCount = clockCount;
	long         Count = clockCount;
	long         bulletcount = clockCount;
	UPOINT       ptscore,pthi;
	int          enemySpeed=500 / SPEED_CONTROL ;

	InitConsole();
	InitMyship();
	Initenemyship();

	ptCurrentMypos.x = ptMyoldpos.x = MYSHIP_BASE_POSX;
	ptCurrentMypos.y = ptMyoldpos.y = MYSHIP_BASE_POSY;

	ptscore.x = 68;
	ptscore.y = 1;

	pthi.x =  2;
	pthi.y =  1;


	while(TRUE)
	{
	    clockCount = clock();

        // 진행 도중 키 입력 발생할 시 동작
	    if (kbhit())
	    {
		   switch(getch())
		   {
		    case 'a':
			    if(clockCount - bulletcount > 500 / SPEED_CONTROL) // 연사속도 조절
			    {
				   MyBulletshot(ptCurrentMypos);
				   bulletcount = clockCount;
			    }
			    break;
		    case 'j':
			    ptMyoldpos.x = ptCurrentMypos.x;
			    if(--ptCurrentMypos.x < 1)
			    {
				   // 좌측으로 최대 이동한 상태에서 추가 이동 시도할 시
				   ptCurrentMypos.x = 1;
			    }
			    DrawMyship(&ptCurrentMypos , &ptMyoldpos); // 이동
			    break;
		    case 'l':
			    ptMyoldpos.x = ptCurrentMypos.x;
			    if(++ptCurrentMypos.x > 75)
			    {
				   // 우측으로 최대 이동한 상태에서 추가 이동 시도할 시
				   ptCurrentMypos.x = 75 ;
			    }
			    DrawMyship(&ptCurrentMypos , &ptMyoldpos); // 이동
			    break;


		    case 'q':
			    exit(0); // 종료

			    break;
		    }
	    }

       // clockCount - Count 는 초시계와 유사한 동작을 수행하는듯 하다(일정 시간마다 함수가 동작하게끔 역할)
	   if(clockCount - Count > 150 / SPEED_CONTROL)
	   {

		   if(CheckMybullet(ptCurrentMypos) == 0)
		   {
			    if(score > 2000)
				{
					hiscore = score;
				}
			    break;
		   }
		   CheckenemyBullet(enemyship);
		   DrawMyBullet();
		   DrawMyship(&ptCurrentMypos , &ptMyoldpos);
		   gotoXY(ptscore);

		   if(killnum < 40)
		      printf("178line : %d",score);
		   else
		   {
			   timeflag = TRUE;
			   break;
		   }

		   if(killnum > 20)
		   {
		        enemySpeed = 150 / SPEED_CONTROL;
		   }

		   gotoXY(pthi);

		   Count = clockCount;
	   }

       // 두 clock 변수의 차이가 적의 이동, 공격 동작이 행해지는 주기보다 길어졌을 때 적기가 공격, 이동 동작을 수행하도록 함
	   if(clockCount - gCount > enemySpeed)
	   {
		    Bulletshot();
		    DrawBullet();
		    CalenemyshipPos();
		    Drawenemyship();
		    if(Checkenemypos() == 1)
			    break;

		    gCount = clockCount;
	   }
	}
}

// 코드 이해하기!!
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}









