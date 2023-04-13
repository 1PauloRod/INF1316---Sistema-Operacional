/*
Nome: Paulo Rodrigues
Matricula: 1713170
*/
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM 4000


int main(void)
{
    printf("Digite a chave para ser buscada: ");
    int chave;
    scanf("%d", &chave);
    int segmento, status;
    int *p;
    // aloca a memória compartilhada
    segmento = shmget(IPC_PRIVATE, TAM*sizeof (int), IPC_CREAT | S_IRUSR | S_IWUSR);
    // associa a memória compartilhada ao processo
    p = (int *) shmat(segmento, 0, 0); // comparar o retorno com -1
    for (int i = 0; i < TAM; i++)
        p[i] = rand() % 999;
    
    if (fork() != 0)
    {
        //processo pai
        printf("***************PROCESSO PAI EM EXECUCAO***************\n");
        int pos  = -1;
        for (int i = 0; i < 1000; i++)
        {
            if (p[i] == chave)
            {
                pos = i;
                printf("posicao: %4d - valor: %4d - PID: %4d ------------------> **VALOR ENCONTRADO**\n", i, p[i], getpid());
            }
            else
            {
                printf("posicao: %4d - valor: %4d - PID: %4d -> valor nao encontrado\n", i, p[i], getpid());
            }
        }
        waitpid(-1, &status, 0);
        if (pos != -1)
            printf("*----Processo pai finalizado com o valor encontrado----*\n");
        else
            printf("*----Processo pai finalizado com valor NAO encontrado-----*\n");
        exit(0);
    }
    else
    {
        if (fork() != 0)
        {
            //processo filho
            printf("***************PROCESSO FILHO EM EXECUCAO***************\n");
            int pos = -1;
            for (int i = 1000; i < 2000; i++)
            {
                if (p[i] == chave)
                {
                    pos = i;
                    printf("posicao: %4d - valor: %4d - PID: %4d - PPID: %4d --------------> **VALOR ENCONTRADO**\n", i, p[i], getpid(), getppid());
                }
                else
                {
                    printf("posicao: %4d - valor: %4d - PID: %4d - PPID: %4d -> valor nao encontrado\n", i, p[i], getpid(), getppid());
                }

            }
            waitpid(-1, &status, 0);
            if (pos > 0)
                printf("*----Processo filho finalizado com valor encontrado----*\n");
            else
                printf("*----Processo filho finalizado com valor NAO encontrado-----*\n");
            exit(0);
        }
        else
        {
            if (fork() != 0)
            {
                //processo neto
                printf("***************PROCESSO NETO EM EXECUCAO***************\n");
                int pos = -1;
                for (int i = 2000; i < 3000; i++)
                {
                    if (p[i] == chave)
                    {
                        pos = i;
                        printf("posicao: %4d - valor: %4d - PID: %4d - PPID: %4d --------------> **VALOR ENCONTRADO**\n", i, p[i], getpid(), getppid());
                    }
                    else
                    {
                        printf("posicao: %4d - valor: %4d - PID: %4d - PPID: %4d -> valor nao encontrado\n", i, p[i], getpid(), getppid());
                    }   
                }
                waitpid(-1, &status, 0);
                if (pos > 0)
                    printf("*----Processo neto finalizado com o valor encontrado----*\n");
                else
                    printf("*----Processo neto finalizado com o valor NAO encontrado----*\n");
                exit(0);
            }
            else
            {
                //processo bisneto
                printf("***************PROCESSO BISNETO EM EXECUCAO***************\n");
                int pos = -1;
                for (int i = 3000; i < 4000; i++)
                {
                    if (p[i] == chave)
                    {
                        pos = i;
                        printf("posicao: %4d - valor: %4d - PID: %4d - PPID: %4d --------------> **VALOR ENCONTRADO**\n", i, p[i], getpid(), getppid());
                    }
                    else
                    {
                        printf("posicao: %4d - valor: %4d - PID: %4d - PPID: %4d -> valor nao encontrado\n", i, p[i], getpid(), getppid());
                    }
                }
                if (pos > 0)
                    printf("*----Processo bisneto finalizado com o valor encontrado----*\n");
                else
                    printf("*----Processo bisneto finalizado com o valor NAO encontrado----*\n");
                exit(0);
            }
        }
    }
    
    
    // libera a memória compartilhada do processo
    shmdt (p);
    // libera a memória compartilhada
    shmctl (segmento, IPC_RMID, 0);

    
    return 0;
}
