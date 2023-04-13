/* scheduling FCFS */
#include <stdio.h>
#include <unistd.h>


void findWaitingTime(int process_time[], int n, int waiting_time[])
{
    waiting_time[0] = 0;
    
    for (int i = 1; i < n; i++)
    {
        waiting_time[i] = process_time[i-1] + waiting_time[i-1];
    }
}

void turnAroundTime(int process_time[], int n, int turn_around_time[])
{
    turn_around_time[0] = process_time[0];
    for (int i = 1; i < n; i++)
        turn_around_time[i] = process_time[i] + turn_around_time[i-1];
}

void FSFC(int process[], int n, int process_time[])
{
    int wt[3];
    int ta[3];
    float awt; //avarege wating time
    float ata; //avarege turn around time
    findWaitingTime(process_time, n, wt);
    turnAroundTime(process_time, 3, ta);
    printf("Process     Waiting Time     Turn Around\n");
    for(int i = 0; i < n; i++)
    {
        awt+= wt[i];
        ata+=ta[i];
        printf("%d  %10d  %15d\n", process[i], wt[i], ta[i]);
    }
    printf("\n");
    awt /= n;
    ata /= n;
    printf("Avarege Waiting Time: %f\n", awt);
    printf("Avarege Turn Around Time: %f\n", ata);
}

int main(void)
{
    int process[3] = {1, 2, 3};
    int process_time[3] = {10, 5, 8};
    
    FSFC(process, 3, process_time);

    return 0;
}









