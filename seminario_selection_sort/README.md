# Seminário sobre o algoritmo de ordenação Selection SOrt

## Descrição

Este projeto é uma atividade da disciplina de **Análise de Algoritmos** da **Universidade Federal de Roraima** (UFRR), realizada no semestre 2024.1. O objetivo do código fazer a ordenação de números aleatórios com com o algoritimo Selection Sort, medindo o tempo de execução para diferentes tamanhos de entrada. Além disso é feita a comparação com a função relativa ao cálculo da complexidade desse algoritimo **O(n²)**. E também é comparado com outro algoritimo de ordenação que apresenta um melhor desempenho, no caso o Merge Sort, com complexidade O(n log n). Esse trabalho foi feito em dupla pelos alunos: 

- Bárbara Zamperete
- Fernando Rodrigues

### Funcionalidades

- Gerar numeros aleátorios e os armazenar em arquivos .txt dentro do diretório ./numeros_aleatorios
- Ordenar esses numeros usando o Selection Sort ou o Merge Sort (através da função ./main)
- O cálculo do tempo para a ordenação é armazenado nos arquivos de log (log_tempo_execucao.txt e log_tempo_execucao_mergesort.txt)
- Geração dos gráficos e comparação do desempenho desses dois algoritimos em relação ao tempo de execução (grafico.py)
- Os gráficos gerados nos testes realizados estão no diretório ./graficos, contendo o gráfico separado do desempenho de cada algoritimo e o gráfico exibindo ambos os resultados. 