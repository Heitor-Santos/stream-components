if [ $# -ge 2 ]; then
    arg1="$1"
    arg2="$2"
    if [ $# -ge 3 ]; then
        arg3="$3"
        bin/streamcomp "$arg1" "$arg2" "$arg3"
    else 
        bin/streamcomp "$arg1" "$arg2"
    fi
else
    echo "Erro: Pelo menos dois argumentos são necessários"
fi