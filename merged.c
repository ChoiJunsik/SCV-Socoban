#include<stdio.h>
#include<termio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#define LEFT 'h'
#define RIGHT 'l'
#define UP 'k'
#define DOWN 'j' // 이동키 값
#define NOT_MOVED 3 // undo실행시 전에 움직이지 않았음을 알리는 값
#define MOVED_WITH_MONEY 2//undo실행시 전에 돈과 움직였음을 알리는 값
#define JUST_MOVED 1//undo실행시 전에 혼자 움징였음을 알리는 값

//****************************전역변수**********************************
char check_num[6]={0};//undo사용을 위해 필요한 전에 움직일떄의 상황
char undo[6]={0};//undo사용을 위해 필요한 전의 이동 명령어
int X = 0; // X좌표깂
int Y = 0;  //Y좌표값
int bank_location_X[5][20] = {0}; //O위치 X좌표
int bank_location_Y[5][20] = {0}; //O위치 Y좌표
char map[5][30][30]={0};    //불러온 맵
char map_now[5][30][30] = {0};  //이동후의 맵
int count_bank[5]={0};  //O의 수
char name[10] = {0};  //플레이어 이름
unsigned int time_start = 0;  //게임/스테이지를 시작한 시간
unsigned int time_stopped = 0; //일시정지된 시간
char keyinput = 0; // 입력값
int stage=0;//현재 스테이지
int new_stage=0; // new함수 사용여부
int undo_count = 0;


//***************************함수원형***********************************

char move(int keyinput, int stage);  //키입력과 스테이지를 입력받아 움직임

void map_print(int, char);//맵 출력
void map_reader();//맵 읽기
void yourname(void); // 이름 입력함수


//클리어
void cleared();//클리어 한후 출력 함수
int clear_check(int);//클리어 했는지를 체크하는 함수
int cleared_all(void); // 모두 클리어할시 출력후 프로그램 종료 함수

int time_stop(void);  //일시정지에 사용, 시작후 정지까지의 시간 저장

void bank_recover(int,int);//' '로 바뀐 O를 다시 O 로 바꿔주는 함수
void where_is_bank(void);

void save_game(int);//게임 저장
void load_game(void);//게임 불러오기

void undo_input(void);//언두에 필요한 이동키와 상황을 배열에 저장
void undo_bbagi(void);//이미 undo한 이동키와 상황을 빼줌
void undo_fuc(char ,char);//undo주요함수

void replay(char stage);


void ranking_print(void);
int ranking_reset(int);

void getch();
void input(int stage);

void new(void);
//***********************new함수*********************(최준식)
void new(void)
{
	undo_count = 0;
	for(int i=0;i<6;i++){
  check_num[i]=0;
  undo[i]=0;
  }

  for (int reading_stage = 0; reading_stage<5; reading_stage++) //가변 맵 배열에 불러온 맵 덮어쓰기
    for (Y=0; Y<30; Y++)
      for (X=0; X<30; X++)
        map_now[reading_stage][Y][X] = map[reading_stage][Y][X];
  system("clear");

  return;
}
//**************************help함수********************(최준식)
void help(void)
{
	system("clear");
  printf("- h(왼쪽), j(아래), k(위), l(오른쪽) : 창고지기 조정\n- u : 되돌리기, 최대 5번\n- r : 현재 맵을 처음부터 다시 시작(게임시간 유지)\n- n : 첫 번째 맵부터 다시 시작(현재까지의 시간 기록 삭제)\n- e : 게임 종료.\n- s : 저장\n- f : 게임로드\n- d : 명령 내용 출력\n- t : 전체 순위. t+숫자 : 해당 맵의 순위\n- d : 도움말 종료\n");
	while(1){
	getch();
  if (keyinput=='d')
    return;
	}
}
//**************게임을 실행하기전 준비에 필요한 함수**************(모두가 기여)
void map_print(int stage, char keyinput){
	printf("   HELLO %s \n",name);
     for (int i=0; i<30; i++)  //맵 출력
         for (int j=0; j<30; j++)
             printf("%c",map_now[stage][i][j]);
	 printf("\n(COMMAND) %c", keyinput);
}
void map_reader(){ // 맵 파일에서 맵을 읽어들이고 맵을 저장
		int money=0;
		int o=0;
    FILE *mapfile;
    mapfile = fopen("map", "r");
		if (mapfile == NULL){
			printf("오류 : map 파일을 열 수 없습니다.\n");
			exit(1);
   }
    char temp=0;
		char count_map=0;
		for (int reading_stage = 0; reading_stage<5 ; reading_stage++)
		{
			money=0; //스테이지 넘어갈때 오류 체크하기 위한 개수 초기화
			o=0;
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
	        else {
	            map[reading_stage][Y][X] = temp;
	            X++;
	        }
					 if(temp=='O')	//오류검사(최준식,우호진,박세준,이상현)
						o++;				 //오류검사(최준식,우호진,박세준,이상현)
					else if(temp=='$')//오류검사(최준식,우호진,박세준,이상현)
						money++;       //오류검사(최준식,우호진,박세준,이상현)
	    }

									if (o!=money){   //오류검사(최준식,우호진,박세준,이상현)
										printf("ERROR\n");//오류검사(최준식,우호진,박세준,이상현)
										fclose(mapfile);//오류검사(최준식,우호진,박세준,이상현)
										exit(1);//오류검사(최준식,우호진,박세준,이상현)
									}
	}
	    fclose(mapfile);

		for (int reading_stage = 0; reading_stage<5; reading_stage++) //가변 맵 배열에 불러온 맵 덮어쓰기
			for (Y=0; Y<30; Y++)
				for (X=0; X<30; X++)
					map_now[reading_stage][Y][X] = map[reading_stage][Y][X];

}
void yourname(void){
  printf("input name : ");
  scanf("%s",&name);
  system("clear");
  printf("Hello, %s\n",name);
  sleep(1);
  system("clear");
}

//**************************이동함수********************************(기여자:이상현)
char move (int keyinput, int stage){
    for (Y=0; Y<30; Y++) // 플레이어 위치 찾기
        for(X=0; X<30; X++)
            if (map_now[stage][Y][X] == '@'){
    switch (keyinput){

        case DOWN :

            if (map_now[stage][Y+1][X] == '#') //다음칸이 벽
                return NOT_MOVED;//움직이지 않았음을 알려줌
            else if (map_now[stage][Y+1][X] == ' ' ){ //다음칸이 공간
                map_now[stage][Y][X] = ' ';
                map_now[stage][Y+1][X] = '@';
                    return JUST_MOVED;//혼자 움직였음울 알려줌
            }
            else if (map_now[stage][Y+1][X] == 'O'){ //다음칸이 은행
                map_now[stage][Y][X] = ' ';
                map_now[stage][Y+1][X] = '@';
                    return JUST_MOVED;
            }
            else if (map_now[stage][Y+1][X] == '$'){ //다음칸이 돈
                if (map_now[stage][Y+2][X] == '#' || map_now[stage][Y+2][X] == '$') //다다음칸이 벽이나 돈
                    return NOT_MOVED;
                else if (map_now[stage][Y+2][X] == 'O'){ //다다음칸이 은행
                    map_now[stage][Y][X] = ' ';
                    map_now[stage][Y+1][X] = '@';
                    map_now[stage][Y+2][X] = '$';
                    return MOVED_WITH_MONEY;//돈과 움직였음을 알려줌
                }
    else if (map_now[stage][Y+2][X] == ' '){ //다다음칸이 공간
                    map_now[stage][Y][X] = ' ';
                    map_now[stage][Y+1][X] = '@';
                    map_now[stage][Y+2][X] = '$';
                    return MOVED_WITH_MONEY;
                }

	    }
	    break;

        case UP :

            if (map_now[stage][Y-1][X] == '#') //다음칸이 벽
                return NOT_MOVED;
            else if (map_now[stage][Y-1][X] == ' '){ //다음칸이 공간
                map_now[stage][Y-1][X] = '@';
                map_now[stage][Y][X] = ' ';
                    return JUST_MOVED;
            }
            else if (map_now[stage][Y-1][X] == 'O'){ //다음칸이 은행
                map_now[stage][Y-1][X] = '@';
                map_now[stage][Y][X] = ' ';
                    return JUST_MOVED;
            }
            else if (map_now[stage][Y-1][X] == '$'){ //다음칸이 돈
                if (map_now[stage][Y-2][X] == '#' || map_now[stage][Y-2][X] == '$') //다다음칸이 벽이나 돈
                    return NOT_MOVED;
                else if (map_now[stage][Y-2][X] == 'O'){ //다다음칸이 은행
                    map_now[stage][Y-2][X] = '$';
                    map_now[stage][Y-1][X] = '@';
                    map_now[stage][Y][X] = ' ';
                    return MOVED_WITH_MONEY;
                }
    else if (map_now[stage][Y-2][X] == ' '){ //다다음칸이 공간
                    map_now[stage][Y-2][X] = '$';
                    map_now[stage][Y-1][X] = '@';
                    map_now[stage][Y][X] = ' ';
                    return MOVED_WITH_MONEY;
                }
            }
            break;

        case LEFT :

            if (map_now[stage][Y][X-1] == '#')
                    return NOT_MOVED;
            else if (map_now[stage][Y][X-1] == ' '){
                map_now[stage][Y][X-1] = '@';
                map_now[stage][Y][X] = ' ';
              		return JUST_MOVED;
            }
            else if (map_now[stage][Y][X-1] == 'O'){
                map_now[stage][Y][X-1] = '@';
                map_now[stage][Y][X] = ' ';
                    return JUST_MOVED;
            }
 else if (map_now[stage][Y][X-1] == '$'){
                if (map_now[stage][Y][X-2] == '#' || map_now[stage][Y][X-2] == '$')
                    return NOT_MOVED;
                else if (map_now[stage][Y][X-2] == 'O'){
                    map_now[stage][Y][X-2] = '$';
                    map_now[stage][Y][X-1] = '@';
                    map_now[stage][Y][X] = ' ';
                    return MOVED_WITH_MONEY;
                }
                else if (map_now[stage][Y][X-2] == ' '){
                    map_now[stage][Y][X-2] = '$';
                    map_now[stage][Y][X-1] = '@';
                    map_now[stage][Y][X] = ' ';
                    return MOVED_WITH_MONEY;
                }
            }
            break;

        case RIGHT :

            if (map_now[stage][Y][X+1] == '#')
                    return NOT_MOVED;
            else if (map_now[stage][Y][X+1] == ' '){
                map_now[stage][Y][X] = ' ';
                map_now[stage][Y][X+1] = '@';
                    return JUST_MOVED;
            }
            else if (map_now[stage][Y][X+1] == 'O'){
                map_now[stage][Y][X] = ' ';
                map_now[stage][Y][X+1] = '@';
                    return JUST_MOVED;
            }
 else if (map_now[stage][Y][X+1] == '$'){
                if (map_now[stage][Y][X+2] == '#' || map_now[stage][Y][X+2] == '$')
                    return NOT_MOVED;
                else if (map_now[stage][Y][X+2] == 'O'){
                    map_now[stage][Y][X] = ' ';
                    map_now[stage][Y][X+1] = '@';
                    map_now[stage][Y][X+2] = '$';
                    return MOVED_WITH_MONEY;
                }
                else if (map_now[stage][Y][X+2] == ' '){
                    map_now[stage][Y][X] = ' ';
                    map_now[stage][Y][X+1] = '@';
                    map_now[stage][Y][X+2] = '$';
                    return MOVED_WITH_MONEY;
                }
            }
            break;
        default :
            break;
    }

			}
}

//*******************O(돈의 도착 장소)와 관련된 함수******************(기여자:이상현)
void bank_recover(int keyinput, int stage) {
         for(int i=0;i<count_bank[stage];i++) // 플레이어 이동으로 인해 스페이스가 된 은행을 원상복구
             if (map_now[stage][bank_location_Y[stage][i]][bank_location_X[stage][i]]== ' ')
                 map_now[stage][bank_location_Y[stage][i]][bank_location_X[stage][i]] = 'O';
		 map_now[stage][0][0] = map[stage][0][0]; //오류 해결
}
void where_is_bank(void){
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
//*********************클리어관련함수**********************(기여자:이상현)
void cleared(void){//스테이지 클리어 시
	ranking_reset(stage);
	system("clear");
	printf("축하합니다 클리어입니다\n");
	sleep(3);
	system("clear");
	for(int i=0;i<=6;i++)
		check_num[i]=0;
}
int cleared_all(void){ //마지막 스테이지 클리어 시

	system("clear");
	printf("모든 스테이지를 클리어 하셨습니다!\n");
	printf("%s 님의 기록을 랭킹에 저장했습니다!\n");
	sleep(5);
	printf("See You Again!");
	exit(0); //게임 종료
}
int clear_check(int stage){
	int success=0;
	for (int count = 0; count<20; count++){
	   if (map_now[stage][bank_location_Y[stage][count]][bank_location_X[stage][count]] == '$'){
			success++;   //은행위치에 돈이 있으면 성공 +1
			if (count_bank[stage] == success){  // 은행 갯수와 성공수가 같으면 클리어
					stage++;
					if (stage < 6){ //스테이지 4까지 완료 시
						cleared();
						time_start = time(NULL);
						return stage;
					}
					else if (stage == 6) //스테이지 5 완료 시
						cleared_all();
			}
	   }
	}
	if (new_stage != 0)
		stage = 0;
	return stage;

}

//**********************시간 함수*****************************(기여자:이상현)
int time_stop(void){//일시정지에 사용, 시작후 정지까지의 시간 저장
	time_stopped += time(NULL) - time_start; //로스타임을 계산해줌
	return time_stopped;
}


//***********************키입력을 받는 함수***********************(기여자:박세준,이상현)
void getch(){
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
}
void input(int stage) {
	getch();
	switch (keyinput){
		case 'h' :
		case 'j' :
		case 'k' :
		case 'l' :
			undo_input();//입력받은 이동 명령어와 그 움직임으로 인해
									 // 플레이어가 이동했는지,돈과함께이동했는지,안이동했는지를 배열에 저장함
			check_num[5]=move(keyinput, stage);

			bank_recover(keyinput, stage);
			keyinput = 0;
			break;
		case 'u' :
			undo_fuc(undo[5],check_num[5]);
			undo_bbagi();//한번 언두한 이동 명령어와 상황을 없애준다
			bank_recover(keyinput, stage);
			break;

		case 'r' :
			replay(stage);
			break ;
		case 'n' :
			new();
			stage=0;
			time_start = time(NULL);
			new_stage++;
			break ;
		case 'e' :
			save_game(stage);
			system("clear");
			printf("SEE YOU %s....\n\n", name);
			printf("\n(COMMAND) e");
			printf("\n");
			sleep(3);
			exit(0);
			break ;
		case 's' :
			save_game(stage);
			break ;
		case 'f' :
			load_game();
			break ;
		case 'd' :
			help();
			break ;
		case 't' :
			ranking_print();
			time_start = time(NULL);
			break ;
		default :
			break;
	}
}
//********************랭킹관련함수******************(우호진)
void ranking_print(void){

	FILE *rank;
	rank = fopen("ranking", "r");
	if (rank == NULL){
		printf("랭킹파일 에러.\n");
		}
	int record[5][6];
	int stage_amin;
	char name_amin[5][6][10] = {0};
	time_stop();
	for (int k = 0; k < 5; k += 1){
		fscanf(rank, "===%d===\n", &stage_amin);
		for (int n = 0; n < 5; n += 1)
			fscanf(rank, "%s  -  %d\n", name_amin[stage_amin][n], &record[stage_amin][n]);
		}
	system("clear");
	printf("맵 번호별로 보기 : 1, 2, 3, 4, 5 \n t : 종료\n");
	for (int k = 0; k < 5; k += 1){
		printf("map %d\n", k + 1);
		for (int n = 0; n < 5; n += 1)
			printf("%s    %d:%d\n", name_amin[k][n], record[k][n] / 60, record[k][n] % 60);
		}
		printf("(command)");
	while(1){

		getch();

		if (keyinput == 't')
			return;
		if (keyinput == '1'){
			system("clear");
			printf("map 1\n");
			for (int n = 0; n < 5; n += 1)
				printf("%s    %d:%d\n", name_amin[0][n], record[0][n] / 60, record[0][n] % 60);
		}
		if (keyinput == '2'){
			system("clear");
			printf("map 2\n");
			for (int n = 0; n < 5; n += 1)
				printf("%s    %d:%d\n", name_amin[1][n], record[1][n] / 60, record[1][n] % 60);
		}
		if (keyinput == '3'){
			system("clear");
			printf("map 3\n");
			for (int n = 0; n < 5; n += 1)
				printf("%s    %d:%d\n", name_amin[2][n], record[2][n] / 60, record[2][n] % 60);
		}
		if (keyinput == '4'){
			system("clear");
			printf("map 4\n");
			for (int n = 0; n < 5; n += 1)
				printf("%s    %d:%d\n", name_amin[3][n], record[3][n] / 60, record[3][n] % 60);
		}
		if (keyinput == '5'){
			system("clear");
			printf("map 5\n");
			for (int n = 0; n < 5; n += 1)
				printf("%s    %d:%d\n", name_amin[4][n], record[4][n] / 60, record[4][n] % 60);
		}
		switch(keyinput){
			case '1' :
			case '2' :
			case '3' :
			case '4' :
			case '5' :
				printf("(command) t %c",keyinput);
				break;
			default :
				break;
		}
	}
}
int ranking_reset(int stage){
	FILE *rank;
	rank = fopen("ranking", "rt");
	if (rank == NULL){
		printf("랭킹파일 에러.\n");
		}
	time_stop();
	int gotrash;
	int trashforname[10] = {0};
	int record[5][6];
	int stage_amin;
	char name_amin[5][6][10] = {0};
	for (int k = 0; k < 5; k += 1){
		fscanf(rank, "===%d===\n", &stage_amin);
		for (int n = 0; n < 5; n += 1)
			fscanf(rank, "%s  -  %d\n", name_amin[stage_amin][n], &record[stage_amin][n]);
	}
	for (int nm = 0; nm < 10; nm += 1){
		name_amin[stage][5][nm] = name[nm];
	}
	record[stage][5] = time_stopped;

	fclose(rank);
	rank = fopen("ranking", "wt");
	//정렬할거야 ><
	for (int outplay = 0; outplay < 5; outplay += 1){
		for (int inplay = 0; inplay < 5 - outplay; inplay += 1){
			if (record[stage][inplay] > record[stage][inplay + 1]){
				gotrash = record[stage][inplay];
				record[stage][inplay] = record[stage][inplay + 1];
				record[stage][inplay + 1] = gotrash;

				for (int nm = 0; nm < 10; nm += 1){
					trashforname[nm] = name_amin[stage][inplay][nm];
					name_amin[stage][inplay][nm] = name_amin[stage][inplay + 1][nm];
					name_amin[stage][inplay + 1][nm] = trashforname[nm];
				}

			}
		}
	}

	for (int k = 0; k < 5; k += 1){
		fprintf(rank, "===%d===\n", k);
		for (int n = 0; n < 5; n += 1)
			fprintf(rank, "%s  -  %d\n", name_amin[k][n], record[k][n]);
	}

	fclose(rank);


	return stage;

}
//***********************undo함수***************************(기여자:박세준,최준식)
void undo_fuc (char input,char check){
	undo_count++;
	if (undo_count>5)
						return;
    for (Y=0; Y<30; Y++) // 플레이어 위치 찾기
        for(X=0; X<30; X++)
   		 if (map_now[stage][Y][X] == '@'){
    		switch (input){

        	case DOWN :

					if(check==NOT_MOVED)//전 상황에서 같이 움직였는지 아닌지를 체크함
						return;
						if(check==MOVED_WITH_MONEY)//전 상황에서 같이 움직였는지 아닌지를 체크함
						{
							map_now[stage][Y-1][X] = '@';
							map_now[stage][Y][X] = '$';
							map_now[stage][Y+1][X] = ' ';
							return;
						}
						if(check==JUST_MOVED)	//전 상황에서 같이 움직였는지 아닌지를 체크함
						{
							map_now[stage][Y-1][X] = '@';
							map_now[stage][Y][X] = ' ';
							return;
						}
						break;


        	case UP :

					if(check==NOT_MOVED)
						return;
						if(check==MOVED_WITH_MONEY)
						{
							map_now[stage][Y+1][X] = '@';
							map_now[stage][Y][X] = '$';
							map_now[stage][Y-1][X] = ' ';
							return;
						}
						if(check==JUST_MOVED)
						{
							map_now[stage][Y+1][X] = '@';
							map_now[stage][Y][X] = ' ';
							return;
						}
						break;


        	case LEFT :

					if(check==NOT_MOVED)
						return;
						if(check==MOVED_WITH_MONEY)
						{
							map_now[stage][Y][X+1] = '@';
							map_now[stage][Y][X] = '$';
							map_now[stage][Y][X-1] = ' ';
							return;
						}
						if(check==JUST_MOVED)
						{
							map_now[stage][Y][X+1] = '@';
							map_now[stage][Y][X] = ' ';
							return;
						}
						break;

        	case RIGHT :
					if(check==NOT_MOVED)
						return;
						if(check==MOVED_WITH_MONEY)
						{
							map_now[stage][Y][X-1] = '@';
							map_now[stage][Y][X] = '$';
							map_now[stage][Y][X+1] = ' ';
							return;
						}
						if(check==JUST_MOVED)
						{
							map_now[stage][Y][X-1] = '@';
							map_now[stage][Y][X] = ' ';
							return;
						}
						break;

        	default :
            break;
    }

	}
}
void undo_bbagi(){
	for(int i=4;i>0;i--)
	{
		undo[i+1]=undo[i];
		check_num[i+1]=check_num[i];
		check_num[i]=0;
		undo[i]=0;
	}
}
void undo_input(){
	for(int i=0;i<5;i++){
		undo[i]=undo[i+1];
		check_num[i]=check_num[i+1];}
	undo[5]=keyinput;
}

//*********************세이브앤로드**************************(기여자:우호진)
void save_game(int stage){
		FILE *savefile;
		savefile = fopen("sokoban", "w");
		if (savefile == NULL){
			printf("오류 : 세이브 파일을 열 수 없습니다.\n");
			exit(1);
   	}
		time_stop();
		fprintf(savefile, "%d, %s\n", stage, name);
		for (Y=0; Y<30; Y++)
			for (X=0; X<30; X++)
				fprintf(savefile, ".%c", map_now[stage][Y][X]);
		fprintf(savefile, "\n%d", time_stop());
		fclose(savefile);

}
void load_game(void){
		FILE *savefile;
		savefile = fopen("sokoban", "r");
		if (savefile == NULL){
			printf("세이브 파일이 없습니다.\n");
			}
		time_start = time(NULL);
		fscanf(savefile, "%d, %s\n", &stage, &name);
		for (Y=0; Y<30; Y++)
			for (X=0; X<30; X++)
				fscanf(savefile, ".%c", &map_now[stage][Y][X]);
		fscanf(savefile, "\n%d", &time_stopped);
		fclose(savefile);

}

//*****************리플레이********************************(기여자:박세준)
void replay(char stage){
	    undo_count = 0;
			for (Y=0; Y<30; Y++)
				for (X=0; X<30; X++)
					map_now[stage][Y][X] = map[stage][Y][X];
}

//**********************8메인함수**********************
int main(void)
{

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
