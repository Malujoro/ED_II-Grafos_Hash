#include <stdio.h>
#include <stdlib.h>
#include "hanoi/hanoi.h"
#include "extras/extras.h"

#define HASTES 3

typedef struct no
{
    int indice;
    int valor;
} No;

void djikstra(int *inicial, int *final, int n_discos, int **vertices, int **matriz, int n_vertices)
{
    int pos_inicial, pos_final;

    pos_inicial = vertice_posicao(inicial, n_discos, vertices, n_vertices);
    pos_final = vertice_posicao(final, n_discos, vertices, n_vertices);

    // for(int i = 0; i < )
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
    inicial =  inicializar_vetor(HASTES, 1);
    final = inicializar_vetor(HASTES, 3);
    
    djikstra(inicial, final, n_discos, vertices, matriz, n_vertices);


    return 0;
}