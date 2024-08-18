# Memória Virtual e Páginas de Memória em C

## Descrição

Este projeto é uma atividade da disciplina de **Análise de Algoritmos** da **Universidade Federal de Roraima** (UFRR), realizada no semestre 2024.1. O objetivo do código é demonstrar o uso de memória virtual e páginas de memória em um programa escrito em C. Ele faz uso da função `mmap` para alocar dinamicamente uma página de memória, escreve dados nessa página, e em seguida, exibe o conteúdo escrito. Por fim, o código libera a memória alocada utilizando a função `munmap`.

### Funcionalidades

- Alocação de uma página de memória virtual.
- Escrita de um arquivo "biblia.txt" nessa memória.
- Exibição do conteúdo da memória alocada.
- Liberação da memória virtual após o uso.


## Como Executar

### Requisitos

- Sistema operacional Linux (testado no Linux Mint).
- GCC (GNU Compiler Collection) instalado.

### Passos para Compilar e Executar

1. **Clone o repositório ou crie um arquivo de código-fonte:**
   
   Se estiver criando o arquivo manualmente:
   ```bash
   nano exemplo_mmap.c
   ```

   Em seguida, copie e cole o código no arquivo.

2. **Compile o código usando o GCC:**

   ```bash
   gcc -o exemplo_mmap exemplo_mmap.c
   ```

   Este comando compilará o código e gerará um executável chamado `exemplo_mmap`.

3. **Execute o programa:**

   ```bash
   ./exemplo_mmap
   ```

   O programa imprimirá o tamanho da página de memória e o texto que foi escrito na memória virtual.

## Autor

Atividade realizada como parte da disciplina de **Análise de Algoritmos** na **Universidade Federal de Roraima (UFRR)**, semestre 2024.1. Feito pela aluna **Bárbara Zamperete**.
