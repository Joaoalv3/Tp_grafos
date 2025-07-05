// include/floyd_warshall.h
#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include "Grafos.h" // Inclui INF e os protótipos de funções auxiliares

// Assinatura da função alterada para usar int** grafo
void floydWarshall(int num_vertices, int** grafo);

#endif // FLOYD_WARSHALL_H