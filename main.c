#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <locale.h>
#include <string.h>

    void consultar();
    void menu ();
    void cadastrar();
    void conectar();
    void fzreserva();
    int verificarCampo();

    int main ()

    {
        setlocale(LC_ALL, "Portuguese");

        int i;
        char nome[60], rg[10], cpf[12], nascimento;

        MYSQL conexao;

        mysql_init(&conexao);
        conectar(&conexao);

        menu(&conexao);

    }

    void voltar(MYSQL *conexao)
    {
        char voltar;

        do{
            printf("\nVocê quer voltar para o menu(S/N): ");
            scanf(" %c", &voltar);
            printf("%c", voltar);
        }
        while (voltar != 's' && voltar != 'S' && voltar != 'n' && voltar != 'N');

        if(voltar == 's' || voltar == 'S')
        {
            system("cls"); //Limpando a tela de comando!
            menu(conexao);
        }
        else
        {
            printf("Saindo...");
        }
    }

    void menu (MYSQL *conexao)

    {
        int opc;
        char cadastro[7][100] = {};

        // estrutura do menu.

        printf("              Tif Palace HOTEL\n\n||             Menu Principal             ||\n||----------------------------------------||\n||                                        ||\n||      1 - Cadastrar Cliente.            ||\n||      2 - Buscar Cliente.               ||\n||      3 - fazer Reserva.                ||\n||      0 - Para Sair.                    ||\n||                                        ||\n||                                        ||\n");

        printf("\t>>> ");

        do{
            scanf("%d", &opc);

            if(opc < 0 || opc > 3)
            {
                printf("Opção invalida\n\t>>>");
            }

        } while (opc < 0 || opc > 3);

        if (opc == 1)

        {
            cadastrar(cadastro, conexao);
        }
        else
        if (opc == 2)

        {
            consultar(conexao);
        }
        else
        if (opc == 0)

        {
            printf("Cya!");
            exit(0);
        }
        else
        if (opc == 3)
        {
            fzreserva();
        }
    }

void conectar(MYSQL *conexao)
{
	printf("Conectando... \n");

    //realiza a conexÃ£o com o banco de dado  e faz o teste.

    if (mysql_real_connect(conexao, "db4free.net", "tifhotell", "tifhotel", "tifhotell", 0, NULL, 0))
    {
		printf("Banco de dados conectado com sucesso!\n");
	}
	else
	{
        printf("Algo deu errado %s %d\n", mysql_error(conexao), mysql_errno(conexao));
    }
}

void cadastrar(char cadastro[][100], MYSQL *conexao)
{
    //Limpa o lixo da memoria, assim o gets funciona normalmente

	char ano[5], mes[3], dia[3];
    system("cls");

    printf("CADASTRAR USUARIO:\n");

    fflush(stdin);
    printf("Nome: ");
    gets(cadastro[0]);

    printf("Data de nascimento(DD MM AAAA): ");
    scanf("%s %s %s", &dia, &mes, &ano);

    //Junta a data com o - pois o SQL sÃ³ aceita esse formato
    strcat(ano, "-");
    strcat(ano, mes);
    strcat(ano, "-");
    strcat(ano, dia);
    strcpy(cadastro[1], ano);


    printf("CPF: ");
    scanf("%s", &cadastro[2]);

    //verificar se CPF já está em uso
    int valido = verificarCampo(conexao, "cpf", cadastro[2]);

    while(valido != 0){
        printf("CPF: ");
        scanf("%s", &cadastro[2]);
        valido = verificarCampo(conexao, "cpf", cadastro[2]);
    }

    printf("RG: ");
    scanf("%s", &cadastro[3]);

    //verificar se RG já está em uso
    valido = verificarCampo(conexao, "rg", cadastro[3]);

    while(valido != 0){
        printf("RG: ");
        scanf("%s", &cadastro[3]);
        valido = verificarCampo(conexao, "rg", cadastro[3]);
    }


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

    printf("\nCADASTRO SALVO COM SUCESSO!");

    char query[200];

    sprintf(query,"INSERT INTO cadastro (nome, cpf, rg, nascimento, telefone, cidade, estado, pais) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');"
            , cadastro[0], cadastro[2], cadastro[3], cadastro[1], cadastro[7], cadastro[4], cadastro[5], cadastro[6]);

	mysql_query(conexao, query);

	voltar(conexao);
}

void consultar (MYSQL *conexao)
{
    system("cls");
    printf("CONSULTAR CLIENTES:\n");
    char nome[100];

    fflush(stdin);

    printf("Nome: ");
    gets(nome);

    char query[100];
    sprintf(query, "SELECT * FROM cadastro WHERE nome='%s'", nome);
    if(mysql_query(conexao, query))
        printf("Erro\n");
    else
        printf("Query com sucesso\n");
    MYSQL_RES *resp = mysql_store_result(conexao);
    MYSQL_ROW linhas = mysql_fetch_row(resp);
    //Se o numero retornado for 0 quer dizer que não encontrou ninguém no banco de dados
    int numero_linhas = mysql_num_rows(resp);

    if (numero_linhas == 0){
        printf("Não encontrei %s", nome);
    }else{
        char campos[9][100]={{"Id"}, {"Nome"}, {"CPF"}, {"RG"}, {"Nascimento"}, {"Telefone"}, {"Cidade"}, {"Estado"}, {"Pais"}};
        int i = 0;
        printf("\n");
        while (i<mysql_num_fields(resp)){
            printf("%s: %s\n", campos[i], linhas[i]);
            i++;
        }
    }

    voltar(conexao);
}

void fzreserva ()

{
    char resp;
    int id;

    printf ("O usuario ja é cadastrado (S ou N): ");
    scanf ("%s", &resp);

    if (resp == 'S' || resp == 's')
    {

        printf ("\nDigite o cpf do cliente:");
        // Fazer consulta com o servidor.
    }
    else
    if (resp == 'N' || resp == 'n')

    {
        void cadastrar();
    }


    printf ("Digite o numero do Quarto:");
    scanf ("%i", &id);

    //Verificar disponibilidade do quarto no Banco de dados.
}

int verificarCampo(MYSQL *conexao, char field[100], char value[100]){
    char query[100];
    sprintf(query, "SELECT * FROM cadastro WHERE %s='%s'", field, value);

    mysql_query(conexao, query);

    MYSQL_RES *resultado = mysql_store_result(conexao);

    int linhas = mysql_num_rows(resultado);

    if(linhas == 0){
        printf("\n%s válido\n\n", field);
    }else{
        printf("\n%s já está em uso!\n\n", field);
    }

    // limpa todas as queries antes de voltar para a função cadastro
    mysql_free_result(resultado);

    return linhas;
}

