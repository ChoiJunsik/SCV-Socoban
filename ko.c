#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>
#define WIDTH 30
#define HEIGHT 30
#define STAGE 5
char name[10];
char map[STAGE][WIDTH][HEIGHT]={' '};
int map_stage;

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
      if(ch=='\n'){
                  x++;
                  y=0;}
      map[i][x][y]=ch;
      y++;
  }

  if(money!=O)
    printf("돈,공간 오류");
  fclose(fp);

  return;
}

void map_load(int map_stage)
{
  printf("Hello %s\n\n",name);
  for(int i=0; i<WIDTH; i++)
    for(int j=0; j<HEIGHT; j++)
        printf("%c",map[map_stage][i][j]);

  return;
}
void help(void)
{
    int input_char;
    input_char = getch();
    if(input_char =='d'){
      system("clear");
      printf("명령내용\n");
      input_char = getch();
      if(input_char =='d')
      system("clear");
      map_load(0);
                  return;
}
}

void PlayerMove(void)
{
  map_load(0);
  int dx,dy;
  int input_char;
  while(1){
    help();
    for(int i=0; i<WIDTH; i++)
      for(int j=0; j<HEIGHT; j++){
          if(map[map_stage][i][j] == '@')
            {
              dy=i;
              dx=j;
            }
    }
    input_char = getch();
    if(input_char=='k'||input_char=='K')
    {
      map[map_stage][dy][dx] = ' ';
      map[map_stage][dy-2][dx+7] = '@';
      system("clear");
      map_load(0);
    }
    else if(input_char=='h'||input_char=='H')
    {
      map[map_stage][dy][dx] = ' ';
      map[map_stage][dy][dx-1] = '@';
      system("clear");
      map_load(0);
    }

    else if(input_char=='l'||input_char=='L')
    {
      map[map_stage][dy][dx] = ' ';
      map[map_stage][dy][dx+1] = '@';
      system("clear");
      map_load(0);
    }
    else if(input_char=='j'||input_char=='J')
    {
      map[map_stage][dy][dx] = ' ';
      map[map_stage][dy+2][dx-7] = '@';
      system("clear");
      map_load(0);
    }

  }
  return;
}



int main(void)
{

  start();
  PlayerMove();
  return 0;
}
