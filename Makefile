# Makefile

# Variáveis
CC = gcc             # Compilador C
CFLAGS = -Wall -Iinclude # Flags do compilador: -Wall para todos os warnings, -Iinclude para procurar cabeçalhos em 'include/'
LDFLAGS =            # Flags do linker (para bibliotecas externas, por exemplo)
BINDIR = bin         # Diretório para o executável final
OBJDIR = obj         # Diretório para os arquivos objeto
SRC_DIR = src        # Diretório dos arquivos fonte
INCLUDE_DIR = include # Diretório dos arquivos de cabeçalho

# Nome do executável
TARGET = meu_programa

# Lista de arquivos fonte .c
SRCS = $(wildcard $(SRC_DIR)/*.c) # Pega todos os arquivos .c no diretório src/

# Lista de arquivos objeto .o correspondentes aos arquivos fonte
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

.PHONY: all clean run

all: dirs $(BINDIR)/$(TARGET)

# Cria os diretórios de saída se não existirem
dirs:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)

# Regra para compilar o executável final
$(BINDIR)/$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

# Regra genérica para compilar arquivos .c em .o
# $< é o primeiro pré-requisito (o arquivo .c)
# $@ é o nome do target (o arquivo .o)
$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de limpeza: remove arquivos gerados
clean:
	@rm -rf $(OBJDIR) $(BINDIR)

# Regra para executar o programa após a compilação
run: all
	@./$(BINDIR)/$(TARGET)