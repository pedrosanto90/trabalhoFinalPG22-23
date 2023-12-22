#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

struct manutencoes {
    int codManutencao; // gerado automaticamente
    char dataManutencao[11]; //YYYY-MM-DD
    char tipoManutencao[11]; // Correctiva/Preventiva
    char horaInicio[6]; //HH:MM
    char horaFim[6]; // HH:MM
    int duracao[6]; // HH:MM
    char descricao[100]; // descricao do que foi efetuado
};

struct clientes {
    int idCliente;
    char nomeCliente[50];
    char morada[50];
    int nif;
    int contato;
};

void criarManutencao();
int consultaManCliente();
void consultarManutencao();
void alterarManutencao();
char criarCodigoManutencao(int *numCliente, char *codManutencao);
void menu();
void consultaFicheiroManutencao();
char criarNomeFicheiro(char *codManutencao, char *fileName);

void listarFicheiros();


/* Funcao para limpar o terminal
 Funciona em ambientes windows e ambientes Unix/Linux */

void limparTerminal() {
#ifdef _WIN32
    system("cls"); // Para Windows
#else
    system("clear"); // Para sistemas Unix/Linux
#endif
}

int main() {
    menu();
    return 0;
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
    struct manutencoes *manutencao =  (struct manutencoes*) malloc(sizeof(struct manutencoes));
    struct clientes *cliente = (struct clientes*) malloc(sizeof(struct clientes));
    char codigoManutencao;
    printf("Indique o numero de cliente: ");
    scanf("%i", &cliente->idCliente);
    setbuf(stdin, NULL);


    char *codManutencao;
    codManutencao = &codigoManutencao;
    criarCodigoManutencao(&cliente->idCliente, codManutencao); 
    char nomeFicheiro;
    char *fileName = &nomeFicheiro;
    criarNomeFicheiro(codManutencao, fileName);
    FILE *file;
    file = fopen(fileName, "w");
    // chamar funcao em vez de colocar o nome do ficheiro
    if(file == NULL) {
        printf("Erro ao abrir ficheiro\n");
        menu();
    }
    // Inserir numero de cliente
    // inserir data da manutencao
    printf("Data da Manutencao(AAAA-MM-DD): ");

    // le os dados inseridos pelo utilizador e insere a partir do stdin 
    fgets(manutencao->dataManutencao, 11, stdin);
    setbuf(stdin, NULL);
    while ((getchar()) != '\n');

    // inserir tipo de manutencao

    printf("Tipo de Manutencao: ");

    // le os dados inseridos pelo utilizador e insere a partir do stdin
    fgets(manutencao->tipoManutencao, 11, stdin);
    setbuf(stdin, NULL);
    while ((getchar()) != '\n');

    // inserir hora de inicio

    printf("Hora de Inicio da Manutencao(HH:MM): ");

    // le os dados inseridos pelo utilizador e insere a partir do stdin
    fgets(manutencao->horaInicio, 6, stdin);
    setbuf(stdin, NULL);
    while ((getchar()) != '\n');

    // inserir hora de fim

    printf("Hora de Fim da Manutencao(HH:MM): ");

    // le os dados inseridos pelo utilizador e insere a partir do stdin
    fgets(manutencao->horaFim, 6, stdin);
    setbuf(stdin, NULL);
    while ((getchar()) != '\n');

    // inserir descricao da manutencao


    printf("Descricao da Manutencao: ");

    // le os dados inseridos pelo utilizador e insere a partir do stdin
    fgets(manutencao->descricao, 100, stdin);
    setbuf(stdin, NULL);
    // while ((getchar()) != '\n');
    
    // Escreve os dados da struct no respetivo ficheiro
    fprintf(file, "Numero de Cliente: %i\n", cliente->idCliente);
    fprintf(file, "Data: %s\n", manutencao->dataManutencao);
    fprintf(file, "Tipo: %s\n", manutencao->tipoManutencao);
    fprintf(file, "Hora de Inicio: %s\n", manutencao->horaInicio);
    fprintf(file, "Hora de fim: %s\n", manutencao->horaFim);

    // duracao da manutencao
    int horaInicio, minutoInicio, horaFim, minutoFim;
    sscanf(manutencao->horaInicio, "%d:%d", &horaInicio, &minutoInicio);
    sscanf(manutencao->horaFim, "%d:%d", &horaFim, &minutoFim);
    int diferencaMinutos = (horaFim * 60 + minutoFim) - (horaInicio * 60 + minutoInicio);
    int diferencaHoras = diferencaMinutos / 60;
    int diferencaMinutosRestantes = diferencaMinutos % 60;
    fprintf(file, "Duração: %02d:%02d\n", diferencaHoras, diferencaMinutosRestantes);
    fprintf(file, "Descricao: %s\n", manutencao->descricao);

    // falta criar funcao para calcular duracao da manutencao e criacao do codigo de manutencao

    fclose(file);

    free(manutencao);
    free(cliente);
    menu();
}

int consultaManCliente() {
    setbuf(stdin, NULL);
    limparTerminal();
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

    DIR *dir;
    struct dirent *entrada;

    dir = opendir(".");

    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        return;
    }

    while ((entrada = readdir(dir)) != NULL) {
        // Verifica se o arquivo tem a extensão .txt
        if (strstr(entrada->d_name, ".txt") != NULL) {
            printf("%s\n", entrada->d_name);
        }
    }
    consultaFicheiroManutencao();

    closedir(dir);
    // pesquisar manutencoes num intervalo de tempo
    // mostrar manutencoes da mais recente para a mais antiga
    // mostrar manutencoes de acordo com a duracao
}

void alterarManutencao() {
    setbuf(stdin, NULL);
    FILE *file;
    char ficheiro[256];
    char linha[150];
    printf("Indique o ficheiro que quer alterar: ");
    scanf("%s", ficheiro);
    setbuf(stdin, NULL);
    strcat(ficheiro, ".txt");
    file = fopen(ficheiro, "r+");

    if (file == NULL) {
        printf("Erro ao abrir ficheiro\n");
        alterarManutencao();
    }


    // Pedir ao usuário para indicar qual linha deseja alterar
    int numeroLinha = 6;

    // Mover o ponteiro para o início do arquivo
    fseek(file, 0, SEEK_SET);

    // Variável para contar as linhas
    int contadorLinhas = 0;
    char novaDescricao[100];
    printf("Descricao: ");
    fgets(novaDescricao, sizeof(novaDescricao), stdin);
    novaDescricao[strcspn(novaDescricao, "\n")] = '\0'; 
    // Percorrer o arquivo novamente
    while (fgets(linha, sizeof(linha), file) != NULL) {
        contadorLinhas++;

        // Se a linha atual é a linha desejada, realizar a alteração
        if (contadorLinhas == numeroLinha) {
            // Aqui você pode pedir ao usuário para inserir a nova informação
            // e substituir a linha atual com a nova informação usando fprintf
            // Exemplo: fprintf(file, "Nova informacao\n");

            // Exemplo: substituir a linha por "Nova informacao"
            fprintf(file, "Descricao: %s\n", novaDescricao);

            printf("Linha alterada com sucesso!\n");
            break; // Parar a busca, pois a linha já foi alterada
        }
    }

    fclose(file);
}

void menu() {
    limparTerminal();
    setbuf(stdin, NULL);
    // Criar menu para escolher o que fazer
    // inserir
    // consulta por cliente
    // consulta manutencao
    // alterar manutencao
    int opcao;

    printf("Trabalho Final\nGestao de Manutencoes\n");

    printf("1 - Criar Manutencao;\n2 - Consultar Manutencao por Cliente;\n3 - Consultar Todas as Manutencoes;\n4 - Alterar Manutencao;\n0 - Sair;\n");
    scanf("%d", &opcao);
    setbuf(stdin, NULL);

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
            listarFicheiros();
            alterarManutencao();
            break;
        case 0:
            printf("Terminar Programa\n");
            exit(0);
        default:
           printf("Opcao Invalida\nPressione <ENTER>\n");
           getchar();
           menu();
            

    }
    setbuf(stdin, NULL);
}
void listarFicheiros() {

    DIR *dir;
    struct dirent *entrada;

    dir = opendir(".");

    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        return;
    }

    while ((entrada = readdir(dir)) != NULL) {
        // Verifica se o arquivo tem a extensão .txt
        if (strstr(entrada->d_name, ".txt") != NULL) {
            printf("%s\n", entrada->d_name);
        }
    }

    closedir(dir);
}

char criarCodigoManutencao(int *numCliente, char *codManutencao) {
    int numero = 0;  // Inicialize a variável numero
    int temp;
    char charTemp[4];
    char nomeFicheiro[15];
    DIR *dir;
    int contador = 0;
    struct dirent *entrada;

    dir = opendir(".");

    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        exit(1);
    }

    while ((entrada = readdir(dir)) != NULL) {
        if (strstr(entrada->d_name, ".txt") != NULL) {
            strcpy(nomeFicheiro, entrada->d_name);

            char *token = strtok(nomeFicheiro, "_");
            token = strtok(NULL, "_");

            if (token != NULL) {
                strcpy(charTemp, token);
                temp = atoi(charTemp);
                if (temp > numero) {
                    numero = temp;
                }
            }
            contador++;
        }
    }

    closedir(dir);

    char num[15];
    char temporaria[30];
    sprintf(num, "%d", *numCliente);
    strcpy(temporaria, num);
    strcat(temporaria, "_");
    numero++;  // Incrementa o número
    sprintf(num, "%d", numero);
    strcat(temporaria, num);
    sprintf(num, "%d", contador);
    strcat(temporaria, num);
    strcpy(codManutencao, temporaria);

    return *codManutencao;
}

char criarNomeFicheiro(char *codManutencao, char *fileName) {
    strcpy(fileName, codManutencao);
    strcat(fileName, ".txt");
    return *fileName;
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
