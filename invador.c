#include "MAIN.H"

UPOINT ptthisMypos;
int    timeflag = FALSE;
int    score,hiscore =2000, killnum;
char   *Aboom[8];

// 난이도 조절 기능
// 폭발 애니메이션을 별도로 작성하여 적기 격추 애니메이션에도 적용 가능하도록 함

int main(void)
{	
	UPOINT        ptend;
	int	loop = 1;
	
	Aboom[0] = "i<^>i";
	Aboom[1] = "i(*)i";
	Aboom[2] = "(* *)";
	Aboom[3] = "(** **)";
	Aboom[4] = " (* *) ";
	Aboom[5] = "  (*)  ";
	Aboom[6] = "   *   ";
	Aboom[7] = "       ";
	ptend.x = 36;
	ptend.y = 12;
	while(loop)
	{
		clock_t       updatedClockCnt = clock();
	    clock_t       prevClockCnt = updatedClockCnt;
		int           bp =0;
		int enemySpeed = 40 * TIME_UNIT; // 기본 보통
		int firespeed = 20 * TIME_UNIT;
		printf("난이도 선택--> e:쉬움, n:보통, h:어려움\n");
		
		switch (getch())
		{
			// '쉬움' 조건에서의 환경 세팅
		    case 'e':
				enemySpeed = 6 * TIME_UNIT;
				firespeed = 15 * TIME_UNIT;
			// '보통' 조건에서의 환경 세팅
			case 'n':
				;
			// '어려움' 조건에서의 환경 세팅
			case 'h':
				enemySpeed = 20 * TIME_UNIT;
				firespeed = 30 * TIME_UNIT;
		}

		// 동작
		play(enemySpeed, firespeed);
		
		for(;;)  
		{
			if(timeflag == FALSE)
			{
				updatedClockCnt = clock();
				
				if(updatedClockCnt - prevClockCnt > 30 *TIME_UNIT)
				{
					gotoxy(ptthisMypos);
					printf("%s",Aboom[bp]); // 적의 총알에 맞은 좌표(ptthisMypos)에서 printf 사용하여 폭발 애니메이션 활성화
					bp++;
					if(bp > 7)
					   break;
					prevClockCnt = updatedClockCnt;
				}
			}
			else
			 break;
		}
		
		gotoxy(ptend);
		printf("당신의 비행기는 파괴되었습니다.");
		ptend.y +=1;
		gotoxy(ptend);
		printf("다시 할까요? (y/n)\n");

		if(getch() == 'y')
		{
			ClearScreen();  
			bp=0;
			killnum = 0;
			timeflag = 0;
			ptend.y  = 12;
			loop = 1;      
		}
		else
			loop = 0;       		
	}

	return 0;
}

void play(int juckspeed, int firespeed)
{
	static UPOINT ptMyoldpos;
	clock_t       gthisClockCount = clock();
    clock_t       gCount = gthisClockCount;
	clock_t       Count = gthisClockCount;
	clock_t       bulletcount = gthisClockCount;
	UPOINT        ptscore,pthi;
	//int           juckspeed=500;
	InitConsole();    
	InitMyship();    
	Initenemyship();  
	
	ptthisMypos.x = ptMyoldpos.x = MYSHIP_BASE_POSX;
    ptthisMypos.y = ptMyoldpos.y = MYSHIP_BASE_POSY;
	
	ptscore.x = 68;
	ptscore.y = 1;

	pthi.x =  2;
	pthi.y =  1;
	
	
	while(TRUE)
	{
	   gthisClockCount = clock(); // 기준시
	
	   if(kbhit())  
	   {
		   switch(getch())    
		   {
			   // 스페이스바로 발사
		   case 32:
			   if(gthisClockCount - bulletcount > firespeed) // 연사속도 조정
			   {
				   MyBulletshot(ptthisMypos);        
				   bulletcount = gthisClockCount;
			   }
			   break;
		   case 'j':
			   ptMyoldpos.x = ptthisMypos.x;        
			   if(--ptthisMypos.x < 1)ptthisMypos.x = 1;
			   DrawMyship(&ptthisMypos , &ptMyoldpos);
			   break;
		   case 'l':
			   ptMyoldpos.x = ptthisMypos.x;          
			   if(++ptthisMypos.x > 75)ptthisMypos.x = 75 ;
			   DrawMyship(&ptthisMypos , &ptMyoldpos);
			   break;
		   }
	   }
 
	   if(gthisClockCount - Count > 15 * TIME_UNIT)
	   {
	
		   // 격추된 경우
		   if(CheckMybullet(ptthisMypos) == 0)            
		   {
			   if(score > 2000)
				   hiscore = score;
			   break; // play 이하 구문을 진행하고자 반복문 탈출
		   }

	       CheckenemyBullet(enemyship);                  
		   DrawMyBullet();                                
		   DrawMyship(&ptthisMypos , &ptMyoldpos);        
		   gotoxy(ptscore);
		  
		   if(killnum < 40)
		      printf("점수 : %d",score);
		   else
		   {
			   timeflag = TRUE;
			   break;
		   }

		   if(killnum > 20)                              
			   juckspeed = 150;                          
		  
		   gotoxy(pthi);
		  
	   	   Count = gthisClockCount;
	   }
	  
	   if(gthisClockCount - gCount > juckspeed)
	   {
		   Bulletshot();                                  
	       DrawBullet();                                  
	  	   CalenemyshipPos();                            
		   Drawenemyship();                              
		   if(Checkenemypos() == 1)
			   break;                
		   gCount = gthisClockCount;                      
	   }
	}

}