import csv
import matplotlib.pyplot as plt

N = []
seq = []
sen = []
binaria = []
inter = []

with open('resultados.csv', 'r', encoding='utf-16') as arquivo:
    leitor = csv.reader(arquivo)
    next(leitor)
    
    for linha in leitor:
        N.append(int(linha[0]))
        seq.append(int(linha[1]))
        sen.append(int(linha[2]))
        binaria.append(int(linha[3]))
        inter.append(int(linha[4]))


plt.figure(figsize=(10, 6))

plt.plot(N, seq, label='Sequencial', marker='o')
plt.plot(N, sen, label='Sentinela', marker='s')
plt.plot(N, binaria, label='Binária', marker='^', linewidth=2)
plt.plot(N, inter, label='Interpolação', marker='x', linewidth=2)

plt.title('Comparação de Desempenho: Algoritmos de Busca')
plt.xlabel('Tamanho do Vetor (N)')
plt.ylabel('Número de Operações (Custo)')
plt.legend() 
plt.grid(True)

plt.show()