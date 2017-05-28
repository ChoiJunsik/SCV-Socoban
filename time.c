#include<time.h>
int time_calculate(void)
unsigned int time_start = 0;

{
    int time_passed = time(NULL) - time_start;
    return time_passed;
}

