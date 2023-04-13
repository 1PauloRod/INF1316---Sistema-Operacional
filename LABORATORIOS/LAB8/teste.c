#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

void printFileAttributes(const char* directory, struct stat stats)
{
    struct tm dt;

    printf("arquivo: %s\n", directory);
    // permissoes do arquivo
    printf("acesso do arquivo: ");
    if (stats.st_mode & R_OK)
        printf("leitura ");
    if (stats.st_mode & W_OK)
        printf("escrita ");
    if (stats.st_mode & X_OK)
        printf("executa");

    // tamanho do arquivo
    printf("\nTamanho do arquivo: %ld", stats.st_size);

    // Pega o tempo de criacao do arquivo em segundos
    // e converte para o formato de data
    dt = *(gmtime(&stats.st_ctime));
    printf("\nCriado em: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                                              dt.tm_hour, dt.tm_min, dt.tm_sec);

    // File modification time
    dt = *(gmtime(&stats.st_mtime));
    printf("\nModificado em: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                                              dt.tm_hour, dt.tm_min, dt.tm_sec);
    printf("\n");
}



int main(void)
{
    struct stat stats;
    const char* main_directory = "so";
    const char* directory_a;
    const char* directory_b;
    const char* directory_c;
    const char* write_a = "o arquivo a foi escrito\n";
    const char* write_b = "o arquivo b foi escrito\n";
    const char* write_c = "o arquivo c foi escrito\n";
    char file_search[100];
    char option;
    char option_search;
    int create_directory;
    int file_a, file_b, file_c, search_file, tamanho;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    //cria diretorio principal
    create_directory = mkdir(main_directory, S_IRWXU);
    if (create_directory == -1)
    {
        printf("Erro ao criar diretorio principal.\n");
        exit(1);
    }


    //cria subdiretorios 

    directory_a = "so/a";
    create_directory = mkdir(directory_a, S_IRWXU);
    if (create_directory == -1)
    {
        printf("Erro ao criar diretorio a.\n");
        exit(1);
    }

    directory_b = "so/b";
    create_directory = mkdir(directory_b, S_IRWXU);
    if (create_directory == -1)
    {
        printf("Erro ao criar diretorio b.\n");
        exit(1);
    }
                 
    directory_c = "so/c";
    create_directory = mkdir(directory_c, S_IRWXU);
    if (create_directory == -1)
    {
        printf("Erro ao criar diretorio c.\n");
        exit(1);
    }
      
    //cria os arquivos

    creat("so/a/arqa.txt", mode);
    creat("so/b/arqb.txt", mode);
    creat("so/c/arqc.txt", mode);

    
    //abre os arquivos

    file_a = open("so/a/arqa.txt", O_RDWR);
    file_b = open("so/b/arqb.txt", O_RDWR);
    file_c = open("so/c/arqc.txt", O_RDWR);


    //escreve nos arquivos

    write(file_a, write_a, strlen(write_a));
    write(file_b, write_b, strlen(write_b));
    write(file_c, write_c, strlen(write_c));

    
    //fecha arquivos 

    close(file_a);
    close(file_b);
    close(file_c);
    
    //busca e mostra os atributos

    printf("digite qual arquivo gostaria de ver os atributos(a, b, c): ");
    scanf("%c%*c", &option);

    if (option == 'a')
    {
        if (stat("so/a/arqa.txt", &stats) == 0)
        {
            printFileAttributes(directory_a, stats);
        }
        else
        {
            printf("erro ao encontrar arquivo.\n");
            exit(1);
        }
    }
    else if (option == 'b')
    {
        if (stat("so/b/arqb.txt", &stats) == 0)
         {
             printFileAttributes(directory_b, stats);
         }
         else
         {
             printf("erro ao encontrar arquivo.\n");
             exit(1);
         }
    }
    else if (option == 'c')
    {
        if (stat("so/c/arqc.txt", &stats) == 0)
         {
             printFileAttributes(directory_c, stats);
         }
         else
         {
             printf("erro ao encontrar arquivo.\n");
             exit(1);
         }

    }
    else
    {
        printf("arquivo inexistente.\n");
        exit(1);
    }
    
    //busca arquivo
    
    printf("\n");
    printf("digite qual arquivo gostaria de modificar(a, b, c): ");
    scanf("%c%*c", &option_search);
    if (option_search == 'a')
    {
        search_file = open("so/a/arqa.txt", O_RDWR);
        strcat(file_search, "so/a/arqa.txt");
        if (search_file == -1)
        {
            printf("erro ao encontrar arquivo.\n");
            exit(1);
        }
    }
    else if (option_search == 'b')
    {
        search_file = open("so/b/arqb.txt", O_RDWR);
        strcat(file_search, "so/b/arqb.txt");
        if (search_file == -1)
         {
             printf("erro ao encontrar arquivo.\n");
             exit(1);
         }
    }
    else if (option_search == 'c')
    {
        search_file = open("so/c/arqc.txt", O_RDWR);
        strcat(file_search, "so/c/arqc.txt");
        if (search_file == -1)
         {
             printf("erro ao encontrar arquivo.\n");
             exit(1);
         }
    }
    else
    {
        printf("arquivo inexistente.\n");
        exit(1);
    }

    //mostra conteudo do arquivo

    char* conteudo = (char *)calloc(100, sizeof(char));
    tamanho = read(search_file, conteudo, 100);
    conteudo[tamanho] = '\0';
    printf("conteudo do arquivo encontrado: ");
    printf("%s\n", conteudo);
    free(conteudo);

    //modifica arquivo

    FILE* fp = fopen(file_search, "r+");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    
    fseek(fp, 0, SEEK_END);
    char s[100];
    int tam = ftell(fp);
    rewind(fp);
    int pos = ftell(fp);
    while(fscanf(fp, "%s%*c", s) == 1 && strcmp(s, "escrito") != 0)
    {
        pos = ftell(fp);
    }
    int tamcp = tam - ftell(fp);
    char* copia = malloc(tamcp);
    fread(copia, tamcp, 1, fp);
    fseek(fp, pos, SEEK_SET);
    fprintf(fp, "%s", "modificado ");
    fwrite(copia, tamcp, 1, fp);
    free(copia);

    fclose(fp);

    //exibe arquivo modificado
    printf("conteudo do arquivo modificado: ");
    fp = fopen(file_search, "r");
    while(fscanf(fp, "%[^\n]", s) == 1)
        printf("%s\n", s);
    fclose(fp);


    return 0;
}
