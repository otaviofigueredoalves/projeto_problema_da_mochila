#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char nome[50];
    float peso;
    int valor;
    int ativo;
} Item;

const char *MOCHILA = "mochila.bin";

void cadastrarItens()
{
    Item objeto;
    FILE *arquivo = fopen(MOCHILA, "ab");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    printf("Digite o nome do item:\n");
    fgets(objeto.nome, 50, stdin);
    objeto.nome[strcspn(objeto.nome, "\n")] = 0;

    printf("Digite o peso:\n");
    scanf("%f", &objeto.peso);

    printf("Digite o valor:\n");
    scanf("%d", &objeto.valor);
    getchar();

    objeto.ativo = 1;

    fwrite(&objeto, sizeof(Item), 1, arquivo);
    fclose(arquivo);
    printf("Item cadastrado!\n");
}

void exibirItens()
{
    Item objeto;
    FILE *arquivo = fopen(MOCHILA, "rb");

    if(arquivo == NULL){
        printf("Nenhum item cadastrado.\n");
        return;
    }

    printf("@ LISTA DE ITENS\n");
    while(fread(&objeto, sizeof(Item),1,arquivo)){
        if(objeto.ativo == 1){
            printf("NOME: %s\nPESO: %.2f\nVALOR: %d\n",objeto.nome, objeto.peso, objeto.valor);
        }
    }
    fclose(arquivo);
}

int calcularPeso()
{
    Item objeto;
    float pesoTotal = 0.0;
    FILE *arquivo = fopen(MOCHILA, "rb");

    if(arquivo == NULL){
        return 0.0;
    }

    while(fread(&objeto, sizeof(Item), 1, arquivo)){
        if(objeto.ativo == 1){
            pesoTotal += objeto.peso;
        }
    }
    fclose(arquivo);
    return pesoTotal;
}

void deletarItens()
{
    Item objeto;
    int encontrado = 0;
    char nomeBuscado[50];
    FILE *arquivo = fopen(MOCHILA, "r+b");
    
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    printf("\nDigite o nome do item:");
    fgets(nomeBuscado, 50, stdin);
    nomeBuscado[strcspn(nomeBuscado, "\n")] = 0;
    while(fread(&objeto, sizeof(Item), 1, arquivo)){
        if(strcmp(objeto.nome, nomeBuscado) == 0){
            fseek(arquivo, -sizeof(Item), SEEK_CUR);
            objeto.ativo = 0;
            fwrite(&objeto, sizeof(Item), 1, arquivo);
            encontrado = 1;
            break;
        }
    }
    fclose(arquivo);
    printf(encontrado ? "Item apagado!\n" : "Item não encontrado\n");
}

int main()
{
    int choose;

    printf("@ ESCOLHA UMA AÇÃO\n");
    printf("[0] -> CRIAR\n");
    printf("[1] -> LISTAR\n");
    printf("[2] -> ATUALIZAR\n");
    printf("[3] -> DELETE\n");
    scanf("%d", &choose);
    getchar();

    switch (choose)
    {
        case 0:
            printf("@ CADASTRAR ESCOLHIDO\n");
            cadastrarItens();
            break;
        case 1:
            printf("@ LISTAR ITENS\n");
            exibirItens();
            break;
        case 3:
            printf("@ Deltar Itens\n");
            deletarItens();
    }

    // float pesoMochila = calcularPesoTotal();
    // printf("Peso total é: %.2f kg\n", pesoMochila);
}