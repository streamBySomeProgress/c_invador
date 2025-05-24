// 운영체제 종류에 따라 전처리
#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#define KBHIT kbhit
#define GETCH getch
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// 커스텀 kbhit 헤더
int kbhit(void);

// 커스텀 getch 구현
int getch(void);

#define KBHIT kbhit
#define GETCH getch
#endif
#endif