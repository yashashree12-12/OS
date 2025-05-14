#!/bin/bash

# Check if 3 arguments are passed
if [ $# -ne 3 ]; then
    echo "Usage: $0 num1 num2 num3"
    exit 1
fi

a=$1
b=$2
c=$3

# Compare numbers
if [ $a -ge $b ] && [ $a -ge $c ]; then
    echo "$a is the biggest"
elif [ $b -ge $c ]; then
    echo "$b is the biggest"
else
    echo "$c is the biggest"
fi


# Run Example:

# bash
# ./biggest.sh 5 12 8