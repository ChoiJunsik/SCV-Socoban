#include <termio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WIDTH 30
#define HEIGHT 30
#define STAGE 5
char name[10];
char map[STAGE][WIDTH][HEIGHT];
int move(int);
int scan_at_x(int);
int scan_at_y(int);
int getch(void);
int scan_at_y(int i);
char key_input(int);
void start(void);

int main(void)
{
	  char ch=0;
	  start();
	  for(int i=0;i<=4;i++){
	      while(1){
		  printf("hello %s",name);
		  for(int y=0; y<WIDTH;y++){
			 for(int x=0; x<HEIGHT;x++)
				printf("%c",map[i][y][x]);} 
	    	  printf("(Command)");
               	  key_input(i);
		  printf("\n");
      	          system("clear"); 
       	      }      
  }
  return 0;
}
int scan_at_x(int i)
{
	int x,y=0;
	for(;y<=30;y++){
		for(;x<=30;x++)
		{
			if (map[i][y][x]=='@')
			return y;
		}
	}
}
int scan_at_y(int i)
{
	int x,y=0;
	for(;y<=30;y++){
		for(;x<=30;x++)
		{
			if (map[i][y][x]=='@')
			return y;
		}
	}
}
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
char key_input(int i)
{
  char key=getch();
  switch(key){
    case 'h':
    case 'j':
    case 'k':
    case 'l':move(key); break;
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

void start(void)
{
  printf("Start....\n");
  printf("input name : ");
  scanf("%s",&name);
  system("clear");

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
      if(ch=='\n')
                  y++;

      map[i][y][x]=ch;
      x++;
  }

  if(money!=O)
    printf("돈,공간 오류");
  fclose(fp);

  return;
}
