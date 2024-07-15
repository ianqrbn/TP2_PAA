import random

def gerar_entrada_aleatoria(n, num_testes):
    for i in range(num_testes):
        arquivo = f'entrada_{i+1}.txt'
        with open(arquivo, 'w') as f:
            # Gera uma lista de N inteiros aleatórios, incluindo negativos
            sequencia = [random.randint(-2147483648, 2147483647) for _ in range(n)]
            # Escreve N e a sequência de inteiros no arquivo
            f.write(f"{n}\n")
            f.write(" ".join(map(str, sequencia)) + '\n')

# Solicita que o usuário determine o tamanho da entrada e o número de testes
try:
    n = int(input("Digite o número de elementos na sequência: "))
    num_testes = int(input("Digite o número de testes: "))
    if n >= 0 and num_testes > 0:
        gerar_entrada_aleatoria(n, num_testes)
        print(f"{num_testes} entradas geradas e salvas em arquivos separados.")
    else:
        print("Por favor, insira valores válidos.")
except ValueError:
    print("Por favor, insira números inteiros válidos.")
