import matplotlib.pyplot as plt
import numpy as np

def plot_curves_from_files(file1_path, file2_path):
    # carrrega os dados do primeiro arquivo
    data1 = np.loadtxt(file1_path, delimiter=',')
    x1, y1 = data1[:, 0], data1[:, 1]
    
    # carrrega os dados do segundo arquivo
    data2 = np.loadtxt(file2_path, delimiter=',')
    x2, y2 = data2[:, 0], data2[:, 1]
    
    # cria o gráfico
    plt.figure(figsize=(10, 6))
    plt.plot(x1, y1, label='Curve 1', color='blue', marker='o')
    plt.plot(x2, y2, label='Curve 2', color='red', marker='x')
    
    # Adiciona título, rótulos e legenda
    plt.title('Comparison of Two Curves')
    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')
    plt.legend()
    plt.grid(True)
    
    # Exibe o gráfico
    plt.show()

if __name__ == "__main__":
    plot_curves_from_files('curve1_data.txt', 'curve2_data.txt')