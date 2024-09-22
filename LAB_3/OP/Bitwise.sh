#!/bin/bash

#reading data from the user
read -p 'Enter a : ' a
read -p 'Enter b : ' b

bitwiseAND=$(( a&b ))
echo Bitwise AND of a and b is $bitwiseAND

bitwiseOR=$(( a|b ))
echo Bitwise OR of a and b is $bitwiseOR

bitwiseXOR=$(( a^b ))
echo Bitwise XOR of a and b is $bitwiseXOR

bitiwiseComplement=$(( ~a ))
echo Bitwise Compliment of a is $bitiwiseComplement

leftshift=$(( a<<1 ))
echo Left Shift of a is $leftshift

rightshift=$(( b>>1 ))
echo Right Shift of b is $rightshift
