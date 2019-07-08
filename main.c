#include <stdio.h>
#include <mysql.h>
#include <locale.h>

void menu ();
void conectar(MYSQL *conexao);

int main ()

{
    setlocale (LC_ALL,"");

    int opc;
    char nome[60], rg[10], cpf[12], nascimento; // nascimento é no formato 2019-12-23. no mysql.  Variaveis para o Inser Into no banco. mude para a estrututura do banco de dados de voces.

    MYSQL conexao;
    mysql_init(&conexao);
    conectar(&conexao);

    menu(); 							// Estrutura de opções.
    scanf ("%i", &opc);

    if (opc > 2 || opc < 1)
    {
        printf ("Opção Invalida:");

        for (;opc > 2 || opc < 1;)
        {
            printf ("selecione uma opção valida");
            scanf ("%i", &opc);

        }
    }
    else if (opc == 1)
    {

    }
    else if (opc ==2)
    {

    }
}

void menu ()
{
    // estrutura do menu.
    printf("              Tif Palace HOTEL\n\n||             Menu Principal             ||\n||----------------------------------------||\n||                                        ||\n||      1 - Cadastrar CLiente.            ||\n||      2 - Buscar Cliente.               ||\n||                                        ||\n||                                        ||\n||                                        ||\n||                                        ||\n");
}

void conectar(MYSQL *conexao)
{
    //realiza a conexão com o banco de dado  e faz o teste.
    if (mysql_real_connect(conexao, "db4free.net", "tifhotell", "tifhotel", "", 0, NULL, 0))
        printf("Banco de dados conectado com sucesso!\n");
    else
        printf("Algo deu errado %s\n", mysql_error(conexao));
}


