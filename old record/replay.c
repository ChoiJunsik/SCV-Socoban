//input  키입력받는  함수
char map[5][30][30];
char map_now[30][30];
void replay(char stage){//  이 함수를 실행할시  map_now에  들어있는  맵의  원래   상태를  map[][][]에  
for( char y=0;y<=30;y++)
        for( char x=0;x<=30;x++)
                map[stage][y][x]=map_now[y][x];
                return ;
}
int main(){
          for(int stage=0;stage<=4;stage++){
              for(int y=0; y<WIDTH;y++)
              {
                       for(int x=0; x<HEIGHT;x++){ 
                               map_now[y][x]=map[stage][y][x];
                                         }// map_now   가 초기화되지  않고 한번만 처음맵을저장함
               }
              while(1)
              {
                      printf("hello %s",name);
                      for(int y=0; y<WIDTH;y++)
                      {
                               for(int x=0; x<HEIGHT;x++)
                                                printf("%c",map[stage][y][x]);
                      }
                printf("(Command)");
          printf("%c",input(stage));
                                        for(char i; i<10;i++);
          printf("\n");
          system("clear");


              }
  }
return 0;
}
