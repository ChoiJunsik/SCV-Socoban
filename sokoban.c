#include <termio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WIDTH 30
#define HEIGHT 30
#define STAGE 5
char name[10]={0};
char map[STAGE][WIDTH][HEIGHT];
void move(char,int);
int scan_at_x(int);
int scan_at_y(int);
int getch(void);
int scan_at_y(int);
char key_input(int);
void start(void);

int main(void)
{
	  char ch=0;
	  start();
	  for(int stage=0;stage<=4;stage++){
	      while(1)
	      {
		      printf("hello %s",name);
		      for(int y=0; y<WIDTH;y++)
		      {
			       for(int x=0; x<HEIGHT;x++)
				  printf("%c",map[stage][y][x]);
		      }
	              printf("(Command)");
          	      key_input(stage);
          	      printf("\n");
          	      system("clear");
	      }
  }
  return 0;
}
int scan_at_x(int stage)
{
	
	for(int y=0;y<=30;y++){
		for(int x=0;x<=30;x++)
		{
			if (map[stage][y][x]=='@')
				return x;
	}
	}
}
int scan_at_y(int stage)
{
	
	for(int y=0;y<=30;y++){
		for(int x=0;x<=30;x++)
		{
			if (map[stage][y][x]=='@')
				return y;
		}
	}
}
void move (char key,int i){//i==스테이지
    int x = scan_at_x(i);
    int y = scan_at_y(i);
    switch (key){

        case 'j' :

            if (map[i][y+1][x] == '#') //다음칸이 벽
                return;
            else if (map[i][y+1][x] == ' '){ //다음칸이 공간
                map[i][y][x] = ' ';
                map[i][y+1][x] = '@';
                    return;
            }
            else if (map[i][y+1][x] == 'O'){ //다음칸이 은행
                map[i][y][x] = ' ';
                map[i][y+1][x] = '@';
                    return;
            }
            else if (map[i][y+1][x] == '$'){ //다음칸이 돈
                if (map[i][y+2][x] == '#' || map[i][y+2][x] == '$') //다다음칸이 벽이나 돈
                    return;
                else if (map[i][y+2][x] == 'O'){ //다다음칸이 은행
                    map[i][y][x] = ' ';
                    map[i][y+1][x] = '@';
                    map[i][y+2][x] = '$';
                    return;
                }
    else if (map[i][y+2][x] == ' '){ //다다음칸이 공간
                    map[i][y][x] = ' ';
                    map[i][y+1][x] = '@';
                    map[i][y+2][x] = '$';
                    return;
                }
            }
            return;

        case 'k' :

            if (map[i][y-1][x] == '#') //다음칸이 벽
                return;
            else if (map[i][y-1][x] == ' '){ //다음칸이 공간
                map[i][y-1][x] = '@';
                map[i][y][x] = ' ';
                    return;
            }
            else if (map[i][y-1][x] == 'O'){ //다음칸이 은행
                map[i][y-1][x] = '@';
                map[i][y][x] = ' ';
                    return;
            }
            else if (map[i][y-1][x] == '$'){ //다음칸이 돈
                if (map[i][y-2][x] == '#' || map[i][y-2][x] == '$') //다다음칸이 벽이나 돈
                    return;
                else if (map[i][y-2][x] == 'O'){ //다다음칸이 은행
                    map[i][y-2][x] = '$';
                    map[i][y-1][x] = '@';
                    map[i][y][x] = ' ';
                    return;
                }
    else if (map[i][y-2][x] == ' '){ //다다음칸이 공간
                    map[i][y-2][x] = '$';
                    map[i][y-1][x] = '@';
                    map[i][y][x] = ' ';
                    return;
                }
            }
            break;

        case 'h' :

            if (map[i][y][x-1] == '#')
                    return;
            else if (map[i][y][x-1] == ' '){
                map[i][y][x-1] = '@';
                map[i][y][x] = ' ';
                    return;
            }
            else if (map[i][y][x-1] == 'O'){
                map[i][y][x-1] = '@';
                map[i][y][x] = ' ';
                    return;
            }
 else if (map[i][y][x-1] == '$'){
                if (map[i][y][x-2] == '#' || map[i][y][x-2] == '$')
                    return;
                else if (map[i][y][x-2] == 'O'){
                    map[i][y][x-2] = '$';
                    map[i][y][x-1] = '@';
                    map[i][y][x] = ' ';
                    return;
                }
                else if (map[i][y][x-2] == ' '){
                    map[i][y][x-2] = '$';
                    map[i][y][x-1] = '@';
                    map[i][y][x] = ' ';
                    return;
                }
            }
            return;

        case 'l' :

            if (map[i][y][x+1] == '#')
                    return;
            else if (map[i][y][x+1] == ' '){
                map[i][y][x] = ' ';
                map[i][y][x+1] = '@';
                    return;
            }
            else if (map[i][y][x+1] == 'O'){
                map[i][y][x] = ' ';
                map[i][y][x+1] = '@';
                    return;
            }
 else if (map[i][y][x+1] == '$'){
                if (map[i][y][x+2] == '#' || map[i][y][x+2] == '$')
                    return;
                else if (map[i][y][x+2] == 'O'){
                    map[i][y][x] = ' ';
                    map[i][y][x+1] = '@';
                    map[i][y][x+2] = '$';
                    return;
                }
                else if (map[i][y][x+2] == ' '){
                    map[i][y][x] = ' ';
                    map[i][y][x+1] = '@';
                    map[i][y][x+2] = '$';
                    return;
                }
            }
            return;
        default :
            break;
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
