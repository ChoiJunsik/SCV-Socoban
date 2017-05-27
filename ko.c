#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WIDTH 30
#define HEIGHT 30
#define STAGE 5
char name[10];
char map[STAGE][WIDTH][HEIGHT];

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
      map[i][x][y]=ch;
      y++;
      if(ch=='\n'){
              x++;
      }
  }

  if(money!=O)
    printf("돈,공간 오류");
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
  start();
  map_start();
    for(int j=0; j<WIDTH;j++)
      for(int k=0; k<HEIGHT;k++)
          printf("%c",map[0][j][k]);


  return 0;
}
