#include<time.h>
int time_stopped;
unsigned int time_start;

void time_stop(void)  //일시정지에 사용, 시작후 정지까지의 시간 저장
{
    time_stopped += time(NULL) - time_start; //로스타임을 계산해줌
    time_start = time(NULL);  //시작시간을 현재시간으로 바꿈
}


int time_calculate(void) //흐른 시간 측정
{
    unsigned int time_passed;
    time_passed = time_stopped + time(NULL) - time_start; //로스타임, 흐른시간을 더해줌
    return time_passed;
}
