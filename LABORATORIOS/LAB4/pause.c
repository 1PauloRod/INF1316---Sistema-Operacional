#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void handler(int sinal);

int main (void)
{
    signal(SIGKILL, handler);
    printf ("vou parar...%d\n", getpid());
    pause();
    printf ("Continuei!\n");
    return 0;
}
void handler(int sinal)
{
    printf ("Sinal %d recebido\n", sinal);
}
