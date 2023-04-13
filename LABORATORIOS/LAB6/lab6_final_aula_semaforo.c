#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>


union semun
{
	int val;
	struct semid_ds *buf;
	ushort *array;
};
// inicializa o valor do semáforo
int setSemValue(int semId);
// remove o semáforo
void delSemValue(int semId);
// operação P
int semaforoP(int semId);
//operação V
int semaforoV(int semId);


int main(void)
{
    int segmento, status;
    int *p;
    segmento = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    p = (int *)shmat(segmento, 0, 0);

    *p = 0;

    int semId = semget(8752, 1, 0666 | IPC_CREAT);
    setSemValue(semId);
    
    if (fork() != 0)
    {
        semaforoP(semId);
        printf("Processo Pai\n");
        for (int i = 0; i < 50000; i++)
            *p += 1;
        semaforoV(semId);
        waitpid(-1, &status, 0);
    }
    else
    {
        if (fork() != 0)
        {
            semaforoP(semId);
            printf("Processo Filho\n");
            for (int i = 0; i < 50000; i++)
                *p += 2;
            semaforoV(semId);
            waitpid(-1, &status, 0);
        }
        else
        {
            semaforoP(semId);
            printf("Processo Neto\n");
            for (int i = 0; i < 50000; i++)
                *p += 3;
            //sleep(1);
            printf("final: %d\n", *p);
            semaforoV(semId);
            exit(0);
            
        }
    } 
    delSemValue(semId);
    shmdt(p);
    shmctl(segmento, IPC_RMID, 0);
    return 0;
}


int setSemValue(int semId)
{
    union semun semUnion;
    semUnion.val = 1;
    return semctl(semId, 0, SETVAL, semUnion);
}

void delSemValue(int semId)
{
    union semun semUnion;
    semctl(semId, 0, IPC_RMID, semUnion);
}

int semaforoP(int semId)
{
    struct sembuf semB;
    semB.sem_num = 0;
    semB.sem_op = -1;
    semB.sem_flg = SEM_UNDO;
    semop(semId, &semB, 1);
    return 0;
}

int semaforoV(int semId)
{
    struct sembuf semB;
    semB.sem_num = 0;
    semB.sem_op = 1;
    semB.sem_flg = SEM_UNDO;
    semop(semId, &semB, 1);
    return 0;
}
