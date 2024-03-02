#!/bin/bash
size=10
for ((i=1; i<=10; i++)); do
    echo "$i"/10
    nodes=$((i*1000))
    #remove old files
    if [ -e output_nodes_"$nodes"_original ]; then
        rm output_nodes_"$nodes"_original
        rm output_nodes_"$nodes"_improved
        rm original_"$nodes"_nodes_time
        rm improved_"$nodes"_nodes_time
        rm input_nodes_"$nodes"_input
    fi
    #generate input
    node generate_input.js $nodes 1000 500 "input_nodes_$nodes"
    exec 3>&1 4>&2
    #run both versions 
    original_time=$( { time ../bin/streamcomp original input_nodes_"$nodes"_input "output_nodes_$nodes" 1>&3 2>&4; } 2>&1 )
    cat output_nodes_"$nodes"_original > output_nodes_"$nodes"_original_1
    improved_time=$( { time ../bin/streamcomp improved input_nodes_"$nodes"_input "output_nodes_$nodes"  1>&3 2>&4; } 2>&1 )
    exec 3>&- 4>&-
    rm output_nodes_"$nodes"_original
    cp output_nodes_"$nodes"_original_1 output_nodes_"$nodes"_original
    rm output_nodes_"$nodes"_original_1
    #comparissions
    echo "Original time for $nodes node" >> original_"$nodes"_nodes_time
    echo $original_time >> original_"$nodes"_nodes_time
    echo "Improved time for $nodes node" >> improved_"$nodes"_nodes_time
    echo $improved_time >> improved_"$nodes"_nodes_time
    resultado=$(diff output_nodes_"$nodes"_original output_nodes_"$nodes"_improved)

    # Verificar se a saída do diff não está vazia
    if [ -n "$resultado" ]; then
        # Se a saída não estiver vazia, imprimir o resultado
        echo "$resultado"
        exit 1
    fi
done