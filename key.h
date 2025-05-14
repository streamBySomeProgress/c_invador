#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include "Main.h" 


int kbhit(void); // 비차단 입력 감지
int getch(void); // 감지된 키를 읽음 