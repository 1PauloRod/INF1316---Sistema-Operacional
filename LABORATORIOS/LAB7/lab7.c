#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#define TRUE 1
#define FALSE 0

struct pagina
{
	int frequencia;
	unsigned int endereco;
	struct pagina* proximo;	
};typedef struct pagina Pagina;


int tamanhoPagina, tamanhoMemoria, numeroPaginas, escritas=0, paginasUsadas=0, faults=0, hit = 0;
char *algoritmo, *arquivo;
FILE *arq;
Pagina* inicio, *ultimo;
char rw;
unsigned int addr;

void addNovaPagina(unsigned int end)
{
	Pagina *novo = (Pagina*)malloc(sizeof(Pagina));
	novo->endereco = end;
	novo->frequencia = 1;
	novo->proximo = NULL;
	
	if(paginasUsadas == 0)
	{
		inicio = novo;
		ultimo = inicio;
	}
	else 
	{
		ultimo->proximo = novo;
		ultimo = novo;
	}
	
	if(paginasUsadas < numeroPaginas) paginasUsadas++;
}




void FIFO(unsigned int end)
{
	addNovaPagina(end);
	if (paginasUsadas == numeroPaginas) inicio = inicio->proximo;
	
}

void LRU(unsigned int end)
{
	Pagina *tmp = inicio, *anterior = NULL;
	while(tmp != NULL)
	{
	if(tmp->endereco == end)
	{
		tmp->frequencia++;
		
		if(anterior != NULL)
		{
			if(tmp->proximo != NULL)
				anterior->proximo = tmp->proximo;							
		}
		else 
		{
			inicio = inicio->proximo;
		}
		ultimo->proximo = tmp;
		ultimo = tmp;
		tmp->proximo = NULL;
	}
	anterior = tmp;	
	tmp = tmp->proximo;
	}
	addNovaPagina(end);
	if (paginasUsadas == numeroPaginas) inicio = inicio->proximo;
}

Pagina* removeFrequencia(int freq)
{
    Pagina* anterior = NULL;
    Pagina* aux = inicio;
    while(aux != aux->proximo && (aux->frequencia != freq))
    {
        anterior = aux;
        aux = aux->proximo;
    }
    if(aux == NULL)
        return inicio;
    else if (anterior == NULL)
        inicio = aux->proximo;
    else
        anterior->proximo = aux->proximo;
    free(aux);
    return inicio;

}

void LFU(unsigned int end)
{

    Pagina* t = NULL;
    int menorFrequencia = 1000000;
    for (t = inicio; t != NULL; t = t->proximo)
    {
        if (t->frequencia < menorFrequencia) menorFrequencia = t->frequencia;
    }
    addNovaPagina(end);
    if (paginasUsadas == numeroPaginas) inicio = removeFrequencia(menorFrequencia);
}

int busca(unsigned int end)
{
	Pagina* t = NULL;
	for (t = inicio; t != NULL; t = t->proximo)
	{
		if (t->endereco == end)
        {
            t->frequencia++;
			return TRUE;
        }
	}
	return FALSE;
}

void substituiPagina(unsigned int end)
{
	if(strcmp(algoritmo, "lru") == 0 || strcmp(algoritmo, "LRU") == 0) LRU(end);
	else if(strcmp(algoritmo, "lfu") == 0 || strcmp(algoritmo, "LFU") == 0) LFU(end);
	else if(strcmp(algoritmo, "fifo") == 0 || strcmp(algoritmo, "FIFO") == 0) FIFO(end);
	
}

void escreveEndereco()
{
	if(paginasUsadas < numeroPaginas)
		addNovaPagina(addr);
	
	else
	{
		faults++;
		substituiPagina(addr);
	}
}



int main(int argc, char *argv[])
{
	algoritmo = argv[1];
	arquivo = argv[2];
	tamanhoPagina = atoi(argv[3]);
	tamanhoMemoria = atoi(argv[4]);

	if(tamanhoPagina < 8 || tamanhoPagina > 32)
	{	
		printf("Erro: tamanho da pagina tem que ser entre 8 a 32.\n");
		exit(1);
	}
		
	if(tamanhoMemoria < 1 || tamanhoMemoria > 16)
	{
		printf("Erro: tamanho da memoria tem que ser entre 1 e 16.\n");
		exit(1);
	}	
	
	if(strcmp(algoritmo, "lru")   &&
	   strcmp(algoritmo, "LRU")   &&
	   strcmp(algoritmo, "fifo")  &&
	   strcmp(algoritmo, "FIFO")  &&
	   strcmp(algoritmo,"lfu") &&
	   strcmp(algoritmo,"LFU"))
	     {
		printf("ERRO: algoritmo tem que ser fifo/lru/random.\n");
		exit(1);	
	}
	
	arq = fopen(arquivo, "r");
	
	if (arq == NULL)
	{
		printf("Erro: nao foi possivel abrir o arquivo.\n");
		exit(1);
	}
	
	numeroPaginas = tamanhoMemoria*1000/tamanhoPagina;
	
	printf("\nExecutando o simulador...\n");
	
	while(fscanf(arq, "%x %c", &addr, &rw) != EOF)
	{
		if (tamanhoPagina == 8) addr = addr >> 13;
		else if(tamanhoPagina > 8 && tamanhoPagina <= 16) addr = addr >> 14;
		else if (tamanhoPagina > 16 && tamanhoPagina <= 32) addr = addr >> 15;
			
		if(rw == 'W')
		{
			escritas++;
			escreveEndereco();
		}
		else if(rw == 'R')
		{				
			if(busca(addr) == FALSE) escreveEndereco();
			else hit++;
		}	
	}
	
	printf("Arquivo de entrada: %s\n", arquivo);
	printf("Tamanho da memoria fisica: %d MB\n", tamanhoMemoria);
	printf("Tamanho das paginas: %d KB\n", tamanhoPagina);
	printf("Algoritmo de substituicao: %s\n", algoritmo);
	printf("Numero de Faltas de Paginas: %d\n", faults);
	printf("Numero de Paginas Escritas: %i\n", escritas);
	
	
	fclose(arq);
		
	return 0;
}
