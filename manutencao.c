#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

struct manutencoes {
    int codManutencao; // gerado automaticamente tendo em conta o registo anterior
    char dataManutencao[11]; //YYYY-MM-DD
    char tipoManutencao[16]; // Correctiva/Preventiva
    char horaInicio[6]; //HH:MM
    char horaFim[6]; // HH:MM
    int duracao[6]; // HH:MM
    char descricao[100]; // descricao do que foi efetuado, material utilizado (consoante informacao do grupo 1-fornecedores)
//    char equipamento[50];
};

void criarManutencao();
int consultaManCliente();
void consultarManutencao();
void alterarManutencao();
char criarCodigoManutencao(int numCliente, const char file_name);
char procurarFicheiro(int numCliente);
void menu();
void consultaFicheiroManutencao();
void removerNovaLinha(char *str);

// Funcao para limpar o terminal
// Funciona em ambientes windows e ambientes Unix/Linux
void limparTerminal() {
    #ifdef _WIN32
        system("cls"); // Para Windows
    #else
        system("clear"); // Para sistemas Unix/Linux
    #endif
}

int main() {
    printf("Trabalho Final\nGestao de Manutencoes\n");
    menu();
    return 0;
}

void removerNovaLinha(char *str) {
    int pos = strcspn(str, "\n");
    if (str[pos] == '\n') {
        str[pos] = '\0';
    }
}

void criarManutencao() {
    // Limpa o terminal
    limparTerminal();
    // codigo de manutencao criado automaticamente de acordo com o ultimo registo (numero de manutencao conjugado com numero de cliente)
    // inserir data, hara de inicio e de fim de manutencao, duracao calculada automaticamente 
    // indicar o cliente ao qual foi feita a manutencao
    // indicar o que foi feito durante a manutencao
    // inserir dados num documento .txt (cliente?) todas as manutencoes de um cliente num mesmo documento ou agrupado em pastas de cliente?
        // nome do ficheiro sera dado consoante o decidido no ponto anterior 
    struct manutencoes *manutencao =  ( struct manutencoes*) malloc(sizeof(struct manutencoes));

    FILE *file;
    file = fopen("novo.txt", "w");

    if(file == NULL) {
        printf("Erro ao abrir ficheiro\n");
        menu();
    }
    // inserir data da manutencao
    // limpa o buufer
    setbuf(stdin, NULL);
    printf("Data da Manutencao(AAAA-MM-DD): ");
    
    // le os dados inseridos pelo utilizador e insere a partir do stdin 
    fgets(manutencao->dataManutencao, 11, stdin);
    //removerNovaLinha(manutencao->dataManutencao);

    // inserir tipo de manutencao
    setbuf(stdin, NULL);
    printf("Tipo de Manutencao: ");
    // le os dados inseridos pelo utilizador e insere a partir do stdin
    fgets(manutencao->tipoManutencao, 15, stdin);
    //removerNovaLinha(manutencao->tipoManutencao);while ((getchar()) != '\n');
    while ((getchar()) != '\n');

    // inserir hora de inicio
    setbuf(stdin, NULL);
    printf("Hora de Inicio da Manutencao(HH:MM): ");
    // le os dados inseridos pelo utilizador e insere a partir do stdin
    fgets(manutencao->horaInicio, 6, stdin);
    //removerNovaLinha(manutencao->horaInicio);
    while ((getchar()) != '\n');

    // inserir hora de fim
    setbuf(stdin, NULL);
    printf("Hora de Fim da Manutencao(HH:MM): ");
    // le os dados inseridos pelo utilizador e insere a partir do stdin
    fgets(manutencao->horaFim, 6, stdin);
    //removerNovaLinha(manutencao->horaFim);
    while ((getchar()) != '\n');
    
    // inserir descricao da manutencao

    setbuf(stdin, NULL);
    printf("Descricao da Manutencao: ");
    // le os dados inseridos pelo utilizador e insere a partir do stdin
    fgets(manutencao->descricao, 100, stdin);
    //removerNovaLinha(manutencao->descricao);
    while ((getchar()) != '\n');

    // Escreve os dados da struct no respetivo ficheiro
    // codigo manutencao
    // criarCodigoManutencao(int numCliente, char file_name);

    fprintf(file, "Data: %s\n", manutencao->dataManutencao);
    fprintf(file, "Tipo: %s\n", manutencao->tipoManutencao);
    fprintf(file, "Hora de Inicio: %s\n", manutencao->horaInicio);
    fprintf(file, "Data de fim: %s\n", manutencao->horaFim);
    // duracao da manutencao
    fprintf(file, "Descricao: %s\n", manutencao->descricao);

    // falta criar funcao para calcular duracao da manutencao e criacao do codigo de manutencao

    fclose(file);

    free(manutencao);
    menu();
}

int consultaManCliente() {
    // pesquisar por cliente e retorna uma lista de todas as manutencoes efetuadas a esse cliente
    // mostra o total de manutencoes (media anual/mensal???)
    // escolher uma das manutencoes e ver os detalhes dessa manutencao
    // Solicita ao usuário inserir a string de pesquisa
    char search_string[256];
    printf("Numero de Cliente: ");
    fgets(search_string, sizeof(search_string), stdin);
    // Remove a quebra de linha do final da string
    search_string[strcspn(search_string, "\n")] = '\0';

    // Caractere a partir do qual a pesquisa será ignorada
    char ignore_char = '_';

    // Abre o diretório atual
    DIR *dir = opendir(".");

    // Verifica se o diretório foi aberto com sucesso
    if (dir != NULL) {
        // Lê cada entrada no diretório
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            // Ignora as entradas "." e ".."
            if (ent->d_name[0] != '.') {
                // Verifica se a string de pesquisa está presente e ignora a partir do caractere especificado
                char *filename_without_extension = strtok(ent->d_name, ".");
                char *substring = strstr(filename_without_extension, search_string);
                if (substring != NULL && substring[0] != ignore_char) {
                    // Imprime o nome do arquivo
                    printf("%s\n", ent->d_name);
                }
            }
        }
        consultaFicheiroManutencao();
        

        // Fecha o diretório
        closedir(dir);
    } else {
        char opcao;
        // Se não foi possível abrir o diretório, imprime uma mensagem de erro
        printf("O cliente que prentende consultar nao tem nenhuma manutencao registada.\n");
        printf("Deseja criar um registo para este cliente?[S]im [N]ao\n");
        scanf("%c", &opcao);

        if(opcao == 'S') {
            criarManutencao();
        } else if (opcao == 'N') {
            menu();
        } else {
            printf("Leitura nao efetuada");
            menu();
        }

    }

    return 0;
}

void consultarManutencao() {
    // pesquisar manutencoes num intervalo de tempo
    // mostrar manutencoes da mais recente para a mais antiga
    // mostrar manutencoes de acordo com a duracao
}

void alterarManutencao() {
    // retornar os dados do cliente conforme estrutura do grupo 2
    // mostrar manutencoes feitas nesse cliente e uma breve descricao da mesma 
    // alterar manutencao
}

void menu() {
    // Criar menu para escolher o que fazer
    // inserir
    // consulta por cliente
    // consulta manutencao
    // alterar manutencao
    int opcao;
    printf("1 - Criar Manutencao;\n2 - Consultar Manutencao por Cliente;\n3 - Consultar Todas as Manutencoes;\n4 - Alterar Manutencao;\n0 - Sair;\n");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            criarManutencao();
            break;
        case 2:
            consultaManCliente();
            break;
        case 3:
            consultarManutencao();
            break;
        case 4:
            alterarManutencao();
        case 0:
            printf("Terminar Programa\n");
            exit(0);

        }
}

char criarCodigoManutencao(int numCliente, const char file_name) {
    char fileName;
    
    return fileName;
}
char procurarFicheiro(int numCliente) {
    char codigo[10];
    char nomeFicheiro;
    //diretorio = "./manutencoes";
    printf("Inserir Codigo Manutencao: ");
    scanf("%s", codigo);

    DIR *dir;
    //dir = opendir(diretorio);
    return nomeFicheiro;
}

void consultaFicheiroManutencao() {
    char codManutencao[15];
    char linha[150];

    // limpa o buffer
    setbuf(stdin, NULL);
    printf("Indique qual a manutencao que deseja ver: ");
    scanf("%s", codManutencao);
    
    // faz a concatenacao do codigo de manutencao com .txt para gerar um nome de arquivo valido para abrir
    strcat(codManutencao, ".txt");

    FILE *file;
    // abre o  ficheiro
    file = fopen(codManutencao, "r");

    // verifica se consegue abrir o ficheiro
    if (file == NULL) {
        printf("Erro ao abrir ficheiro.");
        // se nao conseguir chama novamente a funcao consultaManClinete
        consultaManCliente();
    }

    // percorre cada linha do ficheiro e imprime para o utilizador ver
    while (fgets(linha, sizeof(linha), file) != NULL) {
        printf("%s", linha);
    }
    // fecha o ficheiro
    fclose(file);
}