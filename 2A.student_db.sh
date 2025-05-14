#!/bin/bash

DB="student_database.txt"

# Create database
create_database() {
    echo -n > "$DB"
    echo "Database created successfully!"
}

# View database
view_database() {
    if [ ! -s "$DB" ]; then
        echo "Database is empty!"
        return
    fi
    echo "----- Student Database -----"
    awk 'BEGIN {
        printf "%-10s %-15s %-5s %-10s %-6s\n", "RollNo", "Name", "Age", "Dept", "Marks"
        print "-----------------------------------------------------"
    }
    {
        printf "%-10s %-15s %-5s %-10s %-6s\n", $1, $2, $3, $4, $5
    }' "$DB"
}

# Insert record
insert_record() {
    echo "Enter Roll Number:"
    read roll
    echo "Enter Name:"
    read name
    echo "Enter Age:"
    read age
    echo "Enter Department:"
    read dept
    echo "Enter Marks:"
    read marks
    echo "$roll $name $age $dept $marks" >> "$DB"
    echo "Record inserted!"
}

# Delete a record
delete_record() {
    echo "Enter Roll Number to delete:"
    read roll
    awk -v r="$roll" '$1 != r' "$DB" > temp && mv temp "$DB"
    echo "Record deleted if existed."
}

# Modify a record
modify_record() {
    echo "Enter Roll Number to modify:"
    read roll
    awk -v r="$roll" '
    $1 == r {
        print "Current Record: "$0
        found=1
        printf "Enter New Name: "; getline name < "-"
        printf "Enter New Age: "; getline age < "-"
        printf "Enter New Dept: "; getline dept < "-"
        printf "Enter New Marks: "; getline marks < "-"
        print r, name, age, dept, marks
        next
    }
    { print }
    END { if (!found) print "Roll Number not found!" > "/dev/stderr" }
    ' "$DB" > temp && mv temp "$DB"
    echo "Record updated if Roll Number was found."
}

# Show result of a student
student_result() {
    echo "Enter Roll Number:"
    read roll
    awk -v r="$roll" '$1 == r {
        print "Roll No: " $1
        print "Name: " $2
        print "Marks: " $5
        if ($5 >= 40)
            print "Result: PASS"
        else
            print "Result: FAIL"
        found=1
    }
    END {
        if (!found) print "Student not found!"
    }' "$DB"
}

# Menu loop
while true; do
    echo ""
    echo "========== Student Database Menu =========="
    echo "a) Create Database"
    echo "b) View Database"
    echo "c) Insert Record"
    echo "d) Delete Record"
    echo "e) Modify Record"
    echo "f) Result of a Student"
    echo "g) Exit"
    echo "Choose an option:"
    read choice

    case $choice in
        a) create_database ;;
        b) view_database ;;
        c) insert_record ;;
        d) delete_record ;;
        e) modify_record ;;
        f) student_result ;;
        g) echo "Exiting..."; break ;;
        *) echo "Invalid choice. Try again." ;;
    esac
done


# nano student_db.sh
# chmod +x student_db.sh
# ./student_db.sh
