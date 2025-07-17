

#include "bellman_ford.h" 
#include <stdio.h>
#include <limits.h> 
#include <stdlib.h> 
#include <time.h>   


#ifndef INF
#define INF INT_MAX
#endif

void imprimirDistancias(int num_vertices, int dist[], int inicio, const char* algoritmo);

/**
 * @brief Executa o algoritmo de Bellman-Ford para encontrar os caminhos mais curtos
 * a partir de um único vértice de origem em um grafo ponderado.
 * @param num_vertices O número de vértices no grafo.
 * @param grafo A matriz de adjacência que representa o grafo.
 * @param vertice_inicial O vértice de onde os caminhos mais curtos são calculados.
 */
void bellmanFord(int num_vertices, int** grafo, int vertice_inicial) {
    
    clock_t tempo_inicio, tempo_fim;
    double tempo_cpu;

    tempo_inicio = clock(); // Marca o tempo de início

   
    int* dist = malloc(num_vertices * sizeof(int));
    if (dist == NULL) {
        perror("Falha ao alocar memória para o array de distâncias");
        return;
    }

   
    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INF;
    }
   
    dist[vertice_inicial] = 0;

    for (int count = 0; count < num_vertices - 1; count++) {
        for (int u = 0; u < num_vertices; u++) {
            for (int v = 0; v < num_vertices; v++) {
               
                if (dist[u] != INF && grafo[u][v] != INF && (long long)dist[u] + grafo[u][v] < dist[v]) {
                    dist[v] = dist[u] + grafo[u][v];
                }
            }
        }
    }

    
    for (int u = 0; u < num_vertices; u++) {
        for (int v = 0; v < num_vertices; v++) {
            if (dist[u] != INF && grafo[u][v] != INF && (long long)dist[u] + grafo[u][v] < dist[v]) {
                printf("AVISO: O grafo contém um ciclo de peso negativo! Os caminhos mais curtos não podem ser determinados.\n");
                free(dist); // Libera a memória antes de sair
                return;
            }
        }
    }

    tempo_fim = clock(); // Marca o tempo de fim

    
    tempo_cpu = ((double)(tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
    
    // Imprime os resultados
    imprimirDistancias(num_vertices, dist, vertice_inicial, "Bellman-Ford");
    printf("O algoritmo de Bellman-Ford levou %f segundos para executar.\n\n", tempo_cpu);

    // Libera a memória alocada para o array de distâncias
    free(dist);
}
