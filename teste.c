#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// -----------------------------
// Estrutura
// -----------------------------
typedef struct No {
    char id[30];         
    char tipo[20];       
    char endereco[100];  
    int quartos;         
    float qtd;           
    float valorCompra;   
    struct No* prox;
} No;

typedef struct {
    No* inicio;
    int tamanho;
    int proximo_id_casa;
    int proximo_id_apto;
} Lista;

// -----------------------------
// Inicialização
// -----------------------------
void inicializar(Lista* lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
    lista->proximo_id_casa = 1;
    lista->proximo_id_apto = 1;
}

// -----------------------------
// Criar nó
// -----------------------------
No* criarNo(char id[], char tipo[], char endereco[], int quartos, float qtd, float valor) {
    No* novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro de alocação!\n");
        exit(1);
    }

    strcpy(novo->id, id);
    strcpy(novo->tipo, tipo);
    strcpy(novo->endereco, endereco);
    novo->quartos = quartos;
    novo->qtd = qtd;
    novo->valorCompra = valor;
    novo->prox = NULL;

    return novo;
}

// -----------------------------
// Inserir
// -----------------------------
void inserir(Lista* lista, char tipo[], char endereco[], int quartos, float qtd, float valor) {
    char id_gerado[30];
    
    if (strcmp(tipo, "casa") == 0) {
        sprintf(id_gerado, "%s%d", tipo, lista->proximo_id_casa++);
    } else if (strcmp(tipo, "apto") == 0) {
        sprintf(id_gerado, "%s%d", tipo, lista->proximo_id_apto++);
    } else {
        sprintf(id_gerado, "%s_%d", tipo, lista->tamanho + 1); 
    }

    No* novo = criarNo(id_gerado, tipo, endereco, quartos, qtd, valor);

    novo->prox = lista->inicio;
    lista->inicio = novo;
    lista->tamanho++;
}

// -----------------------------
// Exibir
// -----------------------------
void exibir(Lista* lista) {
    No* aux = lista->inicio;

    if (aux == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    while (aux != NULL) {
        printf("ID: %-7s | Quartos: %d | Meses: %.0f | Aluguel: R$ %.2f | Endereço: %s\n",
               aux->id, aux->quartos, aux->qtd, aux->valorCompra, aux->endereco);
        aux = aux->prox;
    }
}

// -----------------------------
// Buscar
// -----------------------------
No* buscar(Lista* lista, char id_busca[]) {
    No* aux = lista->inicio;

    while (aux != NULL) {
        if (strcmp(aux->id, id_busca) == 0) {
            return aux;
        }
        aux = aux->prox;
    }

    return NULL;
}

// -----------------------------
// Remover
// -----------------------------
void remover(Lista* lista, char id_busca[]) {
    No* atual = lista->inicio;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->id, id_busca) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Imóvel não encontrado!\n");
        return;
    }

    if (anterior == NULL) {
        lista->inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    lista->tamanho--;

    printf("Imóvel (ID: %s) removido com sucesso!\n", id_busca);
}

// -----------------------------
// Relatório
// -----------------------------
void relatorio(Lista* lista) {
    No* aux = lista->inicio;
    float total = 0;

    while (aux != NULL) {
        total += aux->qtd * aux->valorCompra;
        aux = aux->prox;
    }

    printf("\nValor total previsto nos contratos: R$ %.2f\n", total);
}

// -----------------------------
// Menu
// -----------------------------
void menu() {
    printf("\n--- Imobiliaria Rafa&James ---\n");
    printf("1 - Cadastrar imóvel\n");
    printf("2 - Exibir imóveis\n");
    printf("3 - Buscar imóvel por ID\n");
    printf("4 - Remover imóvel por ID\n");
    printf("5 - Relatório de faturamento\n");
    printf("0 - Sair\n\nOpção: ");
}

// -----------------------------
// MAIN
// -----------------------------
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    Lista lista;
    inicializar(&lista);

    // Carga inicial
    inserir(&lista, "casa", "Rua das Flores, 123", 3, 12, 1500.00);
    inserir(&lista, "apto", "Av. Central, 45", 2, 24, 2300.00);
    inserir(&lista, "casa", "Praça da Matriz, 7", 4, 6, 3500.00);

    int op, quartos;
    char tipo[20], endereco[100], id_busca[30];
    float qtd, valor;

    do {
        menu();
        scanf(" %d", &op); // CORREÇÃO PRINCIPAL

        switch(op) {
            case 1:
                printf("Tipo (casa/apto): ");
                scanf(" %s", tipo);

                printf("Endereço: ");
                getchar(); // limpa antes do fgets
                fgets(endereco, 100, stdin);
                endereco[strcspn(endereco, "\n")] = 0;

                printf("Quartos: ");
                scanf("%d", &quartos);

                printf("Meses: ");
                scanf("%f", &qtd);

                printf("Valor aluguel: ");
                scanf("%f", &valor);

                inserir(&lista, tipo, endereco, quartos, qtd, valor);
                printf("Imóvel cadastrado!\n");
                break;

            case 2:
                exibir(&lista);
                break;

            case 3: {
                printf("ID para buscar: ");
                scanf("%s", id_busca);

                No* encontrado = buscar(&lista, id_busca);

                if (encontrado) {
                    printf("Encontrado: %s | %s\n", encontrado->id, encontrado->endereco);
                } else {
                    printf("Não encontrado!\n");
                }
                break;
            }

            case 4:
                printf("ID para remover: ");
                scanf("%s", id_busca);
                remover(&lista, id_busca);
                break;

            case 5:
                relatorio(&lista);
                break;

        }

    } while(op != 0);

    return 0;
}