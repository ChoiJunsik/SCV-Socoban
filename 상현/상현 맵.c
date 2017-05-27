#include<stdio.h>
#include<termio.h>
#include<unistd.h>
#include<stdlib.h>
#define LEFT 104
#define RIGHT 108
#define DOWN 107
#define UP 106
int X = 0;
int Y = 0;
char input = 0;
char player = 0;
int bank_location_X[20] = {0};
int bank_location_Y[20] = {0};
char map[30][30]={0};
char map_now[30][30] = {0};
void delay()
{
    usleep(5000);
    system("clear");
}
void map_print()
{
            for (int i=0; i<30; i++)  //맵 출력
                 for (int j=0; j<30; j++)
                     printf("%c",map_now[i][j]);
}

void map_reader (char stage)
{
    FILE *mapfile;
    mapfile = fopen("map", "r");
    int temp;
    while(1){ //원하는 스테이지 찾음
        fscanf(mapfile,"%c",&temp);
        if (temp == stage)
            break;
    }
    temp = getc(mapfile); // 레벨 뒤의 \n 없앰

    while(1){ //지형을 배열에 입력
        fscanf(mapfile,"%c",&temp);
        if (temp == '\n'){ //공백문장을 만나면 Y축 값 +1
            map[Y][X] = temp;
            Y++;
            X=0;
        }
        else if (temp == stage+1) //다음레벨 파일을 만나면 읽기종료
            break;
        else{
            map[Y][X] = temp;
            X++;
        }
    }

    for (int i=0; i<30; i++)  //맵 출력
       for (int j=0; j<30; j++)
           printf("%c",map_now[i][j]);

    fclose(mapfile);
}

int getch(void)
{
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
   tcsetattr(0,TCSAFLUSH,&save);
   return ch;
}

void move (int input){
    char player;
    for (Y=0; Y<30; Y++) // 플레이어 위치 찾기
        for(X=0; X<30; X++)
            if (map_now[Y][X] == '@'){
    switch (input){
        case UP :
            if (map_now[Y+1][X] == '#') //다음칸이 벽
                break;
            else if (map_now[Y+1][X] == ' '){ //다음칸이 공간
                map_now[Y+1][X] = '@';
                map_now[Y][X] = ' ';
                    break;
            }
            else if (map_now[Y+1][X] == 'O'){ //다음칸이 은행
                map_now[Y+1][X] = map_now[Y][X];
                map_now[Y][X] = ' ';
                    break;
            }
            else if (map_now[Y+1][X] == '$'){ //다음칸이 돈
                if (map_now[Y+2][X] == '#' || map_now[Y+2][X] == '$') //다다음칸이 벽이나 돈
                    break;
                else if (map_now[Y+2][X] == 'O'){ //다다음칸이 은행
                    map_now[Y+2][X] = '$';
                    map_now[Y+1][X] = '@';
                    map_now[Y][X] = ' ';
                    break;
                }
    else if (map_now[Y+2][X] == ' '){ //다다음칸이 공간
                    map_now[Y+2][X] = '$';
                    map_now[Y+1][X] = '@';
                    map_now[Y][X] = ' ';
                    break;
                }
            }
            break;
        case DOWN :
            if (map_now[Y-1][X] == '#')
                break;
            else if (map_now[Y-1][X] == ' '){
                map_now[Y-1][X] = '@';
                map_now[Y][X] = ' ';
                break;
            }
            else if (map_now[Y-1][X] == 'O'){
                map_now[Y-1][X] = '@';
                map_now[Y][X] = ' ';
                break;
            }
            else if (map_now[Y-1][X] == '$'){
                if (map_now[Y-2][X] == '#' || map_now[Y-2][X] == '$')
                    break;
                else if (map_now[Y-2][X] == 'O'){
                    map_now[Y-2][X] = '$';
                    map_now[Y-1][X] = '@';
                    map_now[Y][X] = ' ';
                    break;
                }
                else if (map_now[Y-2][X] == ' '){
                    map_now[Y-2][X] = '$';
                    map_now[Y-1][X] = '@';
                    map_now[Y][X] = ' ';
                    break;
                }
            }
            break;
        case LEFT :
            if (map_now[Y][X-1] == '#')
                    break;
            else if (map_now[Y][X-1] == ' '){
                map_now[Y][X-1] = '@';
                map_now[Y][X] = ' ';
                    break;
            }
            else if (map_now[Y][X-1] == 'O'){
                map_now[Y][X-1] = map_now[Y][X];
                map_now[Y][X] = ' ';
                    break;
            }
 else if (map_now[Y][X-1] == '$'){
                if (map_now[Y][X-2] == '#' || map_now[Y][X-2] == '$')
                    break;
                else if (map_now[Y][X-2] == 'O'){
                    map_now[Y][X-2] = '$';
                    map_now[Y][X-1] = '@';
                    map_now[Y][X] = ' ';
                    break;
                }
                else if (map_now[Y][X-2] == ' '){
                    map_now[Y][X-2] = '$';
                    map_now[Y][X-1] = '@';
                    map_now[Y][X] = ' ';
                    break;
                }
            }
            break;
        case RIGHT :
            if (map_now[Y][X+1] == '#')
                    break;
            else if (map_now[Y][X+1] == ' '){
                map_now[Y][X+1] = '@';
                map_now[Y][X] = ' ';
                    break;
            }
            else if (map_now[Y][X+1] == 'O'){
                map_now[Y][X+1] = map_now[Y][X];
                map_now[Y][X] = ' ';
                    break;
            }
            else if (map_now[Y][X+1] == '$'){
                if (map_now[Y][X+2] == '#' || map_now[Y][X+2] == '$')
                    break;
                else if (map_now[Y][X+2] == 'O'){
                    map_now[Y][X+2] = '$';
                    map_now[Y][X+1] = '@';
                    map_now[Y][X] = ' ';
                    break;
                }
                else if (map_now[Y][X+2] == ' '){
                    map_now[Y][X+2] = '$';
                    map_now[Y][X+1] = '@';
                    map_now[Y][X] = ' ';
                    break;
                }
            }
            break;
        default :
            break;
    }
            }
}
void where_is_bank(void)
{
int count = 0;
for(Y = 0; Y<30; Y++) // 현재맵을 불러온 맵에 넣어주고, 0위치를 저장해둠
    for (X = 0; X<30; X++){
        map_now[Y][X]=map[Y][X];
        if (map_now[Y][X] == 'O'){
            bank_location_X[count] = X;
            bank_location_Y[count] = Y;
            count++;
        }
    }
}

int main()
{
    char stage=0;
    printf("Input stage\n");
    scanf("%c",&stage);
    system("clear");
    map_reader(stage); //맵파일에서 맵을 읽어들임
    where_is_bank();
    while(1){
        input = getch();
        if (input == LEFT || input == RIGHT || input == UP || input == DOWN){
            move(input);
            for(int i=0;i<20;i++)
                if (map_now[bank_location_Y[i]][bank_location_X[i]]== ' ')
                    map_now[bank_location_Y[i]][bank_location_X[i]] = 'O';

            delay();
            map_print();
        }
    }
}

