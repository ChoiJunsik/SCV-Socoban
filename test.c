#include<stdio.h>
#include<termio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#define LEFT 'h'
#define RIGHT 'l'
#define UP 'k'
#define DOWN 'j'
int X = 0; // X좌표깂
int Y = 0;  //Y좌표값
int moved = 0; 
int bank_location_X[5][20] = {0}; //은행위치 X좌표
int bank_location_Y[5][20] = {0}; //은행위치 Y좌표
char map[5][30][30]={0};    //불러온 맵
char map_now[5][30][30] = {0};  //이동후의 맵
int count_bank[5]={0};  //은행의 수
char name[10] = {0};  //플레이어 이름
unsigned int time_start = 0;  //게임/스테이지를 시작한 시간
unsigned int time_stopped = 0; //일시정지된 시간
char keyinput = 0; // 입력값

void move(int keyinput, int stage);  //키입력과 스테이지를 입력받아 움직임
void map_print(int, char);  
void map_reader();
void playermove(int, int);
void where_is_bank(void);
void cleared();
int clear_check(int);
int time_calculate();
void time_stop(void);  //일시정지에 사용, 시작후 정지까지의 시간 저장
void bank_recover(int,int);

void replay(char stage){
			for (Y=0; Y<30; Y++)
				for (X=0; X<30; X++)
					map_now[stage][Y][X] = map[stage][Y][X];
}
void map_print(int stage, char keyinput)
{
	printf("   HELLO %s \n",name);
     for (int i=0; i<30; i++)  //맵 출력
         for (int j=0; j<30; j++)
             printf("%c",map_now[stage][i][j]);
	 printf("\n(COMMAND) %c", keyinput);
}

void map_reader () // 맵 파일에서 맵을 읽어들이고 맵을 저장
{
    FILE *mapfile;
    mapfile = fopen("map", "r");
    char temp=0;
	char count_map=0;
	for (int reading_stage = 0; reading_stage<5 ; reading_stage++){
		while(1){  //읽기 무한루프
    	    fscanf(mapfile,"%c",&temp);
			if (temp == 'a'){
			   for (int i = 0; i<2 ; i++)
    	    		fscanf(mapfile,"%c",&temp); // p, \n 버림
				break; // 읽기 무한루프 빠져나감
			}
		}
			
		X=0;  //좌표 초기화
		Y=0;
		
		while(1){  //쓰기 무한루프
			fscanf(mapfile,"%c", &temp);
			if (temp == '\n'){ //공백문장을 만나면 Y축 값 +1
	            map[reading_stage][Y][X] = temp;
  		         Y++;
		         X=0;
   	        }
	        else if (temp == 'm' || temp == 'e') //m,e 를 만나면 쓰기 무한루프 빠져나감
	            break;
	        else{
	            map[reading_stage][Y][X] = temp;
	            X++;
	        }
	    }
	}	
	    fclose(mapfile);
	
		for (int reading_stage = 0; reading_stage<5; reading_stage++) //가변 맵 배열에 불러온 맵 덮어쓰기
			for (Y=0; Y<30; Y++)
				for (X=0; X<30; X++)
					map_now[reading_stage][Y][X] = map[reading_stage][Y][X];

}

void input(int stage) // 키입력
{
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
   
	switch (keyinput){
		case 'h' :
		case 'j' :
		case 'k' :
		case 'l' :
			move(keyinput, stage);
			bank_recover(keyinput, stage);	
			keyinput = 0;
			break;
		case 'u' :
			break ;
		case 'r' :
			replay(stage);
			break ;
		case 'n' :
			break ;
		case 'e' :
			break ;
		case 's' :
			break ;
		case 'f' :
			break ;
		case 'd' :
			break ;
		case 't' :
			break ;
		default :
			break;
	}
}




void bank_recover(int keyinput, int stage) //은행 복귀
{
         for(int i=0;i<count_bank[stage];i++) // 플레이어 이동으로 인해 스페이스가 된 은행을 원상복구
             if (map_now[stage][bank_location_Y[stage][i]][bank_location_X[stage][i]]== ' ')
                 map_now[stage][bank_location_Y[stage][i]][bank_location_X[stage][i]] = 'O';
		 map_now[stage][0][0] = map[stage][0][0]; //오류 해결
}

void move (int keyinput, int stage){
    for (Y=0; Y<30; Y++) // 플레이어 위치 찾기
        for(X=0; X<30; X++)
            if (map_now[stage][Y][X] == '@'){
    switch (keyinput){

        case DOWN :

            if (map_now[stage][Y+1][X] == '#') //다음칸이 벽
                return;
            else if (map_now[stage][Y+1][X] == ' ' ){ //다음칸이 공간
                map_now[stage][Y][X] = ' ';
                map_now[stage][Y+1][X] = '@';
                    return;
            }
            else if (map_now[stage][Y+1][X] == 'O'){ //다음칸이 은행
                map_now[stage][Y][X] = ' ';
                map_now[stage][Y+1][X] = '@';
                    return;
            }
            else if (map_now[stage][Y+1][X] == '$'){ //다음칸이 돈
                if (map_now[stage][Y+2][X] == '#' || map_now[stage][Y+2][X] == '$') //다다음칸이 벽이나 돈
                    return;
                else if (map_now[stage][Y+2][X] == 'O'){ //다다음칸이 은행
                    map_now[stage][Y][X] = ' ';
                    map_now[stage][Y+1][X] = '@';
                    map_now[stage][Y+2][X] = '$';
                    return;
                }
    else if (map_now[stage][Y+2][X] == ' '){ //다다음칸이 공간
                    map_now[stage][Y][X] = ' ';
                    map_now[stage][Y+1][X] = '@';
                    map_now[stage][Y+2][X] = '$';
                    return;
                }
            }
            return;

        case UP :

            if (map_now[stage][Y-1][X] == '#') //다음칸이 벽
                return;
            else if (map_now[stage][Y-1][X] == ' '){ //다음칸이 공간
                map_now[stage][Y-1][X] = '@';
                map_now[stage][Y][X] = ' ';
                    return;
            }
            else if (map_now[stage][Y-1][X] == 'O'){ //다음칸이 은행
                map_now[stage][Y-1][X] = '@';
                map_now[stage][Y][X] = ' ';
                    return;
            }
            else if (map_now[stage][Y-1][X] == '$'){ //다음칸이 돈
                if (map_now[stage][Y-2][X] == '#' || map_now[stage][Y-2][X] == '$') //다다음칸이 벽이나 돈
                    return;
                else if (map_now[stage][Y-2][X] == 'O'){ //다다음칸이 은행
                    map_now[stage][Y-2][X] = '$';
                    map_now[stage][Y-1][X] = '@';
                    map_now[stage][Y][X] = ' ';
                    return;
                }
    else if (map_now[stage][Y-2][X] == ' '){ //다다음칸이 공간
                    map_now[stage][Y-2][X] = '$';
                    map_now[stage][Y-1][X] = '@';
                    map_now[stage][Y][X] = ' ';
                    return;
                }
            }
            break;

        case LEFT :

            if (map_now[stage][Y][X-1] == '#')
                    return;
            else if (map_now[stage][Y][X-1] == ' '){
                map_now[stage][Y][X-1] = '@';
                map_now[stage][Y][X] = ' ';
              		return;
            }
            else if (map_now[stage][Y][X-1] == 'O'){
                map_now[stage][Y][X-1] = '@';
                map_now[stage][Y][X] = ' ';
                    return;
            }
 else if (map_now[stage][Y][X-1] == '$'){
                if (map_now[stage][Y][X-2] == '#' || map_now[stage][Y][X-2] == '$')
                    return;
                else if (map_now[stage][Y][X-2] == 'O'){
                    map_now[stage][Y][X-2] = '$';
                    map_now[stage][Y][X-1] = '@';
                    map_now[stage][Y][X] = ' ';
                    return;
                }
                else if (map_now[stage][Y][X-2] == ' '){
                    map_now[stage][Y][X-2] = '$';
                    map_now[stage][Y][X-1] = '@';
                    map_now[stage][Y][X] = ' ';
                    return;
                }
            }
            return;

        case RIGHT :

            if (map_now[stage][Y][X+1] == '#')
                    return;
            else if (map_now[stage][Y][X+1] == ' '){
                map_now[stage][Y][X] = ' ';
                map_now[stage][Y][X+1] = '@';
                    return;
            }
            else if (map_now[stage][Y][X+1] == 'O'){
                map_now[stage][Y][X] = ' ';
                map_now[stage][Y][X+1] = '@';
                    return;
            }
 else if (map_now[stage][Y][X+1] == '$'){
                if (map_now[stage][Y][X+2] == '#' || map_now[stage][Y][X+2] == '$')
                    return;
                else if (map_now[stage][Y][X+2] == 'O'){
                    map_now[stage][Y][X] = ' ';
                    map_now[stage][Y][X+1] = '@';
                    map_now[stage][Y][X+2] = '$';
                    return;
                }
                else if (map_now[stage][Y][X+2] == ' '){
                    map_now[stage][Y][X] = ' ';
                    map_now[stage][Y][X+1] = '@';
                    map_now[stage][Y][X+2] = '$';
                    return;
                }
            }
            return;
        default :
            break;
    }
			
			}
}

void where_is_bank(void) //맵의 은행 위치의 좌표를 저장
{
for (int stage=0; stage<5; stage++){
	int count = 0;
	for(Y = 0; Y<30; Y++) 
	    for (X = 0; X<30; X++)
	        if (map_now[stage][Y][X] == 'O'){
	            bank_location_X[stage][count] = X;
	            bank_location_Y[stage][count] = Y;
	            count_bank[stage]++;
				count++;
	        }
    }
}

void cleared(void) //스테이지 클리어 시
{
	system("clear");
	printf("축하합니다 클리어입니다\n");
	sleep(3);
	system("clear");
}

int cleared_all(void) //마지막 스테이지 클리어 시
{
	system("clear");
	printf("모든 스테이지를 클리어 하셨습니다!\n");
	printf("%s 님의 기록을 랭킹에 저장했습니다!\n");
	sleep(5);
	printf("See You Again!");
	exit(0); //게임 종료
}

int clear_check(int stage)
{
	int success=0;
	for (int count = 0; count<20; count++){
	   if (map_now[stage][bank_location_Y[stage][count]][bank_location_X[stage][count]] == '$'){
			success++;   //은행위치에 돈이 있으면 성공 +1
			if (count_bank[stage] == success){  // 은행 갯수와 성공수가 같으면 클리어
					stage++;
					if (stage < 6){ //스테이지 4까지 완료 시
						cleared();
						return stage;
					}
					else if (stage == 6) //스테이지 5 완료 시
						cleared_all();
			}
	   }
	}
	return stage;

}


void time_stop(void)  //일시정지에 사용, 시작후 정지까지의 시간 저장
{
	time_stopped += time(NULL) - time_start; //로스타임을 계산해줌
}


int time_calculate(void) //흐른 시간 측정
{
	unsigned int time_passed;
	time_passed = time_stopped + time(NULL) - time_start; //로스타임, 흐른시간을 더해줌
	return time_passed;
}
			
void yourname(void)
{
  printf("input name : ");
  scanf("%s",&name);
  system("clear");
  printf("Hello, %s\n",name);
  sleep(1);
  system("clear");
}

int main(void)
{
	int stage=0;
	system("clear");
	yourname();
    map_reader(); 
    where_is_bank();
	time_start = time(NULL); //시작 시간 저장
	while(1){ //무한루프
		input(stage);
     	system("clear");
		stage = clear_check(stage); //클리어했다면 stage+1, 아니면 변하지 않은 값을 저장
		map_print(stage, keyinput); //맵 출력
	}
	return 0;
}

