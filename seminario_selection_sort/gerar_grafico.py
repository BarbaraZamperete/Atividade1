import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import re

# Obter o diretório atual
current_directory = os.getcwd()

# Arquivo de log e arquivo de saída do gráfico
input_log_file = os.path.join(current_directory, 'log_tempo_execucao.txt')
output_graph_file = os.path.join(current_directory, 'grafico_tempo_execucao.png')

# Exibir o caminho completo do arquivo de log para verificar se está correto
print(f"Caminho do arquivo de log: {input_log_file}")

# Função para extrair dados do arquivo de log
def parse_log_file(log_file):
    data = []
    try:
        with open(log_file, 'r', encoding='utf-8') as file:
            content = file.read()
            print(f"Conteúdo do arquivo de log:\n{content}")  # Exibir o conteúdo do arquivo de log

            # Ajustar a expressão regular
            for line in content.splitlines():
                match = re.search(r'quantidade de numeros: (\d+), Tempo de execucao: ([\d.]+) segundos', line)
                if match:
                    quantity = int(match.group(1))
                    time = float(match.group(2))
                    data.append((quantity, time))
    except FileNotFoundError:
        print("Erro: O arquivo de log não foi encontrado.")
    return data

# Carregar dados do log
data = parse_log_file(input_log_file)
df = pd.DataFrame(data, columns=['Quantidade', 'Tempo'])

# Verificar se o DataFrame não está vazio
if df.empty:
    print("Erro: O DataFrame está vazio. Verifique se o arquivo de log foi lido corretamente.")
    exit()

# Exibir os dados carregados para debugging
print(df)

# Ordenar os dados por quantidade de números
df = df.sort_values('Quantidade')

# Plotar os dados reais
plt.plot(df['Quantidade'], df['Tempo'], color='blue',  linestyle='-', label='Dados Reais')

# Plotar a função de custo teórica
quantidades = np.linspace(1000, 100000, 500)
tempos_teoricos = (quantidades / 1000)**2 * 0.01  # Ajustar o fator de escala para comparar visualmente
plt.plot(quantidades, tempos_teoricos, color='red', linestyle='--', label='O(n^2) Teórica')
custo = ((quantidades/1000)**2*0.01-1)/2
plt.plot(quantidades, custo, color='green', linestyle='--', label='T(n) = n^2-1/2')

# Adicionar rótulos e legenda
plt.xlabel('Quantidade de Entradas')
plt.ylabel('Tempo de Execução (s)')
plt.title('Tempo de Execução vs Quantidade de Entradas')
plt.legend()
plt.grid(True)

#Salvar gráfico
plt.savefig(output_graph_file)
# Mostrar o gráfico
plt.show()


print(f"Gráfico salvo em {output_graph_file}")
