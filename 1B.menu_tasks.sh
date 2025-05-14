#!/bin/bash

factorial() {
    read -p "Enter number: " num
    fact=1
    for ((i=1; i<=num; i++)); do
        fact=$((fact * i))
    done
    echo "Factorial of $num is $fact"
}

greatest() {
    read -p "Enter three numbers: " a b c
    if ((a >= b && a >= c)); then
        echo "$a is greatest"
    elif ((b >= c)); then
        echo "$b is greatest"
    else
        echo "$c is greatest"
    fi
}

is_prime() {
    read -p "Enter number: " num
    if ((num <= 1)); then
        echo "Not Prime"
        return
    fi
    for ((i=2; i<=num/2; i++)); do
        if ((num % i == 0)); then
            echo "Not Prime"
            return
        fi
    done
    echo "Prime Number"
}

num_palindrome() {
    read -p "Enter number: " num
    rev=0
    temp=$num
    while ((num > 0)); do
        r=$((num % 10))
        rev=$((rev * 10 + r))
        num=$((num / 10))
    done
    [[ $temp -eq $rev ]] && echo "Palindrome" || echo "Not Palindrome"
}

string_palindrome() {
    read -p "Enter string: " str
    rev=$(echo "$str" | rev)
    [[ "$str" == "$rev" ]] && echo "Palindrome" || echo "Not Palindrome"
}

while true; do
    echo ""
    echo "===== MENU ====="
    echo "1. Factorial"
    echo "2. Greatest of 3 numbers"
    echo "3. Prime check"
    echo "4. Number Palindrome"
    echo "5. String Palindrome"
    echo "6. Exit"
    read -p "Enter choice: " ch

    case $ch in
        1) factorial ;;
        2) greatest ;;
        3) is_prime ;;
        4) num_palindrome ;;
        5) string_palindrome ;;
        6) exit ;;
        *) echo "Invalid choice" ;;
    esac
done

# nano 1B.menu_tasks.sh
# chmod +x 1B.menu_tasks.sh
# ./1B.menu_tasks.sh
