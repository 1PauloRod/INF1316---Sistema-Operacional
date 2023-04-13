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
#include <string.h>

int main(int argc, char* argv[])
{   
    int segmento;
    char *p;
    // aloca a memória compartilhada
    segmento = shmget (8000, sizeof (int), IPC_CREAT | S_IRUSR | S_IWUSR);
    // associa a memória compartilhada ao processo
    p = (char *) shmat (segmento, 0, 0); // comparar o retorno com -1
    printf("%s\n", p);
    // libera a memória compartilhada do processo
    shmdt (p);
    // libera a memória compartilhada
    shmctl (segmento, IPC_RMID, 0);
    return 0;
}