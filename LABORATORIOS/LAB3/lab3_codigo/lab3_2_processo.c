#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/shm.h>

#define TAM 4000
#define N 4


int main(void)
{
    int segmento, status;
    int *p;
    int max = 0;
    int *vet_max;
    //aloca a memória compartilhada
    segmento = shmget(IPC_PRIVATE, TAM*sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    //associa a memória compartilhada ao processo
    p = (int *)shmat(segmento, 0, 0);
    vet_max = (int *)shmat(segmento, 0, 0); 
    // preenche o vetor com valores aleatórios
    srand(time(NULL));
    for (int i = 0; i < TAM; i++)
        p[i] = rand() % 9999;

    //Cria os 4 processos
    clock_t begin[N];
    clock_t end[N];
    for (int i = 0; i < N; i++)
    {
        begin[i] = clock();
        if (fork() == 0)
        {
            //printf("Processo %d criado - PID: %d\n", i+1, getpid());

            for (int j = i*1000; j < (i+1)*1000; j++) 
            {
                //Verifica o maior valor de cada processo
                if (p[j] > max)
                {
                    max = p[j];
                }
            }
            vet_max[i] = max;//armazena na memória compartilhada os maiores valores encontrados em cada processo
            exit(0);
        }
        end[i] = clock();
    }
    double tot;
    for (int i = 0; i < N; i++)
    {
        tot+=end[i] - begin[i];
    }

    clock_t begin2 = clock();
    //Espera de um processo
    for (int i = 0; i < N; i++)
    {
        waitpid(-1, &status, 0);
    }
    clock_t end2 = clock();

    //Verifica o maior valor entre os processos
    clock_t begin3 = clock();
    for (int i = 0; i < N; i++)
    {
        if (vet_max[i] > max)
            max = vet_max[i];
    }
    clock_t end3 = clock();
    //clock_t end = clock();
    printf("Maior valor encontrado: %d\n", max);

    printf("Tempo de execucao: %f s\n", (tot + (double)(end2 - begin2) + (double)(end3 - begin3))/CLOCKS_PER_SEC); 
    //printf("Tempo de execucao: %f s\n", ((double)(end - begin))/CLOCKS_PER_SEC);

    // libera a memória compartilhada do processo
    shmdt (p);
    // libera a memória compartilhada
    shmctl (segmento, IPC_RMID, 0);
    return 0;
}
