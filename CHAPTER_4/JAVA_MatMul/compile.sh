#!/bin/bash

# Biên dịch các file Java
javac MatrixGenerator.java
javac MatrixMultiplication.java
javac MatrixMultiplicationThread.java
javac MatrixMultiplicationForkJoin.java


# Kiểm tra xem việc biên dịch có thành công hay không
if [ $? -eq 0 ]; then
    echo "Biên dịch thành công!"
else
    echo "Biên dịch thất bại!"
fi
