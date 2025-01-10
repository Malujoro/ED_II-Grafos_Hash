#pragma once

int *alocar_int(int tam);
int **alocar_matriz(int linhas, int colunas);
void liberar_vetor(int **vetor);
void liberar_matriz(int ***matriz, int linhas);
int *inicializar_vetor(int tam, int num);
int *copiar_vetor(int *vetor, int tam);
void exibir_vetor(int *vetor, int tam);
void exibir_matriz(int **vertices, int **matriz, int n_vertices, int n_discos);
int vetor_igual(int *vetor1, int *vetor2, int tam);
