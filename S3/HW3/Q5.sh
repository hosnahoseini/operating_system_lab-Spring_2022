# !/bin/bash
function shape_1(){
    for i in {1..5}
    do
        for j in `seq $i`
        do
            echo -n $i
        done
        echo
    done
}

function shape_2(){
    for i in {1..6}
    do
        ((num_of_space = 6-$i))
        for sapce in `seq $num_of_space`
        do
            echo -n " "
        done

        for j in `seq $i`
        do
            echo -n ". "
        done
        echo
    done

    for i in {6..1..-1}
    do
        
        ((num_of_space = 6-$i))
        for sapce in `seq $num_of_space`
        do
            echo -n " "
        done

        for j in `seq $i`
        do
            echo -n ". "
        done
        echo
    done
}

function shape_3(){
    for i in {1..5}
    do
        ((num_of_line = $i-1))
        for j in `seq $num_of_line`
        do
            echo -n "| "
        done
        echo "|_"
    done
}

echo "Enter number (1, 2, 3): "
read n

case $n in
1)shape_1
;;
2)shape_2
;;
3)shape_3
;;
*)echo "Error: enter a valid input!"
;;
esac