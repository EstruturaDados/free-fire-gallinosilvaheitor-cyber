#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// -----------------------------------------------------------
// STRUCTS
// -----------------------------------------------------------

// Estrutura que representa um item da mochila
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Nó da lista encadeada
struct No {
    struct Item dados;
    struct No* proximo;
};

// -----------------------------------------------------------
// VARIÁVEIS GLOBAIS
// -----------------------------------------------------------
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// -----------------------------------------------------------
// FUNÇÕES PARA MOCHILA COM VETOR
// -----------------------------------------------------------

void inserirItemVetor(struct Item mochila[], int *qtdItens) {
    if (*qtdItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    struct Item novo;
    printf("Digite o nome do item: ");
    scanf("%s", novo.nome);
    printf("Digite o tipo do item: ");
    scanf("%s", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*qtdItens] = novo;
    (*qtdItens)++;
    printf("Item adicionado com sucesso!\n");
}

void listarItensVetor(struct Item mochila[], int qtdItens) {
    if (qtdItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    printf("\n=== Itens na Mochila (Vetor) ===\n");
    for (int i = 0; i < qtdItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
