#!/bin/sh

set -xe

# Compile os arquivos .c localizados na pasta src
gcc  -g main.c client.c route.c delivery.c auxiliary.c allocation.c -o saida -lm  

# Execute o binário
./saida
