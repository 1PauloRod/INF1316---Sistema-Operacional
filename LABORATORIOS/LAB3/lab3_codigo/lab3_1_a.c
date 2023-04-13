#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 60

void* contCrescente(void* arg)
{
    for (int i = 1; i <= N; i++)
    {
        printf("valor thread 1: %d\n", i);
        sleep(2);
    }
    pthread_exit(NULL);
}

void* contDecrescente(void* arg)
{
    for (int i = N; i >= 1; i--)
    {
        printf("valor thread 2: %d\n", i);
        sleep(1);
    }
    pthread_exit(NULL);

}

int main(void)
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, contCrescente, (void*) NULL);
    pthread_create(&t2, NULL, contDecrescente, (void*)NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0; 
}

