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

void atualizarItens()
{
    char nomeBusca[50];
    char escolhas[20]; //Usuario digita quais campos quer atualizar
    Item objeto;

    FILE *arquivo=fopen(MOCHILA, "rb+");

    if (arquivo==NULL){
        printf("Erro: A mochila está vazia.\n");
        return;
    }

    printf("Digite o nome do item que deseja editar:\n");
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")]=0;

    int achou=0;

    while (fread(&objeto, sizeof(Item), 1, arquivo)){
        if (strcmp(objeto.nome, nomeBusca)==0 && objeto.ativo==1){
            achou=1;

            printf("\nItem Encontrado\n");
            printf("[1] Nome | [2] Peso | [3]Valor\n");
            printf("Digite os números dos campos que quer alterar: ");
            fgets(escolhas, 20, stdin);


            if (strchr(escolhas, '1')!=NULL){
                printf("Digite o novo nome:\n");
                fgets(objeto.nome, 50, stdin);
                objeto.nome[strcspn(objeto.nome, "\n")]=0;
            }

            if (strchr(escolhas, '2') != NULL) {
                printf("Digite o novo peso:\n");
                scanf("%f", &objeto.peso);
                getchar();
            }
            
            if (strchr(escolhas, '3') != NULL) {
                printf("Digite o novo valor:\n");
                scanf("%d", &objeto.valor);
                getchar();
            }

            if (strchr(escolhas, '1') == NULL && strchr(escolhas, '2') == NULL && strchr(escolhas, '3') == NULL) {
                printf("Nenhuma opção válida foi digitada.\n");
                fclose(arquivo);
                return;
            }

            
            fseek(arquivo, -sizeof(Item), SEEK_CUR);
            fwrite(&objeto, sizeof(Item), 1, arquivo);
            break;
        }
    }

    fclose(arquivo);

    if (achou){
        printf("Campo(s) atualizado(s)!\n");
    } else {
        printf("Aviso: Item não encontrado\n");
    }
}
float calcularPeso()
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
        case 2:
            printf("@ATUALIZAR ITEM\n");
            atualizarItens();
            break;
        case 3:
            printf("@ DELETAR ITENS\n");
            deletarItens();
    }

    float pesoMochila = calcularPeso();
    printf("Peso total é: %.2f kg\n", pesoMochila);
}