#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdint.h>

int main() {
    // Definir o tamanho da página de memória

    const char *filename = "biblia.txt";

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Determinar o tamanho do arquivo
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Erro ao determinar o tamanho do arquivo");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    size_t file_size = st.st_size;

    size_t page_size = sysconf(_SC_PAGESIZE); //Obtem o tamanho da pagina

    printf("Tamanho da página: %zu bytes\n", page_size);

    // Quantidade de páginas necessárias
    size_t num_pages = (file_size + page_size - 1) / page_size;

    printf("Quantidade de páginas: %ld\n", num_pages);

    // Alocar memória virtual para o arquivo
    void *pages = mmap(NULL, num_pages * page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    /*
    mmap é uma função para mapear uma pagina de memoria
    NULL: significa que o proprio sistema escohe o endereço virtual
    Page_size + num_pages: indica a quantidade de espaço a ser alocado
    PROT_READ e PROT_WRITE: são as permissões de leitura e escrita na pagina
    MAP_PRIVATE: As alterações não afetam outras copias
    MAT_ANONYMOUS: A memoria não esta associada a nenhum arquivo
    -1,0: É onde deve ser descrito o arquivo para mapea-lo, como esta definido como MAT_ANONYMOUS então não precisa.  

    O retorno dessa função é um objeto do tipo PAGE. 
    */
    if (pages == MAP_FAILED) {
        perror("Erro ao mapear a página de memória");
        exit(EXIT_FAILURE);
    }

    // Ler o arquivo e escrever nas páginas de memória
    size_t total_bytes_read = 0;
    for (size_t i = 0; i < num_pages; i++) {
        char buffer[page_size];
        size_t bytes_read = fread(buffer, 1, page_size, file);
        // buffer é um ponteiro para indicar onde os dados lidos serão armazenados. 
        // A leitura é feita de um em um byte até atingir o tamanho de uma pagina (page_size)
        if (bytes_read == 0 && ferror(file)) {
            perror("Erro ao ler o arquivo");
            munmap(pages, num_pages * page_size);
            fclose(file);
            exit(EXIT_FAILURE);
        }
        memcpy((char *)pages + total_bytes_read, buffer, bytes_read);
        // o conteudo dos dados lido no arquivo (equivalete a uma pag de memoria) é copiado para a memória mapeada
        // pages + total_bytes_read serve para que os dados seguinte sejam gravados logo ao fim dos dados anteriores na memoria.
        // pages é um ponteiro para o inicio dos blocos de gravação na memoria, e total_bytes_read indica o que já foi ocupa até então
        
        total_bytes_read += bytes_read;
    }


    // Verificação dos últimos 5 bytes para garantir integridade, garantindo que os últimos 5 bytes alocados nas paginas de memoria
    // são equivalentes ao 5 ultimos bytes do arquivo carregado
    char *last_data_address = (char *)pages + file_size - 1;
    assert(*(last_data_address - 4) == 'm');
    assert(*(last_data_address - 3) == 'e');
    assert(*(last_data_address - 2) == 'n');
    assert(*(last_data_address - 1) == '.');
    assert(*(last_data_address)     == '\n');

    // Manipulação dos endereços de memória
    uintptr_t data_address_as_int = (uintptr_t)pages;
    uintptr_t data_address_page_number = data_address_as_int >> 12;
    uintptr_t data_address_page_offset = data_address_as_int & 0xFFF;

    uintptr_t last_data_address_as_int = (uintptr_t)last_data_address;
    uintptr_t last_data_address_page_number = last_data_address_as_int >> 12;
    uintptr_t last_data_address_page_offset = last_data_address_as_int & 0xFFF;

    // Exibir informações sobre os endereços de memória
    printf("\nFormat (HEX):            PAGE_NUMBER PAGE_OFFSET\n");
    printf(
        "Data address (HEX):      0x%lx %03lx\n",
        data_address_page_number,
        data_address_page_offset
    );
    printf(
        "Last data address (HEX): 0x%lx %03lx\n",
        last_data_address_page_number,
        last_data_address_page_offset
    );

    printf("\nFormat (DEC):            PAGE_NUMBER PAGE_OFFSET\n");
    printf(
        "Data address (DEC):      %ld %03ld\n",
        data_address_page_number,
        data_address_page_offset
    );
    printf(
        "Last data address (DEC): %ld %03ld\n",
        last_data_address_page_number,
        last_data_address_page_offset
    );

    // Exibir o conteúdo da primeira página
    printf("\nConteúdo das primeiras páginas da memória:\n");
    printf("%.*s\n", (int)(1 * page_size), (char *)pages);

    // Desmapear as páginas de memória
    if (munmap(pages, num_pages * page_size) == -1) {
        perror("Erro ao desmapear as páginas de memória");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Fechar o arquivo
    fclose(file);

    return 0;
}
