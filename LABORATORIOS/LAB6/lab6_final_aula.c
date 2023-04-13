#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>




int main(void)
{
    int segmento, status;
    int *p;
    segmento = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    p = (int *)shmat(segmento, 0, 0);

    *p = 0;
    

    if (fork() != 0)
    {                  
        printf("Processo Pai\n");
        for (int i = 0; i < 50000; i++)
            *p += 1;
        waitpid(-1, &status, 0);
    }
    else
    {
        if (fork() != 0)
        {
            printf("Processo Filho\n");
            for (int i = 0; i < 50000; i++)
                *p += 2;
            waitpid(-1, &status, 0);
        }
        else
        {
            printf("Processo Neto\n");
            for (int i = 0; i < 50000; i++)
                *p += 3;
            //sleep(1);
            printf("final: %d\n", *p);
            exit(0);
            
        }
    } 
    shmdt(p);
    shmctl(segmento, IPC_RMID, 0);
    return 0;
}
