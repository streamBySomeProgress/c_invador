#define MAX_ENEMY           40  
#define MAXENEMY_BASE_ROW    4  
#define MAXENEMY_BASE_COL   10  
#define MAXENEMY_BULLET     10  
#define ENEMYSHIP_BASE_POSX 20  
#define ENEMYSHIP_BASE_POSY  2  
#define TRUE                 1
#define FALSE                0

#define MAXMY_BULLET        3 // 총알 개수
#define MYSHIP_BASE_POSX    38  
#define MYSHIP_BASE_POSY    23  
#define TIME_UNIT 12000 // 클럭을 사용함에 따라 일정 단위의 시간을 정의하기 위하여 사용하는 메크로

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Console.h"
#include "keyInput.h"

typedef struct{  
	int flag;
	UPOINT pos;  
} MYSHIP;

typedef struct{
	int flag;
	UPOINT pos;
} BULLET;

typedef struct{
	int flag;
	UPOINT pos;
} ENEMYSHIP;

extern BULLET     myship_bullet[MAXMY_BULLET];
extern BULLET     enemy_bullet[MAXENEMY_BULLET];
extern ENEMYSHIP  enemyship[MAX_ENEMY];
extern int        score,killnum;

void DrawMyship(UPOINT *pt,UPOINT*);
void InitMyship();
void MyBulletshot(UPOINT );
void DrawMyBullet();
int  CheckMybullet(UPOINT ptthisMypos);

void Drawenemyship( );
void Initenemyship();
void CalenemyshipPos();
int  Checkenemypos();
int  Calflag();
void CalTime();
void Bulletshot();
void DrawBullet();
void InitBullet();
void CheckenemyBullet(ENEMYSHIP*);

void boom(UPOINT pt,int );
void play(int juckspeed, int firespeed);