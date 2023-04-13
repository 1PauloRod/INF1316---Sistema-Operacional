#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>


int main(void)
{
    int status;
    if (fork() != 0)
    {
        printf("***************PROCESSO PAI EM EXECUCAO***************\n");
        int soma1 = 0;
        for(int i = 0; i <= 999; i++)
        {
            soma1 += i;
            printf("*   valor de i: %4d - soma: %7d - PID: %5d - PPID: %5d    *\n", i, soma1, getpid(), getppid());
        }
        waitpid(-1, &status, 0);
        printf("*----Processo pai finalizado com soma:   %7d ----*\n", soma1);
        exit(0);
    }
    else
    {
        if (fork() != 0)
        {
            printf("***************PROCESSO FILHO EM EXECUCAO***************\n");
            int soma2 = 0;
            for (int i = 1000; i <= 1999; i++)
            {
                soma2 += i;
                printf("*   valor de i: %4d - soma: %7d - PID: %5d - PPID: %5d    *\n", i, soma2, getpid(), getppid());
            }
            waitpid(-1, &status, 0);
            printf("*----Processo filho finalizado com soma: %7d ----*\n", soma2);
            exit(0);
        }
        else
        {
            printf("***************PROCESSO NETO EM EXECUCAO***************\n");
            int soma3 = 0;
            for (int i = 2000; i <= 2999; i++)
            {
                soma3 += i;
                printf("*   valor de i: %4d - soma: %7d - PID: %5d - PPID: %5d    *\n", i, soma3, getpid(), getppid());
            }
            printf("*----Processo neto finalizado com soma:  %7d ----*\n", soma3);
            exit(0);

        }

    }

}
/*soma1: 499500
soma2: 1499500
soma3: 2499500
*/



