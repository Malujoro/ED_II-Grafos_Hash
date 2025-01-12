#include <stdio.h>
#include <stdlib.h>
#include "hanoi/hanoi.h"
#include "extras/extras.h"
#include <limits.h>

#define HASTES 3

typedef struct no
{
    int indice;
    int valor;
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
        vetor[i].indice = -1;
        vetor[i].valor = INT_MAX;
        vetor[i].marcado = 0;
    }

    return vetor;
}

int buscar_menor_no(No *vetor_nos, int n_vertices)
{
    int menor = INT_MAX;
    int pos_menor = -1;

    for(int i = 0; i < n_vertices; i++)
    {
        if(!vetor_nos[i].marcado && vetor_nos[i].valor < menor)
        {
            menor = vetor_nos[i].valor;
            pos_menor = i;
        }
    }

    return pos_menor;
}

void exibir_caminho(int pos_atual, No *vetor_nos, int pos_inicial, int **vertices, int n_discos)
{
    if(pos_atual != -1)
    {
        if(pos_atual != pos_inicial)
            exibir_caminho(vetor_nos[pos_atual].indice, vetor_nos, pos_inicial, vertices, n_discos);

        // for(int i = 0; i < n_discos; i++)
        //     printf("[%d], ", vertices[pos_atual][i]);
        // printf("\n");
        printf("[%d] -> ", pos_atual);
    }
}

No *dijkstra(int *inicial, int *final, int n_discos, int **vertices, int **matriz, int n_vertices)
{
    int pos_inicial, pos_atual;

    pos_inicial = vertice_posicao(inicial, n_discos, vertices, n_vertices);
    pos_atual = pos_inicial;

    No *vetor_nos;
    vetor_nos = NULL;

    if(pos_atual != -1)
    {
        int pos_final = vertice_posicao(final, n_discos, vertices, n_vertices);
        vetor_nos = alocar_no(n_vertices);
        vetor_nos[pos_atual].indice = pos_atual;
        vetor_nos[pos_atual].valor = 0;

        while(pos_atual != pos_final && pos_atual != -1)
        {
            vetor_nos[pos_atual].marcado = 1;
            for(int i = 0; i < n_vertices; i++)
            {
                if(matriz[pos_atual][i])
                {
                    int valor_aresta = vetor_nos[pos_atual].valor + matriz[pos_atual][i];

                    if(!vetor_nos[i].marcado && valor_aresta < vetor_nos[i].valor)
                    {
                        vetor_nos[i].valor = valor_aresta;
                        vetor_nos[i].indice = pos_atual;
                    }
                }
            }
            pos_atual = buscar_menor_no(vetor_nos, n_vertices);
        }
    }

    return vetor_nos;
}

No *ford_moore_bellman(int *inicial, int *final, int n_discos, int **vertices, int **matriz, int n_vertices)
{
    int modificou = 1;

    int pos_inicial = vertice_posicao(inicial, n_discos, vertices, n_vertices);

    No *vetor_nos;
    vetor_nos = NULL;

    if(pos_inicial != -1)
    {
        vetor_nos = alocar_no(n_vertices);
        vetor_nos[pos_inicial].indice = pos_inicial;
        vetor_nos[pos_inicial].valor = 0;

        for(int it = 0; it < n_vertices - 1; it++)
        {
            modificou = 0;
            for(int i = 0; i < n_vertices; i++)
            {
                if(i != pos_inicial)
                {
                    for(int j = 0; j < n_vertices; j++)
                    {
                        if(vetor_nos[j].indice != -1 && matriz[j][i] && ((vetor_nos[j].valor + matriz[j][i]) < vetor_nos[i].valor))
                        {
                            vetor_nos[i].indice = j;
                            vetor_nos[i].valor = matriz[j][i] + vetor_nos[j].valor;
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
    int n_discos = 3;

    int **vertices, **matriz;

    int n_vertices = gerar_possibilidades(n_discos, &vertices, &matriz);

    exibir_matriz(vertices, matriz, n_vertices, n_discos);

    int *inicial, *final;
    inicial =  inicializar_vetor(n_discos, 1);
    final = inicializar_vetor(n_discos, 3);
    int pos_final = vertice_posicao(final, n_discos, vertices, n_vertices);
    
    No *vetor_nos;
    for(int i = 0; i < n_vertices; i++)
    {
        printf("\n[%d] até [%d]: ", i, pos_final);
        vetor_nos = dijkstra(vertices[i], final, n_discos, vertices, matriz, n_vertices);

        if(vetor_nos != NULL)
        {
            int pos_inicial = vertice_posicao(vertices[i], n_discos, vertices, n_vertices);
            printf("\n");
            exibir_caminho(pos_final, vetor_nos, pos_inicial, vertices, n_discos);
            printf("\n");

            free(vetor_nos);
            vetor_nos = NULL;
        }
    }

    for(int i = 0; i < n_vertices; i++)
    {
        printf("\n[%d] até [%d]: ", i, pos_final);
        vetor_nos = ford_moore_bellman(vertices[i], final, n_discos, vertices, matriz, n_vertices);

        if(vetor_nos != NULL)
        {
            int pos_inicial = vertice_posicao(vertices[i], n_discos, vertices, n_vertices);
            printf("\n");
            exibir_caminho(pos_final, vetor_nos, pos_inicial, vertices, n_discos);
            printf("\n");

            free(vetor_nos);
            vetor_nos = NULL;
        }
    }

    printf("\n");
    
    return 0;
}