// 운영체제 종류에 따라 전처리
#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
extern void init_console(void);
extern void cleanup_console(void);

extern int kbhit(void); // 커스텀 kbhit 헤더
extern int getch(void); // 커스텀 getch 헤더
#endif