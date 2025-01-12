#include <stdio.h>
#include <stdlib.h>
#include "extras/extras.h"
#include <limits.h>

#define INFINITO -1
#define INVALIDO -1

typedef struct no
{
    int indice;
    float valor;
    int marcado;
} No;

No *alocar_no(int tam)
{
    No *vetor;

    vetor = (No *) malloc(sizeof(No) * tam);

    if(!vetor)
    {
        printf("Erro ao alocar vetor de nós Dijkstra");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < tam; i++)
    {
        vetor[i].indice = INVALIDO;
        vetor[i].valor = INFINITO;
        vetor[i].marcado = 0;
    }

    return vetor;
}

int exibir_caminho(int pos_atual, No *vetor_nos, int pos_inicial)
{
    int retorno = 1;
    if(pos_atual != INVALIDO)
    {
        if(pos_atual != pos_inicial)
            retorno = exibir_caminho(vetor_nos[pos_atual].indice, vetor_nos, pos_inicial);

        if(retorno)
            printf("[%d] -> ", pos_atual);
    }
    else
        retorno = 0;

    return retorno;
}

No *ford_moore_bellman(int pos_inicial, int n_vertices, float matriz[][n_vertices])
{
    int modificou = 1;

    No *vetor_nos;
    vetor_nos = NULL;

    if(pos_inicial != INVALIDO)
    {
        vetor_nos = alocar_no(n_vertices);
        vetor_nos[pos_inicial].indice = pos_inicial;
        vetor_nos[pos_inicial].valor = 1;

        for(int it = 0; it < n_vertices - 1 && modificou; it++)
        {
            // for(int i = 0; i < n_vertices; i++)
            //     printf("\n[%d] até [%d] com custo [%lf]", i, vetor_nos[i].indice, vetor_nos[i].valor);
            // printf("\n");
            modificou = 0;
            for(int i = 0; i < n_vertices; i++)
            {
                if(i != pos_inicial)
                {
                    for(int j = 0; j < n_vertices; j++)
                    {
                        float valor_aresta = vetor_nos[j].valor * matriz[j][i];
                        if(vetor_nos[j].indice != INVALIDO && matriz[j][i] != 0 && (valor_aresta > vetor_nos[i].valor))
                        {
                            vetor_nos[i].indice = j;
                            vetor_nos[i].valor = valor_aresta;
                            modificou = 1;
                        }
                    }
                }
            }
        }
    }

    return vetor_nos;
}

int main()
{
    int n_vertices = 7;

    float matriz[n_vertices][n_vertices];

    for(int i = 0; i < n_vertices; i++)
    {
        for(int j = 0; j < n_vertices; j++)
            matriz[i][j] = 0;
    }

    matriz[0][1] = 0.3;
    matriz[0][2] = 0.5;

    matriz[1][3] = 0.9;
    matriz[1][4] = 0.4;
    matriz[1][5] = 0.7;

    matriz[2][3] = 0.1;
    matriz[2][4] = 0.3;
    matriz[2][5] = 0.4;

    matriz[3][6] = 0.9;
    matriz[4][6] = 0.2;
    matriz[5][6] = 0.5;

    No *vetor_nos;
    for(int i = 0; i < n_vertices; i++)
    {
        for(int j = 0; j < n_vertices; j++)
        {
            printf("\n[%d] até [%d]: ", i, j);
            vetor_nos = ford_moore_bellman(i, n_vertices, matriz);

            if(vetor_nos != NULL)
            {
                printf("\n");
                if(!exibir_caminho(j, vetor_nos, i))
                    printf("Não há caminho válido");
                printf("\n");

                free(vetor_nos);
                vetor_nos = NULL;
            }
        }
    }

    printf("\n");
    
    return 0;
}