#include "keyInput.h"

static struct termios oldt;

void init_console(void) {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt); // oldt 참조를 통해 기존 터미널 설정 저장함
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // 비표준 입력, 에코 끄기
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK); // 비차단 모드 설정
}

void cleanup_console(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 기존 터미널 설정 복구
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) & ~O_NONBLOCK); // 비차단 해제
}

// 커스텀 kbhit 구현
int kbhit(void) {
    int ch = getchar(); // 키 입력 시도
    if (ch != EOF) {
        ungetc(ch, stdin); // 입력된 키를 버퍼에 되돌림(getch 에서 입력된 키를 읽을수 있도록)
        return 1; // 키 입력 있음
    }
    return 0; // 키 입력 없음
}

// 커스텀 getch 구현
int getch(void) {
    return getchar();
}