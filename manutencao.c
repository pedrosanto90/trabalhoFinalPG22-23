#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

struct manutencao {
    int codManutencao; // gerado automaticamente tendo em conta o registo anterior
    char dataManutencao[10]; //YYYY-MM-DD
    char tipoManutencao[15]; // Correctiva/Preventiva
    char horaInicio[6]; //HH:MM
    char horaFimi[6]; // HH:MM
    int duracao[6]; // HH:MM
    char descricao; // descricao do que foi efetuado, material utilizado (consoante informacao do grupo 1-fornecedores)
//    char equipamento[50];
};

void criarManutencao();
void consultaManCliente();
void consultarManutencao();
void alterarManutencao();
char createFileName(int clientNumber, const char diretorio, const char file_name);
char procurarFicheiro(int codManutencao);
int main() {
    printf("Trabalho Final\nGestao de Manutencoes\n");
    return 0;
}

void criarManutencao() {
    // codigo de manutencao criado automaticamente de acordo com o ultimo registo (numero de manutencao conjugado com numero de cliente)
    // inserir data, hara de inicio e de fim de manutencao, duracao calculada automaticamente 
    // indicar o cliente ao qual foi feita a manutencao
    // indicar o que foi feito durante a manutencao
    // inserir dados num documento .txt (cliente?) todas as manutencoes de um cliente num mesmo documento ou agrupado em pastas de cliente?
        // nome do ficheiro sera dado consoante o decidido no ponto anterior 
}

void consultaManCliente() {
    // pesquisar por cliente e retorna uma lista de todas as manutencoes efetuadas a esse cliente
    // mostra o total de manutencoes (media anual/mensal???)
    // escolher uma das manutencoes e ver os detalhes dessa manutencao
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
char procurarFicheiro(int codManutencao) {
    char codigo[10];
    char nomeFicheiro;
    diretorio = "./manutencoes";
    printf("Inserir Codigo Manutencao: ");
    scanf("%s", codigo);

    DIR *dir;
    dir = opendir(diretorio);
    return nomeFicheiro;
}

