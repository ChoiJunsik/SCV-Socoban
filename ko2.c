#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>
#define WIDTH 30
#define HEIGHT 30
#define STAGE 5
#define LEFT 104
#define RIGHT 108
#define UP 107
#define DOWN 106
char name[10] = {0};
char map[STAGE][WIDTH][HEIGHT] = {0};
int map_stage=0;
int bank_location_X[59] = {0};
int bank_location_Y[59] = {0};
////////////////////
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
////////////////////입력함수
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
      else if(ch=='\n'){
                  x++;
                  y=0;
      }
      map[i][x][y]=ch;
      y++;
  }

  if(money!=O)
    printf("돈,공간 오류");
  fclose(fp);
  return;
}
/////////////시작시 이름입력+맵불러오기
void map_load(int map_stage)
{
  printf("Hello %s\n\n",name);
  for(int i=0; i<WIDTH; i++)
    for(int j=0; j<HEIGHT; j++)
        printf("%c",map[map_stage][i][j]);

  return;
}
///////////////////맵출력함수
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
//////////////////////도움말함수
void PlayerMove(void)
{
  int dx,dy;
  int input_char;
  int map_stage=0;
  for(int i=0; i<WIDTH; i++)
    for(int j=0; j<HEIGHT; j++){
        if(map[map_stage][i][j] == '@')
          {
              dy=i;
              dx=j;
          }
        }
  input_char = getch();
  switch (input_char){

        case DOWN :

            if (map[map_stage][dy+1][dx] == '#') //다음칸이 벽
                return;
            else if (map[map_stage][dy+1][dx] == ' '){ //다음칸이 공간
                map[map_stage][dy][dx] = ' ';
                map[map_stage][dy+1][dx] = '@';
                    return;
            }
            else if (map[map_stage][dy+1][dx] == 'O'){ //다음칸이 은행
                map[map_stage][dy][dx] = ' ';
                map[map_stage][dy+1][dx] = '@';
                  return;
            }
            else if (map[map_stage][dy+1][dx] == '$'){ //다음칸이 돈
                if (map[map_stage][dy+2][dx] == '#' || map[map_stage][dy+2][dx] == '$') //다다음칸이 벽이나 돈
                    return;
                else if (map[map_stage][dy+2][dx] == 'O'){ //다다음칸이 은행
                    map[map_stage][dy][dx] = ' ';
                    map[map_stage][dy+1][dx] = '@';
                    map[map_stage][dy+2][dx] = '$';
                    return;
                }
    else if (map[map_stage][dy+2][dx] == ' '){ //다다음칸이 공간
                    map[map_stage][dy][dx] = ' ';
                    map[map_stage][dy+1][dx] = '@';
                    map[map_stage][dy+2][dx] = '$';
                    return;
                }
            }
            return;

        case UP :

                if (map[map_stage][dy-1][dx] == '#') //다음칸이 벽
                    return;
                else if (map[map_stage][dy-1][dx] == ' '){ //다음칸이 공간
                    map[map_stage][dy][dx] = ' ';
                    map[map_stage][dy-1][dx] = '@';
                        return;
                }
                else if (map[map_stage][dy-1][dx] == 'O'){ //다음칸이 은행
                    map[map_stage][dy][dx] = ' ';
                    map[map_stage][dy-1][dx] = '@';
                      return;
                }
                else if (map[map_stage][dy-1][dx] == '$'){ //다음칸이 돈
                    if (map[map_stage][dy-2][dx] == '#' || map[map_stage][dy+2][dx] == '$') //다다음칸이 벽이나 돈
                        return;
                    else if (map[map_stage][dy-2][dx] == 'O'){ //다다음칸이 은행
                        map[map_stage][dy][dx] = ' ';
                        map[map_stage][dy-1][dx] = '@';
                        map[map_stage][dy-2][dx] = '$';
                        return;
                    }
        else if (map[map_stage][dy-2][dx] == ' '){ //다다음칸이 공간
                        map[map_stage][dy][dx] = ' ';
                        map[map_stage][dy-1][dx] = '@';
                        map[map_stage][dy-2][dx] = '$';
                        return;
                    }
                }
                return;

            case RIGHT :

            if (map[map_stage][dy][dx+1] == '#') //다음칸이 벽
                            return;
                        else if (map[map_stage][dy][dx+1] == ' '){ //다음칸이 공간
                            map[map_stage][dy][dx] = ' ';
                            map[map_stage][dy][dx+1] = '@';
                                return;
                        }
                        else if (map[map_stage][dy][dx+1] == 'O'){ //다음칸이 은행
                            map[map_stage][dy][dx] = ' ';
                            map[map_stage][dy][dx+1] = '@';
                              return;
                        }
                        else if (map[map_stage][dy][dx+1] == '$'){ //다음칸이 돈
                            if (map[map_stage][dy][dx+2] == '#' || map[map_stage][dy+2][dx] == '$') //다다음칸이 벽이나 돈
                                return;
                            else if (map[map_stage][dy][dx+2] == 'O'){ //다다음칸이 은행
                                map[map_stage][dy][dx] = ' ';
                                map[map_stage][dy][dx+1] = '@';
                                map[map_stage][dy][dx+2] = '$';
                                return;
                            }
                else if (map[map_stage][dy][dx+2] == ' '){ //다다음칸이 공간
                                map[map_stage][dy][dx] = ' ';
                                map[map_stage][dy][dx+1] = '@';
                                map[map_stage][dy][dx+2] = '$';
                                return;
                            }
                        }
                        return;

              case LEFT :

                  if (map[map_stage][dy][dx-1] == '#') //다음칸이 벽
                                              return;
                else if (map[map_stage][dy][dx-1] == ' '){ //다음칸이 공간
                                    map[map_stage][dy][dx] = ' ';
                                    map[map_stage][dy][dx-1] = '@';
                                        return;
                      }
                else if (map[map_stage][dy][dx-1] == 'O'){ //다음칸이 은행
                          map[map_stage][dy][dx] = ' ';
                          map[map_stage][dy][dx-1] = '@';
                                      return;
                                }
                  else if (map[map_stage][dy][dx-1] == '$'){ //다음칸이 돈
                          if (map[map_stage][dy][dx-2] == '#' || map[map_stage][dy+2][dx] == '$') //다다음칸이 벽이나 돈
                                        return;
                                    else if (map[map_stage][dy][dx-2] == 'O'){ //다다음칸이 은행
                                        map[map_stage][dy][dx] = ' ';
                                        map[map_stage][dy][dx-1] = '@';
                                        map[map_stage][dy][dx-2] = '$';
                                        return;
                                    }
                        else if (map[map_stage][dy][dx-2] == ' '){ //다다음칸이 공간
                                        map[map_stage][dy][dx] = ' ';
                                        map[map_stage][dy][dx-1] = '@';
                                        map[map_stage][dy][dx-2] = '$';
                                        return;
                                    }
                                }
                                return;
                  default :
                                break;
    }
            }
void whereis_bank(void)
{
  int c=0;
  for(int k=0;k<5;k++)
    for(int i=0; i<WIDTH; i++)
      for(int j=0; j<HEIGHT; j++)
        if(map[k][i][j]=='O'){
          bank_location_X[c]=i;
          bank_location_Y[c]=j;
          c++;
        }


  return;
}
void bank_recover(void){

  for(int k=0;k<5;k++){
    if(k==0)
      for(int c=0; c<6; c++)
      if(map[k][bank_location_X[c]][bank_location_Y[c]]==' ')
            map[k][bank_location_X[c]][bank_location_Y[c]]='O';
    if(k==1)
      for(int c=6; c<16; c++)
              if(map[k][bank_location_X[c]][bank_location_Y[c]]==' ')
                    map[k][bank_location_X[c]][bank_location_Y[c]]='O';
    if(k==2)
      for(int c=16; c<27; c++)
              if(map[k][bank_location_X[c]][bank_location_Y[c]]==' ')
                            map[k][bank_location_X[c]][bank_location_Y[c]]='O';
    if(k==3)
      for(int c=27; c<47; c++)
              if(map[k][bank_location_X[c]][bank_location_Y[c]]==' ')
                            map[k][bank_location_X[c]][bank_location_Y[c]]='O';
    if(k==4)
      for(int c=47; c<59; c++)
              if(map[k][bank_location_X[c]][bank_location_Y[c]]==' ')
                            map[k][bank_location_X[c]][bank_location_Y[c]]='O';

}
return;
}

////////////플레이어 이동함수
///////////////////////
int main(void)
{
  start();
  map_load(0);
  whereis_bank();
  while(1){
    PlayerMove();
    bank_recover();
    system("clear");
    map_load(0);
  }
  return 0;
}
