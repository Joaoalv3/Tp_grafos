#include "dijkstra.h"
#include <stdio.h>
#include <limits.h> // Para INT_MAX
#include <stdlib.h> // Para malloc e free
#include <time.h>   // Para clock

// Supondo que INF esteja definido em Grafos.h como INT_MAX
#ifndef INF
#define INF INT_MAX
#endif

void dijkstra(int **grafo, int numVertices, int origem) {
    // AVISO: Dijkstra não funciona com pesos negativos.
    // A lógica para não chamar esta função deve estar no main.

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
        distancia[i] = INF; // CORREÇÃO: Infinito deve ser um valor muito grande.
        visitado[i] = 0;
    }

    distancia[origem] = 0;

    for (int count = 0; count < numVertices; count++) { // Loop pode ir até V vezes
        // Encontra o vértice com a menor distância entre os não visitados
        int min_dist = INF, u = -1; // CORREÇÃO: min_dist também começa como INF
        
        for (int i = 0; i < numVertices; i++) {
            if (!visitado[i] && distancia[i] < min_dist) { // CORREÇÃO: Lógica simplificada
                min_dist = distancia[i];
                u = i;
            }
        }

        if (u == -1 || min_dist == INF) break; // Se não houver mais vértices alcançáveis

        visitado[u] = 1;

        // Atualiza a distância dos vértices adjacentes
        for (int v = 0; v < numVertices; v++) {
            // CORREÇÃO: Verifica se existe aresta (peso diferente de 0 E de INF)
            // e se o vértice de origem 'u' é alcançável.
            // A verificação `grafo[u][v]` depende de como você representa "sem aresta".
            // Se "sem aresta" for 0 (do seu gerador) ou INF (do seu inicializador), a verificação muda.
            // A melhor é usar um valor consistente, como INF.
            // Vamos assumir que "sem aresta" é INF e peso 0 é válido.
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

    // --- Seção de Exibição ---
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