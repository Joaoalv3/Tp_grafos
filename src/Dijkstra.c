#include "dijkstra.h"
#include <stdio.h>
#include <limits.h> 
#include <stdlib.h> 
#include <time.h>  

#ifndef INF
#define INF INT_MAX
#endif

void dijkstra(int **grafo, int numVertices, int origem) {
   

    clock_t inicio, fim;
    double tempo_cpu;

    inicio = clock();

    int *distancia = (int *)malloc(numVertices * sizeof(int));
    int *visitado = (int *)malloc(numVertices * sizeof(int));

    if (distancia == NULL || visitado == NULL) {
        perror("Erro de alocacao em Dijkstra");
        exit(EXIT_FAILURE);
    }

    // Inicializa os arrays
    for (int i = 0; i < numVertices; i++) {
        distancia[i] = INF;
        visitado[i] = 0;
    }

    distancia[origem] = 0;

    for (int count = 0; count < numVertices; count++) { 
        // Encontra o vértice com a menor distância entre os não visitados
        int min_dist = INF, u = -1;
        
        for (int i = 0; i < numVertices; i++) {
            if (!visitado[i] && distancia[i] < min_dist) { 
                min_dist = distancia[i];
                u = i;
            }
        }

        if (u == -1 || min_dist == INF) break; // Se não houver mais vértices alcançáveis

        visitado[u] = 1;

        // Atualiza a distância dos vértices adjacentes
        for (int v = 0; v < numVertices; v++) {
           
            if (!visitado[v] && grafo[u][v] != INF && distancia[u] != INF) {
                int novaDistancia = distancia[u] + grafo[u][v];
                if (novaDistancia < distancia[v]) {
                    distancia[v] = novaDistancia;
                }
            }
        }
    }

    fim = clock();
    tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;


    printf("\n--- Resultado de Dijkstra (Origem: %d) ---\n", origem);
    for (int i = 0; i < numVertices; i++) {
        if (distancia[i] != INF) {
            printf("Distancia para o vertice %d: %d\n", i, distancia[i]);
        } else {
            printf("Distancia para o vertice %d: Inalcancavel\n", i);
        }
    }
    printf("Tempo de execucao (Dijkstra): %f segundos.\n", tempo_cpu);
    
    // Libera a memória
    free(distancia);
    free(visitado);
}