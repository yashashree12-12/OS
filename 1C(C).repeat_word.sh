#!/bin/bash

# Check if 2 arguments are passed
if [ $# -ne 2 ]; then
    echo "Usage: $0 N word"
    exit 1
fi

N=$1
word=$2

for ((i=1; i<=N; i++)); do
    echo "$word"
done


# ./repeat_word.sh 5 Hello