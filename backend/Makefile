# Variabili
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Nome dell'eseguibile
TARGET = server

# Directory di output per i file oggetto
OBJ_DIR = output

# File sorgente
SRCS = $(wildcard *.c) $(wildcard endpoints/*.c) $(wildcard log/*.c) $(wildcard connection/*.c)

# File oggetto generati dalla compilazione
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Regola predefinita
all: $(TARGET)
	@echo "\033[0;32m✅ Compilazione completata con successo\033[0m"

# Crea la directory di output se non esiste
#$(OBJ_DIR):
#	mkdir -p $(OBJ_DIR)

# Regola per la creazione della directory output/endpoints
#$(OBJ_DIR)/endpoints:
#	mkdir -p $(OBJ_DIR)/endpoints

# Regola per la creazione della directory output/formatters
#$(OBJ_DIR)/formatters:
#	mkdir -p $(OBJ_DIR)/formatters

# Regola per la compilazione dell'eseguibile
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regola generica per la compilazione dei file oggetto
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Pulizia degli oggetti e dell'eseguibile
clean:
	$(RM) $(TARGET) $(OBJS)
