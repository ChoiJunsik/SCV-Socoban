#include<stdio.h>
#include<stdlib.h>
#define WIDTH 30
#define HEIGHT 30
int main()
{
	int x=-1,y=0; 
	char money=0,o=0;
	int map[5][HEIGHT][WIDTH]={0};
	int tmp = 0;
	FILE *fp;
	fp = fopen("map.txt","rt");
	tmp=0;
	
	for(int i=-1;;){
		fscanf(fp,"%c",&tmp);
		if(tmp=='m')
		{
			i++;
			tmp=0;		
		}
		if(tmp=='a'||'p'){
			tmp=0;
			continue;
		}
		if(tmp=='e'){
			tmp=0;
			break;
		}	
		else{
			if(tmp=='$')
				money++;
			if(tmp=='O')
				o++;
			x++;
			map[i][y][x]=tmp;
			if(tmp='\n')
				y++;
		}
	}
	fclose(fp);
	
	if(money!=o)
	{
		printf("오류발생 돈의 숫자와 공간의 숫자가 맞지 않음");
		exit(1);
	}

	for(y=0;y<=30;y++){
		for(x=0;x<=30;x++)
			printf("%c",map[0][y][x]);
		}
	return 0;	
}
