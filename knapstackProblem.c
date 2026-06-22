#include <stdio.h>
#include <string.h>

#define MAX_ITENS 100

typedef struct {
    char nome[50];
    int peso;
    int valor;
    int ativo;
} Item;

int capacidade_mochila = 0;
int mochila[MAX_ITENS];
int total_na_mochila = 0;

void cadastrarItens(Item catalogo[], int *total_catalogo) {
    if (*total_catalogo >= MAX_ITENS) {
        printf("Limite máximo do catálogo atingido!\n");
        return;
    }

    Item novo;
    printf("\n@ CADASTRAR ITEM \n");
    printf("Digite o nome do item: ");
    fgets(novo.nome, 50, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Digite o peso (kg): ");
    scanf("%d", &novo.peso);

    printf("Digite o valor de importância: ");
    scanf("%d", &novo.valor);
    getchar();

    novo.ativo = 1;
    catalogo[*total_catalogo] = novo;
    (*total_catalogo)++;

    printf("Item cadastrado com sucesso!\n");
}

void exibirItens(Item catalogo[], int total_catalogo) {
    printf("\n @ ITENS DISPONÍVEIS\n");
    int encontrou = 0;
    for (int i = 0; i < total_catalogo; i++) {
        if (catalogo[i].ativo == 1) {
            printf("[%d] %s | Peso: %d kg | Valor: %d\n", i, catalogo[i].nome, catalogo[i].peso, catalogo[i].valor);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum item disponível.\n");
    }
}

int calcularPeso(Item catalogo[], int indices_mochila[], int qtd_mochila) {
    int peso_total = 0;
    for (int i = 0; i < qtd_mochila; i++) {
        int indice_item = indices_mochila[i];
        peso_total += catalogo[indice_item].peso;
    }
    return peso_total;
}

int calcularValor(Item catalogo[], int indices_mochila[], int qtd_mochila) {
    int valor_total = 0;
    for (int i = 0; i < qtd_mochila; i++) {
        int indice_item = indices_mochila[i];
        valor_total += catalogo[indice_item].valor;
    }
    return valor_total;
}

void gerarRelatorio(Item catalogo[], int indices_mochila[], int qtd_mochila, int capacidade) {
    printf("\n @ RELATÓRIO FINAL\n");
    if (qtd_mochila == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    printf("Itens escolhidos:\n");
    for (int i = 0; i < qtd_mochila; i++) {
        int idx = indices_mochila[i];
        printf("- %s\n", catalogo[idx].nome);
    }

    int peso_total = calcularPeso(catalogo, indices_mochila, qtd_mochila);
    int valor_total = calcularValor(catalogo, indices_mochila, qtd_mochila);
    float porcentagem = ((float)peso_total / capacidade) * 100;

    printf("\nPeso total: %d kg\n", peso_total);
    printf("Valor total: %d\n", valor_total);
    printf("Capacidade utilizada: %.2f%%\n", porcentagem);
}

void atualizarItens(Item catalogo[], int total_catalogo) {
    int id;
    exibirItens(catalogo, total_catalogo);
    printf("\nDigite o número [#] do item que deseja alterar: ");
    scanf("%d", &id);
    getchar();

    if (id >= 0 && id < total_catalogo && catalogo[id].ativo == 1) {
        printf("Novo nome: ");
        fgets(catalogo[id].nome, 50, stdin);
        catalogo[id].nome[strcspn(catalogo[id].nome, "\n")] = 0;

        printf("Novo peso: ");
        scanf("%d", &catalogo[id].peso);

        printf("Novo valor: ");
        scanf("%d", &catalogo[id].valor);
        getchar();

        printf("Item atualizado!\n");
    } else {
        printf("Item inválido!\n");
    }
}
void selecionarItemMochila(Item catalogo[], int total_catalogo) {
    if (capacidade_mochila <= 0) {
        printf("Defina a capacidade da mochila primeiro!\n");
        return;
    }

    int id;
    exibirItens(catalogo, total_catalogo);
    printf("\nDigite o número [#] do item para adicionar à mochila: ");
    scanf("%d", &id);
    getchar();

    if (id >= 0 && id < total_catalogo && catalogo[id].ativo == 1) {
        for (int i = 0; i < total_na_mochila; i++) {
            if (mochila[i] == id) {
                printf("O item já está na mochila!\n");
                return;
            }
        }

        int peso_atual = calcularPeso(catalogo, mochila, total_na_mochila);
        if (peso_atual + catalogo[id].peso > capacidade_mochila) {
            printf("Capacidade da mochila excedida!\n");
        } else {
            mochila[total_na_mochila] = id;
            total_na_mochila++;
            printf("Item adicionado com sucesso!\n");
        }
    } else {
        printf("Item inválido!\n");
    }
}
void removerDaMochila(Item catalogo[]) {
    if (total_na_mochila == 0) {
        printf("A mochila já está vazia.\n");
        return;
    }

    int id;
    printf("\n @ ITENS NA MOCHILA\n");
    for (int i = 0; i < total_na_mochila; i++) {
        int idx = mochila[i];
        printf("[%d] %s\n", idx, catalogo[idx].nome);
    }

    printf("\nDigite o número [#] do item que deseja remover: ");
    scanf("%d", &id);
    getchar();

    int encontrou = 0;
    for (int i = 0; i < total_na_mochila; i++) {
        if (mochila[i] == id) {
            encontrou = 1;
            for (int j = i; j < total_na_mochila - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            total_na_mochila--;
            printf("Item removido da mochila!\n");
            break;
        }
    }
    if (!encontrou) {
        printf("Item não está na mochila.\n");
    }
}

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(Item catalogo[], int indices[], int baixo, int alto) {
    int pivo = catalogo[indices[alto]].valor;
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (catalogo[indices[j]].valor >= pivo) {
            i++;
            trocar(&indices[i], &indices[j]);
        }
    }
    trocar(&indices[i + 1], &indices[alto]);
    return (i + 1);
}

void quickSort(Item catalogo[], int indices[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(catalogo, indices, baixo, alto);
        quickSort(catalogo, indices, baixo, pi - 1);
        quickSort(catalogo, indices, pi + 1, alto);
    }
}

void estrategiaAutomatica(Item catalogo[], int total_catalogo) {
    if (capacidade_mochila <= 0) {
        printf("Defina a capacidade da mochila primeiro!\n");
        return;
    }

    total_na_mochila = 0; // Limpa a mochila atual

    // Criar um array temporário de índices dos itens ativos
    int indices_ordenados[MAX_ITENS];
    int cont = 0;
    for (int i = 0; i < total_catalogo; i++) {
        if (catalogo[i].ativo == 1) {
            indices_ordenados[cont++] = i;
        }
    }
    if (cont > 0) {
        quickSort(catalogo, indices_ordenados, 0, cont - 1);
    }

    int peso_atual = 0;
    for (int i = 0; i < cont; i++) {
        int id = indices_ordenados[i];
        if (peso_atual + catalogo[id].peso <= capacidade_mochila) {
            mochila[total_na_mochila++] = id;
            peso_atual += catalogo[id].peso;
        }
    }
    printf("Mochila preenchida automaticamente priorizando itens de maior valor!\n");
}
int main() {
    Item catalogo[MAX_ITENS];
    int total_catalogo = 0;
    int escolha;

    do {
        printf("\n========================================\n");
        printf("  SISTEMA DE PLANEJAMENTO DE MOCHILA\n");
        printf("========================================\n");
        printf("[1] Cadastrar Item no Catálogo\n");
        printf("[2] Exibir Catálogo\n");
        printf("[3] Editar Item do Catálogo (Nível 2)\n");
        printf("[4] Definir Capacidade da Mochila\n");
        printf("[5] Adicionar Item na Mochila\n");
        printf("[6] Remover Item da Mochila (Nível 3)\n");
        printf("[7] Seleção Automática de Itens (Nível 4)\n");
        printf("[8] Gerar Relatório Final\n");
        printf("[0] Sair\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &escolha) != 1) {
            getchar(); // Previne loop infinito se o usuário digitar letras
            continue;
        }
        getchar();

        switch (escolha) {
            case 1:
                cadastrarItens(catalogo, &total_catalogo);
                break;
            case 2:
                exibirItens(catalogo, total_catalogo);
                break;
            case 3:
                atualizarItens(catalogo, total_catalogo);
                break;
            case 4:
                printf("\nDigite a capacidade máxima da mochila (kg): ");
                scanf("%d", &capacidade_mochila);
                getchar();
                printf("Capacidade definida para %d kg!\n", capacidade_mochila);
                total_na_mochila = 0; 
                break;
            case 5:
                selecionarItemMochila(catalogo, total_catalogo);
                break;
            case 6:
                removerDaMochila(catalogo);
                break;
            case 7:
                estrategiaAutomatica(catalogo, total_catalogo);
                break;
            case 8:
                gerarRelatorio(catalogo, mochila, total_na_mochila, capacidade_mochila);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (escolha != 0);

    return 0;
}