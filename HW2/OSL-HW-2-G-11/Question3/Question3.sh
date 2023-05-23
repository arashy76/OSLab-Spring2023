#!/bin/bash

read -p "Please enter a number greater than 100: " number

if ((number <= 100)); then
    echo "Error: The number should be greater than 100."
    exit 1
fi

echo "Prime numbers less than $number:"
for ((i = 2; i < number; i++)); do
    is_prime=true

    for ((j = 2; j < i; j++)); do
        if ((i % j == 0)); then
            is_prime=false
            break
        fi
    done

    if [ "$is_prime" = true ]; then
        echo "$i"
    fi
done
