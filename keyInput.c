#include "keyInput.h"

// 커스텀 kbhit 구현
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt); // 현재 터미널 설정 저장
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // 비표준 입력, 에코 끄기
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // 새 설정 적용
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); // 비차단 모드 설정

    ch = getchar(); // 키 입력 시도

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 원래 설정 복구
    fcntl(STDIN_FILENO, F_SETFL, oldf); // 원래 파일 상태 복구

    if (ch != EOF) {
        ungetc(ch, stdin); // 입력된 키를 버퍼에 되돌림
        return 1; // 키 입력 있음
    }
    return 0; // 키 입력 없음
}

// 커스텀 getch 구현
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