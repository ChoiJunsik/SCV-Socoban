#include<time.h>
int time_stopped;
unsigned int time_start;

void time_stop(void)  //�Ͻ������� ���, ������ ���������� �ð� ����
{
    time_stopped += time(NULL) - time_start; //�ν�Ÿ���� �������
    time_start = time(NULL);  //���۽ð��� ����ð����� �ٲ�
}


int time_calculate(void) //�帥 �ð� ����
{
    unsigned int time_passed;
    time_passed = time_stopped + time(NULL) - time_start; //�ν�Ÿ��, �帥�ð��� ������
    return time_passed;
}
