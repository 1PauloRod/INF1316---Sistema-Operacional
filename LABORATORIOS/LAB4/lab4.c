#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define N 4

int main (void)
{
    int pid1;
    int pid2;
    int pid3;
    int pid4;
    

    pid1 = fork();
    if (pid1 == 0)
    {
        printf("inicio da execucao pid1\n");
        while (1) 
        {
            //printf ("pid1 executando...\n");
            sleep(1);
        }
    }
    pid2 = fork(); 
    if (pid2 == 0)
    {
        printf("inicio da execucao pid2\n");
        while (1) /* Infinite loop */
        {
            //printf ("pid2 executando...\n");
            sleep(1);
        }
    }
    pid3 = fork();
    if (pid3 == 0)
    {
        //printf("inicio da execucao pid3\n");
        while(1)
        {
            sleep(1);
        }
    }
    pid4 = fork();
    if (pid4 == 0)
    {
        printf("inicio da execucao pid4\n");
        while(1)
        {
            //printf("pid4 executando...\n");
            sleep(1);
        }
    } 
    
    sleep(1);
    kill (pid1, SIGSTOP); 
    kill (pid1, SIGCONT);
    sleep(1);
    kill(pid2, SIGSTOP);
    kill (pid2, SIGCONT);
    sleep(1);
    kill(pid3, SIGSTOP);
    kill(pid3, SIGCONT);

    sleep(20);
    kill (pid1, SIGINT);
    printf("processo pid1 encerrado...\n");
    sleep(20);
    kill(pid2, SIGINT);                    
    printf("processo pid2 encerrado...\n");
    sleep(20);
    kill(pid3, SIGINT);
    printf("processo pid3 encerrado...\n");
    sleep(20);
    kill(pid4, SIGINT);
    printf("processo pid4 encerrado...\n");
    
    
    return 0;
}

