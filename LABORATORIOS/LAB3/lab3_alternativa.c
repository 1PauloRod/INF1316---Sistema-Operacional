#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 1000

int vet[1000];


void *buscaValor574(void *threadid)
{
    long i = (long)threadid;
    if (vet[i] == 574)
        printf("posicao %ld - valor - %d: valor encontrado\n", i, vet[i]);
    else
        printf("posicao %ld - valor - %d: valor nao encontrado\n", i, vet[i]);
    pthread_exit(NULL); /*not necessary*/
}

int main()
{
    //atribui valores ao vetor, onde, a posicao que for divisivel por 13 atribui o valor de 574.
    for (int i = 0; i < 1000; i++)
    {
        vet[i] = i+1;
        if (i % 13 == 0)
            vet[i] = 574;
    }
    pthread_t threads[NUM_THREADS];
    long t;
    for(t=0;t < NUM_THREADS;t++)
    {
        printf("Creating thread %ld\n", t);
        pthread_create(&threads[t], NULL, buscaValor574, (void *)t);
    }
    for(t=0; t < NUM_THREADS; t++)
        pthread_join(threads[t],NULL); /* wait for all the threads to terminate*/
}
