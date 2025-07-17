#include "Grafos.h" 

// Implementação das funções de gerenciamento de grafo
int** criarGrafo(int num_vertices) {
    int** grafo = (int**)malloc(num_vertices * sizeof(int*));
    if (grafo == NULL) {
        perror("Erro ao alocar memória para linhas do grafo");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_vertices; i++) {
        grafo[i] = (int*)malloc(num_vertices * sizeof(int));
        if (grafo[i] == NULL) {
            perror("Erro ao alocar memória para colunas do grafo");
            for (int j = 0; j < i; j++) { free(grafo[j]); }
            free(grafo);
            exit(EXIT_FAILURE);
        }
    }
    return grafo;
}

void liberarGrafo(int** grafo, int num_vertices) {
    if (grafo == NULL) return;
    for (int i = 0; i < num_vertices; i++) {
        if (grafo[i] != NULL) free(grafo[i]);
    }
    free(grafo);
}

void inicializarMatrizGrafo(int** grafo, int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (i == j) {
                grafo[i][j] = 0;
            } else {
                grafo[i][j] = INF;
            }
        }
    }
}
int** gerarMatrizAdjacenciaAleatoria(int numVertices, int permitirNegativos, int controleCiclo) {
    if (numVertices <= 0) {
        printf("Erro: O número de vértices deve ser positivo.\n");
        return NULL;
    }
    if (permitirNegativos == 0 && controleCiclo == 1) {
        printf("Aviso: Não é possível garantir ciclo negativo com pesos apenas positivos. Gerando sem ciclo.\n");
        controleCiclo = 0;
    }

    int **grafo = criarGrafo(numVertices);
    if (grafo == NULL) return NULL;

    inicializarMatrizGrafo(grafo, numVertices);
    if (permitirNegativos && controleCiclo == 0) {
        printf("Gerando grafo com pesos negativos, mas sem ciclos negativos (DAG).\n");
        for (int i = 0; i < numVertices; i++) {
            for (int j = i + 1; j < numVertices; j++) {
                if (rand() % 2 == 1) { // 50% de chance de aresta
                    int peso = (rand() % 41) - 20; // [-20, 20]
                    if (peso == 0) peso = 1; // Evita peso 0 se não desejado
                    grafo[i][j] = peso;
                }
                if (rand() % 4 == 1) {
                    grafo[j][i] = (rand() % 20) + 1; // [1, 20]
                }
            }
        }
    } else {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (i == j) continue;
                if (grafo[i][j] == INF && (rand() % 2 == 1)) {
                    int peso;
                    if (permitirNegativos) {
                        peso = (rand() % 41) - 20;
                        if (peso == 0) peso = 1;
                    } else {
                        peso = (rand() % 20) + 1;
                    }
                    grafo[i][j] = peso;
                }
            }
        }

        if (permitirNegativos && controleCiclo == 1) {
            printf("Implantando um ciclo de peso negativo garantido.\n");
            if (numVertices >= 3) {
                grafo[0][1] = -10;
                grafo[1][2] = -10;
                grafo[2][0] = 5;   // Soma do ciclo = -15
            } else {
                printf("Aviso: O grafo é muito pequeno para garantir um ciclo negativo (necessário >= 3 vértices).\n");
            }
        }
    }

    return grafo;
}

void imprimirDistancias(int num_vertices, int dist[], int inicio, const char* algoritmo) {
    printf("Distancias mais curtas do vertice %d (Algoritmo %s):\n", inicio, algoritmo);
    for (int i = 0; i < num_vertices; i++) {
        if (dist[i] == INF) {
            printf("Vertice %d: INF\n", i);
        } else {
            printf("Vertice %d: %d\n", i, dist[i]);
        }
    }
}

void imprimirMatrizCaminhos(int num_vertices, int** dist_matrix, const char* algoritmo) {
    printf("Matriz de Distancias Mais Curtas (Algoritmo %s):\n", algoritmo);
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (dist_matrix[i][j] == INF) {
                printf("%6s", "INF");
            } else {
                printf("%6d", dist_matrix[i][j]);
            }
        }
        printf("\n");
    }
}

int** carregarGrafo( int* V) {
    int** grafo;
    FILE* f = fopen("grafo.txt", "r");
    if (!f) {
    printf("Erro ao abrir o arquivo.\n");
    exit(1);
    }
    fscanf(f, "%d", V);
    grafo = (int**)malloc((*V) * sizeof(int*));
    for (int i = 0; i < (*V); i++) {
        grafo[i] = (int*)malloc((*V) * sizeof(int));
    }
    for (int i = 0; i < (*V); i++) {
        for (int j = 0; j < (*V); j++) {
            grafo[i][j] =  INF;
        }
    }
    int u, v, peso;
    while (fscanf(f, "%d %d %d", &u, &v, &peso) != EOF) {
    grafo[u][v] = peso;
    
    }
    fclose(f);
    return grafo;
}


int** gerarGrafoPorArestas(int numVertices, int numArestas, int permitirNegativos) {
    // 1. Validação dos Parâmetros
    if (numVertices <= 0) {
        printf("Erro: O número de vértices deve ser maior que zero.\n");
        return NULL;
    }

    if (numArestas < 0) {
        printf("Erro: O número de arestas não pode ser negativo.\n");
        return NULL;
    }

    long long maxArestasPossiveis = (long long)numVertices * (numVertices - 1);
    if (numArestas > maxArestasPossiveis) {
        printf("Aviso: O número de arestas solicitado (%d) é maior que o máximo possível (%lld).\n", numArestas, maxArestasPossiveis);
        printf("O grafo será gerado com o número máximo de arestas.\n");
        numArestas = maxArestasPossiveis;
    }

    int** grafo = criarGrafo(numVertices);
    if (grafo == NULL) {
        return NULL; 
    }

    inicializarMatrizGrafo(grafo, numVertices);

    int arestasAdicionadas = 0;
    long long tentativas = 0;

    long long limiteDeTentativas = (long long)numArestas * 10 + numVertices * numVertices; 

    while (arestasAdicionadas < numArestas && tentativas < limiteDeTentativas) {
        int u = rand() % numVertices;
        int v = rand() % numVertices;

        if (u == v || grafo[u][v] != INF) {
            tentativas++;
            continue;
        }

        // Gera o peso da aresta
        int peso;
        if (permitirNegativos) {
            peso = (rand() % 41) - 20; // Gera peso entre -20 e 20
            if (peso == 0) peso = 1;   // Evita peso 0
        } else {
            peso = (rand() % 20) + 1;  // Gera peso entre 1 e 20
        }

        // Adiciona a aresta ao grafo
        grafo[u][v] = peso;
        arestasAdicionadas++;
    }

    if (arestasAdicionadas < numArestas) {
        printf("\nAviso: Não foi possível adicionar todas as arestas solicitadas (adicionadas: %d de %d) devido à saturação do grafo.\n", arestasAdicionadas, numArestas);
    }

    return grafo;
}