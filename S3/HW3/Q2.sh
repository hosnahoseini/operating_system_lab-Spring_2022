# !/bin/bash

echo "Enter first numbers : "
read a

re='^[-+]?^[0-9]+$'
if ! [[ $a =~ $re ]]
then
   echo "Error: '$a' is not a number"
   exit 1
fi

# Input type of operation
echo "Enter Operation (+, -, X, /):"
read ch

echo "Enter second numbers : "
read b

if ! [[ $b =~ $re ]]
then
   echo "Error: '$b' is not a number"
   exit 1
fi

if [ $b -eq 0 ]&&[ $ch = "/" ]
then
    echo "Error: zero division!"
    exit 1
fi

# Switch Case to perform
# calculator operations
case $ch in
+)((res= $a + $b))
;;
-)((res= $a - $b))
;;
X)((res= $a * $b))
;;
/)res=`echo "scale=2 ; $a / $b" | bc`
;;
*)res=`echo INVALID format`
;;
esac
echo "Result : $res"
