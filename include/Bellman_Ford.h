
#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "Grafos.h" // Inclui INF e os protótipos de funções auxiliares

// Assinatura da função alterada para usar int** grafo
void bellmanFord(int num_vertices, int** grafo, int inicio);

#endif // BELLMAN_FORD_H