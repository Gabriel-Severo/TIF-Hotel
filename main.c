#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <locale.h>
#include <string.h>

void menu ();
void cadastrar();
void conectar();

int main ()
{
    setlocale(LC_ALL, "Portuguese");

    int opc;
    char nome[60], rg[10], cpf[12], nascimento; // nascimento é no formato 2019-12-23. no mysql.  Variaveis para o Inser Into no banco. mude para a estrututura do banco de dados de voces.
    char cadastro[8][100] = {};

    MYSQL conexao;
    mysql_init(&conexao);
    conectar(&conexao);

    menu(); // Estrutura de opções.
    printf("\t>>> ");

    do{
        scanf("%d", &opc);
        if(opc < 0 || opc > 2)
            printf("Opção inválida\n\t>>>");
    }while (opc < 0 || opc > 2);

    if (opc == 1)
        cadastrar(cadastro, &conexao);
    else if (opc == 2)
        printf("");
    else if (opc == 0){
        printf("Cya!");
        exit(0);
    }
}

void voltar(){
    char voltar;
    printf("\nVocê quer voltar para o menu(S/N): ");
    scanf(" %c", &voltar);

    if(voltar == 's' || voltar == 'S'){
        system("cls");
        menu();
    }else{
        printf("Saindo...");
    }
}

void menu ()
{
    // estrutura do menu.
    printf("              Tif Palace HOTEL\n\n||             Menu Principal             ||\n||----------------------------------------||\n||                                        ||\n||      1 - Cadastrar Cliente.            ||\n||      2 - Buscar Cliente.               ||\n||      0 - Para sair                     ||\n||                                        ||\n||                                        ||\n||                                        ||\n");
}

void conectar(MYSQL *conexao)
{
	printf("Conectando... \n");
    //realiza a conexão com o banco de dado  e faz o teste.
    if (mysql_real_connect(conexao, "db4free.net", "tifhotell", "tifhotel", "tifhotell", 0, NULL, 0))
        printf("Banco de dados conectado com sucesso!\n");
    else
        printf("Algo deu errado %s %d\n", mysql_error(conexao), mysql_errno(conexao));
}

void cadastrar(char cadastro[][100], MYSQL *conexao)
{
    //Limpa o lixo da memória, assim o gets funciona normalmente
    fflush(stdin);
	char ano[5], mes[3], dia[3];
    system("cls");
    printf("CADASTRAR USUÁRIO\n");
    printf("Nome: ");
    gets(cadastro[0]);
    printf("Data de nascimento(DD MM AAAA): ");
    scanf("%s %s %s", &dia, &mes, &ano);
    //Junta a data com o - pois o SQL só aceita esse formato
    strcat(ano, "-");
    strcat(ano, mes);
    strcat(ano, "-");
    strcat(ano, dia);
    strcpy(cadastro[1], ano);
    printf("CPF: ");
    scanf("%s", &cadastro[2]);
    printf("RG: ");
    scanf("%s", &cadastro[3]);
    fflush(stdin);
    printf("Cidade: ");
    gets(cadastro[4]);
    fflush(stdin);
    printf("Estado: ");
    gets(cadastro[5]);
    fflush(stdin);
    printf("País: ");
    gets(cadastro[6]);
    printf("Telefone: ");
    scanf("%s", &cadastro[7]);
    printf("Quarto: ");
    scanf("%s", &cadastro[8]);
    printf("\nCADASTRO SALVO COM SUCESSO!");
    char query[200];
    sprintf(query,"INSERT INTO cadastro (nome, cpf, rg, nascimento, quarto, telefone, cidade, estado, pais) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');"
            , cadastro[0], cadastro[2], cadastro[3], cadastro[1], cadastro[8], cadastro[7], cadastro[4], cadastro[5], cadastro[6]);
    mysql_query(conexao, query);
    voltar();
}


