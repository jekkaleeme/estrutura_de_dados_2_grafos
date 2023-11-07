#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0
typedef int bool;
typedef int PESO;

typedef struct adjacente {
    int vertice;
    PESO peso;
    struct adjacente *prox;
} ADJACENTE;

typedef struct vertice {
    ADJACENTE *cab;
} VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE *v_adjacente;
} GRAFO;

GRAFO *novo_grafo(int v) {
    int i;

    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->v_adjacente = (VERTICE *)malloc(v * sizeof(VERTICE));

    for (i = 0; i < v; i++) {
        g->v_adjacente[i].cab = NULL;
    }
    return (g);
}

ADJACENTE *novo_vertice(int v, PESO peso) {
    ADJACENTE *t = (ADJACENTE *)malloc(sizeof(ADJACENTE));
    t->vertice = v;
    t->peso = peso;
    t->prox = NULL;
    return (t);
}

bool nova_aresta(GRAFO *gr, int vi, int vf, PESO p) {
    if (!gr) return (false);
    if ((vf < 0) || (vf >= gr->vertices)) return (false);
    if ((vi < 0) || (vf >= gr->vertices)) return (false);

    ADJACENTE *novo = novo_vertice(vf, p);

    novo->prox = gr->v_adjacente[vi].cab;
    gr->v_adjacente[vi].cab = novo;
    gr->arestas++;
    return (true);
}

void imprimir(GRAFO *gr) {
    printf("vertices: %d. arestas: %d \n", gr->vertices, gr->arestas);
    int i;

    for (i = 0; i < gr->vertices; i++) {
        printf("v%d:", i + 1);
        ADJACENTE *ad = gr->v_adjacente[i].cab;
        while (ad) {
            printf("v%d(%d) ", ad->vertice + 1, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
}

void nova_matriz(GRAFO *gr) {
    printf("\n\nmatriz de adjacência:\n");
    for (int i = 0; i < gr->vertices; i++) {
        for (int j = 0; j < gr->vertices; j++) {
            int adjacente = 0;
            ADJACENTE *ad = gr->v_adjacente[i].cab;
            while (ad) {
                if (ad->vertice == j) {
                    adjacente = ad->peso;
                }
                ad = ad->prox;
            }
            printf("%d\t", adjacente);
        }
        printf("\n");
    }
}

int calculo_caminho(GRAFO *gr, int *caminho, int numero_vertices) {
    int valor_caminho = 0;

    for (int i = 0; i < numero_vertices - 1; i++) {
        int vi = caminho[i] - 1; 
        int vf = caminho[i + 1] - 1; 
        ADJACENTE *ad = gr->v_adjacente[vi].cab;
        bool found = false;

        while (ad) {
            if (ad->vertice == vf) {
                valor_caminho += ad->peso;
                found = true;
                break;
            }
            ad = ad->prox;
        }

        if (!found) {
            return -1;
        }
    }

    return valor_caminho;
}

int calculo_caminho(GRAFO *gr, int inicio, int destino, int *visitados) {
    if (inicio == destino) {
        return 0;
    }

    visitados[inicio] = 1;
    ADJACENTE *ad = gr->v_adjacente[inicio].cab;
    int soma = 0;

    while (ad != NULL) {
        int prox_vertice = ad->vertice;
        int aresta = ad->peso;

        if (!visitados[prox_vertice]) {
            soma += aresta + calculo_caminho(gr, prox_vertice, destino, visitados);
        }

        ad = ad->prox;
    }

    visitados[inicio] = 0;
    return soma;
}

int soma(GRAFO *gr, int inicio, int destino) {
    int *visitados = (int *)malloc(gr->vertices * sizeof(int));
    for (int i = 0; i < gr->vertices; i++) {
        visitados[i] = 0;
    }
    int soma = calculo_caminho(gr, inicio, destino, visitados);
    free(visitados);
    return soma;
}

int main() {
    GRAFO *grafito = novo_grafo(5);

    nova_aresta(grafito, 0, 0, 0);
    nova_aresta(grafito, 0, 2, 0);
    nova_aresta(grafito, 1, 2, 0);
    nova_aresta(grafito, 1, 3, 0);
    nova_aresta(grafito, 1, 4, 0);
    nova_aresta(grafito, 2, 3, 0);
    nova_aresta(grafito, 3, 4, 0);

    printf("\ngrafo em lista de adjacência:\n");
    imprimir(grafito);

    nova_matriz(grafito);

    printf("\n");
    for (int l = 0; l < 25; l++) if (l < 24) printf("-"); else printf("\n");

    GRAFO *grafo_orientado = novo_grafo(5);

    nova_aresta(grafo_orientado, 0, 0, 2);
    nova_aresta(grafo_orientado, 0, 2, 7);
    nova_aresta(grafo_orientado, 2, 1, 5);
    nova_aresta(grafo_orientado, 2, 3, 10);
    nova_aresta(grafo_orientado, 3, 1, 9);
    nova_aresta(grafo_orientado, 3, 4, 1);
    nova_aresta(grafo_orientado, 4, 1, 12);

    printf("lista de adjacência (Grafo Orientado e Ponderado):\n");
    imprimir(grafo_orientado);
    nova_matriz(grafo_orientado);

    imprimir(grafo_orientado);
    printf("\nvalor total do caminho: %d ", soma(grafo_orientado, 0, 4));

    return 0;
}