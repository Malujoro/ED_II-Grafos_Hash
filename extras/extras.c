#include <stdio.h>
#include <stdlib.h>
#include "extras.h"

int *alocar_int(int tam)
{
    int *vetor;
    vetor = (int *) calloc(sizeof(int), tam);

    if(!vetor)
    {
        printf("Erro ao alocar vetor de int");
        exit(EXIT_FAILURE);
    }

    return vetor;
}

int **alocar_matriz(int linhas, int colunas)
{
    int **matriz;
    matriz = (int **) malloc(sizeof(int *) * linhas);

    if(!matriz)
    {
        printf("Erro ao alocar matriz de int");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < colunas; i++)
        matriz[i] = alocar_int(colunas);

    return matriz;
}

void liberar_vetor(int **vetor)
{
    free(*vetor);
    *vetor = NULL;
}

void liberar_matriz(int ***matriz, int linhas)
{
    for(int i = 0; i < linhas; i++)
        liberar_vetor(&((*matriz)[i]));
    
    *matriz = NULL;
}

int *inicializar_vetor(int tam, int num)
{
    int *vetor;
    vetor = alocar_int(tam);

    for(int i = 0; i < tam; i++)
        vetor[i] = num;

    return vetor;
}

int *copiar_vetor(int *vetor, int tam)
{
    int *copia;
    copia = alocar_int(tam);

    for(int i = 0; i < tam; i++)
        copia[i] = vetor[i];

    return copia;
}

void exibir_vetor(int *vetor, int tam)
{
    for(int i = 0; i < tam; i++)
        printf("%d, ", vetor[i]);
}

void exibir_caminhos(int *vetor, int tam)
{
    for(int i = 0; i < tam; i++)
    {
        if(vetor[i])
            printf("%d -> ", i);
    }
}

void exibir_matriz(int **vertices, int **matriz, int n_vertices, int n_discos)
{
    for(int i = 0; i < n_vertices; i++)
    {
        printf("\n[%dª] Configuração: ", i);
        exibir_vetor(vertices[i], n_discos);
        printf("Pode ir para: ");
        exibir_caminhos(matriz[i], n_vertices);
        printf("\n");
    }
}

int vetor_igual(int *vetor1, int *vetor2, int tam)
{
    int igual = 1;

    for(int j = 0; j < tam && igual; j++)
        igual = vetor1[j] == vetor2[j];

    return igual;
}
