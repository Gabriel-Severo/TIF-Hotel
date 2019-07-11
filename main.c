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
    int validarCampo();
    int verificarCPF();
    void efetivarReserva();

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
            exit(0);
        }
    }

    void menu (MYSQL *conexao)

    {
        int opc;
        char cadastro[7][100] = {};

        // estrutura do menu.

        printf("              Tif Palace HOTEL\n\n||             Menu Principal             ||\n||----------------------------------------||\n||                                        ||\n||      1 - Cadastrar Cliente.            ||\n||      2 - Buscar Cliente.               ||\n||      3 - fazer Reserva.                ||\n||      4 - Sobre                         ||\n||      0 - Para Sair.                    ||\n||                                        ||\n||                                        ||\n");

        printf("\t>>> ");

        do{
            scanf("%d", &opc);

            if(opc < 0 || opc > 4)
            {
                printf("Opção invalida\n\t>>>");
            }

        } while (opc < 0 || opc > 4);

        if (opc == 1)

        {
            cadastrar(cadastro, conexao);
            voltar(conexao);
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
            fzreserva(cadastro, conexao);
            voltar(conexao);
        }
        else
        if (opc == 4){
            system("cls");
            printf("\a\t\t\tCRIADO POR: \n\n");
            printf("\t\tGabriel Rodrigues\n");
            printf("\t\tLucas Rodrigues\n");
            printf("\t\tMatheus Andrade\n");
            voltar(conexao);
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

    int valido = 0;
    int campoEmUso = 0;

    // pegar o CPF
    do{
        printf("CPF: ");
        scanf("%s", &cadastro[2]);
        // verificar se o CPF é válido
        valido = validarCampo(cadastro[2], 11);
        // verificar se o CPF já está em uso
        campoEmUso = verificarCampo(conexao, "cadastro", "cpf", cadastro[2]);
    }
    while(valido != 1 || campoEmUso != 0);

    // pegar o RG
    do{
        printf("RG: ");
        scanf("%s", &cadastro[3]);
        //verificar se o RG é válido
        valido = validarCampo(cadastro[3], 9);
        //verificar se o RG já está em uso
        campoEmUso = verificarCampo(conexao, "cadastro", "rg", cadastro[3]);
    }
    while(valido != 1 || campoEmUso != 0);

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
}

void consultar (MYSQL *conexao)
{
    system("cls");
    printf("CONSULTAR CLIENTES:\n");
    char cpf[100];

    fflush(stdin);

    printf("CPF: ");
    gets(cpf);

    char query[100];
    sprintf(query, "SELECT * FROM cadastro WHERE cpf='%s'", cpf);
    if(mysql_query(conexao, query))
        printf("Erro\n");
    else
        printf("Query com sucesso\n");
    MYSQL_RES *resp = mysql_store_result(conexao);
    MYSQL_ROW linhas = mysql_fetch_row(resp);
    //Se o numero retornado for 0 quer dizer que não encontrou ninguém no banco de dados
    int numero_linhas = mysql_num_rows(resp);

    if (numero_linhas == 0){
        printf("Não encontrado CPF: %s", cpf);
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

void fzreserva (char cadastro[][100], MYSQL *conexao)

{
    system("cls");
    char resp;

    int cadastroExiste = 0;
    char criarNovoCadastro = ' ';
    char cpf[100] = {};
    int novoCadastro = 0;

    printf ("O usuario ja é cadastrado (S ou N): ");
    scanf ("%s", &resp);

    if (resp == 'S' || resp == 's')
    {
        printf("Digite seu CPF: ");
        fflush(stdin);
        gets(cpf);
        cadastroExiste = verificarCampo(conexao, "cadastro", "cpf", cpf);

        // verifica se o CPF informado é válido, caso não seja, pergunta se a pessoa quer fazer um novo cadastro
        if(cadastroExiste == 0){
            printf("\nDesculpe, mas o CPF não foi encontrado!\n");
            do{
                printf("\nVocê quer se registrar? ");
                scanf(" %c", &criarNovoCadastro);
            }while(criarNovoCadastro != 's' && criarNovoCadastro != 'S' && criarNovoCadastro != 'n' && criarNovoCadastro != 'N');

            //se sim, faz um novo cadastro
            if(criarNovoCadastro == 'S' || criarNovoCadastro == 's'){
                cadastrar(cadastro, conexao);
                novoCadastro = 1;
            }else{
                voltar(conexao);
            }
        }
    }
    else
    if (resp == 'N' || resp == 'n')

    {
        cadastrar(cadastro, conexao);
        novoCadastro = 1;
    }

    // caso houver um novo cadastro, ele já irá puxar do banco o último registro feito
    if(novoCadastro == 1){
        char query[100];
        sprintf(query, "SELECT cpf FROM cadastro ORDER BY id DESC");
        mysql_query(conexao, query);
        MYSQL_RES *resultado = mysql_store_result(conexao);
        MYSQL_ROW cpfRegistrado = mysql_fetch_row(resultado);
        strcpy(cpf, cpfRegistrado[0]);
    }

    char id[3] = {};
    int quartoEmUso;
    int quartoNegativo = 0;

    //verificar se o quarto digitado está disponível
    do{
        printf("\nDigite o numero do Quarto: ");
        scanf("%s", &id);
        quartoNegativo = (id[0] - 48);
        if((quartoNegativo < 1)){
            printf("\nQUARTO inválido\n");
            exit(0);
        }
        quartoEmUso = verificarCampo(conexao, "quarto", "id", id);
    }while(quartoEmUso == 1);

    //Verificar disponibilidade do quarto no Banco de dados.
    efetivarReserva(conexao, id, cpf);
}

int verificarCampo(MYSQL *conexao, char table[100], char field[100], char value[100]){
    char query[100];
    sprintf(query, "SELECT * FROM %s WHERE %s='%s'", table, field, value);

    mysql_query(conexao, query);

    MYSQL_RES *resultado = mysql_store_result(conexao);

    int linhas = mysql_num_rows(resultado);

    if(linhas != 0){
        printf("\n%s já está em uso!\n\n", field);
    }

    // limpa todas as queries antes de voltar para a função cadastro
    mysql_free_result(resultado);

    return linhas;
}

int verificarCPF(char valor[]){
    int verificador, posicao, vezes = 0, vezes2, correto=0;
    while(vezes<2){
        verificador=0;
        if (vezes==0){
            posicao=10;
            vezes2=posicao-1;
        }else
            posicao=11;
            vezes2=posicao-1;

        for(int i = 0; i < vezes2; i++){
            //Uma maneira fácil de converter char para int é subtraindo -48 pois o 0 é 48
            verificador += (valor[i]-48) * posicao;
            posicao--;
        }
        verificador =  11 - verificador % 11;
        if(verificador>9)
            verificador=0;
        if(verificador==valor[vezes+9]-48)
            correto++;
        vezes++;
    }
    if (correto == 2)
        return 1;
    else{
        printf("CPF Inválido\n");
        return 0;
    }

}
int validarCampo(char valor[], int tamanho){
    if(tamanho == 11){
        //Verifica se foi digitado apenas números
        for (int i = 0; i < tamanho; i++)
            if (valor[i]>57||valor[i]<48){
                printf("CPF Inválido\n");
                return 0;
            }
        if(strlen(valor) == 11){
            int valido = verificarCPF(valor);
            if (valido == 0)
                return 0;
            else
                return 1;
        }else if(strlen(valor) > 11){
            printf("\nCPF COM DIGITOS A MAIS\n");
            return 0;
        }
    }else if(tamanho == 9){
        //Verifica se foi digitado apenas números
        for (int i = 0; i < tamanho; i++)
            if (valor[i]>57||valor[i]<48){
                printf("RG Inválido\n");
                return 0;
            }
        if(strlen(valor) == 9){
            return 1;
        }else if(strlen(valor) > 9){
            printf("\nRG COM DIGITOS A MAIS\n");
            return 0;
        }
    }
}

void efetivarReserva(MYSQL *conexao, char id[3], char cpf[100]){
    char query[100];
    sprintf(query, "INSERT INTO quarto (id, ocupacao, pessoa) VALUES ('%s', 'S', '%s')", id, cpf);
    mysql_query(conexao, query);

    system("cls");
    printf("\nRESERVA CONCLUIDA!\n");
    printf("Cadastro: %s\n", cpf);
    printf("Quarto: %s\n", id);
}
