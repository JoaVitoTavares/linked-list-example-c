#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* estrutura criada - item da lista */
typedef struct reg {
    int chave;
    struct reg *proximo;
} registro;

/* variaveis globais */
registro *inicio; /* ponteiro para o primeiro item da lista */
registro *fim;    /* ponteiro para o ultimo item da lista */
int controle;

/* prototipos */
int seleciona_menu(void);
void inclui_item(void);
void exclui_item(void);
void lista(void);
void pesquisa_valor(void);
registro *percorre_lista(int);
void display(registro *);
registro *localiza_item(int);
void elimina_lista(void);

/* Funcao para limpar a tela */
void clear_screen() {
    system("clear"); // For Unix-like systems
    // system("cls"); // For Windows
}

int seleciona_menu(void) {
    char s;
    clear_screen();
    printf("\n\n");
    printf("1. Inserir um item\n");
    printf("2. Deletar um item\n");
    printf("3. Listar itens\n");
    printf("4. Pesquisar\n");
    printf("5. Sair\n");
    do {
        printf("\nOpcao : ");
        s = getchar();
    } while (s < '0' || s > '5');
    clear_screen();
    return s - '0';
}

void inclui_item(void) {
    registro *aux;
    aux = (registro *)malloc(sizeof(registro));
    if (!aux) {
        printf("\n\nSem Memoria\n");
        printf("<=======Digite qualquer tecla para continuar=======>");
        getchar();
        exit(0);
    }
    printf("\n\n");
    printf("\nInsira o valor : ");
    scanf("%d", &aux->chave);
    if (fim == NULL) {
        inicio = aux;
    } else
        fim->proximo = aux;
    aux->proximo = NULL;
    fim = aux;
}

void exclui_item(void) {
    registro *anterior, *aux;
    int val;
    controle = 0;
    if (inicio == NULL) {
        printf("\n\nLista Vazia!\n");
        printf("<=======Digite qualquer tecla para continuar=======>");
        getchar();
        return;
    }
    printf("\n\n");
    printf("\nInsira o valor a excluir : ");
    scanf("%d", &val);
    anterior = localiza_item(val);
    if (anterior != NULL) {
        if (controle == 1) {
            inicio = inicio->proximo;
            if (inicio == NULL)
                fim = NULL;
            free(anterior);
        } else {
            aux = anterior->proximo;
            anterior->proximo = aux->proximo;
            if (aux->proximo == NULL)
                fim = anterior;
            free(aux);
        }
    }
}

registro *localiza_item(int val) {
    registro *aux, *anterior;
    anterior = aux = inicio;
    if (val == inicio->chave) {
        controle = 1;
        return inicio;
    } else
        aux = aux->proximo;
    while (aux) {
        if (val == aux->chave)
            return anterior;
        anterior = aux;
        aux = aux->proximo;
    }
    printf("\n\nValor nao encontrado!\n");
    printf("<=======Digite qualquer tecla para continuar=======>");
    getchar();
    return NULL;
}

void lista(void) {
    registro *aux;
    aux = inicio;
    if (inicio == NULL) {
        printf("\n\nLista Vazia!\n");
        printf("<=======Digite qualquer tecla para continuar=======>");
        getchar();
        return;
    }
    while (aux) {
        display(aux);
        aux = aux->proximo;
    }
    printf("\n\n<=======Digite qualquer tecla para continuar=======>");
    getchar();
}

void display(registro *aux) {
    printf("[%d]", aux->chave);
}

void pesquisa_valor(void) {
    int val;
    registro *aux;
    if (inicio == NULL) {
        printf("\n\nLista Vazia!\n");
        printf("<=======Digite qualquer tecla para continuar=======>");
        getchar();
        return;
    }
    printf("\n\n");
    printf("\nInsira o valor a procurar: ");
    scanf("%d", &val);
    aux = percorre_lista(val);
    if (aux == NULL) {
        printf("\n\nValor nao encontrado!\n");
        printf("<=======Digite qualquer tecla para continuar=======>");
        getchar();
    } else {
        display(aux);
        printf("\n\n");
        printf("<=======Digite qualquer tecla para continuar=======>");
        getchar();
    }
}

registro *percorre_lista(int val) {
    registro *aux;
    aux = inicio;
    while (aux) {
        if (val == aux->chave)
            return aux;
        aux = aux->proximo;
    }
    return NULL;
}

void elimina_lista() {
    registro *aux;
    aux = inicio;
    while (aux) {
        inicio = aux;
        aux = aux->proximo;
        free(inicio);
    }
}

int main(void) {
    inicio = fim = NULL;
    for (;;) {
        switch (seleciona_menu()) {
            case 1:
                inclui_item();
                break;
            case 2:
                exclui_item();
                break;
            case 3:
                lista();
                break;
            case 4:
                pesquisa_valor();
                break;
            case 5:
                elimina_lista();
                exit(0);
        }
    } /*for*/
}
