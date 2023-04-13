#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define THREAD 4
#define TAM 4000

int vet[TAM];
int max = 0, max2 = 0;
int max_vet[THREAD] = {0};
int current_thread = 0;

void* buscaMaior(void* arg)
{
    max = vet[0];
    int j = current_thread++;
    for (int i = j * (TAM/THREAD); i < ((j+1)*(TAM/THREAD)); i++)
    {
        if (vet[i] > max)
            max = vet[i];
    }
    max_vet[j] = max;
    pthread_exit(NULL); 
}

int main(void)
{
    srand(time(NULL));
    for (int i = 0; i < TAM; i++)
        vet[i] = rand() % 9999;

    pthread_t threads[THREAD];

    clock_t begin1 = clock();
    for (int i = 0; i < THREAD; i++)
        pthread_create(&threads[i], NULL, buscaMaior, (void*)NULL);
    clock_t end1 = clock();
    
    clock_t begin2 = clock();
    for (int i = 0; i < THREAD; i++)
        pthread_join(threads[i], NULL);
    clock_t end2 = clock();

    clock_t begin3 = clock();
    for (int i = 0; i < THREAD; i++)
    {
        if (max_vet[i] > max)
            max = max_vet[i];
    }
    clock_t end3 = clock();
    printf("Maior valor encontrado:%d\n", max);
    printf("Tempo de execucao: %f s\n", (double)((end1 - begin1) + (end2 - begin2) + (end3 - begin3))/CLOCKS_PER_SEC);

    return 0; 
}
