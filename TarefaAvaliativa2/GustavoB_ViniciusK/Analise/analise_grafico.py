import numpy as np
import matplotlib.pyplot as plt
import csv

tamanhos = []
medias = []

try:
    with open('resultados.csv', 'r') as file:
        reader = csv.reader(file)
        next(reader) 
        for row in reader:
            tamanhos.append(int(row[0]))
            medias.append(float(row[1]))
except FileNotFoundError:
    print("Arquivo resultados.csv não encontrado. Execute o experimento em C primeiro.")
    exit()

x = np.array(tamanhos)
y = np.array(medias)


coeficientes = np.polyfit(x, y, 2) # PRIMEIRO GRAU
polinomio = np.poly1d(coeficientes)
y_ajustado = polinomio(x)

plt.figure(figsize=(10, 6))
plt.scatter(x, y, color='blue', label='Média Empírica (Iterações por Inserção)', zorder=5)
plt.plot(x, y_ajustado, color='red', linestyle='--', 
         label = f'Ajuste Linear (polyfit): y = {coeficientes[0]:.2e}x + {coeficientes[1]:.4f}')

plt.title('Desempenho da Inserção em Heap Priority Queue')
plt.xlabel('Tamanho da Base (N)')
plt.ylabel('Média de Iterações de Heapification')
plt.grid(True, linestyle=':', alpha=0.7)
plt.legend()

plt.savefig('grafico_resultados.png', dpi=300, bbox_inches='tight')
plt.show()