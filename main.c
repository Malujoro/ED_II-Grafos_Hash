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
        printf("Erro ao alocar vetor de nós");
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

void exibir_djikstra(int pos_atual, No *vetor_nos)
{
    if(pos_atual != -1)
    {
        exibir_djikstra(vetor_nos[pos_atual].indice, vetor_nos);
        printf("[%d] -> ", pos_atual);
    }
}

void djikstra(int *inicial, int *final, int n_discos, int **vertices, int **matriz, int n_vertices)
{
    int pos_inicial, pos_atual, pos_final;

    pos_inicial = vertice_posicao(inicial, n_discos, vertices, n_vertices);
    pos_atual = pos_inicial;
    pos_final = vertice_posicao(final, n_discos, vertices, n_vertices);

    No *vetor_nos;
    vetor_nos = alocar_no(n_vertices);

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

    // printf("\n[%d] -> ", pos_inicial);

    printf("\n");
    exibir_djikstra(pos_atual, vetor_nos);
    printf("\n");
    // while(pos_atual != -1 && pos_atual != pos_inicial)
    // {
    //     printf("[%d] <- ", pos_atual);
    //     pos_atual = vetor_nos[pos_atual].indice;
    // }
    // printf("[%d].\n", pos_final);
}

void ford_moore_bellman()
{

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
    
    int teste[] = {2, 3, 1};
    // djikstra(inicial, final, n_discos, vertices, matriz, n_vertices);

    for(int i = 0; i < n_vertices; i++)
    {
        printf("\n[%d] até [%d]: ", i, pos_final);
        djikstra(vertices[i], final, n_discos, vertices, matriz, n_vertices);
    }


    return 0;
}