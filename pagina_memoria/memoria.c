#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    // Definir o tamanho da página de memória
    size_t page_size = sysconf(_SC_PAGESIZE); //Obtem o tamanho da pagina
    printf("Tamanho da página: %zu bytes\n", page_size);

    // Alocar uma página de memória virtual
    void *page = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    /*
    mmap é uma função para mapear uma pagina de memoria
    NULL: significa que o proprio sistema escohe o endereço virtual
    Page_size: é o tamanho da pagina a ser alocado
    PROT_READ e PROT_WRITE: são as permissões de leitura e escrita na pagina
    MAP_PRIVATE: As alterações não afetam outras copias
    MAT_ANONYMOUS: A memoria não esta associada a nenhum arquivo
    -1,0: É onde deve ser descrito o arquivo para mapea-lo, como esta definido como MAT_ANONYMOUS então não precisa.  

    O retorno dessa função é um objeto do tipo PAGE. 
    */
    if (page == MAP_FAILED) {
        perror("Erro ao mapear a página de memória");
        exit(EXIT_FAILURE);
    }

    // Escrever dados na página de memória
    const char *text = "Olha, eu estou escrevendo em paginas de memoria!";
    strncpy((char *)page, text, page_size - 1); // Copia o texto para a memória alocada
    /*
    O page_size - 1 garante que a copia não exceda o tamanho da pagina
    */

    ((char *)page)[page_size - 1] = '\0'; // Assegura que o texto esteja terminado em '\0'

    // Exibir o texto que foi escrito na memória virtual direito do objeto PAGE
    printf("Texto na memória virtual: %s\n", (char *)page);

    // Desalocar a página de memória
    if (munmap(page, page_size) == -1) {
        perror("Erro ao desmapear a página de memória");
        exit(EXIT_FAILURE);
    }

    return 0;
}
