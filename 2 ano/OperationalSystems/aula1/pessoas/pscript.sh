#!/bin/bash

for ((i = 1; i <= $1; i++))
do
    IDADE=$(((RANDOM % 100)+1))
    echo "./pessoas -i Pessoa${i} $IDADE"

    ./pessoas -i Pessoa${i} $IDADE

done
