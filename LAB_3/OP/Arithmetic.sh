#!/bin/bash

# reading data from the user
read -r -p "Enter a: " a

read -r -p "Enter b: " b

add=$((a+b))
echo "Addition of a and b are: "${add}

sub=$((a-b))
echo "Subtraction of a and b are: "${sub}

mul=$((a*b))
echo "Multiplication of a and b are: "${mul}

div=$((a/b))
echo "Division of a and b are: "${div}

mod=$((a%b))
echo "Modulis of a and b are: "${mod}

((++a))
echo "Increment operator when applied on $a results into a :" "${a}"

((--b))
echo "Decrement operator when applied on 'b' results into b :" "${b}"
