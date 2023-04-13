#include <stdio.h> 


struct process
{
    int id;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
};typedef struct process Process;

Process* findctTime(Process p[], int n)
{
    int small_ct = 100000;
    int small_process_index;
    Process aux[n];
    for (int i = 0; i < n; i++)
    {
        if (p[i].at < small_ct)
        {
            small_ct = p[i].at;
            small_process_index = i;
        }
    }
    for (int i = 0, j = 1; i < n && j < n; i++, j++)
    {
        if (i == small_process_index)
            i++;
        aux[j] = p[i];
    }
    aux[0] = p[small_process_index];
    aux[0].ct = aux[0].at + aux[0].bt;
    for (int i = 1; i < n; i++)
    {
        //aux[i].ct = aux[i-1].ct + aux[i].bt;
        if(aux[i].at > aux[i-1].ct)
        {
            aux[i].ct = aux[i].at + aux[i].bt;
            //printf("%d - %d\n", aux[i].at, aux[i].at + aux[i].bt);
        }
        else
        {
            aux[i].ct = aux[i-1].ct + aux[i].bt;
            //printf("%d - %d\n", aux[i-1].ct, aux[i-1].ct + aux[i].bt);
 
        }

        
    }
    for (int i = 0; i < n; i++)
        p[i] = aux[i];

    return p;

}
   


void findTurnAroundTime(Process p[], int n)
{
    for (int i = 0; i < n; i++)
        p[i].tat = p[i].ct - p[i].at;
}

void findWaitingTime(Process p[], int n)
{
    for (int i = 0; i < n; i++)
        p[i].wt = p[i].tat - p[i].bt;
}

void SJF(Process p[], int n)
{
    float awt; //average waiting time
    float ata; //average turn around time
    Process temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].bt > p[j].bt)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
            else if (p[i].bt == p[j].bt)
            {
                if (p[i].at > p[j].at)
                {
                    temp = p[i];
                    p[i] = p[j];
                    p[j] = p[i];
                }
            }
        }
    }
    p = findctTime(p, n);
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
    Process p[5] = {{1, 2, 1}, {2, 1, 5}, {3, 4, 1}, {4, 0, 6}, {5, 2, 3}};
    //Process p[4] = {{1, 2, 3}, {2, 0, 4}, {3, 4, 2}, {4, 5, 4}}    ;
    int n = 5;
    //int n = 4;
    SJF(p, n);

    return 0;
}
