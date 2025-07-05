// src/utils.c
#include "Grafos.h" // Inclui todas as definições e protótipos

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

    // --- CORREÇÃO PRINCIPAL ---
    // Em vez de preencher com 0, inicializamos o grafo corretamente.
    // Agora, grafo[i][j] = INF (se i != j) e grafo[i][i] = 0.
    inicializarMatrizGrafo(grafo, numVertices);

    // O restante da lógica para adicionar arestas aleatórias permanece o mesmo.
    // Ela agora funcionará sobre uma matriz base correta.

    if (permitirNegativos && controleCiclo == 0) {
        // --- CENÁRIO 1: GARANTIR AUSÊNCIA DE CICLOS NEGATIVOS (ESTRUTURA DAG) ---
        printf("Gerando grafo com pesos negativos, mas sem ciclos negativos (DAG).\n");
        for (int i = 0; i < numVertices; i++) {
            for (int j = i + 1; j < numVertices; j++) { // Arestas sempre para frente (i -> j)
                if (rand() % 2 == 1) { // 50% de chance de aresta
                    int peso = (rand() % 41) - 20; // [-20, 20]
                    if (peso == 0) peso = 1; // Evita peso 0 se não desejado
                    grafo[i][j] = peso;
                }
                if (rand() % 4 == 1) { // 25% de chance de aresta de retorno
                    // Arestas de "retorno" (j -> i) devem ter peso positivo para evitar ciclos
                    grafo[j][i] = (rand() % 20) + 1; // [1, 20]
                }
            }
        }
    } else {
        // --- CENÁRIO 2 e 3: GERAÇÃO PADRÃO (PODE OU NÃO TER CICLOS) ---
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (i == j) continue;

                // Apenas adiciona uma aresta se não houver uma (grafo[i][j] == INF)
                // e se o sorteio for positivo (ex: 50% de chance).
                if (grafo[i][j] == INF && (rand() % 2 == 1)) {
                    int peso;
                    if (permitirNegativos) {
                        peso = (rand() % 41) - 20; // [-20, 20]
                        if (peso == 0) peso = 1;
                    } else {
                        peso = (rand() % 20) + 1;  // [1, 20]
                    }
                    grafo[i][j] = peso;
                }
            }
        }

        if (permitirNegativos && controleCiclo == 1) {
            // --- IMPLANTAR UM CICLO NEGATIVO GARANTIDO ---
            printf("Implantando um ciclo de peso negativo garantido.\n");
            if (numVertices >= 3) {
                // Cria um ciclo 0 -> 1 -> 2 -> 0 com soma negativa
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

// void gerarGrafoAleatorio(int** grafo, int num_vertices, double densidade, int 50, int permitir_pesos_negativos) {
//     inicializarMatrizGrafo(grafo, num_vertices);
//     srand((unsigned int)time(NULL));

//     long long max_arestas_possiveis = (long long)num_vertices * (num_vertices - 1);
//     long long arestas_a_adicionar = (long long)(densidade * max_arestas_possiveis);

//     long long arestas_adicionadas = 0;
//     while (arestas_adicionadas < arestas_a_adicionar) {
//         int u = rand() % num_vertices;
//         int v = rand() % num_vertices;

//         if (u == v) continue;

//         if (grafo[u][v] == INF) {
//             int peso;
//             if (permitir_pesos_negativos && (rand() % 100 < 30)) {
//                 peso = -(rand() % max_peso) - 1;
//             } else {
//                 peso = (rand() % max_peso) + 1;
//             }
//             grafo[u][v] = peso;
//             arestas_adicionadas++;
//         }
//     }
// }

// Implementação das funções de impressão
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

// int** carregarGrafo(const char* nomeArquivo, int* V) {
//     FILE* f = fopen(nomeArquivo, "r");
//     if (!f) {
//         printf("Erro ao abrir o arquivo '%s'.\n", nomeArquivo);
//         exit(1);
//     }

//     int A; // Variável para armazenar o número de arestas

//     // Lê o número de vértices (V) e de arestas (A) da primeira linha
//     if (fscanf(f, "%d %d", V, &A) != 2) {
//         printf("Erro ao ler o numero de vertices e arestas.\n");
//         fclose(f);
//         exit(1);
//     }

//     // Declara a variável 'grafo' antes de usar
//     int** grafo;

//     // Aloca a matriz usando o valor de V (*V)
//     grafo = (int**)malloc((*V) * sizeof(int*));
//     for (int i = 0; i < (*V); i++) {
//         grafo[i] = (int*)malloc((*V) * sizeof(int));
//     }

//     // Inicializa a matriz com um valor para "infinito"
//     // (garanta que a constante INF esteja definida em algum lugar)
//     for (int i = 0; i < (*V); i++) {
//         for (int j = 0; j < (*V); j++) {
//             if (i == j) {
//                 grafo[i][j] = 0; // Distância de um nó para ele mesmo é 0
//             } else {
//                 grafo[i][j] = INF; // Ou INF, -1 para indicar ausência de aresta
//             }
//         }
//     }

//     int u, v, peso;
//     // Lê cada aresta do arquivo
//     while (fscanf(f, "%d %d %d", &u, &v, &peso) == 3) {
//         grafo[u][v] = peso;
//         // Se o grafo for não-direcionado, adicione a linha abaixo:
//         // grafo[v][u] = peso;
//     }

//     fclose(f);
//     return grafo; // Retorna o grafo criado
// }

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

    // O número máximo de arestas em um grafo direcionado sem laços é V * (V-1)
    long long maxArestasPossiveis = (long long)numVertices * (numVertices - 1);
    if (numArestas > maxArestasPossiveis) {
        printf("Aviso: O número de arestas solicitado (%d) é maior que o máximo possível (%lld).\n", numArestas, maxArestasPossiveis);
        printf("O grafo será gerado com o número máximo de arestas.\n");
        numArestas = maxArestasPossiveis;
    }

    // 2. Alocação e Inicialização do Grafo
    int** grafo = criarGrafo(numVertices);
    if (grafo == NULL) {
        return NULL; // Falha na alocação
    }
    // Inicializa com 0 na diagonal e INF no resto, passo fundamental!
    inicializarMatrizGrafo(grafo, numVertices);

    // 3. Adição Aleatória das Arestas
    int arestasAdicionadas = 0;
    long long tentativas = 0;
    // Fator de segurança para evitar loop infinito se for difícil encontrar arestas livres
    long long limiteDeTentativas = (long long)numArestas * 10 + numVertices * numVertices; 

    while (arestasAdicionadas < numArestas && tentativas < limiteDeTentativas) {
        int u = rand() % numVertices;
        int v = rand() % numVertices;

        // Tenta novamente se for um laço (u == v) ou se a aresta já existe (grafo[u][v] != INF)
        if (u == v || grafo[u][v] != INF) {
            tentativas++;
            continue;
        }

        // Gera o peso da aresta
        int peso;
        if (permitirNegativos) {
            peso = (rand() % 41) - 20; // Gera peso entre -20 e 20
            if (peso == 0) peso = 1;   // Evita peso 0, se desejado
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