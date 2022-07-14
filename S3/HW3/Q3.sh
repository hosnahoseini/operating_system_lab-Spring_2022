# !/bin/bash

function reverse_number(){
    ((temp=$number))
    ((reverse=0))
    while [ $temp -gt 0 ]
    do
        ((reverse=$reverse * 10 + ($temp % 10)))
        ((temp=$temp/10))
    done
    echo "reverse = $reverse"
}

function sum_of_digit(){
    ((sum=0))
    while [ $number -gt 0 ]
    do
        ((sum=$sum + $number%10))
        ((number=$number/10))
    done
    echo "sum of digits = $sum"
}

while [ true ]
do

    echo "Enter number:"
    read number
    
    re='^[-+]?^[-+]?^[0-9]+$'
    if ! [[ $number =~ $re ]]
    then
    echo "Error: '$number' is not a number"
    exit 1
    fi


    reverse_number
    sum_of_digit
done