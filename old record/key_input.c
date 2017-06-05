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
char key_input(int stage)
{
  char key=getch();
  switch(key){
    case 'h':
    case 'j':
    case 'k':
    case 'l':move(key,stage); break;
    case 'u':printf("%c",key);break;
    case 'r':printf("%c",key);break;
    case 'n':printf("%c",key);break;
    case 'e':printf("%c",key);break;
    case 's':printf("%c",key);break;
    case 'f':printf("%c",key);break;
    case 'd':printf("%c",key);break;
    case 't':printf("%c",key);break;
    default :break;
   return 0;
  }

}
