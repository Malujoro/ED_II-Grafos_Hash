#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lista/lista.h"

#define HASTES 3

typedef struct noGrafo
{
    int info;
    int peso;
} NoGrafo;

typedef struct noHanoi
{
    int *vetor;
    Lista *lista;
} NoHanoi;


NoHanoi *alocar_no_hanoi(int tam)
{
    NoHanoi *vetor;
    vetor = (NoHanoi *) malloc(sizeof(NoHanoi) * tam);

    if(!vetor)
    {
        printf("Erro ao alocar vetor de Nós de Hanoi");
        exit(EXIT_FAILURE);
    }

    return vetor;
}

NoHanoi **alocar_matriz(int tam)
{
    NoHanoi **matriz;
    matriz = (NoHanoi **) malloc(sizeof(NoHanoi *) * tam);

    if(!matriz)
    {
        printf("Erro ao alocar matriz de Nós de Hanoi");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < tam; i++)
        matriz[i] = alocar_no_hanoi(1);

    return matriz;
}

int *alocar_int(int tam)
{
    int *vetor;
    vetor = (int *) malloc(sizeof(int) * tam);

    if(!vetor)
    {
        printf("Erro ao alocar vetor de int");
        exit(EXIT_FAILURE);
    }

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

void exibir_matriz(NoHanoi **matriz, int linhas, int colunas)
{
    for(int i = 0; i < linhas; i++)
    {
        printf("\n[%dª] Configuração: ", i);
        exibir_vetor(matriz[i]->vetor, colunas);
        printf("Pode ir para: ");
        lista_exibir(matriz[i]->lista);
        printf("\n");
    }
}

int vertice_existe(int *vetor, int tam, NoHanoi **vertices, int tot_vertices)
{
    int existe = -1, iguais;

    for(int i = 0; i < tot_vertices && existe == -1; i++)
    {
        iguais = 0;
        for(int j = 0; j < tam; j++)
        {
            if(vertices[i]->vetor[j] == vetor[j])
                iguais += 1;
        }
        if(iguais == tam)
            existe = i;
    }

    return existe;
}

int pode_mover(int *vetor, int tam, int disco, int *posicoes)
{
    int pode = 1;

    posicoes[vetor[disco] - 1] = 0;
    for(int i = disco + 1; i < tam && pode; i++)
    {
        if(vetor[disco] == vetor[i])
            pode = 0;

        posicoes[vetor[i] - 1] = 0;
    }

    return pode;
}

void calcula_movimentos(NoHanoi *vetor_hanoi, int n_discos, NoHanoi **vertices, int *tot_vertices)
{
    int posicoes[] = {1, 1, 1};

    printf("\n\nConfiguração [%d]: ", *tot_vertices);
    exibir_vetor(vetor_hanoi->vetor, n_discos);
    printf("\n");
    printf("\nPossibilidades:\n");

    for(int i = n_discos - 1; i >= 0; i--)
    {
        if(pode_mover(vetor_hanoi->vetor, n_discos, i, posicoes))
        {
            for(int j = 0; j < HASTES; j++)
            {
                if(posicoes[j])
                {
                    int *copia = copiar_vetor(vetor_hanoi->vetor, n_discos);
                    copia[i] = j + 1;
                    
                    int pos_existe = vertice_existe(copia, n_discos, vertices, *tot_vertices);

                    if(pos_existe == -1)
                    {
                        vertices[*tot_vertices]->vetor = copia;
                        vertices[*tot_vertices]->lista = lista_criar();
                        lista_inserir(&vetor_hanoi->lista, *tot_vertices);

                        printf("[%d] - ", *tot_vertices);
                        exibir_vetor(copia, n_discos);

                        (*tot_vertices)++;

                        calcula_movimentos(vertices[(*tot_vertices) - 1], n_discos, vertices, tot_vertices);
                        printf("\nFinalizando Possibilidades do [");
                        exibir_vetor(vetor_hanoi->vetor, n_discos);
                        printf("]\n");
                    }
                    else
                    {
                        lista_inserir(&vetor_hanoi->lista, pos_existe);
                        printf("[%d] - ", pos_existe);
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

// void movimentos_possiveis(NoHanoi **vertices, int tot_vertices, int n_discos)
// {
//     int diferente;

//     for(int i = 0; i < tot_vertices; i++)
//     {
//         for(int j = i + 1; j < tot_vertices - 1; j++)
//         {
//             int posicoes[] = {1, 1, 1};
//             int pode = pode_mover(vertices[i]->vetor, n_discos, i, posicoes);

//             diferente = 0;
//             for(int k = 0; k < n_discos && diferente <= 1; k++)
//             {
//                 if(posicoes[k] && vertices[i]->vetor[k] != vertices[j]->vetor[k])
//                     diferente++;
//             }
//             if(diferente <= 1)
//             {
//                 exibir_vetor(vertices[i]->vetor, n_discos);
//                 printf(" -> ");
//                 exibir_vetor(vertices[j]->vetor, n_discos);
//                 printf("\n");
//             }
//         }
//     }
// }

int main()
{
    int n_discos = 3;

    int *vetor;
    vetor = alocar_int(n_discos);
    for(int i = 0; i < n_discos; i++)
        vetor[i] = 1;

    int total_vertices = pow(3, n_discos);
    int n_vertices = 1;

    NoHanoi **matriz = alocar_matriz(total_vertices);
    matriz[0]->vetor = vetor;
    matriz[0]->lista = lista_criar();

    calcula_movimentos(matriz[0], n_discos, matriz, &n_vertices);

    // movimentos_possiveis(matriz, n_vertices, n_discos);

    exibir_matriz(matriz, n_vertices, n_discos);

    return 0;
}