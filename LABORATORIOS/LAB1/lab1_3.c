#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int status;
    if (fork() != 0)
    {
        printf("Processo pai: %d (PID)\n", getpid());
        char* args1[] = {"meu", "echo", NULL};
        execv("./meuecho", args1);
        waitpid(-1, &status, 0);
        //printf("Processo pai finalizado...\n");
        exit(0);
    }
    else
    {
        if (fork() != 0)
        {
            printf("Processo filho: %d (PID) - %d (PPID)\n", getpid(), getppid());
            char *args2[] = {"./bomdia", NULL};
            execv(args2[0], args2);
            waitpid(-1, &status, 0);
            //printf("Processo filho finalizado...\n");
            exit(0);
        }
        else
        {
            printf("Processo neto: %d (PID) - %d (PPID)\n", getpid(), getppid());
            char* cat[] = {"cat", "meuecho.c", NULL};
            execv("/bin/cat", cat);
            //printf("Processo neto finalizado...\n");
            exit(0);
        }
        
    }
    return 0;
}
