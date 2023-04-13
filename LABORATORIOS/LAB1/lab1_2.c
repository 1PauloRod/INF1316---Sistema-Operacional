#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>


#define NUM 3


int main(void)
{
    int status;

    pid_t pid;
    for (int i = 0; i < NUM; i++)
    {
        pid = fork();
        int soma = 0;
        if (pid == 0)
        {
            if (i == 0) printf("***************PROCESSO PAI CRIADO***************\n");
            if (i == 1) printf("***************PROCESSO FILHO CRIADO***************\n");
            if (i == 2) printf("***************PROCESSO NETO CRIADO***************\n");

            for (int j = i*1000; j < (i + 1)*1000; j++)
            {
                soma+=j;
                printf("* valor de j: %4d - soma: %7d - PID: %5d - PPID: %5d *\n", j, soma,
getpid(), getppid());
            }
            
            printf("%d\n", soma);
            exit(0);
        }
    }

    for (int i = 0; i < NUM; i++)
    {
        waitpid(-1, &status, 0);
        if (i == 0) printf("Processo pai finalizado\n");
        if (i == 1) printf("Processo filho finalizado\n");
        if (i == 2) printf("Processo neto finalizado\n");
        //waitpid(-1, &status, 0);
    }
    return 0;
}
