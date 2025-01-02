#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HASTES 3

int **alocar_matriz(int tam)
{
    int **vetor;
    vetor = (int **) malloc(sizeof(int*) * tam);

    if(!vetor)
    {
        printf("Erro ao alocar matriz de int");
        exit(EXIT_FAILURE);
    }

    return vetor;
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
    printf("\n");
}

void exibir_matriz(int **matriz, int linhas, int colunas)
{
    for(int i = 0; i < linhas; i++)
    {
        printf("\n[%dª] Configuração: ", i + 1);
        exibir_vetor(matriz[i], colunas);
    }
}

int vertice_existe(int *vetor, int tam, int **vertices, int tot_vertices)
{
    int existe = 0, iguais;

    for(int i = 0; i < tot_vertices && !existe; i++)
    {
        iguais = 0;
        for(int j = 0; j < tam; j++)
        {
            if(vertices[i][j] == vetor[j])
                iguais += 1;
        }
        existe = iguais == tam;
    }

    return existe;
}

int pode_mover(int *vetor, int tam, int disco, int *posicoes)
{
    int pode = 1;

    posicoes[vetor[disco] - 1] = 0;
    for(int i = disco+1; i < tam && pode; i++)
    {
        if(vetor[disco] == vetor[i])
            pode = 0;

        posicoes[vetor[i] - 1] = 0;
    }

    return pode;
}

void calcula_movimentos(int *vetor, int n_discos, int **vertices, int *tot_vertices)
{
    int posicoes[] = {1, 1, 1};

    for(int i = n_discos - 1; i >= 0; i--)
    {
        int pode = pode_mover(vetor, n_discos, i, posicoes);
        // if(pode)
        // {
        //     // printf("\nConfiguração: ");
        //     // exibir_vetor(vetor, n_discos);

        //     // printf("\nPode ir para: ");
        //     // exibir_vetor(posicoes, HASTES);
        //     // printf("\n");
        // }

        for(int j = 0; j < HASTES; j++)
        {
            if(posicoes[j])
            {
                int *copia = copiar_vetor(vetor, n_discos);
                copia[i] = j+1;

                if(!vertice_existe(copia, n_discos, vertices, *tot_vertices))
                {
                    vertices[*tot_vertices] = copia;
                    (*tot_vertices)++;

                    // printf("\nCópia: ");
                    // exibir_vetor(copia, HASTES);
                    // printf("\n");

                    calcula_movimentos(copia, n_discos, vertices, tot_vertices);
                }
                else
                    free(copia);
            }
        }
    }
}


int main()
{
    int n_discos = 3;

    int *vetor;
    vetor = alocar_int(n_discos);
    for(int i = 0; i < n_discos; i++)
        vetor[i] = 1;

    int total_vertices = pow(3, n_discos);
    int n_vertices = 1;

    int **matriz = alocar_matriz(total_vertices);
    matriz[0] = vetor;

    calcula_movimentos(vetor, n_discos, matriz, &n_vertices);

    exibir_matriz(matriz, n_vertices, n_discos);

    return 0;
}