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
            for (int i=0; i<30; i++)  //�� ���
                 for (int j=0; j<30; j++)
                     printf("%c",map_now[i][j]);
}

void map_reader (char stage)
{
    FILE *mapfile;
    mapfile = fopen("map", "r");
    int temp;
    while(1){ //���ϴ� �������� ã��
        fscanf(mapfile,"%c",&temp);
        if (temp == stage)
            break;
    }
    temp = getc(mapfile); // ���� ���� \n ����

    while(1){ //������ �迭�� �Է�
        fscanf(mapfile,"%c",&temp);
        if (temp == '\n'){ //���鹮���� ������ Y�� �� +1
            map[Y][X] = temp;
            Y++;
            X=0;
        }
        else if (temp == stage+1) //�������� ������ ������ �б�����
            break;
        else{
            map[Y][X] = temp;
            X++;
        }
    }

    for (int i=0; i<30; i++)  //�� ���
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
    for (Y=0; Y<30; Y++) // �÷��̾� ��ġ ã��
        for(X=0; X<30; X++)
            if (map_now[Y][X] == '@'){
    switch (input){
        case UP :
            if (map_now[Y+1][X] == '#') //����ĭ�� ��
                break;
            else if (map_now[Y+1][X] == ' '){ //����ĭ�� ����
                map_now[Y+1][X] = '@';
                map_now[Y][X] = ' ';
                    break;
            }
            else if (map_now[Y+1][X] == 'O'){ //����ĭ�� ����
                map_now[Y+1][X] = map_now[Y][X];
                map_now[Y][X] = ' ';
                    break;
            }
            else if (map_now[Y+1][X] == '$'){ //����ĭ�� ��
                if (map_now[Y+2][X] == '#' || map_now[Y+2][X] == '$') //�ٴ���ĭ�� ���̳� ��
                    break;
                else if (map_now[Y+2][X] == 'O'){ //�ٴ���ĭ�� ����
                    map_now[Y+2][X] = '$';
                    map_now[Y+1][X] = '@';
                    map_now[Y][X] = ' ';
                    break;
                }
    else if (map_now[Y+2][X] == ' '){ //�ٴ���ĭ�� ����
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
for(Y = 0; Y<30; Y++) // ������� �ҷ��� �ʿ� �־��ְ�, 0��ġ�� �����ص�
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
    map_reader(stage); //�����Ͽ��� ���� �о����
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

