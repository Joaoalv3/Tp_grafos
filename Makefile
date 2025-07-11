# Makefile

# Variáveis de compilação
CC = gcc
# -Iinclude diz ao compilador para procurar cabeçalhos em 'include/'
# -std=c99 ou gnu99 é bom para garantir recursos C modernos
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = # Para bibliotecas extras, se necessário

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Nome do executável
TARGET = grafo_analise

# Lista de todos os arquivos fonte .c
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Transforma a lista de arquivos .c em .o, colocando-os no diretório OBJ_DIR
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean run dirs

# Regra padrão: compila tudo
all: dirs $(BIN_DIR)/$(TARGET)

# Cria os diretórios de saída se não existirem
dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Regra para linkar os arquivos objeto e criar o executável
$(BIN_DIR)/$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

# Regra genérica para compilar um arquivo .c em um .o
# Compila todos os .c de SRC_DIR para .o em OBJ_DIR
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de limpeza: remove arquivos objeto e o executável
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

# Regra para executar o programa após a compilação
run: all
	@./$(BIN_DIR)/$(TARGET)