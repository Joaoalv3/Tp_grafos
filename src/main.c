// src/main.c
#include <stdio.h>
#include <stdlib.h> // Para exit, se necessário
#include <time.h>   // Para srand, time

// Inclua seus cabeçalhos personalizados
#include "Grafos.h" // Contém INF, e protótipos de funções auxiliares e de gerenciamento de grafo
#include "dijkstra.h"
#include "bellman_ford.h"
#include "floyd_warshall.h"



int main() {
    int i = 1;
    while(i){
        int op;
         printf("-------------------------------------------------(MENU)------------------------------------------------------------------\n");
        printf("Operação a se realizar\n");
        printf("-----------------------------------------------------------------------------------------------------------------------\n");
        printf("1: Grafo simples\n2: Grafo esparso/denso aleatório\n3: Grade 2D\n4: Sair\n");
        scanf("%d",&op);
        printf("-----------------------------------------------------------------------------------------------------------------------\n");
        switch (op){
            case 1 :
                    int num_vertices,negativos;
                    printf("Numero de Vertices: ");
                    scanf("%d", &num_vertices);
                    printf("Permitir pesos negativos?(1-sim,0-Não): ");
                    scanf("%d", &negativos);
                    if(negativos == 1){
                        int ciclos;
                        printf("Permitir ciclos negativos?(1-sim,0-Não): ");
                        scanf("%d", &ciclos);
                        int **grafo = gerarMatrizAdjacenciaAleatoria(num_vertices,negativos,ciclos);
                        dijkstra(grafo, num_vertices, 0);
                        bellmanFord(num_vertices, grafo, 0);
                        floydWarshall(num_vertices, grafo);
                        liberarGrafo(grafo, num_vertices);
                        printf("\n");

                    } else{
                        int **grafo = gerarMatrizAdjacenciaAleatoria(num_vertices,negativos,0);
                        dijkstra(grafo, num_vertices, 0);
                        bellmanFord(num_vertices, grafo, 0);
                        floydWarshall(num_vertices, grafo);
                        liberarGrafo(grafo, num_vertices);
                        printf("\n");
                    }

                break;
            case 2:

                int numvertices,neg,num_arestas;
                printf("Numero de Vertices: ");
                scanf("%d", &numvertices);
                printf("Numero de arestas: ");
                scanf("%d", &num_arestas);
                printf("Permitir pesos negativos?(1-sim,0-Não): ");
                scanf("%d", &neg);

                int **grafo2 = gerarGrafoPorArestas(numvertices,num_arestas,neg);

                dijkstra(grafo2, numvertices, 0);
                bellmanFord(numvertices, grafo2, 0);
                floydWarshall(numvertices, grafo2);
                liberarGrafo(grafo2, numvertices);

                break;
            
            case 3:
                int vertices;
                int **grafo3 = carregarGrafo(&vertices);

                dijkstra(grafo3, vertices, 0);
                bellmanFord(vertices, grafo3, 0);
                floydWarshall(vertices, grafo3);
                liberarGrafo(grafo3, vertices);
                


                break;
            
            case 4:
                i = 0;
                break;
            default:
                i = 0;
                break;
        }
    }
    /*// --- Teste com Grafo Pequeno (definido manualmente) ---
    int num_pequeno = 5;
    int **grafo_pequeno = criarGrafo(num_pequeno);
    inicializarMatrizGrafo(grafo_pequeno, num_pequeno); // Garante que tudo começa como INF

    // Exemplo de preenchimento manual (similar ao seu exemplo inicial)
    grafo_pequeno[0][1] = 10;
    grafo_pequeno[0][4] = 5;
    grafo_pequeno[1][2] = 1;
    grafo_pequeno[1][4] = 2;
    grafo_pequeno[2][3] = 4;
    grafo_pequeno[3][0] = 7;
    grafo_pequeno[4][1] = 3;
    grafo_pequeno[4][2] = 9;
    grafo_pequeno[4][3] = 2;

    printf("\n--- Teste com Grafo Pequeno (%d vertices) ---\n", num_pequeno);
    dijkstra(num_pequeno, grafo_pequeno, 0);
    bellmanFord(num_pequeno, grafo_pequeno, 0);
    floydWarshall(num_pequeno, grafo_pequeno);
    liberarGrafo(grafo_pequeno, num_pequeno); // Sempre libere a memória!
    printf("\n");

    // --- Teste com Grafo Esparso ---
    int num_esparso = 50;            // Um número maior de vértices
    double densidade_esparsa = 0.05; // 5% de densidade (poucas arestas)
    int **grafo_esparso = criarGrafo(num_esparso);
    // Gerar grafo com pesos positivos (Dijkstra)
    gerarGrafoAleatorio(grafo_esparso, num_esparso, densidade_esparsa, 100, 0);

    printf("\n--- Teste com Grafo Esparso (%d vertices, %.0f%% densidade) ---\n", num_esparso, densidade_esparsa * 100);
    // Para grafos grandes, a impressão das distâncias pode ser extensa.
    // Para estudos de performance, você pode querer desabilitar a impressão aqui.
    dijkstra(num_esparso, grafo_esparso, 0);
    bellmanFord(num_esparso, grafo_esparso, 0);
    // Floyd-Warshall é O(V^3), pode ser lento para 50 vértices (50^3 = 125.000 operações básicas)
    // floydWarshall(num_esparso, grafo_esparso);
    liberarGrafo(grafo_esparso, num_esparso);
    printf("\n");

    // --- Teste com Grafo Denso ---
    int num_denso = 25;           // Menos vértices para denso devido à complexidade O(V^3)
    double densidade_densa = 0.8; // 80% de densidade (muitas arestas)
    int **grafo_denso = criarGrafo(num_denso);
    // Gerar grafo que permite pesos negativos (para Bellman-Ford e Floyd-Warshall)
    gerarGrafoAleatorio(grafo_denso, num_denso, densidade_densa, 50, 1);

    printf("\n--- Teste com Grafo Denso (%d vertices, %.0f%% densidade) ---\n", num_denso, densidade_densa * 100);
    // Dijkstra não é adequado para grafos com pesos negativos
    bellmanFord(num_denso, grafo_denso, 0);
    floydWarshall(num_denso, grafo_denso);
    liberarGrafo(grafo_denso, num_denso);
    printf("\n");

    // --- Teste Bellman-Ford com ciclo negativo ---
    int num_ciclo_negativo = 3;
    int **grafo_ciclo = criarGrafo(num_ciclo_negativo);
    inicializarMatrizGrafo(grafo_ciclo, num_ciclo_negativo);
    grafo_ciclo[0][1] = 1;
    grafo_ciclo[1][2] = -1;
    grafo_ciclo[2][0] = -1; // Ciclo 0 -> 1 -> 2 -> 0 com soma -1

    printf("\n--- Teste Bellman-Ford com Ciclo Negativo (%d vertices) ---\n", num_ciclo_negativo);
    bellmanFord(num_ciclo_negativo, grafo_ciclo, 0);
    liberarGrafo(grafo_ciclo, num_ciclo_negativo);
    printf("\n");

    return 0;*/
}