#!/bin/bash

DB="student_db.txt"

# Create file if it doesn't exist
if [ ! -f "$DB" ]; then
    touch "$DB"
fi   

add_student() {
    echo "Enter Roll Number:"
    read roll
    echo "Enter Name:"
    read name
    echo "Enter Age:"
    read age
    echo "Enter Department:"
    read dept

    if grep -q "^$roll " "$DB"; then
        echo "Student with Roll No $roll already exists!"
    else
        echo "$roll $name $age $dept" >> "$DB"
        echo "Student added!"
    fi
}

view_students() {
    echo "----- Student List -----"
    awk '{ print "Roll No: " $1 ", Name: " $2 ", Age: " $3 ", Department: " $4 }' "$DB"
}

search_student() {
    echo "Enter Roll Number to search:"
    read roll
    result=$(grep "^$roll " "$DB")
    if [ -n "$result" ]; then
        echo "Student found: $result"
    else
        echo "Student not found."
    fi
}

delete_student() {
    echo "Enter Roll Number to delete:"
    read roll
    if grep -q "^$roll " "$DB"; then
        grep -v "^$roll " "$DB" > temp && mv temp "$DB"
        echo "Student deleted."
    else
        echo "Student not found."
    fi
}

update_student() {
    echo "Enter Roll Number to update:"
    read roll
    if grep -q "^$roll " "$DB"; then
        echo "Enter new Name:"
        read name
        echo "Enter new Age:"
        read age
        echo "Enter new Department:"
        read dept

        grep -v "^$roll " "$DB" > temp
        echo "$roll $name $age $dept" >> temp
        mv temp "$DB"
        echo "Student updated."
    else
        echo "Student not found."
    fi
}

# Main menu
while true; do
    echo ""
    echo "=== Student Database Menu ==="
    echo "1. Add Student"
    echo "2. View Students"
    echo "3. Search Student"
    echo "4. Update Student"
    echo "5. Delete Student"
    echo "6. Exit"
    echo "Choose an option:"
    read choice

    case $choice in
        1) add_student ;;
        2) view_students ;;
        3) search_student ;;
        4) update_student ;;
        5) delete_student ;;
        6) echo "Goodbye!"; exit ;;
        *) echo "Invalid option. Try again." ;;
    esac
done

# nano student_db.sh
# chmod +x student_db.sh
# ./student_db.sh
