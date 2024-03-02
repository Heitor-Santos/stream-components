#!/bin/bash
size=10
for ((i=1; i<=1000; i++)); do
    echo "$i"/100
    nodes=$((size*100))
    rm output_nodes_"$nodes"_original
    rm output_nodes_"$nodes"_improved
    rm original_"$nodes"_nodes_time
    rm improved_"$nodes"_nodes_time
    rm input_nodes_"$nodes"_input
    node generate_input.js $nodes 1000 500 "input_nodes_$nodes"
    original_time=$(../bin/streamcomp original input_nodes_"$nodes"_input "output_nodes_$nodes")
    cat output_nodes_"$nodes"_original > output_nodes_"$nodes"_original_1
    improved_time=$(../bin/streamcomp improved input_nodes_"$nodes"_input "output_nodes_$nodes")
    rm output_nodes_"$nodes"_original
    cp output_nodes_"$nodes"_original_1 output_nodes_"$nodes"_original
    rm output_nodes_"$nodes"_original_1
    echo "Original time for $nodes node" >> original_"$nodes"_nodes_time
    # echo $original_time >> original_"$nodes"_nodes_time
    echo "Improved time for $nodes node" >> improved_"$nodes"_nodes_time
    #echo $improved_time >> improved_"$nodes"_nodes_time
    resultado=$(diff output_nodes_"$nodes"_original output_nodes_"$nodes"_improved)

    # Verificar se a saída do diff não está vazia
    if [ -n "$resultado" ]; then
        # Se a saída não estiver vazia, imprimir o resultado
        echo "$resultado"
        exit 1
    fi
done