#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct funcionario
{
    char matricula[7];
    char nome[100];
    char funcao[50];
    float salario;
} Funcionario;

typedef double tempo_tipo;

tempo_tipo calcula_tempo(clock_t inicio, clock_t fim)
{
    return ((tempo_tipo) (fim - inicio)) / CLOCKS_PER_SEC * 1000 * 1000;
}

Funcionario **alocar_vetor_func(int tam)
{
    Funcionario **vetor = (Funcionario **) malloc(sizeof(Funcionario *) * tam);

    if(!vetor)
    {
        printf("Não foi possível alocar um vetor");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < tam; i++)
        vetor[i] = NULL;

    return vetor;
}

Funcionario *alocar_funcionario(int num)
{
    Funcionario *func = (Funcionario *) malloc(sizeof(Funcionario));

    if(!func)
    {
        printf("Não foi possível alocar um funcionário");
        exit(EXIT_FAILURE);
    }

    sprintf(func->matricula, "%06d", num);
    func->matricula[0] = '1';

    sprintf(func->nome, "Nome %d", num);
    sprintf(func->funcao, "Funcao %d", num);
    func->salario = num * 100;
    return func;
}

void *desalocar(Funcionario **vetor, int tam)
{
    for(int i = 0; i < tam; i++)
    {
        if(vetor[i] != NULL)
        {
            free(vetor[i]);
            vetor[i] = NULL;
        }
    }

    free(vetor);
    return NULL;
}

int str_to_int(char letra)
{
    return letra - '0';
}

void exibir_funcionarios(Funcionario **vetor, int tam)
{
    for(int i = 0; i < tam; i++)
    {
        if(vetor[i] != NULL)
        {
            printf("\n[%dº] [%s] | [%s] | [%s] | [%.2f]", i, vetor[i]->matricula, vetor[i]->nome, vetor[i]->funcao, vetor[i]->salario);
        }
    }
}

int colisao(int posicao, int tam_vet, int acrescimo, int *colisoes, Funcionario **vetor)
{
    if(posicao >= tam_vet)
        posicao -= tam_vet;

    int invalido = 0, inicial = posicao;
    do
    {
        if(vetor[posicao] == NULL)
            invalido = 0;
        else
        {
            posicao += acrescimo;

            if(posicao >= tam_vet)
                posicao -= tam_vet;

            (*colisoes)++;
            invalido = 1;
        }
    }while(invalido && inicial != posicao);

    if(vetor[posicao] != NULL)
        free(vetor[posicao]);

    return posicao;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Hashing com Rotação de 2 dígitos:
void rotacao_dois_digitos(char *matricula, char *mat_rotacionada){
    strcpy(mat_rotacionada, matricula+4);    // copia da posição 4 em diante
    strncat(mat_rotacionada, matricula, 4);  // adiciona os 4 primeiros ao final
}

int hash_rotacao(char *matricula, int tam_vet)
{
    char mat_rotacionada[7];
    rotacao_dois_digitos(matricula, mat_rotacionada);

    int digito2 = str_to_int(mat_rotacionada[1]) * 100;
    int digito4 = str_to_int(mat_rotacionada[3]) * 10;
    int digito6 = str_to_int(mat_rotacionada[5]);

    int resto = ((digito2 + digito4 + digito6) % tam_vet) + 1;

    return resto;
}

Funcionario **aplicar_hash_a(int tam_vet, int quant, int *colisoes, tempo_tipo *media)
{
    Funcionario **vetor = alocar_vetor_func(tam_vet);
    *colisoes = 0;

    *media = 0;
    clock_t inicio, fim;
    tempo_tipo tempo_gasto;

    for(int i = 0; i < quant; i++)
    {
        Funcionario *func = alocar_funcionario(i);

        inicio = clock();
        
        int posicao = hash_rotacao(func->matricula, tam_vet);

        posicao = colisao(posicao, tam_vet, str_to_int(func->matricula[0]), colisoes, vetor);
        
        vetor[posicao] = func;

        fim = clock();
        
        tempo_gasto = calcula_tempo(inicio, fim);
        (*media) += tempo_gasto;
    }

    (*media) /= quant;
    
    return vetor;
}
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Hashing com Fold Shift        
int hash_fold_shift(char *matricula, int tam_vet)
{
    int grupo1 = (str_to_int(matricula[0]) * 100) + (str_to_int(matricula[2]) * 10) + str_to_int(matricula[5]);

    int grupo2 = (str_to_int(matricula[1]) * 100) + (str_to_int(matricula[3]) * 10) + str_to_int(matricula[4]);

    return ((grupo1 + grupo2) % tam_vet) + 1;
}

Funcionario **aplicar_hash_b(int tam_vet, int quant, int *colisoes, tempo_tipo *media)
{
    Funcionario **vetor = alocar_vetor_func(tam_vet);
    *colisoes = 0;

    *media = 0;
    clock_t inicio, fim;
    tempo_tipo tempo_gasto;

    for(int i = 0; i < quant; i++)
    {
        Funcionario *func = alocar_funcionario(i);

        inicio = clock();

        int posicao = hash_fold_shift(func->matricula, tam_vet);
        
        posicao = colisao(posicao, tam_vet, 7, colisoes, vetor);

        vetor[posicao] = func;

        fim = clock();

        tempo_gasto = calcula_tempo(inicio, fim);
        (*media) += tempo_gasto;
    }

    (*media) /= quant;

    return vetor;
}
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

Funcionario **(*funcao_hash[2])(int, int, int *, tempo_tipo *) = {aplicar_hash_a, aplicar_hash_b};

int main()
{
    int quant = 1000, colisoes, quant_exec = 30;
    
    int tam[2] = {101, 150};

    Funcionario **vetor;

    tempo_tipo media, media2;
    
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            media2 = 0;
            for(int k = 0; k < quant_exec; k++)
            {
                colisoes = 0;
                vetor = (funcao_hash[i])(tam[j], quant, &colisoes, &media);
                // exibir_funcionarios(vetor, tam[j]);
                vetor = desalocar(vetor, tam[j]);
                media2 += media;
            }
            media2 /= quant_exec;
            printf("[Hash %c][Tam %d][%d colisões][%lf microssegundos]\n", 'A' + i, tam[j], colisoes, media2);
        }
    }

    return 0;
}