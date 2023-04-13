#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM 4000


int main(void)
{
    int segmento;
    int *p;
    // aloca a memória compartilhada
    segmento = shmget(5000, TAM*sizeof (int), IPC_CREAT | S_IRUSR | S_IWUSR);
    // associa a memória compartilhada ao processo
    p = (int *) shmat(segmento, 0, 0); // comparar o retorno com -1

    for (int i = 0; i < TAM; i++)
        printf("%d\n", p[i]);
    

    // libera a memória compartilhada do processo
    shmdt (p);
    // libera a memória compartilhada
    shmctl (segmento, IPC_RMID, 0);



    return 0;
}