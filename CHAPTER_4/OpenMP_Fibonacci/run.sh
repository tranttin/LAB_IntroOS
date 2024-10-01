#!/bin/bash

# Biên dịch các file
gcc -fopenmp -o fibonacci_openmp fibonacci_openmp.c
gcc -o fibonacci_normal fibonacci_normal.c

# Chạy các chương trình
echo "Running Fibonacci with OpenMP..."
./fibonacci_openmp

echo "Running Fibonacci without OpenMP..."
./fibonacci_normal
