import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Função para ler o arquivo de log e extrair os tamanhos de entrada e tempos de execução
def ler_log(arquivo):
    tamanhos = []
    tempos = []
    with open(arquivo, 'r') as f:
        for linha in f:
            partes = linha.split(',')
            tamanho = int(partes[1].split(': ')[1])
            tempo = float(partes[2].split(': ')[1].split()[0])
            tamanhos.append(tamanho)
            tempos.append(tempo)
    return np.array(tamanhos), np.array(tempos)

# Ler os logs do Selection Sort e Merge Sort
# tamanhos_ss, tempos_ss = ler_log('log_tempo_execucao.txt')
tamanhos_ms, tempos_ms = ler_log('log_tempo_execucao_mergesort.txt')

# Criar DataFrames separados para cada algoritmo
# df_selection_sort = pd.DataFrame({
#     'Input_Size': tamanhos_ss,
#     'Time': tempos_ss
# })

df_merge_sort = pd.DataFrame({
    'Input_Size': tamanhos_ms,
    'Time': tempos_ms
})

# Função para plotar os dados
def plot_data(ax, df_ms):
    # Ordenar os dados por 'Input_Size' para garantir que os gráficos sejam ordenados
    # df_ss = df_ss.sort_values('Input_Size')
    df_ms = df_ms.sort_values('Input_Size')
    
    # Plotar o tempo real de execução de cada algoritmo
    # ax.plot(df_ss['Input_Size'], df_ss['Time'], label='Selection Sort')
    ax.plot(df_ms['Input_Size'], df_ms['Time'], label='Merge Sort')
    
    # Adicionar as linhas de complexidade esperada com base no Merge Sort
    input_sizes = np.array(df_ms['Input_Size'])
    
    if len(input_sizes) > 0:
        n_log_n = input_sizes * np.log2(input_sizes)
        n_squared = input_sizes ** 2

        # Usar um fator de escala que se alinhe com o tempo médio de execução do Merge Sort
        scale_factor_nlogn = np.mean(df_ms['Time']) / np.mean(n_log_n)
        scale_factor_nsq = np.mean(df_ms['Time']) / np.mean(n_squared)

        # Escalar as curvas de complexidade
        n_log_n_scaled = n_log_n * scale_factor_nlogn
        n_squared_scaled = n_squared * scale_factor_nsq

        # Plotar as curvas escaladas
        ax.plot(input_sizes, n_log_n_scaled, 'k--', label='O(n log n)')
        # ax.plot(input_sizes, n_squared_scaled, 'r--', label='O(n²)')
    
    ax.set_xlabel('Tamanho da Entrada')
    ax.set_ylabel('Tempo de Execução (segundos)')
    ax.set_title('Desempenho dos Algoritmos de Ordenação')
    ax.legend()
    ax.grid(True)

# Criar o subplot
fig, ax = plt.subplots(figsize=(10, 6))

# Plotar os dados
plot_data(ax, df_merge_sort)
plt.savefig("grafico_mergesort.png")

# Exibir o gráfico
plt.show()
