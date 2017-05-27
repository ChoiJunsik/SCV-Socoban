#include <termio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WIDTH 30
#define HEIGHT 30
#define STAGE 5
char name[10];
char map[STAGE][WIDTH][HEIGHT];
int scan_at_y(int i)
{
	int x,y=0;
	for(;y<=30;y++){
		for(;x<=30;x++)
		{
			if (map[i][y][x]=='@')
			return y;
		}
	}
}
int scan_at_x(int i)
{
	int x,y=0;
	for(;y<=30;y++){
		for(;x<=30;x++)
		{
			if (map[i][y][x]=='@')
			return y;
		}
	}
}
void move_left(int i)
	{
		int x = scan_at_x(i);
		int y = scan_at_y(i); 
		switch(map[i][y][x-1]){
			case '#':
				 break;
			case ' ':
				 map[i][y][x-1]='@';
				 break;
			case 'O':
				 map[i][y][x-1]='@'; 
				 break;
			case '$':
				 if(map[i][y][x-2]=='#'||map[i][y][x-2]=='$')
				 	break;
				 else{
					map[i][y][x-2]='$';
					map[i][y][x-1]='@';
					map[i][y][x]=' ';
				     }
				 
				 
		}
		return ;
	}
void move_down(int i)
	{
		int x = scan_at_x(i);
		int y = scan_at_y(i); 
		switch(map[i][y-1][x]){
			case '#':
				 break;
			case ' ':
				 map[i][y-1][x]='@';
				 map[i][y][x]=' ';
				 break;
			case 'O':
				 map[i][y-1][x]='@'; 
				 map[i][y][x]=' ';
				 break;
			case '$':
				 if(map[i][y-2][x]=='#'||map[i][y-2][x]=='$')
				 	break;
				 else{
	 				map[i][y-2][x]='$';
					map[i][y-1][x]='@';
					map[i][y][x]=' ';
				     }	
				 
				 break;

		}
		return ;
				 
	}
void move_up(int i)
	{
		int x = scan_at_x(i);
		int y = scan_at_y(i); 
		switch(map[i][y+1][x]){
			case '#':
				 break;
			case ' ':
				 map[i][y+1][x]='@';
				 map[i][y][x]=' ';
				 break;
			case 'O':
				 map[i][y+1][x]='@'; 
				 map[i][y][x]=' ';
				 break;
			case '$':
				 if(map[i][y+2][x]=='#'||map[i][y+2][x]=='$')
				 	break;
				 else{
 					map[i][y+2][x]='$';
					map[i][y+1][x]='@';
					map[i][y][x]=' ';
				     }
				 
				 break;

		}
		return ;
				 
	}
void move_right(int i)
	{
		int x = scan_at_x(i);
		int y = scan_at_y(i); 
		switch(map[i][y][x-1]){
			case '#':
				 break;
			case ' ':
				 map[i][y][x-1]='@';
				 break;
			case 'O':
				 map[i][y][x-1]='@'; 
				 break;
			case '$':
				 if(map[i][y][x-2]=='#'||map[i][y][x-2]=='$')
				 	break;
				 else{
					map[i][y][x-2]='$';
					map[i][y][x-1]='@';
					map[i][y][x]=' ';
				     }
				 
				 
		}
		return ;
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
char key_input(int i)
{
  char key=getch();
  switch(key){
    case 'h':move_left(i); break;
    case 'j':move_down(i); break;
    case 'k':move_up(i); break;
    case 'l':move_right(i); break;
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
                  x++;

      map[i][x][y]=ch;
      y++;
  }

  if(money!=O)
    printf("돈,공간 오류");
  fclose(fp);

  return;
}

int main(void)
{
  char ch=0;
  start();
/*  for(int i=0;i<=4;i++){
      while(1){
  	 printf("hello %s",name);
     	 for(int x=0; x<WIDTH;x++){
        	 for(int y=0; y<HEIGHT;y++)
       		 	printf("%c",map[i][x][y]);} 
         printf("(Command)");
         key_input(i);
         system("clear"); 
       }      
  }*/
  return 0;
}
