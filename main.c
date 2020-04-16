#include <stdio.h>
#include "grafo(TAD).h"

int main(void){

    int opc, i, j, n, m, oper, erro, erro2;
    Grafo *novo;

    scanf("%d %d", &n, &m);

    Criar_grafo(&novo, n);

    // Criaremos inicialmente a quantidade de vertices definidas no inicio
    // Todas elas sem arestas
    for(int i = 0; i < n; i++){
        Inserir_vertice(novo, i);
    }

    // Inicialmente quantas arestas haverao == m

    // Insere as arestas iniciais
    for(int k = 0; k < m; k++){
        scanf("%d %d", &i, &j);
        Inserir_aresta(novo, i, j, 1); 
        Inserir_aresta(novo, j, i, 1); 
    }

    scanf("%d", &oper);                             // Quantas operacoes que serao executadas

    for(int contador = 0; contador < oper; contador++){
        scanf("%d", &opc);
        // Apenas a impressao nao precisa de parametros para ser executado
            
        if(opc == 1){
            scanf("%d %d", &i, &j);
            erro = Inserir_aresta(novo, i, j, 1);  
            erro = Inserir_aresta(novo, j, i, 1); 
        }                
        // Remover aresta
        else if(opc == 2){
            scanf("%d %d", &i, &j);
            erro = Remover_aresta(novo, i, j, 0);
            erro = Remover_aresta(novo, j, i, 0);
        }               
        // Exibir matriz
        else if(opc == 3){
            Exibir_matriz(novo, n);
        }
            
        
    }

    Deletar_grafo(&novo);

    return 0;
}