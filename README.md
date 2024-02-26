# stream-components
##  Compilação

    cd src
    make
    
## Modo de uso

    cd bin
    ./streamcomp algorithm input-file output-file
Os valores de algorithm podem ser:

 - `original`: Implementação original com report ao final.
 - `foriginal:` Implementação original com report a cada batch de dados.
 - `improved`: Implementação sugerida com report ao final.
 - `fimproved`: Implementação sugerida com report a cada batch de dados.
 - `debug`: Vai rodar as duas implementações ao mesmo tempo e encerrar o programa na primeira divergência. Tem report a cada batch de dados.

## Entrada
O arquivo de entrada deve conter várias sequências da seguinte forma:

    $node_to_be_insert
    $removed_nodes
    $incoming_edges
    edges_end
    $outgoing_edges
    edges_end
   Por exemplo:

    94616
    
    edges_end
    edges_end
    96638
    
    edges_end
    edges_end
   Um exemplo mais longo pode ser encontrado [aqui](https://drive.google.com/file/d/1Jxn8oy38i_haiy7QU1yd5_K2bf7QUy3Z/view?usp=sharing)
