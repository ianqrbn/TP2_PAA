#!/bin/bash

NUM_TESTES=10  # Altere conforme necessário
RESULTS_lfILE="resultados5.txt"

# Garantir que o locale use ponto como separador decimal
export LC_NUMERIC="en_US.UTf-8"

# Limpar o arquivo de resultados
echo "estrategia,arquivo,tempo_real,tempo_usuario,tempo_sistema" > $RESULTS_lfILE

for i in $(seq 1 $NUM_TESTES); do
    ARQUIVO="entrada_$i.txt"
    
    # Medir o tempo de execução para a estratégia D
    echo "Executando teste no arquivo $ARQUIVO com estratégia D"
    TEMPOS_D=$( { /usr/bin/time -f "%e %U %S" ./tp2 D $ARQUIVO > /dev/null; } 2>&1 )
    TEMPO_REAL_D=$(echo $TEMPOS_D | awk '{print $1}')
    TEMPO_USUARIO_D=$(echo $TEMPOS_D | awk '{print $2}')
    TEMPO_SISTEMA_D=$(echo $TEMPOS_D | awk '{print $3}')
    printf "D,%s,%.6f,%.6f,%.6f\n" "$ARQUIVO" "$TEMPO_REAL_D" "$TEMPO_USUARIO_D" "$TEMPO_SISTEMA_D" >> $RESULTS_lfILE

    # Medir o tempo de execução para a estratégia M
    echo "Executando teste no arquivo $ARQUIVO com estratégia M"
    TEMPOS_M=$( { /usr/bin/time -f "%e %U %S" ./tp2 M $ARQUIVO > /dev/null; } 2>&1 )
    TEMPO_REAL_M=$(echo $TEMPOS_M | awk '{print $1}')
    TEMPO_USUARIO_M=$(echo $TEMPOS_M | awk '{print $2}')
    TEMPO_SISTEMA_M=$(echo $TEMPOS_M | awk '{print $3}')
    printf "M,%s,%.6f,%.6f,%.6f\n" "$ARQUIVO" "$TEMPO_REAL_M" "$TEMPO_USUARIO_M" "$TEMPO_SISTEMA_M" >> $RESULTS_lfILE
done
