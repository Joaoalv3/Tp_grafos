// include/Grafos.h
#ifndef GRAFOS_H
#define GRAFOS_H

#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>  

#define INF INT_MAX

// --- Funções de Gerenciamento e Geração de Grafo ---

// Função para alocar dinamicamente uma matriz de adjacência (nxn)
int** criarGrafo(int num_vertices);

// Função para liberar a memória alocada para o grafo
void liberarGrafo(int** grafo, int num_vertices);

// Função para inicializar a matriz do grafo com INF (ou 0 para arestas de si mesmo)
void inicializarMatrizGrafo(int** grafo, int num_vertices);

// Função para gerar um grafo aleatório (direcionado) com densidade e pesos
void gerarGrafoAleatorio(int** grafo, int num_vertices, double densidade, int max_peso, int permitir_pesos_negativos);

// --- Funções Auxiliares de Impressão ---

// Imprime as distâncias mais curtas de um vértice inicial
void imprimirDistancias(int num_vertices, int dist[], int inicio, const char* algoritmo);

// Imprime a matriz de distâncias mais curtas (para Floyd-Warshall)
void imprimirMatrizCaminhos(int num_vertices, int** dist_matrix, const char* algoritmo);

int** carregarGrafo(int* V);

int** gerarMatrizAdjacenciaAleatoria(int numVertices, int permitirNegativos, int controleCiclo);

int** gerarGrafoPorArestas(int numVertices, int numArestas, int permitirNegativos);
#endif // GRAFOS_H