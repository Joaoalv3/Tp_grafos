#include "bellman_ford.h"
#include <stdio.h>
#include <stdlib.h> // Para malloc e free
#include <limits.h> 

// Garanta que INF esteja definido como INT_MAX em seu header
#ifndef INF
#define INF INT_MAX
#endif

void bellmanFord(int num_vertices, int** grafo, int inicio) {
    clock_t começo, fim;
    double tempo_cpu;

    começo = clock();

    // MUDANÇA: Alocação na heap para segurança contra stack overflow
    int *dist = (int *)malloc(num_vertices * sizeof(int));
    if (dist == NULL) {
        perror("Erro de alocacao em Bellman-Ford");
        exit(EXIT_FAILURE);
    }

    // Inicializa todas as distâncias como infinito
    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INF;
    }
    dist[inicio] = 0;

    // Relaxa todas as arestas V-1 vezes
    for (int count = 0; count < num_vertices - 1; count++) {
        for (int u = 0; u < num_vertices; u++) {
            for (int v = 0; v < num_vertices; v++) {
                // CORREÇÃO: Verifica a existência de aresta comparando com INF
                if (grafo[u][v] != INF) {
                    // Verifica se 'u' é alcançável e se o novo caminho é mais curto
                    if (dist[u] != INF && (long long)dist[u] + grafo[u][v] < dist[v]) {
                        dist[v] = dist[u] + grafo[u][v];
                    }
                }
            }
        }
    }

    // CORREÇÃO: Bloco de detecção de ciclo negativo REATIVADO
    for (int u = 0; u < num_vertices; u++) {
        for (int v = 0; v < num_vertices; v++) {
            if (grafo[u][v] != INF) {
                // Se ainda for possível relaxar, há um ciclo negativo
                if (dist[u] != INF && (long long)dist[u] + grafo[u][v] < dist[v]) {
                    printf("\nAVISO (Bellman-Ford): Grafo contem ciclo de peso negativo!\n");
                    printf("Os resultados de distancia podem ser indefinidos.\n");
                    free(dist); // MUDANÇA: Libera a memória antes de sair
                    return; 
                }
            }
        }
    }
    
    fim = clock();
    tempo_cpu = ((double) (fim - começo)) / CLOCKS_PER_SEC;

    // Imprime o resultado apenas se não houver ciclo negativo
    imprimirDistancias(num_vertices, dist, inicio, "Bellman-Ford");
    printf("Tempo de execucao (Bellman-Ford): %f segundos.\n", tempo_cpu);
    
    // MUDANÇA: Libera a memória alocada
    free(dist);
}