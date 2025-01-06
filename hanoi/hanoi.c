#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hanoi.h"
#include "../extras/extras.h"

#define HASTES 3

int vertice_posicao(int *vetor, int tam, int **vertices, int tot_vertices)
{
    int posicao = -1;

    for(int i = 0; i < tot_vertices && posicao == -1; i++)
    {
        if(vetor_igual(vertices[i], vetor, tam))
            posicao = i;
    }

    return posicao;
}

int pode_mover(int *vetor, int tam, int disco, int *posicoes)
{
    int pode = 1;

    posicoes[vetor[disco] - 1] = 0;

    // Verifica se não há nenhum "disco menor" logo acima dele
    // Caso não tenha, ele "cancela" a possibilidade de ir pra cima de um menor em outra haste
    for(int i = disco + 1; i < tam && pode; i++)
    {
        if(vetor[disco] == vetor[i])
            pode = 0;

        posicoes[vetor[i] - 1] = 0;
    }

    return pode;
}

void calcula_movimentos(int *vetor_hanoi, int n_discos, int **vertices, int *tot_vertices, int **matriz)
{
    int posicoes[HASTES];

    for(int i = 0; i < HASTES; i++)
        posicoes[i] = 1;

    printf("\n\nConfiguração [%d]: ", *tot_vertices);
    exibir_vetor(vetor_hanoi, n_discos);
    printf("\n");
    printf("\nPossibilidades:\n");

    // Verifica todos os discos, começando do menor
    int pos_atual = (*tot_vertices) - 1;

    for(int i = n_discos - 1; i >= 0; i--)
    {
        // Caso possa mover, verifica se é um movimento "novo" e atribui essa possibilidade de movimento ao vértice atual
        if(pode_mover(vetor_hanoi, n_discos, i, posicoes))
        {
            for(int j = 0; j < HASTES; j++)
            {
                if(posicoes[j])
                {
                    int *copia = copiar_vetor(vetor_hanoi, n_discos);
                    copia[i] = j + 1;
                    
                    int pos_vertice = vertice_posicao(copia, n_discos, vertices, *tot_vertices);

                    if(pos_vertice == -1)
                    {
                        vertices[*tot_vertices] = copia;
                        matriz[pos_atual][*tot_vertices] = 1;

                        printf("[%d] - ", *tot_vertices);
                        exibir_vetor(copia, n_discos);

                        (*tot_vertices)++;

                        calcula_movimentos(vertices[(*tot_vertices) - 1], n_discos, vertices, tot_vertices, matriz);

                        printf("\nFinalizando Possibilidades do [");
                        exibir_vetor(vetor_hanoi, n_discos);
                        printf("]\n");
                    }
                    else
                    {
                        matriz[pos_atual][pos_vertice] = 1;
                        printf("[%d] - ", pos_vertice);
                        exibir_vetor(copia, n_discos);

                        printf("X");
                        free(copia);
                    }
                    printf("\n");
                }
            }
        }
    }
}

int gerar_possibilidades(int n_discos, int ***vetor_vertices, int ***matriz_adj)
{
    int *vetor;
    vetor = alocar_int(n_discos);
    for(int i = 0; i < n_discos; i++)
        vetor[i] = 1;

    int total_vertices = pow(3, n_discos);
    int n_vertices = 1;

    int **vertices = alocar_matriz(total_vertices, 0);
    vertices[0] = vetor;

    int **matriz = alocar_matriz(total_vertices, total_vertices);

    calcula_movimentos(vertices[0], n_discos, vertices, &n_vertices, matriz);

    *vetor_vertices = vertices;
    *matriz_adj = matriz;

    return n_vertices;
}

// int main()
// {
//     int n_discos = 3;

//     int **vertices, **matriz;

//     int n_vertices = gerar_possibilidades(n_discos, &vertices, &matriz);

//     exibir_matriz(vertices, matriz, n_vertices, n_discos);

//     return 0;
// }