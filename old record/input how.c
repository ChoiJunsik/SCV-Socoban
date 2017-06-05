#include <stdio.h>
#include <termio.h>
 int getch(void){
    int ch;

    struct termios buf;
    struct termios save;

    tcgetattr(0, &save);

    buf = save;

    buf.c_lflag&=~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;

    tcsetattr(0, TCSAFLUSH, &buf);

    ch = getchar();

    tcsetattr(0, TCSAFLUSH, &save);

    return ch;

 }

 int main(void){
    int input_char;

    while (1){
       printf("명령을 입력하시오 : ");
       input_char = getch();
       if (input_char == 'y')
          printf("You inputed Yes\n");
       else if (input_char == 'q'){
          printf("Bye\n");
          break;
       }
       else
          printf("You inputed %c\n", input_char);
    }

    return 0;

 }
