#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10 // capacidade máxima da mochila

// ----------------------------------------------------------
// STRUCT: Representa um item do inventário do jogador
// ----------------------------------------------------------
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// ----------------------------------------------------------
// FUNÇÃO: Busca sequencial por nome
// Retorna o índice do item encontrado ou -1 se não existir
// ----------------------------------------------------------
int buscarItem(struct Item mochila[], int qtdItens, char nome[]) {
    for (int i = 0; i < qtdItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// ----------------------------------------------------------
// FUNÇÃO: Cadastra um novo item na mochila
// ----------------------------------------------------------
void inserirItem(struct Item mochila[], int *qtdItens) {
    if (*qtdItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    struct Item novo;

    printf("Digite o nome do item: ");
    scanf("%s", novo.nome);

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    scanf("%s", novo.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*qtdItens] = novo;
    (*qtdItens)++;

    printf("Item adicionado com sucesso!\n");
}

// ----------------------------------------------------------
// FUNÇÃO: Remove um item pelo nome
// ----------------------------------------------------------
void removerItem(struct Item mochila[], int *qtdItens) {
    if (*qtdItens == 0) {
        printf("A mochila está vazia. Nada a remover.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nome);

    int pos = buscarItem(mochila, *qtdItens, nome);

    if (pos == -1) {
        printf("Item não encontrado!\n");
        return;
    }

    // Move os itens seguintes uma posição para trás
    for (int i = pos; i < *qtdItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*qtdItens)--;
    printf("Item removido com sucesso!\n");
}

// ----------------------------------------------------------
// FUNÇÃO: Lista todos os itens da mochila
// ----------------------------------------------------------
void listarItens(struct Item mochila[], int qtdItens) {
    if (qtdItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\n=== Itens na Mochila ===\n");
    for (int i = 0; i < qtdItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("========================\n");
}

// ----------------------------------------------------------
// FUNÇÃO PRINCIPAL (menu)
// ----------------------------------------------------------
int main() {
    struct Item mochila[MAX_ITENS];
    int qtdItens = 0;
    int opcao;

    do {
        printf("\n=== Sistema de Inventário ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtdItens);
                listarItens(mochila, qtdItens);
                break;

            case 2:
                removerItem(mochila, &qtdItens);
                listarItens(mochila, qtdItens);
                break;

            case 3:
                listarItens(mochila, qtdItens);
                break;

            case 4: {
                char nome[30];
                printf("Digite o nome do item a buscar: ");
                scanf("%s", nome);
                int pos = buscarItem(mochila, qtdItens, nome);
                if (pos != -1) {
                    printf("Item encontrado: %s | Tipo: %s | Quantidade: %d\n",
                           mochila[pos].nome, mochila[pos].tipo, mochila[pos].quantidade);
                } else {
                    printf("Item não encontrado!\n");
                }
                break;
            }

            case 0:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
