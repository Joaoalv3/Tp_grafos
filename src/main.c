
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "Grafos.h"
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
}