#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


char s[50] = "OLA MUNDO, RIO DE JANEIRO!";

void handler(int signal)
{
    for (int i = 0; i < strlen(s); i++)
       s[i] =  tolower(s[i]);
    printf("%s\n", s);

}   

void handler2(int signal)
{
    printf("Terminou a impressão!\n");
    kill(getpid(), SIGINT);
}

int main(void)
{
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler2);
    printf("%s - %d\n", s, getpid());
    while(1){};

    return 0;
}
