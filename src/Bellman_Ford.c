// src/Bellman_Ford.c

#include "bellman_ford.h" 
#include <stdio.h>
#include <limits.h> // Para INT_MAX, que usaremos como INF
#include <stdlib.h> // Para malloc() e free()
#include <time.h>   // Para clock() e CLOCKS_PER_SEC

// É uma boa prática definir INF caso não esteja em um header.
// Se já estiver definido em bellman_ford.h ou Grafos.h, esta linha pode ser removida.
#ifndef INF
#define INF INT_MAX
#endif

// Protótipo da função de impressão, assumindo que está definida em outro lugar.
void imprimirDistancias(int num_vertices, int dist[], int inicio, const char* algoritmo);

/**
 * @brief Executa o algoritmo de Bellman-Ford para encontrar os caminhos mais curtos
 * a partir de um único vértice de origem em um grafo ponderado.
 * @param num_vertices O número de vértices no grafo.
 * @param grafo A matriz de adjacência que representa o grafo.
 * @param vertice_inicial O vértice de onde os caminhos mais curtos são calculados.
 */
void bellmanFord(int num_vertices, int** grafo, int vertice_inicial) {
    // CORREÇÃO: Variáveis de tempo renomeadas para evitar conflito com o parâmetro.
    clock_t tempo_inicio, tempo_fim;
    double tempo_cpu;

    tempo_inicio = clock(); // Marca o tempo de início

    // MELHORIA: Alocação de memória na heap para o array de distâncias
    // para evitar stack overflow com grafos grandes.
    int* dist = malloc(num_vertices * sizeof(int));
    if (dist == NULL) {
        perror("Falha ao alocar memória para o array de distâncias");
        return;
    }

    // Passo 1: Inicializa as distâncias. A distância para a origem é 0,
    // e todas as outras são infinito.
    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INF;
    }
    // CORREÇÃO: A distância do vértice inicial para ele mesmo é sempre 0.
    dist[vertice_inicial] = 0;

    // Passo 2: Relaxa todas as arestas |V| - 1 vezes.
    // Um caminho mais curto simples pode ter no máximo |V| - 1 arestas.
    for (int count = 0; count < num_vertices - 1; count++) {
        for (int u = 0; u < num_vertices; u++) {
            for (int v = 0; v < num_vertices; v++) {
                // Verifica se existe uma aresta de u para v, se u é alcançável,
                // e se um caminho mais curto para v foi encontrado através de u.
                // O cast para (long long) previne overflow ao somar dist[u] e grafo[u][v].
                if (dist[u] != INF && grafo[u][v] != INF && (long long)dist[u] + grafo[u][v] < dist[v]) {
                    dist[v] = dist[u] + grafo[u][v];
                }
            }
        }
    }

    // Passo 3: Verifica a existência de ciclos de peso negativo.
    // Se for possível relaxar uma aresta novamente, então existe um ciclo.
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

    // CORREÇÃO: Calcula o tempo de CPU em segundos.
    tempo_cpu = ((double)(tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
    
    // Imprime os resultados
    imprimirDistancias(num_vertices, dist, vertice_inicial, "Bellman-Ford");
    printf("O algoritmo de Bellman-Ford levou %f segundos para executar.\n\n", tempo_cpu);

    // Libera a memória alocada para o array de distâncias
    free(dist);
}
