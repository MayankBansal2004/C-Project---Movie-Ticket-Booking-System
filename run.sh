#!/bin/bash

gcc -c movie_system.c -o movie_system.o

ar rcs mylib.a movie_system.o

# Compile the C program with the necessary libraries
gcc -o main main.c -L. -l:mylib.a

# Run the compiled program
./main