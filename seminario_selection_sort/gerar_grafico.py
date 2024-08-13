import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import re

# Arquivo de log e arquivo de saída do gráfico
input_log_file = '/home/barbara/Documentos/Barbara/ufrr/Análise de Algoritmo/SelectionSortSeminario/log_tempo_execucao.txt'
output_graph_file = '/home/barbara/Documentos/Barbara/ufrr/Análise de Algoritmo/SelectionSortSeminario/grafico_tempo_execucao.png'

# Função para extrair dados do arquivo de log
def parse_log_file(log_file):
    data = []
    with open(log_file, 'r') as file:
        for line in file:
            match = re.search(r'Quantidade de números: (\d+), Tempo de execução: ([\d.]+) segundos', line)
            if match:
                quantity = int(match.group(1))
                time = float(match.group(2))
                data.append((quantity, time))
    return data

# Carregar dados do log
data = parse_log_file(input_log_file)
df = pd.DataFrame(data, columns=['Quantidade', 'Tempo'])

# Ordenar os dados por quantidade de números
df = df.sort_values('Quantidade')

# Criar o gráfico
plt.figure(figsize=(10, 6))
plt.plot(df['Quantidade'], df['Tempo'], marker='o', linestyle='-', color='b', label='Dados')

# Ajustar o eixo X para escala logarítmica e o eixo Y para escala linear
plt.xscale('log')
plt.yscale('linear')
plt.xlabel('Quantidade de Números')
plt.ylabel('Tempo de Execução (segundos)')
plt.title('Quantidade de Números vs Tempo de Execução')
plt.grid(True, which='both', linestyle='--', linewidth=0.5)

# Ajustar ticks no eixo X para mostrar potências de 10
plt.gca().set_xticks([10**i for i in range(int(np.log10(df['Quantidade'].max())) + 1)])
plt.gca().get_xaxis().set_major_formatter(plt.ScalarFormatter())

# Ajustar curva de tendência polinomial
coefficients = np.polyfit(np.log10(df['Quantidade']), df['Tempo'], 2)
polynomial = np.poly1d(coefficients)
x_values = np.linspace(df['Quantidade'].min(), df['Quantidade'].max(), 100)
y_values = polynomial(np.log10(x_values))

# Plotar a curva de tendência
plt.plot(x_values, y_values, color='r', linestyle='--', label='Curva de Tendência')

plt.legend()
plt.savefig(output_graph_file)
plt.show()

print(f"Gráfico salvo em {output_graph_file}")
