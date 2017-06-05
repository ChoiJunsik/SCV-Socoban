#include<stdio.h>
#include<termio.h>
#include<unistd.h>
#include<stdlib.h>
#define LEFT 104
#define RIGHT 108
#define UP 107
#define DOWN 106
int X = 0;
int Y = 0;
int moved = 0;
int keyinput = 0;
char player = 0;
int bank_location_X[20] = {0};
int bank_location_Y[20] = {0};
char map[30][30]={0};
char map_now[30][30] = {0};

void move(int);
void delay();
void map_print();
void map_reader(char);
int input();
void playermove(int);
void where_is_bank();

void delay() //키 중복입력 방지, 화면 클리어
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

void map_reader (char stage) // 맵 파일에서 맵을 읽어들이고, 맵을 1회 출력
{
    FILE *mapfile;
    mapfile = fopen("map", "r");
    int temp=0;
	char count_map='0';
    while(1){ //원하는 스테이지 찾음
        fscanf(mapfile,"%c",&temp);
		if (temp == 'm' || temp == 'e')
			count_map++;
        if (count_map == stage)
            break;
    }
	for (int i=0; i<3; i++)
    temp = getc(mapfile); // 레벨 뒤의 a, p, \n 없앰

    while(1){ //지형을 배열에 입력
        fscanf(mapfile,"%c",&temp);
        if (temp == '\n'){ //공백문장을 만나면 Y축 값 +1
            map[Y][X] = temp;
            Y++;
            X=0;
        }
		else if (temp == 'm' || temp == 'e')
			count_map++;
        else if (count_map == stage+1) //다음레벨 파일을 만나면 읽기종료
            break;
        else{
            map[Y][X] = temp;
            X++;
        }
    }

    for (int i=0; i<30; i++)  //맵 출력
       for (int j=0; j<30; j++)
           printf("%c",map[i][j]);

    fclose(mapfile);
}

int input(void) // 키입력
{
    int keyinput;
    struct termios buf;
    struct termios save;
   tcgetattr(0, &save);
   buf = save;
   buf.c_lflag&=~(ICANON|ECHO);
   buf.c_cc[VMIN] = 1;
   buf.c_cc[VTIME] = 0;
   tcsetattr(0, TCSAFLUSH, &buf);
   keyinput = getchar();
   tcsetattr(0,TCSAFLUSH,&save);
   return keyinput;
}

void playermove(int keyinput) //플레이어 이동, 은행 복귀
{
     if (keyinput == LEFT || keyinput == RIGHT || keyinput == UP || keyinput == DOWN){
         move(keyinput);
         for(int i=0;i<20;i++) // 플레이어 이동으로 인해 스페이스가 된 은행을 원상복구
             if (map_now[bank_location_Y[i]][bank_location_X[i]]== ' ')
                 map_now[bank_location_Y[i]][bank_location_X[i]] = 'O';
		 map_now[0][0] = map[0][0]; //오류 해결
    }
}

void move (int keyinput){
    for (Y=0; Y<30; Y++) // 플레이어 위치 찾기
        for(X=0; X<30; X++)
            if (map_now[Y][X] == '@'){
    switch (keyinput){

        case DOWN :

            if (map_now[Y+1][X] == '#') //다음칸이 벽
                return;
            else if (map_now[Y+1][X] == ' '){ //다음칸이 공간
                map_now[Y][X] = ' ';
                map_now[Y+1][X] = '@';
                    return;
            }
            else if (map_now[Y+1][X] == 'O'){ //다음칸이 은행
                map_now[Y][X] = ' ';
                map_now[Y+1][X] = '@';
                    return;
            }
            else if (map_now[Y+1][X] == '$'){ //다음칸이 돈
                if (map_now[Y+2][X] == '#' || map_now[Y+2][X] == '$') //다다음칸이 벽이나 돈
                    return;
                else if (map_now[Y+2][X] == 'O'){ //다다음칸이 은행
                    map_now[Y][X] = ' ';
                    map_now[Y+1][X] = '@';
                    map_now[Y+2][X] = '$';
                    return;
                }
    else if (map_now[Y+2][X] == ' '){ //다다음칸이 공간
                    map_now[Y][X] = ' ';
                    map_now[Y+1][X] = '@';
                    map_now[Y+2][X] = '$';
                    return;
                }
            }
            return;

        case UP :

            if (map_now[Y-1][X] == '#') //다음칸이 벽
                return;
            else if (map_now[Y-1][X] == ' '){ //다음칸이 공간
                map_now[Y-1][X] = '@';
                map_now[Y][X] = ' ';
                    return;
            }
            else if (map_now[Y-1][X] == 'O'){ //다음칸이 은행
                map_now[Y-1][X] = '@';
                map_now[Y][X] = ' ';
                    return;
            }
            else if (map_now[Y-1][X] == '$'){ //다음칸이 돈
                if (map_now[Y-2][X] == '#' || map_now[Y-2][X] == '$') //다다음칸이 벽이나 돈
                    return;
                else if (map_now[Y-2][X] == 'O'){ //다다음칸이 은행
                    map_now[Y-2][X] = '$';
                    map_now[Y-1][X] = '@';
                    map_now[Y][X] = ' ';
                    return;
                }
    else if (map_now[Y-2][X] == ' '){ //다다음칸이 공간
                    map_now[Y-2][X] = '$';
                    map_now[Y-1][X] = '@';
                    map_now[Y][X] = ' ';
                    return;
                }
            }
            break;

        case LEFT :

            if (map_now[Y][X-1] == '#')
                    return;
            else if (map_now[Y][X-1] == ' '){
                map_now[Y][X-1] = '@';
                map_now[Y][X] = ' ';
              		return;
            }
            else if (map_now[Y][X-1] == 'O'){
                map_now[Y][X-1] = '@';
                map_now[Y][X] = ' ';
                    return;
            }
 else if (map_now[Y][X-1] == '$'){
                if (map_now[Y][X-2] == '#' || map_now[Y][X-2] == '$')
                    return;
                else if (map_now[Y][X-2] == 'O'){
                    map_now[Y][X-2] = '$';
                    map_now[Y][X-1] = '@';
                    map_now[Y][X] = ' ';
                    return;
                }
                else if (map_now[Y][X-2] == ' '){
                    map_now[Y][X-2] = '$';
                    map_now[Y][X-1] = '@';
                    map_now[Y][X] = ' ';
                    return;
                }
            }
            return;

        case RIGHT :

            if (map_now[Y][X+1] == '#')
                    return;
            else if (map_now[Y][X+1] == ' '){
                map_now[Y][X] = ' ';
                map_now[Y][X+1] = '@';
                    return;
            }
            else if (map_now[Y][X+1] == 'O'){
                map_now[Y][X] = ' ';
                map_now[Y][X+1] = '@';
                    return;
            }
 else if (map_now[Y][X+1] == '$'){
                if (map_now[Y][X+2] == '#' || map_now[Y][X+2] == '$')
                    return;
                else if (map_now[Y][X+2] == 'O'){
                    map_now[Y][X] = ' ';
                    map_now[Y][X+1] = '@';
                    map_now[Y][X+2] = '$';
                    return;
                }
                else if (map_now[Y][X+2] == ' '){
                    map_now[Y][X] = ' ';
                    map_now[Y][X+1] = '@';
                    map_now[Y][X+2] = '$';
                    return;
                }
            }
            return;
        default :
            break;
    }
			}
}
void where_is_bank(void) //맵의 은행 위치의 좌표를 저장, 불러들인 맵 좌표를 가변 맵 배열로 복사 
{
int count = 0;
for(Y = 0; Y<30; Y++) 
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
	delay();
    printf("Input stage :");
    scanf("%c",&stage);
    map_reader(stage); 
    where_is_bank();
	while(1){ //무한루프
		playermove(input());
		delay();
		map_print();
	}
	return 0;
}

