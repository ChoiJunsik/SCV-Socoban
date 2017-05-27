#include <termio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WIDTH 30
#define HEIGHT 30
#define STAGE 5
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
char at_x[STAGE][1],at_y[STAGE][1];
char name[10];
char map[STAGE][WIDTH][HEIGHT];
char key_input()
{
  char key=getch();
  switch(key){
    case 'h'://move_left() break;
    case 'j'://move_down() break;
    case 'k'://move_up() break;
    case 'l':/*:move_right() */break;
    case 'u':printf("%c",key);break;
    case 'r':printf("%c",key);break;
    case 'n':printf("%c",key);break;
    case 'e':printf("%c",key);exit(0);break;
    case 's':printf("%c",key);break;
    case 'f':printf("%c",key);break;
    case 'd':printf("%c",key);break;
    case 't':printf("%c",key);break;
    default :break;
   return 0;	     
  } 

}
void map_start(void)
{

  int x=0,y=0,i=-1;
  char ch;
  int money=0,O=0;
  FILE *fp=fopen("map.txt","r");
  while(fscanf(fp,"%c",&ch) != EOF){
      if(ch=='m')
      {
        i++;
        x,y=0;
        continue;
      }
      else if(ch=='a'||ch=='p')
        continue;
      else if(ch=='e')
        return;
      else if(ch=='$')
              money++;
      else if(ch=='O')
                  O++;
      else if(ch=='@')
	at_y[i][1]=x,at_x[i][1]=y;
      map[i][x][y]=ch;
      y++;
      if(ch=='\n'){
              x++;
      }
  }

  if(money!=O)
  {
     printf("박스의 갯수와 보관장소의 갯수가 같지 않습니다");
     exit(1);
  }
  fclose(fp);
  return;
}

void start(void)
{
  printf("Start....\n");
  printf("input name : ");
  scanf("%s",&name);
  system("clear");

  return;
}

int main(void)
{
  char ch=0;
  start();
  printf("hello %s",name);
  map_start();
  for(int i=0;i<=4;i++){
    for(int x=0; x<WIDTH;x++)
      for(int y=0; y<HEIGHT;y++)
        printf("%c",map[i][x][y]); 
    printf("(Command)");
    while(1)
    {
       key_input();
       
	      
    } 
  }
  return 0;
}
