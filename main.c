#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

// Estrutura Pessoa
struct tb_endereco
{
    char cep[9]; /**< 00000000 */
    char logradouro[31];
    char numero[11];
    char bairro[21];
    char cidade[21];
    char estado[21];

};
struct tb_dataNacimento
{
    int dia;
    int mes;
    int ano;
};
struct tb_contato
{
    char telefone[13]; // 011900000000
    char email[81];
};

struct tb_diagnostico
{
    int dia;
    int mes;
    int ano;
};
struct tb_comorbidade
{
    char diabetes;
    char obesidade;
    char hipertencao;
    char tuberculose;
    char outros[151];

};
struct tb_pessoa
{
    char cpf[12];
    char nomeCompleto[41];
    struct tb_dataNacimento dataNascimento;
    struct tb_contato contato;
    struct tb_endereco endereco;
    struct tb_diagnostico diagnostico;
    struct tb_comorbidade comorbidade;
} paciente;

int login();
int menu();
int exibirDados();
int cadastrar();
int pesquisar();
void validarDados(char *mensagem, int parametro, int tamanho);
int calcularIdade(struct tb_pessoa p);
void sobre();

int main()
{
    /***
    Inicio do sistema
    ***/
    login();
    return 0;
}
/****
    Autenticação do usuário
****/
int login()
{
    int contador = 0, tam = 0;
    char usuario[10], senha[10];
    while (contador != 3)
    {
        contador++;

        printf("\n\n\t\t%s\n", "===================================");
        printf("\t\t%s\n", "      BEM VINDO AO SISTEMA!!!");
        printf("\t\t%s\n", "===================================");
        printf("\t\t%s\n", "<CHC - Conecte hospitalar COVID-19>");
        printf("\t\t%s\n", "===================================\n");

        printf("\n\t%s", "Digite usuario/senha para acessar o sistema!!!\n\n");
        printf("\t%10s", "Usuario: ");
        fflush(stdin);
        gets(usuario);
        printf("\t%10s", "Senha: ");
        fflush(stdin);
        /// usuario e senha
        do
        {
            senha[tam] = getch();
            if (senha[tam] == 0x08 && tam > 0) //Backspace
            {
                printf("\b \b");
                senha[tam] = 0x00;
                tam--;
            }
            else if (senha[tam] == 13) // Verificar se tecla pressionada foi Enter
            {
                senha[tam] = 0x00;
                break;
            }
            else if (senha[tam] != 0x08)
            {
                putchar('*');
                tam++;
            }
        }
        while (senha[tam] != 13);

        if (strcmp(usuario, "admin") == 0 && strcmp(senha, "admin") == 0)
        {
            contador = 0;
            system("cls");
            menu();
        }
        else
        {
            system("cls");
            printf("\n\t %s [%d/3]!!!\n\n", "Usuario/senha invalido tentativa(s)", contador);
            printf("\t");
            system("pause");
        }
        tam = 0;
        system("cls");
    }
    printf("\n\n\t %s", "Voce atingiu o limite de tentativas tente novamente mais tarde!!!\n\n");
    printf("\t");
    system("pause");
    return 0;
}
/****
    Menu principal de opções
****/
int menu()
{
    /// Opções do menu
    char menu[][13] = {"Cadastro", "Sobre", "Sair"};
    /// Declaração das variáveis
    int opcao = 0, contadorMenu = sizeof(menu) / sizeof(menu[0]), i;
    /// Se opção for igual a 3 volta para tela de login
    while (opcao != 3)
    {
        printf("\n\t\t%s\n", "===================================");
        printf("\t\t%s\n", "<CHC - Conecte hospitalar COVID-19>");
        printf("\t\t%s\n", "===================================\n");

        printf("---------------------------------------------------------------------\n\n");
        /// Exibir as opções do menu
        for (i = 0; i < contadorMenu; i++)
        {
            printf("\t[%d] - %s\n", i + 1, menu[i]);
        }
        printf("\n\t%s", "Digite a opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);
        switch(opcao)
        {
        case 1:
            /// Chamar a opção de cadastro para infromar os dados do paciente
            cadastrar();
            break;
        case 2:
            /// Chamar as informações sobre o sistema
            sobre();
            break;
        case 3:
            /// Continuar para sair do loop
            continue;
            break;
        default:
            /// Exibe mensagem caso a opção não corresponda a uma das opções a cima
            printf("\n\t%s", "Opcao invalida - tecle <Enter>");
            /// Aguar o usuário pressionar enter
            getch() + scanf("Enter");
        }
        /// Limpar a tela do programar
        system("cls");
    }
    return 0;
}
/****
    Cadastrar o paciente
****/
int cadastrar()
{
    char opcao;

    FILE *arqPaciente, *arqSecretaria;
    /******
     Verificar se o paciente já tem cadastro
    ******/
    if ((arqSecretaria = fopen("secretariaSaude.txt", "r")) == NULL)
    {
        arqSecretaria = fopen("secretariaSaude.txt", "w");
        fprintf(arqSecretaria, "CPF;Idade\n");
        fclose(arqSecretaria);
    }
    if ((arqPaciente = fopen("pacientes.txt", "r")) == NULL)
    {
        arqPaciente = fopen("pacientes.txt", "w");
        fprintf(arqPaciente, "CPF;Nome;Data Nasc.;Telefone;Email;CEP;Endereco;Numero;Bairro;Cidade;Estado;Data Diagnost.;Diabetes;Obesidade;Hipertencao;Tuberculose;Outros\n");
        fclose(arqPaciente);
    }
    do
    {
        system("cls");
        printf("\n %s\n", " tecla < ESC > voltar menu!");
        printf("\n\t %s", "Informe os dados do paciente!\n\n");
        printf("\t %s", "-----  Dados Pessoais -----");
        printf("\n---------------------------------------------------\n");
        if (pesquisar() == 0)
        {
            validarDados("Nome Completo....: ", 1, 40); // 1 representar o case para nomecompleto
            validarDados("Data Nascimento (dd/mm/aaaa): ", 2, 10);
            fflush(stdin);
            system("cls");

            /// Contato
            printf("\n %s\n", " tecla < ESC > voltar menu!");
            printf("\n\t %s", "----- Contato -----\n");
            printf("\n---------------------------------------------------\n");
            validarDados("Telefone.........: ", 3, 12);
            validarDados("E-mail...........: ", 4, 80);
            system("cls");

            /// Dados endereço
            printf("\n %s\n", " tecla < ESC > voltar menu!");
            printf("\n\t %s", "----- Endereco -----\n");
            printf("\n---------------------------------------------------\n");
            validarDados("CEP..............: ", 5, 8);
            validarDados("Endereco.........: ", 6, 30);
            validarDados("Numero...........: ", 7, 10);
            validarDados("Bairro...........: ", 8, 20);
            validarDados("Cidade...........: ", 9, 20);
            validarDados("Estado...........: ", 10, 20);
            system("cls");

            /// Dados diagnostico
            printf("\n%s\n", " tecla < ESC > voltar menu!");
            printf("\n\t %s", "----- Diagnostico -----\n");
            printf("\n---------------------------------------------------\n");
            validarDados("Data Diagnostico (dd/mm/aaaa): ", 11, 10);
            system("cls");

            /// Dados comorbidade
            printf("\n %s\n", " tecla < ESC > voltar menu!");
            printf("\n\t %s", "----- Possui Comorbidade -----\n");
            printf("\n---------------------------------------------------\n");
            printf("\n%2s%s","", "Para responder o questionario utilizer [Sim=S/Nao=N]!\n");
            validarDados("Possui Diabetes......: ", 12, 1);
            validarDados("Possui Obesidade.....: ", 13, 1);
            validarDados("Possui Hipertencao...: ", 14, 1);
            validarDados("Possui Tuberculose...: ", 15, 1);
            printf("\n\n%2s%s","", "----- Caso possua outro tipo de comorbidade informe em outros -----\n");
            validarDados("Outros........: ", 16, 150);
            printf("\n---------------------------------------------------\n");

            /// Calcular idade
            int idade = calcularIdade(paciente);

            /// Exibe os dados informados antes de salvar
            exibirDados();

            printf("\n\t %s", "[Salvar=S/Cancelar=C]\n");
            printf("\n\t %s", "Digite opcao: ");
            fflush(stdin);
            opcao = toupper(getchar());
            switch(opcao)
            {
            case 'S':
                /// Salvar o dados
                /// Verificar se idade e maior que 65, se for pertence ao grupo de risco
                /// e será salvo o arquivo de envio para a secretaria de saúde
                if(idade > 65)
                {
                    arqSecretaria = fopen("secretariaSaude.txt", "a");
                    fprintf(arqSecretaria, "%s;%d\n", paciente.endereco.cep, idade);
                    fclose(arqSecretaria);
                }
                arqPaciente = fopen("pacientes.txt", "a");
                fprintf(arqPaciente, "%s;%s;%d-%d-%d;%s;%s;%s;%s;%s;%s;%s;%s;%d-%d-%d;%c;%c;%c;%c;%s\n", paciente.cpf,
                        paciente.nomeCompleto, paciente.dataNascimento.dia, paciente.dataNascimento.mes, paciente.dataNascimento.ano,
                        paciente.contato.telefone, paciente.contato.email, paciente.endereco.cep, paciente.endereco.logradouro,
                        paciente.endereco.numero, paciente.endereco.bairro, paciente.endereco.cidade, paciente.endereco.estado,
                        paciente.diagnostico.dia, paciente.diagnostico.mes, paciente.diagnostico.ano, paciente.comorbidade.diabetes,
                        paciente.comorbidade.obesidade, paciente.comorbidade.hipertencao, paciente.comorbidade.tuberculose, paciente.comorbidade.outros);
                fclose(arqPaciente);
                system("cls");
                printf("\n\n\t %s", "Registro Salvo com sucesso!!!\n\n");
                system("pause");
                fflush(stdin);
                break;
            case 'C':
                system("cls");
                printf("\n\n\t %s", "Registro cancelado com sucesso!!!\n\n");
                system("pause");
                fflush(stdin);
                break;
            }
            if (opcao != 'N')
            {
                printf("\n\t %s", "Deseja continuar cadastrando [S/N]: ");
                opcao = toupper(getchar());
            }
        }
    }
    while(opcao != 'N');
    return 0;
}
/****
    Exibir os dados informados para verificar inconsistências
    antes de mostrar as opções salvar, editar e cancelar
****/
int exibirDados()
{
    system("cls");
    printf("\n\n\t%s", "*** Verifique os dados informados! ***\n");
    printf("\n===================================================\n");
    printf("\t%s", "  *** Dados do Paciente ***");
    printf("\n---------------------------------------------------\n");
    /// Dados do paciente
    printf("%20s%s\n", "CPF...: ", paciente.cpf);
    printf("%20s%s\n", "Nome Completo...: ", paciente.nomeCompleto);
    printf("%20s%d/%d/%d\n", "Data Nasc....: ", paciente.dataNascimento.dia, paciente.dataNascimento.mes, paciente.dataNascimento.ano);
    printf("\n===================================================\n");
    /// Contato
    printf("\t%s", "  *** Contato(s) ***");
    printf("\n---------------------------------------------------\n");
    printf("%20s%s\n", "Telefone...: ", paciente.contato.telefone);
    printf("%20s%s\n", "E-mail...: ", paciente.contato.email);
    printf("\n===================================================\n");
    /// Endereço
    printf("\t%s", "  *** Endereco ***");
    printf("\n---------------------------------------------------\n");
    printf("%20s%s\n", "CEP...: ", paciente.endereco.cep);
    printf("%20s%s\n", "Endereco...: ", strupr(paciente.endereco.logradouro));
    printf("%20s%s\n", "Numero...: ", strupr(paciente.endereco.numero));
    printf("%20s%s\n", "Bairro...: ", strupr(paciente.endereco.bairro));
    printf("%20s%s\n", "Cidade...: ", strupr(paciente.endereco.cidade));
    printf("%20s%s\n", "Estado...: ", strupr(paciente.endereco.estado));
    printf("\n===================================================\n");
    /// Diagnostico
    printf("\t%s", "  *** Diagnostico ***");
    printf("\n---------------------------------------------------\n");
    printf("%20s%d/%d/%d\n", "Data...: ",paciente.diagnostico.dia, paciente.diagnostico.mes, paciente.diagnostico.ano);
    printf("\n===================================================\n");
    /// Comorbidades
    printf("\t%s", "  *** Comorbidades ***");
    printf("\n---------------------------------------------------\n");
    printf("%20s%c\n", "Diabetes...: ", toupper(paciente.comorbidade.diabetes));
    printf("%20s%c\n", "Obesidade...: ", toupper(paciente.comorbidade.obesidade));
    printf("%20s%c\n", "Hipertecao...: ", toupper(paciente.comorbidade.hipertencao));
    printf("%20s%c\n", "Tuberculose...: ", toupper(paciente.comorbidade.tuberculose));
    printf("%20s%s\n\n", "Outros...: ", strupr(paciente.comorbidade.outros));
    printf("===================================================\n");
    return 0;
}
/****
    Pesquisar o paciente pelo cpf informado para verificar se o mesmo já está cadastrado
    no sistema
****/
int pesquisar()
{
    FILE *arqPaciente;
    int cadastrado = 0, bufferLength = 255;
    char *linha, buffer[bufferLength];
    /// Pesquisar
    validarDados("CPF..............: ", 0, 11);
    fflush(stdin);
    if ((arqPaciente = fopen("pacientes.txt", "r")) != NULL)
    {
        while(fgets(buffer, bufferLength, arqPaciente))
        {
            linha = strtok(buffer, ";");
            if (strcmp(paciente.cpf, linha) == 0)
            {
                linha = strtok(NULL, ";");
                printf("\n\n\t Paciente: -> %s <- ja esta cadastrado", linha);
                printf("\n\n\t %s", "Pressione Enter");
                scanf("Enter");
                cadastrado = 1;
            }
        }
        fclose(arqPaciente);
    }
    return cadastrado;
}

void validarDados(char *mensagem, int parametro, int tamanho)
{
    /*****
        Tipo define 0 ou 1; 0 = numeros; 1 = letras
        Mensagem define a mensagem impressa para o usuário
        Parametro define a utilização no switch para identificar as variáveis corretas
        Tamanho define o tamanho para cada variável para evitar estouro de buffer
    *****/
    int tam = 0;
    char validar[tamanho], data[10];
    printf("\n%5s%s", "", mensagem);
    do
    {
        validar[tam] = getch();
        fflush(stdin);
        if (validar[tam] == 27)
        {
            system("cls");
            /// Limpar as variáveis
            memset(&paciente.cpf, 0, sizeof(paciente.cpf));
            memset(&paciente.nomeCompleto, 0, sizeof(paciente.nomeCompleto));
            paciente.dataNascimento.dia = 0;
            paciente.dataNascimento.mes = 0;
            paciente.dataNascimento.ano = 0;
            memset(&paciente.contato.telefone, 0, sizeof(paciente.contato.telefone));
            memset(&paciente.contato.email, 0, sizeof(paciente.contato.email));
            memset(&paciente.endereco.cep, 0, sizeof(paciente.endereco.cep));
            memset(&paciente.endereco.logradouro, 0, sizeof(paciente.endereco.logradouro));
            memset(&paciente.endereco.numero, 0, sizeof(paciente.endereco.numero));
            memset(&paciente.endereco.bairro, 0, sizeof(paciente.endereco.bairro));
            memset(&paciente.endereco.cidade, 0, sizeof(paciente.endereco.cidade));
            paciente.diagnostico.dia = 0;
            paciente.diagnostico.mes = 0;
            paciente.diagnostico.ano = 0;
            memset(&paciente.comorbidade.diabetes, 0, sizeof(paciente.comorbidade.diabetes));
            memset(&paciente.comorbidade.obesidade, 0, sizeof(paciente.comorbidade.obesidade));
            memset(&paciente.comorbidade.hipertencao, 0, sizeof(paciente.comorbidade.hipertencao));
            memset(&paciente.comorbidade.tuberculose, 0, sizeof(paciente.comorbidade.tuberculose));
            memset(&paciente.comorbidade.outros, 0, sizeof(paciente.comorbidade.outros));
            /// Chamar o menu
            menu();

        }
        else if (validar[tam] == 0x08 && tam > 0) //Backspace
        {
            printf("\b \b");
            switch(parametro)
            {
            case 0:
                paciente.cpf[tam] = 0x00;
                break;
            case 1:
                paciente.nomeCompleto[tam] = 0x00;
                break;
            case 3:
                paciente.contato.telefone[tam] = 0x00;
                break;
            case 4:
                paciente.contato.email[tam] = 0x00;
                break;
            case 5:
                paciente.endereco.cep[tam] = 0x00;
                break;
            case 6:
                paciente.endereco.logradouro[tam] = 0x00;
                break;
            case 7:
                paciente.endereco.numero[tam] = 0x00;
                break;
            case 8:
                paciente.endereco.bairro[tam] = 0x00;
                break;
            case 9:
                paciente.endereco.cidade[tam] = 0x00;
                break;
            case 10:
                paciente.endereco.estado[tam] = 0x00;
                break;
            case 12:
                paciente.comorbidade.diabetes = 0x00;
                break;
            case 13:
                paciente.comorbidade.obesidade = 0x00;
                break;
            case 14:
                paciente.comorbidade.hipertencao = 0x00;
                break;
            case 15:
                paciente.comorbidade.tuberculose = 0x00;
                break;
            case 16:
                paciente.comorbidade.outros[tam] = 0x00;
                break;
            }
            validar[tam] = 0x00;
            tam--;
        }
        else if (validar[tam] == 13) // Enter
        {
            validar[tam] = 0x00;
            break;
        }
        else if (validar[tam] != 0x08)
        {
            if (tam < tamanho)
            {

                switch(parametro)
                {
                case 0: ///**< Formatar CPF */
                    if (validar[tam] > 47 && validar[tam] < 58)
                    {
                        putchar(validar[tam]);
                        paciente.cpf[tam] = validar[tam];
                        tam++;
                    }
                    break;
                case 1: /**< Validar nome não aceitando caracteres especiais ou números */
                    if ((validar[tam] > 64 && validar[tam] < 91) || (validar[tam] > 96 && validar[tam] < 123) ||  validar[tam] == 32)
                    {
                        putchar(validar[tam]);
                        paciente.nomeCompleto[tam] = toupper(validar[tam]);
                        tam++;
                    }
                    break;
                case 2: ///**< Formatar data nascimento 00/00/0000*/
                    if ((validar[tam] > 47 && validar[tam] < 58))
                    {
                        data[tam] = validar[tam];
                        putchar(validar[tam]);
                        if (tam == 1)
                        {
                            putchar('/');
                            tam++;
                            data[tam] = '/';
                        }
                        else if (tam == 4)
                        {
                            putchar('/');
                            tam++;
                            data[tam] = '/';
                        }
                        tam++;

                    }
                    break;
                case 3: ///**< Formatar Telefone ex: (011) 98855-5588 */
                    if (validar[tam] > 47 && validar[tam] < 58)
                    {
                        putchar(validar[tam]);
                        paciente.contato.telefone[tam] = validar[tam];
                        tam++;
                    }
                    break;
                case 4: /**< Validar email aceitando letras e números */
                    if ((validar[tam] > 47 && validar[tam] < 58) || (validar[tam] > 64 && validar[tam] < 91) || (validar[tam] > 96 && validar[tam] < 123) ||  validar[tam] == 32 ||  validar[tam] == 64 ||  validar[tam] == 46)
                    {
                        putchar(validar[tam]);
                        paciente.contato.email[tam] = tolower(validar[tam]);
                        tam++;
                    }
                    break;
                case 5: ///**< Formatar CEP ex: 04336-160 */
                    if (validar[tam] > 47 && validar[tam] < 58)
                    {
                        putchar(validar[tam]);
                        paciente.endereco.cep[tam] = validar[tam];
                        tam++;
                    }
                    break;
                case 6: /**< Validar endereço não aceitando caracteres especiais ou números */
                    if ((validar[tam] > 64 && validar[tam] < 91) || (validar[tam] > 96 && validar[tam] < 123) ||  validar[tam] == 32)
                    {
                        putchar(validar[tam]);
                        paciente.endereco.logradouro[tam] = toupper(validar[tam]);
                        tam++;
                    }
                    break;
                case 7: /**< Validar número aceitando números e letras menos aceitando caracteres especiais */
                    if ((validar[tam] > 47 && validar[tam] < 58) || (validar[tam] > 64 && validar[tam] < 91) || (validar[tam] > 96 && validar[tam] < 123) ||  validar[tam] == 32)
                    {
                        putchar(validar[tam]);
                        paciente.endereco.numero[tam] = toupper(validar[tam]);
                        tam++;
                    }
                    break;
                case 8: /**< Validar bairro não aceitando caracteres especiais ou números */
                    if ((validar[tam] > 64 && validar[tam] < 91) || (validar[tam] > 96 && validar[tam] < 123) ||  validar[tam] == 32)
                    {
                        putchar(validar[tam]);
                        paciente.endereco.bairro[tam] = toupper(validar[tam]);
                        tam++;
                    }
                    break;
                case 9: /**< Validar cidade não aceitando caracteres especiais ou números */
                    if ((validar[tam] > 64 && validar[tam] < 91) || (validar[tam] > 96 && validar[tam] < 123) ||  validar[tam] == 32)
                    {
                        putchar(validar[tam]);
                        paciente.endereco.cidade[tam] = toupper(validar[tam]);
                        tam++;
                    }
                    break;
                case 10: /**< Validar estado não aceitando caracteres especiais ou números */
                    if ((validar[tam] > 64 && validar[tam] < 91) || (validar[tam] > 96 && validar[tam] < 123) ||  validar[tam] == 32)
                    {
                        putchar(validar[tam]);
                        paciente.endereco.estado[tam] = toupper(validar[tam]) ;
                        tam++;
                    }
                    break;
                case 11: ///**< Formatar data nascimento 00/00/0000*/
                    if ((validar[tam] > 47 && validar[tam] < 58))
                    {
                        data[tam] = validar[tam];
                        putchar(validar[tam]);
                        if (tam == 1)
                        {
                            putchar('/');
                            tam++;
                            data[tam] = '/';
                        }
                        else if (tam == 4)
                        {
                            putchar('/');
                            tam++;
                            data[tam] = '/';
                        }
                        tam++;
                    }
                    break;
                case 12: /**< Validar comorbidade diabetes aceitando apenas S/N */
                    if (validar[tam] == 78 || validar[tam] == 83 || validar[tam] == 110 || validar[tam]== 115)
                    {
                        putchar(validar[tam]);
                        paciente.comorbidade.diabetes = toupper(validar[tam]);
                        tam++;
                    }
                    break;
                case 13: /**< Validar comorbidade obesidade aceitando apenas S/N */
                    if (validar[tam] == 78 || validar[tam] == 83 || validar[tam] == 110 || validar[tam]== 115)
                    {
                        putchar(validar[tam]);
                        paciente.comorbidade.obesidade = toupper(validar[tam]);
                        tam++;
                    }
                    break;
                case 14: /**< Validar comorbidade hipertenção aceitando apenas S/N */
                    if (validar[tam] == 78 || validar[tam] == 83 || validar[tam] == 110 || validar[tam]== 115)
                    {
                        putchar(validar[tam]);
                        paciente.comorbidade.hipertencao = toupper(validar[tam]);
                        tam++;
                    }
                    break;
                case 15: /**< Validar comorbidade tuberculose aceitando apenas S/N */
                    if (validar[tam] == 78 || validar[tam] == 83 || validar[tam] == 110 || validar[tam]== 115)
                    {
                        putchar(validar[tam]);
                        paciente.comorbidade.tuberculose = toupper(validar[tam]);
                        tam++;
                    }
                    break;
                case 16: /**< Validar comorbidade outros não aceita caracteres especiais e números */
                    if ((validar[tam] > 64 && validar[tam] < 91) || (validar[tam] > 96 && validar[tam] < 123) ||  validar[tam] == 32)
                    {
                        putchar(validar[tam]);
                        paciente.comorbidade.outros[tam] = toupper(validar[tam]);
                        tam++;
                    }
                    break;
                }
            }
        }
    }
    while (validar[tam] != 13);
    if (parametro == 2)
    {
        paciente.dataNascimento.dia = atoi(strtok(data, "/"));
        paciente.dataNascimento.mes = atoi(strtok(NULL, "/"));
        paciente.dataNascimento.ano = atoi(strtok(NULL, "/"));

    }
    else if (parametro == 11)
    {
        paciente.diagnostico.dia = atoi(strtok(data, "/"));
        paciente.diagnostico.mes = atoi(strtok(NULL, "/"));
        paciente.diagnostico.ano = atoi(strtok(NULL, "/"));

    }

}
int calcularIdade(struct tb_pessoa p)
{
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    int diaAtual, mesAtual, anoAtual;

    diaAtual = tm.tm_mday;
    mesAtual = tm.tm_mon+1;
    anoAtual = tm.tm_year+1900;
    int idade=0;
    if (p.dataNascimento.ano < anoAtual)
    {
        idade = anoAtual - p.dataNascimento.ano;

        if (p.dataNascimento.mes >= mesAtual && p.dataNascimento.dia < diaAtual)
            idade--;
        if (idade == 0)
            idade = mesAtual;
        return idade;
    }
    else if (p.dataNascimento.ano == anoAtual)
    {
        if (p.dataNascimento.mes < mesAtual)
            idade = mesAtual - p.dataNascimento.mes;
        else if (p.dataNascimento.mes == mesAtual && p.dataNascimento.dia < diaAtual)
            idade = diaAtual - p.dataNascimento.dia;
        return idade;
    }
    return 0;
}
/// Sobre o sistema
void sobre()
{
    system("cls");

    printf("\n\n\t%s\n", "CHC - Conecte hospitalar COVID-19\n");
    printf("\tSistema desenvolvido para controle e monitoramento de pacientes\n\tinfectados com CORONAVIRUS 'COVID 19'\n");


    printf("\n\n\tDesenvolverdore(s): Silvio Gomes, Gabriel, Evandro, Ewelyn e Gustavo\n");
    printf("\n\tSuporte.\n");
    printf("\t  Contato: (11) 986856197\n");
    printf("\t  E-mail: sgomes.dev@gmail.com\n");

    printf("\n\n\tPlataforma OS......: Windows 7/8/10\n");
    printf("\tVersao Compilacao..: 64 bits\n");
    printf("\tVersao Sistema.....: 2.0.19\n");
    printf("\tBuilder............: 38.13.552\n");

    printf("\n\n\tCopyright%c 2021 Todos os direitos reservados.\n", 169);
    printf("\n\t");
    system("pause");
}



