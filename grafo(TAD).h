#ifndef GRAFO_H
    #define GRAFO_H

    typedef struct grafo Grafo;
    typedef struct no No;
    typedef struct sentinela Sentinela;

    void Criar_grafo(Grafo **novo, int n);

    void Inserir_vertice(Grafo* novo, int vertices);

    int Inserir_aresta(Grafo *novo, int i, int j, int valor);
        
    int Remover_aresta(Grafo *novo, int i, int j, int valor);
            
    void Exibir_matriz(Grafo *novo, int n);

    void Deletar_grafo(Grafo** novo);

    void Deletar_lista(No **novo);

#endif