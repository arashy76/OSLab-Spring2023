#! /bin/bash

echo "Enter the number A : "
read a
echo "Enter the number B : "
read b

while [ $a -gt 0 ]
do
    a=$(( a - 2 ))
done

if [ $a -eq 0 ]
then
    echo $b
else
    b=$(( b * b * b))
    echo $b
fi

echo "Hello finished"

