// include/dijkstra.h
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Grafos.h" // Inclui INF e os protótipos de funções auxiliares

// Assinatura da função alterada para usar int** grafo
void dijkstra(int **grafo, int numVertices, int origem);

#endif // DIJKSTRA_H