#include "floyd_warshall.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h> // Adicionado para clock_t

// Garanta que INF esteja definido como INT_MAX em seu header
#ifndef INF
#define INF INT_MAX
#endif

// Supondo que criarGrafo e liberarGrafo estão em um header incluído (ex: Grafos.h)
int** criarGrafo(int num_vertices);
void liberarGrafo(int** grafo, int num_vertices);
void imprimirMatrizCaminhos(int num_vertices, int** dist_matrix, const char* algoritmo);


void floydWarshall(int num_vertices, int** grafo) {
    clock_t inicio, fim;
    double tempo_cpu;

    inicio = clock();

    int** dist = criarGrafo(num_vertices);

    // --- CORREÇÃO: Bloco de inicialização simplificado e robusto ---
    // A matriz de distâncias iniciais é uma cópia da matriz do grafo.
    // Isso assume que o grafo de entrada já usa INF para "sem aresta".
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            dist[i][j] = grafo[i][j];
        }
    }

    // Loop principal do Floyd-Warshall (esta parte já estava correta)
    for (int k = 0; k < num_vertices; k++) {
        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                // Se o caminho i->k e k->j existem, verifique se são uma melhor rota
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    // O cast para (long long) previne overflow
                    if ((long long)dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Detecção de ciclos negativos (esta parte já estava correta)
    for (int i = 0; i < num_vertices; i++) {
        if (dist[i][i] < 0) {
            printf("\nAVISO (Floyd-Warshall): Grafo contem ciclo de peso negativo!\n");
            break;
        }
    }
    
    fim = clock();
    tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

    imprimirMatrizCaminhos(num_vertices, dist, "Floyd-Warshall");
    printf("Tempo de execucao (Floyd-Warshall): %f segundos.\n", tempo_cpu);
    
    liberarGrafo(dist, num_vertices);
}