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

int buscar_maior_no(No *vetor_nos, int n_vertices)
{
    float maior = INFINITO;
    int pos_maior = INVALIDO;

    for(int i = 0; i < n_vertices; i++)
    {
        if(!vetor_nos[i].marcado && vetor_nos[i].valor > maior)
        {
            maior = vetor_nos[i].valor;
            pos_maior = i;
        }
    }

    return pos_maior;
}

No *dijkstra(int pos_atual, int pos_final, int n_vertices, float matriz[][n_vertices])
{
    No *vetor_nos;
    vetor_nos = NULL;

    if(pos_atual != INVALIDO)
    {
        vetor_nos = alocar_no(n_vertices);
        vetor_nos[pos_atual].indice = pos_atual;
        vetor_nos[pos_atual].valor = 1;

        for(int it = 0; it < n_vertices && !vetor_nos[pos_final].marcado && pos_atual != INVALIDO; it++)
        {
            vetor_nos[pos_atual].marcado = 1;
            for(int i = 0; i < n_vertices; i++)
            {
                if(matriz[pos_atual][i])
                {
                    float valor_aresta = vetor_nos[pos_atual].valor * matriz[pos_atual][i];

                    if(!vetor_nos[i].marcado && valor_aresta > vetor_nos[i].valor)
                    {
                        vetor_nos[i].valor = valor_aresta;
                        vetor_nos[i].indice = pos_atual;
                    }
                }
            }
            // for(int i = 0; i < n_vertices; i++)
            //     printf("\n[%d] até [%d] com custo [%lf]", i, vetor_nos[i].indice, vetor_nos[i].valor);
            // printf("\n");

            pos_atual = buscar_maior_no(vetor_nos, n_vertices);
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
        for(int j = n_vertices - 1; j < n_vertices; j++)
        {
            printf("\n[%d] até [%d]: ", i, j);
            vetor_nos = dijkstra(i, j, n_vertices, matriz);

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