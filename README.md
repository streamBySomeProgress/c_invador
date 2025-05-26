# c_invador
c 언어를 이용한 전투기 공중전

# 컴파일 명렁어
gcc invador.c console.c enemy.c mychar.c keyInput.c -o main -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 
--> -I 이하 헤더파일, -L 이하 라이브러리 파일 경로

## 유의사항

1. mac os 환경에서 개발되고 테스트됨, 리눅스 환경 이외 영역에서는 c 표준 라이브러리 이외에는 include 된 라이브러리들을 재검토할 필요


