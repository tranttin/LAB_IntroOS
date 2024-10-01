#!/bin/bash

# Biên dịch các file
gcc -fopenmp -o sum_array_openmp sum_array_openmp.c
gcc -o sum_array_normal sum_array_normal.c

# Chạy các chương trình
echo "Running sum with OpenMP..."
export OMP_NUM_THREADS=4
./sum_array_openmp

echo "Running sum without OpenMP..."
./sum_array_normal
