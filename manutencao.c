#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

struct manutencoes {
    int codManutencao; // gerado automaticamente tendo em conta o registo anterior
    char dataManutencao[10]; //YYYY-MM-DD
    char tipoManutencao[15]; // Correctiva/Preventiva
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
char createFileName(int numCliente, const char *diretorio, const char file_name);
char procurarFicheiro(int numCliente);
void menu();
int main() {
    printf("Trabalho Final\nGestao de Manutencoes\n");
    menu();
    return 0;
}

void criarManutencao() {

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
        printf("erro\n");
        exit(1);
    }
    // inserir data da manutencao
    setbuf(stdin, NULL);
    printf("Data da Manutencao: ");
    fgets(manutencao->dataManutencao, 10, stdin);
    printf("%s\n", manutencao->dataManutencao);

    // inserir tipo de manutencao
     setbuf(stdin, NULL);
    printf("Tipo de Manutencao: ");
    fgets(manutencao->tipoManutencao, 15, stdin);
    printf("%s\n", manutencao->tipoManutencao);

    // inserir hora de inicio
     setbuf(stdin, NULL);
    printf("Hora de Inicio da Manutencao: ");
    fgets(manutencao->horaInicio, 6, stdin);
    printf("%s\n", manutencao->horaInicio);

    // inserir hora de fim
    setbuf(stdin, NULL);
    printf("Hora de Fim da Manutencao: ");
    fgets(manutencao->horaFim, 6, stdin);
    printf("%s\n", manutencao->horaFim);

    // inserir descricao da manutencao

    setbuf(stdin, NULL);
    printf("Descricao da Manutencao: ");
    fgets(manutencao->descricao, 100, stdin);
    printf("%s\n", manutencao->descricao);

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
    printf("Digite a string de pesquisa: ");
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

        // Fecha o diretório
        closedir(dir);
    } else {
        // Se não foi possível abrir o diretório, imprime uma mensagem de erro
        perror("Erro ao abrir o diretório");
        return 1;
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
    printf("1 - Criar Manutencao;\n2 - Consultar Manutencao por Cliente;\n3 - Consultar Todas as Manutencoes;\n4 - Alterar Manutencao;\n 0 - Sair;\n");
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

char createFileName(int clientNumber, const char *diretorio, const char file_name) {
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
