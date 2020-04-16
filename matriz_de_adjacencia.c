#include <stdlib.h>
#include <stdio.h>
#include "grafo(TAD).h"

struct grafo{
    No* inicio;
    No* fim;
    int numero_de_vertices;
};

struct no{
    int dado;
    Sentinela* cabeca;                          // Este no eh exclusivo para o inicio da proxima lista
    No* proximo;                                // Esta lista eh duplamente encadeada, por isso guardamos os 
    No* anterior;                               // dois enderecos, de anterior e proximo
};

struct sentinela{
    int vertices;                               // Foi utilizado um no cabeca para facilitar na busca das
    No* proximo;                                // adjacencias de cada vertice
};

void Criar_grafo(Grafo **novo, int n){                 // Inicializamos a lista principal
    (*novo) = malloc (sizeof(No*));
    (*novo)->inicio = NULL;
    (*novo)->fim = NULL;
    (*novo)->numero_de_vertices = n;
    return;
}

void cria_no(No* novo, int valor){
    Sentinela* aux = malloc(sizeof(Sentinela*));

    novo->dado = valor;
    novo->proximo = NULL;
    novo->anterior = NULL;
    novo->cabeca = aux;
    novo->cabeca->proximo = NULL;
    novo->cabeca->vertices = 0;
}

void Inserir_vertice(Grafo* novo, int vertices){
    No* aux = malloc(sizeof(No*));
    No* aux2 = malloc(sizeof(No*));

    cria_no(aux, vertices);

    if(novo->inicio == NULL){
        novo->inicio = aux;
        novo->fim = aux;
    }else{
        aux2 = novo->inicio;
        while(aux2->proximo != NULL)
            aux2 = aux2->proximo;
        
        aux2->proximo = aux;
        aux->anterior = aux2;
    }

    return;
}

int Inserir_aresta(Grafo* novo, int i, int j, int valor){
    /* Deixei em aberto (sem uso) a opcao valor, para caso fosse um grafo ponderado,
     * neste caso, usarei como padrao o numero do vertice, porem eh possivel
     * adicionar a struct a area peso
     */

    No* aux = malloc(sizeof(No*));
    No* aux2 = malloc(sizeof(No*));
    
    cria_no(aux, j);
    aux2 = novo->inicio;   

    while(aux2->dado != i)
        aux2 = aux2->proximo;

    /* Apos chegar no primeiro vertice, testamos caso ele tenha outras conexoes,
     * pois a nova conexao sera inserida no fim da lista
     * Todos os vertices ja estao definidos, a partir deste momento, serao criadas 
     * as arestas estas arestas iniciam-se apos a sentinela (que guarda inclusive 
     * quantas arestas este vertice possui)
     */
        
    if(aux2->cabeca->vertices == 0){
        aux2->cabeca->vertices++;
        aux2->cabeca->proximo = aux; 
        aux->anterior = aux2;
    }

    else{
        aux2->cabeca->vertices++;
        aux2 = aux2->cabeca->proximo;

        while(aux2->proximo != NULL){
            if(aux2->dado == j)
                return 0;                   // Erro, esta aresta ja existe
            aux2 = aux2->proximo;
        }
        
        aux2->proximo = aux;
        aux->anterior = aux2;
    }

    return 1;                               // Inserido com sucesso
}
    
int Remover_aresta(Grafo *novo, int i, int j, int valor){
    /** um unico numero ficou repetido?? **
     * caso 3 -> 1: 6 5 5 
     * caso 4 -> 1: 0 0
     * caso 6 -> 0: 1 3 3; 3: 4 0 0
     */
    // Inicialmente precisamos percorrer a lista ate achar o primeiro vertice
    No* aux = malloc(sizeof(No*));
    No* aux2 = malloc(sizeof(No*));
    
    aux2 = novo->inicio;   

    while(aux2->dado != i && aux2->proximo != NULL)
        aux2 = aux2->proximo;
    

    if(aux2->dado != i)
        return 0;                           // Erro, nao existe essa vertice

    /* Apos chegar no primeiro vertice, testamos caso ele tenha outras conexoes,
     * pois a nova conexao sera inserida no fim da lista
     * Todos os vertices ja estao definidos, a partir deste momento, serao criadas 
     * as arestas estas arestas iniciam-se apos a sentinela (que guarda inclusive 
     * quantas arestas este vertice possui)
     */
        
    if(aux2->cabeca->vertices == 0)
        return 0;                           // Erro: nao ha arestas a serem removidas

    else{
        /* Precisamos guardar o no sentinela pois em alguns casos ele sera 
         * necessario para nao perder a referencia da lista
         */

        aux = aux2->cabeca->proximo;

        if(aux->dado == j){
            aux->anterior = aux2;
            aux2->cabeca->proximo = aux->proximo;

        }else{
            while(aux->dado != j && aux->proximo != NULL)
                aux = aux->proximo;

                if(aux->dado != j)
                    return 0;                   // Erro, nao existe essa aresta

            aux->anterior->proximo = aux->proximo;
            if(aux->proximo != NULL) aux->proximo->anterior = aux->anterior;
        }
    }
    free(aux);
    aux2->cabeca->vertices--;
    return 1;                                   // Removido com sucesso
}
        
void Exibir_matriz(Grafo *novo, int n){
    // Percorreremos toda a lista, a cada vertice, guardaremos suas arestas

    No* aux = malloc(sizeof(No*));          // Este auxiliar percorrera a lista principal
    No* aux2 = malloc(sizeof(No*));         // Este auxiliar percorrera a lista de adjacencias

    aux = novo->inicio;

    while(aux != NULL){
        printf("%d:", aux->dado);
        aux2 = aux->cabeca->proximo;

        while(aux2 != NULL){
            printf(" %d", aux2->dado);
            aux2 = aux2->proximo;
        }
        printf("\n");
        aux = aux->proximo;
    }
    printf("\n");

    return;
}

void Deletar_grafo(Grafo** novo){
    if((*novo) != NULL){
        No* current = (*novo)->inicio->proximo;
        No* next;

        while(current != NULL){
            next = current->proximo;
            Deletar_lista(&current);
            current = next;
        }
        free((*novo));
    }
    novo = NULL;
    return;
}

void Deletar_lista(No **novo){
    /* Devemos percorrer a lista de vertices para ir liberando do fim para o 
     * comeco e nao perder o endereco de memoria dos vertices 
     */

    // Percorreremos toda a lista, a cada vertice, guardaremos suas arestas
    No* current = (*novo)->cabeca->proximo;
    No* next;

    while(current != NULL){
        next = current->proximo;
        free(current);
        current = next;
    }

    free(*novo);
    novo = NULL;

    return;      
}