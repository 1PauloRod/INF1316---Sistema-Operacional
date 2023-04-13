#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
    int *p, id, status, pid;
    if ((p = (int *) malloc (sizeof(int))) == NULL)
    {
        puts ("Erro de alocação de memória"); exit (-1);
    }
    *p = 8752;
    if ((id = fork()) < 0)
    {
        puts ("Erro na criação do novo processo"); exit (-2);
    }
    else if (id == 0)
    {
        pid = getpid(); 
        *p += 5; printf ("Processo filho = %d - PID = %d\n", *p, pid);
    }
    else
    {
        pid = wait (&status);
        *p += 10; printf ("Processo pai = %d - PPID = %d\n", *p, pid);
    }
    return 0;
}
