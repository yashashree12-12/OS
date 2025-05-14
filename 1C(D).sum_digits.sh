#!/bin/bash

# Check if exactly 1 argument is passed
if [ $# -ne 1 ]; then
    echo "Usage: $0 4-digit-number"
    exit 1
fi

num=$1

# Check if the number is 4-digit
if ! [[ $num =~ ^[0-9]{4}$ ]]; then
    echo "Please enter a valid 4-digit number"
    exit 1
fi

sum=0

while [ $num -gt 0 ]; do
    digit=$((num % 10))
    sum=$((sum + digit))
    num=$((num / 10))
done

echo "Sum of digits: $sum"

# ./sum_digits.sh 1234