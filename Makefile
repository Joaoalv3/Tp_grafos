# Nome do compilador
CC = gcc

# Flags de compilação (avisos, padrão do C, etc.)
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Nome do executável final
EXECUTAVEL = $(BIN_DIR)/grafo_analise

# Encontra todos os arquivos fonte .c no diretório src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gera a lista de arquivos objeto correspondentes na pasta obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Regra padrão: o que acontece quando você digita apenas "make"
all: $(EXECUTAVEL)

# --- ADICIONE A REGRA 'RUN' AQUI ---
# Regra para compilar (se necessário) e executar o programa
run: all
	@echo "--- Executando o programa ---"
	./$(EXECUTAVEL)
	@echo "--- Programa finalizado ---"

# Regra para linkar os objetos e criar o executável final
$(EXECUTAVEL): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(EXECUTAVEL)

# Regra para compilar cada arquivo .c em um arquivo .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de limpeza: apaga os arquivos gerados
clean:
	@echo "Limpando arquivos gerados..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)