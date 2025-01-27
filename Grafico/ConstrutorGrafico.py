import os
import numpy as np
import matplotlib.pyplot as plt

def ensure_file_exists(file_path):
    if not os.path.exists(file_path):
        with open(file_path, 'w') as f:
            pass  # Cria o arquivo vazio

def plot_curves_from_files(file1_path, file2_path):
    # Garantir que os arquivos existem
    ensure_file_exists(file1_path)
    ensure_file_exists(file2_path)

    # Carregar os dados, ajustando o delimitador para espaço
    try:
        data1 = np.loadtxt(file1_path, delimiter=' ')
        data2 = np.loadtxt(file2_path, delimiter=' ')

        # Divide os dados em coordenadas x e y
        x1, y1 = data1[:, 0], data1[:, 1]
        x2, y2 = data2[:, 0], data2[:, 1]

        # Cria o gráfico
        plt.figure(figsize=(8, 6))
        plt.plot(x1, y1, label='BMSH', color='blue', marker='o')
        plt.plot(x2, y2, label='KMP', color='red', marker='x')

        # Configurações do gráfico
        plt.title('Comparação de tempo entr BMSH e KMP')
        plt.xlabel('padrão de entrada')
        plt.ylabel('tempo (s)') # Segundos
        plt.legend()
        plt.grid(True)
        plt.show()
    except Exception as e:
        print(f"Erro ao carregar ou processar os arquivos: {e}")

# Exemplo de uso
plot_curves_from_files("dados1.txt", "dados2.txt")
