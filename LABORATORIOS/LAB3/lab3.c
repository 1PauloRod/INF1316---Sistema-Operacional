
#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 4

int vet[1000];


void *buscaValor574(void *threadid)
{
    long id_thread = (long)threadid;
    //printf("\n%d: Hello World!\n", i);
    for (int i = 0; i < 1000; i++)
    {
        if (vet[i] == 574)
            printf("thread: %ld - posicao: %d - valor: %d --> valor encontrado\n", id_thread, i, vet[i]);
        else
            printf("thread: %ld - posicao: %d - valor: %d --> valor nao encontrado\n", id_thread, i, vet[i]);
    }
    /* do other things */
    pthread_exit(NULL); /*not necessary*/
}

int main()
{
    //atribui valores ao vetor, onde, a posicao que for divisivel por 13 atribui o valor de 574.
    for (int i = 0; i < 1000; i++)
    {
        vet[i] = i+1;
        if (i % 13 == 0 && i > 0)
            vet[i] = 574;
    }
    pthread_t threads[NUM_THREADS];
    long t;
    for(t=0;t < NUM_THREADS;t++)
    {
        printf("***************Cria thread %ld***************\n", t);
        pthread_create(&threads[t], NULL, buscaValor574, (void *)t);
    }
    for(t=0; t < NUM_THREADS; t++)
        pthread_join(threads[t],NULL); /* wait for all the threads to terminate*/
}


