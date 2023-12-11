#include <stdio.h>
#include <stdlib.h>

void alterarLinhaArquivo(char novoConteudo) {
    setbuf(stdin, NULL);
    int numeroLinha = 4;
    char *nova;
    nova = &novoConteudo;
// Abre o arquivo para leitura e escrita
    FILE *arquivo = fopen("novo.txt", "r+");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Muda para a linha desejada
    for (int i = 1; i < numeroLinha; ++i) {
        while (fgetc(arquivo) != '\n') {
            if (feof(arquivo)) {
                fclose(arquivo);
                fprintf(stderr, "Erro: Linha %d não encontrada no arquivo\n", numeroLinha);
                exit(EXIT_FAILURE);
            }
        }
    }

    // Salva a posição atual no arquivo
    long posicao = ftell(arquivo);

    // Pula para o início da próxima linha
    while (fgetc(arquivo) != '\n') {
        if (feof(arquivo)) {
            break;  // Se atingir o final do arquivo, sai do loop
        }
    }

    // Volta para a posição salva
    fseek(arquivo, posicao, SEEK_SET);

    // Apaga a linha existente
    fprintf(arquivo, "%*s", (int)(ftell(arquivo) - posicao), "");

    // Escreve o novo conteúdo na linha
    fprintf(arquivo, "Descricao: %s\n", &novoConteudo);

    // Fecha o arquivo
    fclose(arquivo);
}

int main() {
    char *novoConteudo;
    char temp;
    novoConteudo = & temp;
    printf("Indique a nova descricao: ");
    scanf("%s", novoConteudo);

    alterarLinhaArquivo(temp);

    printf("Descricao alterada com sucesso.\n");

    return 0;
}
