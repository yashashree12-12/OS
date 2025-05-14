#!/bin/bash

# Check if 1 argument is passed
if [ $# -ne 1 ]; then
    echo "Usage: $0 number"
    exit 1
fi

num=$1
rev=0

while [ $num -gt 0 ]; do
    digit=$((num % 10))
    rev=$((rev * 10 + digit))
    num=$((num / 10))
done

echo "Reversed number: $rev"

# RUN
# ./reverse.sh 1234