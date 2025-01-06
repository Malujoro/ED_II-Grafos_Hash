#include <stdio.h>
#include <stdlib.h>
#include "hanoi/hanoi.h"
#include "extras/extras.h"

#define HASTES 3

void djikstra()
{

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

    return 0;
}