#!/bin/bash
gcc -O3 ./LRU/project3_LRU.c -o ./LRU/project3_LRU.o
./LRU/project3_LRU.o ./LRU/P3.lis 1024
./LRU/project3_LRU.o ./LRU/P3.lis 2048
./LRU/project3_LRU.o ./LRU/P3.lis 4096
./LRU/project3_LRU.o ./LRU/P3.lis 8192
gcc -O3 ./ARC/project3_ARC.c -o ./ARC/project3_ARC.o
./ARC/project3_ARC.o ./ARC/P3.lis 1024
./ARC/project3_ARC.o ./ARC/P3.lis 2048
./ARC/project3_ARC.o ./ARC/P3.lis 4096
./ARC/project3_ARC.o ./ARC/P3.lis 8192



