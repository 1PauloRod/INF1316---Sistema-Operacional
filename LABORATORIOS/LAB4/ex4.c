#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handler(int signal);

int main(void)
{
    signal(SIGFPE, handler);
    float num1;
    float num2;
    printf("digite o primeiro numero: ");
    scanf("%f", &num1);
    printf("digite o segundo numero: ");
    scanf("%f", &num2);
    float soma = num1 + num2;
    float subtracao = num1 - num2;
    float multiplicacao = num1*num2;
    int divisao = (int)num1/(int)num2;
    printf("soma: %f + %f = %f\n", num1, num2, soma);
    printf("subtracao: %f - %f = %f\n", num1, num2, subtracao);
    printf("multiplicacao: %f x %f = %f\n", num1, num2, multiplicacao);
    printf("divisao: %f / %f = %d\n", num1, num2, divisao);   
    return 0;
}                

void handler(int signal)
{
    printf("signal: %d\n", signal);
    exit(signal);
}
