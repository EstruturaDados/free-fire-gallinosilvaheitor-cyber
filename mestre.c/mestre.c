#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição do máximo de componentes permitido
#define MAX_COMPONENTES 20
#define CHAVE_BUSCA "Chip Central" // Componente chave para ativar a torre

// 1. Criação de structs: Componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // De 1 a 10
} Componente;

// Protótipos das Funções
void mostrarComponentes(Componente componentes[], int n);
void cadastrarComponentes(Componente componentes[], int *n);
long bubbleSortNome(Componente componentes[], int n);
long insertionSortTipo(Componente componentes[], int n);
long selectionSortPrioridade(Componente componentes[], int n);
int buscaBinariaPorNome(Componente componentes[], int n, const char chave[]);
void menuPrincipal(Componente componentes[], int n);
void copiarComponentes(Componente destino[], const Componente origem[], int n);

// --- Funções de Utilitário ---

/**
 * @brief Exibe o vetor de componentes formatado.
 * @param componentes Array de Componente a ser exibido.
 * @param n Número de componentes.
 */
void mostrarComponentes(Componente componentes[], int n) {
    if (n == 0) {
        printf("\n[INFO] Nenhum componente cadastrado.\n");
        return;
    }
    printf("\n--- Componentes Atuais da Torre (%d itens) ---\n", n);
    printf("| %-28s | %-18s | %-10s |\n", "Nome", "Tipo", "Prioridade");
    printf("|------------------------------|--------------------|------------|\n");
    for (int i = 0; i < n; i++) {
        printf("| %-28s | %-18s | %-10d |\n", componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
    printf("-------------------------------------------------------------------\n");
}

/**
 * @brief Realiza uma cópia profunda dos componentes.
 * Evita que a ordenação em uma opção afete o array original para as outras opções.
 */
void copiarComponentes(Componente destino[], const Componente origem[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i]; // Cópia de struct
    }
}

// 2. Entrada dos dados: Cadastro de componentes
/**
 * @brief Permite o cadastro de componentes necessários para a montagem da torre.
 * @param componentes Array de Componente onde os dados serão armazenados.
 * @param n Ponteiro para o número atual de componentes.
 */
void cadastrarComponentes(Componente componentes[], int *n) {
    char nome[30], tipo[20], entrada_prioridade[5];
    int prioridade;
    
    // Lista de componentes pré-definidos para facilitar o teste
    Componente pre_definidos[] = {
        {"Cabo de Forca", "Suporte", 4},
        {"Painel Solar", "Propulsao", 8},
        {"Chip Central", "Controle", 10}, // Item-chave
        {"Estrutura Base", "Suporte", 7},
        {"Modulo de Navegacao", "Controle", 9},
        {"Motor de Impulso", "Propulsao", 6},
        {"Antena de Comunicacao", "Controle", 5}
    };
    int total_pre = sizeof(pre_definidos) / sizeof(pre_definidos[0]);
    
    // Limita para não exceder o MAX_COMPONENTES
    int itens_a_cadastrar = (total_pre > MAX_COMPONENTES) ? MAX_COMPONENTES : total_pre;

    if (*n + itens_a_cadastrar > MAX_COMPONENTES) {
         itens_a_cadastrar = MAX_COMPONENTES - *n; // Ajusta se já houver itens
    }

    // Copia os itens pré-definidos
    for (int i = 0; i < itens_a_cadastrar; i++) {
        componentes[*n + i] = pre_definidos[i];
    }
    
    *n += itens_a_cadastrar;
    
    printf("\n✅ [STATUS] %d componentes iniciais foram carregados (Incluindo o \"%s\").\n", *n, CHAVE_BUSCA);
    mostrarComponentes(componentes, *n);

    // Opcional: permitir cadastro manual
    /*
    printf("\n--- Cadastro Manual de Componentes ---\n");
    while (*n < MAX_COMPONENTES) {
        printf("Cadastrar componente #%d? (s/n): ", *n + 1);
        char resp;
        if (scanf(" %c", &resp) != 1 || (resp != 's' && resp != 'S')) {
            break;
        }
        
        // Limpar buffer
        while (getchar() != '\n'); 

        // Nome
        printf("Nome: ");
        if (fgets(nome, sizeof(nome), stdin) == NULL) break;
        nome[strcspn(nome, "\n")] = 0;
        
        // Tipo
        printf("Tipo (ex: Controle, Suporte, Propulsao): ");
        if (fgets(tipo, sizeof(tipo), stdin) == NULL) break;
        tipo[strcspn(tipo, "\n")] = 0;
        
        // Prioridade
        printf("Prioridade (1-10): ");
        if (fgets(entrada_prioridade, sizeof(entrada_prioridade), stdin) == NULL) break;
        prioridade = atoi(entrada_prioridade);
        if (prioridade < 1 || prioridade > 10) {
            printf("Prioridade invalida. Componente nao cadastrado.\n");
            continue;
        }

        // Armazenamento
        strcpy(componentes[*n].nome, nome);
        strcpy(componentes[*n].tipo, tipo);
        componentes[*n].prioridade = prioridade;
        (*n)++;
    }
    printf("\n✅ Cadastro de componentes finalizado. Total de %d itens.\n", *n);
    */
}

// --- Algoritmos de Ordenação (3. Opções de ordenação & 5. Medição de desempenho) ---

/**
 * @brief Ordena os componentes por Nome (string) usando Bubble Sort.
 * @param componentes Array de Componente.
 * @param n Número de componentes.
 * @return Número de comparações realizadas.
 */
long bubbleSortNome(Componente componentes[], int n) {
    long comparacoes = 0;
    Componente temp;
    int trocou;

    for (int i = 0; i < n - 1; i++) {
        trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++; // Comparação de strings
            // Comparação de string: strcoll() ou strcmp()
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca
                temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
                trocou = 1;
            }
        }
        if (trocou == 0) break; // Otimização: se não houve troca, o array está ordenado
    }
    return comparacoes;
}

/**
 * @brief Ordena os componentes por Tipo (string) usando Insertion Sort.
 * @param componentes Array de Componente.
 * @param n Número de componentes.
 * @return Número de comparações realizadas.
 */
long insertionSortTipo(Componente componentes[], int n) {
    long comparacoes = 0;
    int i, j;
    Componente chave;

    for (i = 1; i < n; i++) {
        chave = componentes[i];
        j = i - 1;

        // Compara a chave com cada elemento à esquerda até que um menor/igual seja encontrado
        while (j >= 0) {
            comparacoes++; // Comparação de strings
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j = j - 1;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
    return comparacoes;
}

/**
 * @brief Ordena os componentes por Prioridade (int) usando Selection Sort.
 * @param componentes Array de Componente.
 * @param n Número de componentes.
 * @return Número de comparações realizadas.
 */
long selectionSortPrioridade(Componente componentes[], int n) {
    long comparacoes = 0;
    int i, j, min_idx;
    Componente temp;

    // Um por um move a fronteira do sub-array não ordenado
    for (i = 0; i < n - 1; i++) {
        // Encontra o elemento com a maior prioridade no array não ordenado
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            comparacoes++; // Comparação de inteiros
            // Queremos a maior prioridade (10 é mais prioritário que 1)
            if (componentes[j].prioridade > componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }

        // Troca o elemento de maior prioridade encontrado com o elemento atual (i)
        if (min_idx != i) {
            temp = componentes[min_idx];
            componentes[min_idx] = componentes[i];
            componentes[i] = temp;
        }
    }
    return comparacoes;
}

// 4. Busca binária
/**
 * @brief Realiza busca binária por Nome. Aplicável apenas após ordenação por nome.
 * @param componentes Array de Componente (deve estar ORDENADO por nome).
 * @param n Número de componentes.
 * @param chave String (nome) a ser buscada.
 * @return Índice do componente encontrado ou -1 se não encontrado.
 */
int buscaBinariaPorNome(Componente componentes[], int n, const char chave[]) {
    int inicio = 0;
    int fim = n - 1;
    int meio;
    int comparacoes = 0;
    int resultado = -1;

    printf("\n--- Buscando o componente-chave: \"%s\" ---\n", chave);
    
    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2; // Prevenção de overflow
        comparacoes++;
        
        // Compara o nome no meio com a chave
        int cmp = strcmp(componentes[meio].nome, chave);

        if (cmp == 0) {
            resultado = meio; // Encontrado!
            break;
        } else if (cmp < 0) {
            inicio = meio + 1; // Ignora metade esquerda
        } else {
            fim = meio - 1; // Ignora metade direita
        }
    }

    printf("[BUSCA] Total de comparacoes na busca binaria: %d\n", comparacoes);
    return resultado;
}


// --- Função Principal e Menu ---

/**
 * @brief Gerencia o menu interativo e o fluxo do programa.
 * @param componentes Array de Componente original.
 * @param n Número de componentes.
 */
void menuPrincipal(Componente componentes_originais[], int n) {
    int escolha;
    Componente componentes_temp[MAX_COMPONENTES]; // Array para cópia e manipulação

    do {
        printf("\n\n=============== 🚀 MODO FUGA - ULTIMA SAFE ZONE 🚀 ===============\n");
        printf("| Escolha sua Estrategia de Montagem da Torre:\n");
        printf("| 1. Estrategia 'Alfabetica' (Bubble Sort: Ordenar por Nome)\n");
        printf("| 2. Estrategia 'Agrupamento' (Insertion Sort: Ordenar por Tipo)\n");
        printf("| 3. Estrategia 'Urgencia' (Selection Sort: Ordenar por Prioridade)\n");
        printf("| 4. Iniciar Busca Binaria pelo Componente-Chave\n");
        printf("| 0. Sair do Jogo\n");
        printf("=================================================================\n");
        printf("Sua escolha: ");
        
        if (scanf("%d", &escolha) != 1) {
            printf("\n[ERRO] Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n'); // Limpar buffer
            continue;
        }
        
        if (n == 0 && escolha != 0) {
             printf("\n[ALERTA] Por favor, cadastre os componentes primeiro.\n");
             continue;
        }

        long comparacoes = 0;
        clock_t inicio, fim;
        double tempo_execucao;

        // Copia os dados originais para evitar modificar o array principal em cada teste
        copiarComponentes(componentes_temp, componentes_originais, n);

        switch (escolha) {
            case 1: // Bubble Sort por Nome
                printf("\n>>> 1. Estrategia 'Alfabetica' Ativada (Bubble Sort por Nome) <<<\n");
                inicio = clock();
                comparacoes = bubbleSortNome(componentes_temp, n);
                fim = clock();
                tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                
                // 6. Montagem final: Exibir todos os componentes ordenados
                mostrarComponentes(componentes_temp, n);

                // 5. Medição de desempenho: Feedback educacional
                printf("\n--- Desempenho do Algoritmo Bubble Sort ---\n");
                printf("Tempo de Execucao: %.6f segundos\n", tempo_execucao);
                printf("Numero de Comparacoes: %ld\n", comparacoes);
                printf("--------------------------------------------\n");
                break;

            case 2: // Insertion Sort por Tipo
                printf("\n>>> 2. Estrategia 'Agrupamento' Ativada (Insertion Sort por Tipo) <<<\n");
                inicio = clock();
                comparacoes = insertionSortTipo(componentes_temp, n);
                fim = clock();
                tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                
                // 6. Montagem final: Exibir todos os componentes ordenados
                mostrarComponentes(componentes_temp, n);

                // 5. Medição de desempenho: Feedback educacional
                printf("\n--- Desempenho do Algoritmo Insertion Sort ---\n");
                printf("Tempo de Execucao: %.6f segundos\n", tempo_execucao);
                printf("Numero de Comparacoes: %ld\n", comparacoes);
                printf("----------------------------------------------\n");
                break;

            case 3: // Selection Sort por Prioridade
                printf("\n>>> 3. Estrategia 'Urgencia' Ativada (Selection Sort por Prioridade) <<<\n");
                inicio = clock();
                comparacoes = selectionSortPrioridade(componentes_temp, n);
                fim = clock();
                tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                
                // 6. Montagem final: Exibir todos os componentes ordenados
                mostrarComponentes(componentes_temp, n);

                // 5. Medição de desempenho: Feedback educacional
                printf("\n--- Desempenho do Algoritmo Selection Sort ---\n");
                printf("Tempo de Execucao: %.6f segundos\n", tempo_execucao);
                printf("Numero de Comparacoes: %ld\n", comparacoes);
                printf("----------------------------------------------\n");
                break;

            case 4: // Busca Binária
                // 4. Aplicável apenas após a ordenação por nome.
                printf("\n>>> 4. Preparando Busca Binaria: Reordenando por Nome (Bubble Sort) <<<\n");
                // Reordenar por nome para garantir que a busca binária funcione
                bubbleSortNome(componentes_temp, n);
                
                int indice_chave = buscaBinariaPorNome(componentes_temp, n, CHAVE_BUSCA);

                // 6. Confirmar visualmente a presença do componente-chave
                if (indice_chave != -1) {
                    printf("\n🎉 SUCESSO! 🎉\n");
                    printf("O componente-chave para ativar a torre, \"%s\", foi ENCONTRADO no indice %d.\n", CHAVE_BUSCA, indice_chave);
                    printf("Montagem da Torre de Resgate iniciada!\n");
                    // Exibe o item encontrado
                     printf("| Chave: %-28s | Tipo: %-18s | Prioridade: %-10d |\n", 
                        componentes_temp[indice_chave].nome, 
                        componentes_temp[indice_chave].tipo, 
                        componentes_temp[indice_chave].prioridade);
                } else {
                    printf("\n❌ FALHA! ❌\n");
                    printf("O componente-chave \"%s\" nao foi encontrado. A torre nao pode ser ativada.\n", CHAVE_BUSCA);
                    printf("Verifique se a ordenacao por nome foi realizada corretamente.\n");
                }
                break;
                
            case 0:
                printf("\n[FIM DE JOGO] Fuja da ilha ou tente novamente! Ate logo!\n");
                break;

            default:
                printf("\n[ALERTA] Opcao invalida. Por favor, escolha uma opcao valida do menu.\n");
                break;
        }
    } while (escolha != 0);
}

/**
 * @brief Função principal do programa.
 */
int main() {
    Componente componentes[MAX_COMPONENTES];
    int num_componentes = 0;

    // 2. Entrada dos dados (Cadastro)
    cadastrarComponentes(componentes, &num_componentes);
    
    // Inicia o menu interativo
    menuPrincipal(componentes, num_componentes);

    return 0;
}