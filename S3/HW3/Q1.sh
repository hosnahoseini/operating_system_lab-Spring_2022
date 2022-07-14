#!/bin/bash

if [ $# -lt 2 ]
then
    echo "Error: You should enter two number!"
	exit 1
fi

re='^[-+]?^[0-9]+$'

if ! [[ $1 =~ $re ]]
then
   echo "Error: '$1' is not a number"
   exit 1
fi

if ! [[ $2 =~ $re ]]
then
   echo "Error: '$2' is not a number"
   exit 1
fi


((num1 = $1))
((num2 = $2))
((result = $num1 + $num2))
echo "sum is = $result"

if [ $num1 -gt $num2 ]
then
	echo "larger number = $num1"
else
	echo "larger number = $num2"
fi




