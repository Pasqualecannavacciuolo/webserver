#!/bin/bash

# Creazione cartella di output
mkdir -p output output/endpoints output/log output/connection

# Compila con Makefile
make

# Esegui
./server