#!/bin/bash

factorial() {
    echo "Enter a number:"
    read n
    fact=1
    for ((i=1; i<=n; i++)); do
        fact=$((fact * i))
    done
    echo "Factorial of $n is $fact"
}

greatest_of_three() {
    echo "Enter three numbers:"
    read a b c
    if [ $a -ge $b ] && [ $a -ge $c ]; then
        echo "$a is greatest"
    elif [ $b -ge $c ]; then
        echo "$b is greatest"
    else
        echo "$c is greatest"
    fi
}

check_prime() {
    echo "Enter a number:"
    read n
    if [ $n -le 1 ]; then
        echo "Not a prime number"
        return
    fi
    for ((i=2; i*i<=n; i++)); do
        if ((n % i == 0)); then
            echo "$n is not prime"
            return
        fi
    done
    echo "$n is prime"
}

check_num_palindrome() {
    echo "Enter a number:"
    read n
    temp=$n
    rev=0
    while [ $n -gt 0 ]; do
        digit=$((n % 10))
        rev=$((rev * 10 + digit))
        n=$((n / 10))
    done
    if [ $temp -eq $rev ]; then
        echo "$temp is a palindrome"
    else
        echo "$temp is not a palindrome"
    fi
}

check_str_palindrome() {
    echo "Enter a string:"
    read str
    rev=$(echo "$str" | rev)
    if [ "$str" = "$rev" ]; then
        echo "$str is a palindrome"
    else
        echo "$str is not a palindrome"
    fi
}

# Main menu
while true; do
    echo ""
    echo "======= Math Menu ======="
    echo "a) Factorial"
    echo "b) Greatest of Three Numbers"
    echo "c) Prime Check"
    echo "d) Number Palindrome"
    echo "e) String Palindrome"
    echo "f) Exit"
    echo "Choose option:"
    read opt

    case $opt in
        a) factorial ;;
        b) greatest_of_three ;;
        c) check_prime ;;
        d) check_num_palindrome ;;
        e) check_str_palindrome ;;
        f) echo "Exiting..."; break ;;
        *) echo "Invalid option." ;;
    esac
done


# nano math_menu.sh
# chmod +x math_menu.sh
# ./math_menu.sh
