import random


def gerar_entrada_aleatoria(n_max=100000, arquivo='entrada.txt'):

    N = int(input("Tamanho da entrada: "))
    sequencia = [random.randint(1, 100) for _ in range(N)]

    with open(arquivo, 'w') as f:
        f.write(f"{N}\n")
        f.write(" ".join(map(str, sequencia)) + '\n')

gerar_entrada_aleatoria()