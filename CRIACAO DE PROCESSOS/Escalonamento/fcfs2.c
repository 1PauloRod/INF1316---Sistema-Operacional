/* with arrival value */
#include <stdio.h>

struct process
{
    int id;
    int at;
    int bt;
    int wt;
    int tat;
    int ct;
};typedef struct process Process;


void findcpTime(Process p[], int n)
{
    p[0].ct = p[0].at + p[0].bt;
    printf("%d - %d\n", p[0].at, p[0].at + p[0].bt);
    for (int i = 1; i < n; i++)
    {
        if(p[i].at > p[i-1].ct)
        {
            p[i].ct = p[i].at + p[i].bt;
            printf("%d - %d\n", p[i].at, p[i].at + p[i].bt);
        }
        else
        {
            p[i].ct = p[i-1].ct + p[i].bt;
            printf("%d - %d\n", p[i-1].ct, p[i-1].ct + p[i].bt);

        }

    }
}


void findWaitingTime(Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void findTurnAroundTime(Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
    }
}              

void FCFS(Process p[], int n)
{
    //sort process
    Process temp;
    float awt; //average waiting time
    float ata; //average bust time
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
            else if (p[i].at == p[j].at)
            {
                if (p[i].id > p[j].id)
                {
                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }
    }
    
    findcpTime(p, n);
    findTurnAroundTime(p, n);
    findWaitingTime(p, n);
    printf("Process     Arrivel Time     Bust Time     CT     Waiting Time     Turn Around\n");
    for (int i = 0; i < n; i++)
    {
        awt += (float)p[i].wt;
        ata += (float)p[i].tat;
        printf("%d%12d%17d%14d%14d%17d\n",p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat); 
    }
    printf("\n");
    printf("Average waiting time: %f\n", awt/n);
    printf("Average turn around time: %f\n", ata/n);
}


int main(void)
{
    //Process p[5] = {{0, 3, 4, 0, 0}, {1, 5, 3, 0, 0}, {2, 0, 2, 0, 0}, {3, 5, 1, 0, 0}, {4, 4, 3, 0, 0}};
    Process p[5] = {{1, 2, 2, 0, 0}, {2, 0, 1, 0, 0}, {3, 2, 3, 0, 0}, {4, 3, 5, 0, 0}, {5, 4, 4, 0, 0}};
    int n = 5;
    FCFS(p, n);
    return 0;
}

//p2     x      p0     p4      p1            p3
//0 - 2; 2 - 3; 3 - 7; 7 - 10; 10 - 13; 13 - 14    
