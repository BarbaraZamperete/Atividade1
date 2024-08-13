# Implementação de Árvores AVL e Rubro-Negras

Este repositório contém implementações de duas estruturas de dados importantes em ciência da computação: Árvores AVL e Árvores Rubro-Negras. Ambas são tipos de árvores binárias de busca balanceadas que garantem operações eficientes de inserção, remoção e busca.

## Arquivos

### `arvore_avl.cpp`

Esta implementação refere-se a uma Árvore AVL, que é uma árvore binária de busca auto-balanceada. O balanceamento é feito garantindo que a diferença de altura entre os subárvores esquerda e direita de qualquer nó é no máximo 1. Isso é alcançado através de rotações à esquerda e à direita.

- **Compilação e Execução:**
  Para compilar e executar o código, use os seguintes comandos:
  ```sh
  g++ arvore_avl.cpp -o arvore_avl
  ./arvore_avl
  ```

### `arvore_rb.cpp`

Esta implementação refere-se a uma Árvore Rubro-Negra, que é outra árvore binária de busca balanceada, mas com um sistema de cores (vermelho e preto) para garantir que a árvore se mantenha balanceada. As regras de balanceamento são mais complexas e garantem que a árvore se mantenha aproximadamente balanceada.

- **Compilação e Execução:**
  Para compilar e executar o código, use os seguintes comandos:
  ```sh
  g++ arvore_rb.cpp -o arvore_rb
  ./arvore_rb
  ```

## Descrição dos Algoritmos

### Árvore AVL

A Árvore AVL é uma árvore binária de busca onde a diferença de altura entre os filhos esquerdo e direito de qualquer nó é no máximo 1. Este balanceamento garante que todas as operações de inserção, exclusão e busca sejam feitas em tempo logarítmico.

### Árvore Rubro-Negra

A Árvore Rubro-Negra é uma árvore binária de busca onde cada nó tem uma cor (vermelho ou preto) e segue várias regras de balanceamento para garantir que a árvore permaneça balanceada. As principais regras são que a raiz e as folhas são pretas, e que não há dois nós vermelhos consecutivos.
