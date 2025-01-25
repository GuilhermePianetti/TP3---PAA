import numpy as np
import matplotlib.pyplot as plt

def plot_curves_from_files(file1_path, file2_path):
    # Carrega os dados, ajustando o delimitador para espaço
    data1 = np.loadtxt(file1_path, delimiter=' ')
    data2 = np.loadtxt(file2_path, delimiter=' ')

    # Divide os dados em coordenadas x e y
    x1, y1 = data1[:, 0], data1[:, 1]
    x2, y2 = data2[:, 0], data2[:, 1]

    # Cria o gráfico
    plt.figure(figsize=(8, 6))
    plt.plot(x1, y1, label='Curva 1', color='blue', marker='o')
    plt.plot(x2, y2, label='Curva 2', color='red', marker='x')

    # Configurações do gráfico
    plt.title('Curvas geradas pelos arquivos')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.legend()
    plt.grid(True)
    plt.show()

# Exemplo de uso
plot_curves_from_files('dados1.txt', 'dados2.txt')
