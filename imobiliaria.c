#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------
// Estrutura
// -----------------------------
typedef struct No {
    char endereco[100];
    int quartos;
    float aluguel;
    struct No* prox;
} No;

typedef struct {
    No* inicio;
    int tamanho;
} Lista;

// -----------------------------
// Inicialização
// -----------------------------
void inicializar(Lista* lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
}

// -----------------------------
// Criar nó
// -----------------------------
No* criarNo(char endereco[], int quartos, float aluguel) {
    No* novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro de alocação!\n");
        exit(1);
    }

    strcpy(novo->endereco, endereco);
    novo->quartos = quartos;
    novo->aluguel = aluguel;
    novo->prox = NULL;

    return novo;
}

// -----------------------------
// Inserir no início
// -----------------------------
void inserir(Lista* lista, char endereco[], int quartos, float aluguel) {
    No* novo = criarNo(endereco, quartos, aluguel);

    novo->prox = lista->inicio;
    lista->inicio = novo;
    lista->tamanho++;
}

// -----------------------------
// Exibir lista
// -----------------------------
void exibir(Lista* lista) {
    No* aux = lista->inicio;

    if (aux == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    while (aux != NULL) {
        printf("Endereço: %s | Quartos: %d | Aluguel: R$ %.2f\n",
               aux->endereco, aux->quartos, aux->aluguel);
        aux = aux->prox;
    }
}

// -----------------------------
// Buscar por endereço
// -----------------------------
No* buscar(Lista* lista, char endereco[]) {
    No* aux = lista->inicio;

    while (aux != NULL) {
        if (strcmp(aux->endereco, endereco) == 0) {
            return aux;
        }
        aux = aux->prox;
    }

    return NULL;
}

// -----------------------------
// Remover
// -----------------------------
void remover(Lista* lista, char endereco[]) {
    No* atual = lista->inicio;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->endereco, endereco) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Elemento não encontrado!\n");
        return;
    }

    if (anterior == NULL) {
        lista->inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    lista->tamanho--;

    printf("Removido com sucesso!\n");
}

// -----------------------------
// RELATÓRIO (Obrigatório)
// Total do aluguel mensal
// -----------------------------
void relatorio(Lista* lista) {
    No* aux = lista->inicio;
    float total = 0;

    while (aux != NULL) {
        total += aux->aluguel;
        aux = aux->prox;
    }

    printf("Total do aluguel mensal: R$ %.2f\n", total);
}

// -----------------------------
// Persistência: Salvar em arquivo
// -----------------------------
void salvarArquivo(Lista* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar!\n");
        return;
    }

    No* aux = lista->inicio;
    while (aux != NULL) {
        fprintf(arquivo, "%s,%d,%.2f\n", aux->endereco, aux->quartos, aux->aluguel);
        aux = aux->prox;
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

// -----------------------------
// Persistência: Carregar do arquivo
// -----------------------------
void carregarArquivo(Lista* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Arquivo não encontrado, iniciando com lista vazia.\n");
        return;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char endereco[100];
        int quartos;
        float aluguel;
        if (sscanf(linha, "%99[^,],%d,%f", endereco, &quartos, &aluguel) == 3) {
            inserir(lista, endereco, quartos, aluguel);
        }
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}

// -----------------------------
// Menu
// -----------------------------
void menu() {
    printf("\n--- MENU ---\n");
    printf("1 - Inserir\n");
    printf("2 - Exibir\n");
    printf("3 - Buscar\n");
    printf("4 - Remover\n");
    printf("5 - Relatório\n");
    printf("0 - Sair\n");
}

// -----------------------------
// MAIN
// -----------------------------
int main() {
    Lista lista;
    inicializar(&lista);

    // Carregar dados do arquivo (Persistência)
    carregarArquivo(&lista, "imobiliaria.txt");

    // Carga inicial (OBRIGATÓRIO) - apenas se a lista estiver vazia
    if (lista.tamanho == 0) {
        inserir(&lista, "Rua A, 123", 2, 1500.00);
        inserir(&lista, "Av. B, 456", 3, 2200.00);
        inserir(&lista, "Praça C, 789", 1, 800.00);
    }

    int op;
    char endereco[100];
    int quartos;
    float aluguel;

    do {
        menu();
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("Endereço: ");
                scanf(" %[^\n]", endereco);  // Para ler string com espaços
                printf("Quartos: ");
                scanf("%d", &quartos);
                printf("Aluguel: ");
                scanf("%f", &aluguel);
                inserir(&lista, endereco, quartos, aluguel);
                break;

            case 2:
                exibir(&lista);
                break;

            case 3:
                printf("Endereço para buscar: ");
                scanf(" %[^\n]", endereco);

                No* encontrado = buscar(&lista, endereco);

                if (encontrado)
                    printf("Encontrado: %s | Quartos: %d | Aluguel: R$ %.2f\n",
                           encontrado->endereco, encontrado->quartos, encontrado->aluguel);
                else
                    printf("Não encontrado!\n");
                break;

            case 4:
                printf("Endereço para remover: ");
                scanf(" %[^\n]", endereco);
                remover(&lista, endereco);
                break;

            case 5:
                relatorio(&lista);
                break;

        }

    } while(op != 0);

    // Salvar dados no arquivo antes de sair (Persistência)
    salvarArquivo(&lista, "imobiliaria.txt");

    return 0;
}