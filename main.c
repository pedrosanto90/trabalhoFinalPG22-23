#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


// declaracao a struct manutencoes
struct manutencoes {
    int codManutencao; // gerado automaticamente
    char dataManutencao[11]; //YYYY-MM-DD
    char tipoManutencao[11]; // Correctiva/Preventiva
    char horaInicio[6]; //HH:MM
    char horaFim[6]; // HH:MM
    int duracao[6]; // HH:MM
    char descricao[100]; // descricao do que foi efetuado
};
// declaracao da struct clientes
struct clientes {
    int idCliente;
    char nomeCliente[50];
    char morada[50];
    int nif;
    int contato;
};
// prototipagem das funcoes utilizadas durante o programa
void criarManutencao();
void consultaManCliente();
void consultarManutencao();
void alterarManutencao();
char criarCodigoManutencao(int *numCliente, char *codManutencao);
void menu();
void consultaFicheiroManutencao();
char criarNomeFicheiro(char *codManutencao, char *fileName);
int verificarFormatoHoras(const char *horas);
int verificarFormatoData(const char *data);
void listarFicheiros();
void limparTerminal();
void voltar_menu();


/* Funcao para limpar o terminal
 Funciona em ambientes windows e ambientes Unix/Linux */



int main() {
    // a funcao main apenas chama a funcao menu
    // todas as restantes funcoes sao chamadas dentro da funcao menu
    menu();
    return 0;
}

void menu() {
    // Chamada da funcao limpar terminal para limpar o que ja tiver escrito antes no terminal
    limparTerminal();
    //limpa o buffer para evitar bugs relacionados com carateres no buffer
    setbuf(stdin, NULL);
    // declara a variavel opcao do tipo inteiro que vai ser usada para escolher a opcao do menu
    int opcao;

    printf("Trabalho Final\nGestao de Manutencoes\n");
    setbuf(stdin, NULL);
    printf("1 - Criar Manutencao;\n2 - Consultar Manutencao por Cliente;\n3 - Consultar Todas as Manutencoes;\n4 - Alterar Manutencao;\n0 - Sair;\n");
    // le o que foi introduzido pelo utilizador e guarda na variavel opocao
    scanf("%d", &opcao);



    switch(opcao) {
        case 1:
            // caso a opcao do utilizador seja 1, chama a funcao criarManutencao

            //setbuf(stdin, NULL);
            criarManutencao();
            // o break faz com que o programa nao verifique as restantes opcoes
            break;
        case 2:
            // caso a opcao do utilizador seja 1, chama a funcao consultaManCliente

            //setbuf(stdin, NULL);
            consultaManCliente();
            // o break faz com que o programa nao verifique as restantes opcoes
            break;
        case 3:
            // caso a opcao do utilizador seja 3, chama a funcao consultarManutencao

            //setbuf(stdin, NULL);
            consultarManutencao();
            // o break faz com que o programa nao verifique as restantes opcoes
            break;
        case 4:
            // caso a opcao do utilizador seja 4, chama a funcao listar ficheiros

            //setbuf(stdin, NULL);
            listarFicheiros();
            // depois de chamda a funcao anterior, chama a funcao alterarManutencao
            alterarManutencao();
            // o break faz com que o programa nao verifique as restantes opcoes
            break;
        case 0:
            // caso o utilizador escolha 0, termina o programa

            //setbuf(stdin, NULL);
            printf("Terminar Programa\n");
            exit(0);
        default:
            // caso o utilizador escolha outra opcao que nao as listadas em cima
            // o programa indica que nao escolheu uma opcao valida
            // while ((getchar()) != '\n');
            printf("Opcao Invalida\nPressione <ENTER>\n");
            // a funcao getchar aguarda um input do utilizador para puder seguir para o proximo passo
            getchar();
            setbuf(stdin, NULL);
            // volta a chamar a funcao menu
            menu();


    }
    // limpar o buffer para evitar bugs com carateres guardados no buffer
    setbuf(stdin, NULL);
}

void criarManutencao() {
    // chamada da funcao para limpar o terminal
    limparTerminal();
    // declara a struct manutencao do tipo manutencoes
    // e aloca memoria para a mesma com a funcao malloc e com o tamanho de manutencoes
    struct manutencoes *manutencao =  (struct manutencoes*) malloc(sizeof(struct manutencoes));
    // declara a struct cliente do tipo clientes
    // e aloca memoria para a mesma com a funcao malloc e com o tamanho de clientes
    struct clientes *cliente = (struct clientes*) malloc(sizeof(struct clientes));

    // verifica se conseguiu alocar memoria
    if (manutencao == NULL || cliente == NULL) {
        printf("Erro na alocacao de memoria\n");
        menu();
    }
    setbuf(stdin, NULL);
    printf("Indique o numero de cliente: ");
    // espera o input do utilizador e guarda na struct cliente->idCliente
    scanf("%d", &cliente->idCliente);
    // limpar o buffer para evitar bugs com carateres guardados no buffer

    // declara a variavel codigoManutencao com o tipo char
    char codigoManutencao;
    // declara o apontador codManutencao
    char *codManutencao;
    // apontador codManutencao recebe o endereco de codigoManutencao
    codManutencao = &codigoManutencao;
    // chama a funcao criarCodigoManutencao com 2 argumentos
    // - endereco de cliente->idCliente
    // - codManutencao
    criarCodigoManutencao(&cliente->idCliente, codManutencao);
    // declara a variavel nomem de ficheiro do tipo char
    char nomeFicheiro;
    // declara o apontador fileName e indica que recebe o endereco de nomeFicheiro
    char *fileName = &nomeFicheiro;
    // chama a funcao criarNomeFicheiro com 2 argumentos
    //  - codManutencao
    //  - fileName
    criarNomeFicheiro(codManutencao, fileName);
    // declara o apontador file do tipo FILE
    // FILE E uma biblioteca de C usada para trabalhar com ficheiros
    FILE *file;
    // a variavel file recebe a funcao fopen
    // a funcao fopen serve abrir um ficheiro e recebe dois argumentos
    // o ficheiro para abrir, neste caso atravez da variavel fileName
    // e o modo em que o ficheiro vai ser aberto
    // neste caso em modo w - write
    file = fopen(fileName, "w");
    // verificacao para abrir o ficheiro
    // se nao conseguir abrir o ficheiro informa que ocorreu um erro e chama novamente a funcao menu
    if(file == NULL) {
        printf("Erro ao abrir ficheiro\n");
        menu();
    }
    // informa o cliente para inserir a data da manutencao
    do {
        setbuf(stdin, NULL);
        printf("Data da Manutencao(AAAA-MM-DD): ");

        // le os dados inseridos pelo utilizador e insere a partir do stdin
        fgets(manutencao->dataManutencao, 11, stdin);
        // remove o carater \n
        manutencao->dataManutencao[strcspn(manutencao->dataManutencao, "\n")];

        //garante que nao existe nenhum carater oculto no buffer
       while ((getchar()) != '\n');
    } while(!verificarFormatoData(manutencao->dataManutencao));
    setbuf(stdin, NULL);

    char tipoManOpcao;
    do {
        printf("Tipo de Manutencao(P - Preventiva/C - Corretiva): ");
        scanf("%c", &tipoManOpcao);

        switch(tipoManOpcao) {
            case 'P':
                strcpy(manutencao->tipoManutencao, "Preventiva");
                break;
            case 'C':
                strcpy(manutencao->tipoManutencao, "Corretiva");
                break;
        }
    } while(tipoManOpcao!='P' && tipoManOpcao!='C');

    //garante que nao existe nenhum carater oculto no buffer
    while ((getchar()) != '\n');
    setbuf(stdin, NULL);

    do {
        setbuf(stdin, NULL);
        // pede ao utilizador para inserir a hora de inicio da manutencao
        printf("Hora de Inicio da Manutencao(HH:MM): ");


        // le os dados inseridos pelo utilizador e insere a partir do stdin
        fgets(manutencao->horaInicio, 6, stdin);

        // remove o carater \n
        manutencao->horaInicio[strcspn(manutencao->horaInicio, "\n")];
        // esta linha nao foi comentada na entraga do trabalho
        while ((getchar()) != '\n');
    } while(!verificarFormatoHoras(manutencao->horaInicio));

    do {
        setbuf(stdin, NULL);
        // pede ao utilizador para inserir a hora de fim da manutencao
        printf("Hora de Fim da Manutencao(HH:MM): ");

        // le os dados inseridos pelo utilizador e insere a partir do stdin
        fgets(manutencao->horaFim, 6, stdin);

        // remove o carater \n
        manutencao->horaFim[strcspn(manutencao->horaFim, "\n")];
        // esta linha nao foi comentada na entraga do trabalho
        while ((getchar()) != '\n');
    } while(!verificarFormatoHoras(manutencao->horaFim));

    setbuf(stdin, NULL);
    // pede ao utilizador para inserir uma breve descricao do que fooi feito na manutencao
    printf("Descricao da Manutencao: ");

    // le os dados inseridos pelo utilizador e insere a partir do stdin
    fgets(manutencao->descricao, 101, stdin);
    manutencao->descricao[strcspn(manutencao->descricao, "\n")];


    // Escreve os dados da struct no respetivo ficheiro
    fprintf(file, "Numero de Cliente: %i\n", cliente->idCliente);
    fprintf(file, "Data: %s\n", manutencao->dataManutencao);
    fprintf(file, "Tipo: %s\n", manutencao->tipoManutencao);
    fprintf(file, "Hora de Inicio: %s\n", manutencao->horaInicio);
    fprintf(file, "Hora de fim: %s\n", manutencao->horaFim);

    // faz o calculo de quanto tempo durou a manutencao e guarda no respetivo campo do ficheiro
    int horaInicio, minutoInicio, horaFim, minutoFim;
    sscanf(manutencao->horaInicio, "%d:%d", &horaInicio, &minutoInicio);
    sscanf(manutencao->horaFim, "%d:%d", &horaFim, &minutoFim);
    if (horaFim > horaInicio) {
        int diferencaMinutos = (horaFim * 60 + minutoFim) - (horaInicio * 60 + minutoInicio);
        int diferencaHoras = diferencaMinutos / 60;
        int diferencaMinutosRestantes = diferencaMinutos % 60;
        fprintf(file, "Duracao: %02d:%02d\n", diferencaHoras, diferencaMinutosRestantes);
        fprintf(file, "Descricao: %s\n", manutencao->descricao);
    } else {
        int diferencaMinutos = (horaInicio * 60 + minutoInicio) - (horaFim * 60 + minutoFim);
        int diferencaHoras = 24 - (diferencaMinutos / 60);
        int diferencaMinutosRestantes = 60 - (diferencaMinutos % 60);
            if(diferencaMinutosRestantes == 60) {
                diferencaMinutosRestantes = 0;
            }
        fprintf(file, "Duracao: %02d:%02d\n", diferencaHoras, diferencaMinutosRestantes);
        fprintf(file, "Descricao: %s\n", manutencao->descricao);
    }
    // fecha o ficheiro
    fclose(file);

    // liberta a memoria alocada pela funcao malloc
    free(manutencao);
    free(cliente);
    // chama novamente a funcao menu
    limparTerminal();
    voltar_menu();
}

// funcao para procurar todos os ficheiros de manutencao de um determinado cliente
void consultaManCliente() {
    limparTerminal();

    char search_string[256];
    printf("Numero de Cliente: ");
    scanf("%s", search_string);
    search_string[strcspn(search_string, "\n")] = '\0';
    setbuf(stdin, NULL);

    char ignore_char = '_';

    DIR *dir = opendir(".");
    if (dir == NULL) {
        printf("Erro ao abrir o diretorio");
        menu();
        return;
    }

    int foundFiles = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            char *filename_without_extension = strtok(entry->d_name, ".");
            char *substring = strstr(filename_without_extension, search_string);
            if (substring != NULL && substring[0] != ignore_char) {
                printf("%s\n", entry->d_name);
                foundFiles++;
            }
        }
    }

    closedir(dir);

    if (foundFiles == 0) {
        printf("Nenhum ficheiro encontrado para o cliente %s\n", search_string);
        consultaManCliente();
    }

    consultaFicheiroManutencao();
}

// funcao consultarManutencao
void consultarManutencao() {
    // cria o apontador dir do tipo DIR
    // DIR e uma biblioteca de C usada para abrir diretorios
    DIR *dir;
    struct dirent *entrada;
    // inicializa a variavel dir com a funcao opendir para abrir o diretorio onde o programa corre "."
    dir = opendir(".");

    // se nao conseguir abrir o diretorio imprime uma mensagem de erro
    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        return;
    }

    // percorre todo o diretorio e imprime todos os ficheiros com a extencao ".txt"
    while ((entrada = readdir(dir)) != NULL) {
        // Verifica se o arquivo tem a extensão .txt
        if (strstr(entrada->d_name, ".txt") != NULL) {
            // Remove a extensão .txt do nome do arquivo
            char *nome_sem_extensao = strtok(entrada->d_name, ".");
            printf("%s\n", nome_sem_extensao);
        }
    }

    // chamada da funcao consultarFicheiroManutencao
    consultaFicheiroManutencao();

    // fecha o diretorio
    closedir(dir);
}

// inicializacao da funcao Manutencao
void alterarManutencao() {
    setbuf(stdin, NULL);

    char ficheiro[256];
    char linha[150];
    char novaDescricao[100];

    printf("Indique o ficheiro que quer alterar: ");
    scanf("%s", ficheiro);
    setbuf(stdin, NULL);
    strcat(ficheiro, ".txt");

    FILE *file = fopen(ficheiro, "r+");
    if (file == NULL) {
        printf("Erro ao abrir ficheiro\n");
        alterarManutencao();
        return;
    }

    int numeroLinha = 7;
    fseek(file, 0, SEEK_SET);

    int contadorLinhas = 0;

    printf("Descricao: ");
    // Leitura de uma linha completa
    fgets(novaDescricao, sizeof(novaDescricao), stdin);
    novaDescricao[strcspn(novaDescricao, "\n")] = '\0';

    // Criar um arquivo temporário
    FILE *tempFile = tmpfile();

    while (fgets(linha, sizeof(linha), file) != NULL) {
        contadorLinhas++;

        if (contadorLinhas == numeroLinha) {
            fprintf(tempFile, "Descricao: %s\n", novaDescricao);
            printf("Linha alterada com sucesso!\n");
        } else {
            fprintf(tempFile, "%s", linha);
        }
    }

    fclose(file);

    // Voltar ao início do arquivo original
    rewind(tempFile);

    // Copiar conteúdo do arquivo temporário para o arquivo original
    file = fopen(ficheiro, "w");
    if (file == NULL) {
        printf("Erro ao abrir ficheiro\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(linha, sizeof(linha), tempFile) != NULL) {
        fprintf(file, "%s", linha);
    }

    fclose(file);
    fclose(tempFile);

    voltar_menu();
}
// inicializacao da funcao listarFicheiros
void listarFicheiros() {
    // abre o diretorio
    DIR *dir;
    struct dirent *entrada;

    dir = opendir(".");
    // verifica se o diretorio foi aberto com sucesso
    // se nao foi aberto indica uma mensagem de erro
    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        return;
    }
    // percorre todos os ficheiros do diretorio
    while ((entrada = readdir(dir)) != NULL) {
        // Verifica se o arquivo tem a extensão .txt
        if (strstr(entrada->d_name, ".txt") != NULL) {
            // Usa strtok para obter o nome sem a extensão .txt
            char nome_sem_extensao[256];
            strcpy(nome_sem_extensao, entrada->d_name);
            strtok(nome_sem_extensao, ".");

            // imprime os arquivos sem a extensao ".txt"
            printf("%s\n", nome_sem_extensao);
        }
    }
    // fecha o diretorio
    closedir(dir);
}
// inicializacao da funcao criarCodigoManutencao
// recebe dois argumentos
// um apontador do tipo char - numCliente
// um apontador do tipo char - codManutencao
char criarCodigoManutencao(int *numCliente, char *codManutencao) {
    // declaracao das variaveis
    int numero = 0;
    int temp;
    char charTemp[4];
    char nomeFicheiro[15];
    int contador = 0;
    // declaracao do apontador dir do tipo DIR
    DIR *dir;
    struct dirent *entrada;
    // inicializacao da variavel dir com a funcao opendir que abre o diretorio e recebe o argumento "." que significa o diretorio actual
    dir = opendir(".");
    //verifica se foi possivel abrir o diretorio
    //se nao conseguuir abrir o diretorio imprime uma mensagem de erro e sai do programa com a funcao exit(1)
    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        exit(1);
    }

    // percorre todo o diretorio e procura por ficheiros com extencao .txt
    while ((entrada = readdir(dir)) != NULL) {
        if (strstr(entrada->d_name, ".txt") != NULL) {
            strcpy(nomeFicheiro, entrada->d_name);
            // percorre todo o diretorio e guarda o valor que esta entre _ e .
            char *token = strtok(nomeFicheiro, "_");
            token = strtok(NULL, "_");
            // compara os valores a guarda o mais alto numa variavel
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
    // fecha o diretorio
    closedir(dir);

    char num[15];
    char temporaria[30];
    // transforma a variavel para onde o apontador numCliente esta a apontar e guarda na variavel num com um novo tipo, neste caso char
    sprintf(num, "%d", *numCliente);
    // copia a variavel que esta guardarda em num e guarda em temporaria
    strcpy(temporaria, num);
    // concatena a variavel temporaria com _
    strcat(temporaria, "_");
    numero++;  // Incrementa o número
    // pega na variavel numero, do tipo inteiro e guarda na variavel num com tipo char
    sprintf(num, "%d", numero);
    // concatena a variavel temporaria com a variavel num
    strcat(temporaria, num);
    // pega na variavel contador, do tipo inteiro e guarda na variavel num com tipo char
    sprintf(num, "%d", contador);
    // copia o valor da variavel temporaria para a variavel codManutencaoj
    strcpy(codManutencao, temporaria);
    // retorna o apontador codManutencao
    return *codManutencao;
}
// incializacao da funcao criarNomeFicheiro que recebe dois argumentos
char criarNomeFicheiro(char *codManutencao, char *fileName) {
    // copia o valor para onde codMAnutencao esta a apontar e para a variavel onde fileName aponta
    strcpy(fileName, codManutencao);
    // concatena o valor para onde fileName esta a apontar com .txt
    strcat(fileName, ".txt");
    // retorna o apontador fileName
    return *fileName;
}
// inicializacao da funcao consultaFicheiroManutencao
void consultaFicheiroManutencao() {
    char codManutencao[15];
    char linha[150];

    // limpa o buffer
    setbuf(stdin, NULL);
    printf("Indique qual a manutencao que deseja ver: ");
    // recebe o valor introduzido pelo utilizador guarda na variavel codManutencao
    scanf("%s", codManutencao);

    // faz a concatenacao do codigo de manutencao com .txt para gerar um nome de arquivo valido para abrir
    strcat(codManutencao, ".txt");

    FILE *file;
    // abre o  ficheiro
    file = fopen(codManutencao, "r");

    // verifica se consegue abrir o ficheiro
    if (file == NULL) {
        printf("Erro ao abrir ficheiro.\nPrima <ENTER> para continuar\n");
        getchar();
        // se nao conseguir chama novamente a funcao consultaManClinete
        consultaManCliente();
    }

    // percorre cada linha do ficheiro e imprime para o utilizador ver
    while (fgets(linha, sizeof(linha), file) != NULL) {
        printf("%s", linha);
    }
    // fecha o ficheiro
    fclose(file);
    voltar_menu();
}
int verificarFormatoData(const char *data) {
    if (strlen(data) != 10) {
        return 0;
    }

    if (data[4] != '-' ||  data[7] != '-') {
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7 && (data[i] < '0' || data[i] > '9')) {
            return 0;
        }
    }

    int mes = atoi(data + 5);
    if (mes < 1 || mes > 12) {
        return 0;
    }

    int dia = atoi(data + 8);
    if (dia < 1 ||  dia > 31) {
        return 0;
    }

    return 1;
}

int verificarFormatoHoras(const char *horas) {
    if (strlen(horas) != 5) {
        return 0;
    }

    if (horas[2] != ':') {
        return 0;
    }

    for (int i = 0; i < 5; i++) {
        if (i != 2 && (horas[i] < '0' || horas[i] > '9')) {
            return 0;
        }
    }

    int hora = atoi(horas);
    if (hora < 0 || hora > 24) {
        return 0;
    }

    int minuto = atoi(horas + 3);
    if (minuto < 0 || minuto > 59) {
        return 0;
    }

    return 1;
}

void voltar_menu() {
    setbuf(stdin, NULL);
    char opcao;
    printf("\nDeseja continuar?(S - Sim, N - Nao): ");
    scanf("%c", &opcao);

    switch(opcao) {
        case 'S':
            limparTerminal();
            menu();
            break;
        case 'N':
            exit(0);
        default:
            printf("Opcao invalida");
            voltar_menu();
    }
}

void limparTerminal() {
#ifdef _WIN32
    // Limpa o terminal em ambientes Windows
    system("cls"); // Para Windows
#else
    // Para sistemas Unix/Linux
    system("clear");
#endif
}
