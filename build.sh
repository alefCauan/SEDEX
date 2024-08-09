#!/bin/sh

set -xe

# Compile os arquivos .c localizados na pasta src
gcc  -g src/main.c src/client/client.c src/route/route.c src/delivery/delivery.c src/aux/auxiliary.c src/allocation/allocation.c -Iheader -o saida -lm

# Execute o binário
gdb ./saida