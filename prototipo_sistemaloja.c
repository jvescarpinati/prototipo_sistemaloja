#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define alocar 5 // Constante para controle de memória (5 posições a mais)

typedef struct
{
    char cpf_funcionario[12];
    char nome_funcionario[60];
    float salario_funcionario;
    char cargo_funcionario[30];
} Funcionarios;

typedef struct
{
    char cpf_cliente[12];
    char nome_cliente[60];
    long long int telefone_cliente;
    char genero_cliente[2]; // M (masculino) ou F(feminino)
} Cliente;

typedef struct
{
    float valor_venda;
    int codigo_venda;
    char cpf_funcionario[12]; // só se cadastra a venda se houver um funcionario associado
    char cpf_cliente[12];     // só se cadastra a venda se houver um cliente associado
    int dia;
    int mes;
    int ano;
    char hora[9];
    int produto;
} Venda;

int menu_geral();
int cancelar_operacao();
int busca_cpf_geral(Funcionarios *v_funcionario, int num_funcionario, Cliente *v_cliente, int num_cliente, char *cpf_procurado);

// Binarios
void carregar_dados(Funcionarios **f, int *tf, int *cf, Cliente **c, int *tc, int *cc, Venda **v, int *tv, int *cv);
void salvar_dados(Funcionarios *f, int tf, Cliente *c, int tc, Venda *v, int tv);

/*Comeco funcionario===================================================================================================*/
int menu_funcionarios();
int verificar_nome_fun(Funcionarios *funci);
int verificar_cpf_fun(Funcionarios *funci);
int verificar_cargo_fun(Funcionarios *func);
int cadastro_funcio(Funcionarios *v_funcionario, int i, Cliente *v_cliente, int total_cli);
void apagar_funcionario(Funcionarios **v_funcionario, int *t_funcionario, int *cap_funcionario, Venda *v_venda, int t_vendas);
Funcionarios *busca_funcionario(Funcionarios *vf, int n, char *cpf, int *flag);
void leitura_funcionario(Funcionarios *v_funcionario, int t_funcionarios);
void atualizar_infos_funcionarios(Funcionarios *v_funcionario, int t_funcionarios, Cliente *v_cliente, int t_clientes);
void listar_todos_funcionarios(Funcionarios *v_funcionario, int num_func);

/*Começo clientes======================================================================================================*/
int menu_clientes();
int cadastro_cliente(Cliente *v_cliente, int i, Funcionarios *v_funcionario, int total_func);
int verificar_cpf_cliente(Cliente *cliente);
void leitura_cliente(Cliente *v_cliente, int t_clientes);
void apagar_cliente(Cliente **v_cliente, int *t_cliente, int *cap_cliente, Venda *v_venda, int t_vendas);
Cliente *busca_cliente(Cliente *vc, int n, char cpf_alvo[12], int *Flag);
void atualizar_infos_cliente(Cliente *v_cliente, int t_clientes, Funcionarios *v_funcionario, int t_funcionarios);
int verificar_nome_cliente(Cliente *cli);
void listar_todos_clientes(Cliente *v_clientes, int num_clientes);

// começo vendas========================================================================================================
int menu_vendas();
int cadastro_venda(Venda *v_venda, int i, Funcionarios *v_funcionario, int total_fun, Cliente *v_cliente, int total_cli);
void leitura_venda(Venda *v_venda, int t_vendas, Funcionarios *v_funcionario, int total_fun, Cliente *v_cliente, int total_cli);
void apagar_venda(Venda **v_venda, int *t_venda, int *cap_venda);
void atualizar_infos_venda(Venda *v_venda, int t_vendas, Funcionarios *v_funcionario, int t_funcionarios, Cliente *v_cliente, int t_clientes);
Venda *busca_venda(Venda *vv, int n, int codigo_alvo, int *Flag);
void listar_todas_vendas(Venda *v_venda, int num_vendas);
void consulta_vendas_funcionario(Venda *v_vendas, int total_venda, Funcionarios *v_funcionarios, int total_funcionario, Cliente *clientes, int total_clientes);
void consulta_compras_cliente(Venda *v_vendas, int total_venda, Cliente *clientes, int total_clientes, Funcionarios *v_funcionarios, int total_funcionario);

// comeco gerar arquivo pdf==============================================================================================
int menu_gerar_txt();
int gerar_arquivo_txt_produto_frequencia(Venda *v_vendas, int total_venda);
int gerar_arquivo_txt_funcionario_periodo(Venda *v_vendas, int total_venda, Funcionarios *v_funcionarios, int total_funcionario, Cliente *v_clientes, int total_clientes);
int gerar_arquivo_txt_genero(Venda *v_vendas, int total_venda, Cliente *v_clientes, int total_clientes);

int main()
{
    int opcao_geral;
    int capacidade_funcionario = alocar, total_funcionario = 0;
    int capacidade_clientes = alocar, total_clientes = 0;
    int capacidade_venda = alocar, total_venda = 0;

    Funcionarios *funcionarios = (Funcionarios *)malloc(capacidade_funcionario * sizeof(Funcionarios));
    Cliente *clientes = (Cliente *)malloc(capacidade_clientes * sizeof(Cliente));
    Venda *vendas = (Venda *)malloc(capacidade_venda * sizeof(Venda));

    // Carrega os dados dos arquivos binários logo no início
    carregar_dados(&funcionarios, &total_funcionario, &capacidade_funcionario,
                   &clientes, &total_clientes, &capacidade_clientes,
                   &vendas, &total_venda, &capacidade_venda);

    printf("====Seja Bem-Vindo====\n");
    do
    {
        opcao_geral = menu_geral();

        switch (opcao_geral)
        {
        case 1: // funcionario
        {
            int opcao_funcionario;
            do
            {
                opcao_funcionario = menu_funcionarios();
                if (opcao_funcionario == 1)
                {
                    if (total_funcionario == capacidade_funcionario)
                    {
                        capacidade_funcionario += alocar; // Adiciona +5 de capacidade automaticamente

                        Funcionarios *temp = (Funcionarios *)realloc(funcionarios, capacidade_funcionario * sizeof(Funcionarios));
                        if (temp == NULL)
                        {
                            printf("Erro de memoria\n");
                            exit(0);
                        }
                        funcionarios = temp;
                    }

                    if (total_funcionario < capacidade_funcionario)
                    {
                        if (cadastro_funcio(funcionarios, total_funcionario, clientes, total_clientes) == 1)
                        {
                            total_funcionario++;
                            printf("\nCadastro Realizado com sucesso!\n");
                        }
                    }
                }
                else if (opcao_funcionario == 2)
                {
                    leitura_funcionario(funcionarios, total_funcionario);
                }
                else if (opcao_funcionario == 3)
                {
                    atualizar_infos_funcionarios(funcionarios, total_funcionario, clientes, total_clientes);
                }
                else if (opcao_funcionario == 4)
                {
                    apagar_funcionario(&funcionarios, &total_funcionario, &capacidade_funcionario, vendas, total_venda);
                }
            } while (opcao_funcionario != 5 && opcao_funcionario != 0);

            break;
        }
        case 2: // cliente
        {
            int opcao_cliente;
            do
            {
                opcao_cliente = menu_clientes();
                if (opcao_cliente == 1)
                {
                    if (total_clientes == capacidade_clientes)
                    {
                        capacidade_clientes += alocar;

                        Cliente *temp = (Cliente *)realloc(clientes, capacidade_clientes * sizeof(Cliente));
                        if (temp == NULL)
                        {
                            printf("Erro de memoria\n");
                            exit(0);
                        }
                        clientes = temp;
                    }

                    if (total_clientes < capacidade_clientes)
                    {
                        if (cadastro_cliente(clientes, total_clientes, funcionarios, total_funcionario) == 1)
                        {
                            total_clientes++;
                            printf("\nCadastro de cliente realizado com sucesso!\n");
                        }
                    }
                }
                else if (opcao_cliente == 2)
                {
                    leitura_cliente(clientes, total_clientes);
                }
                else if (opcao_cliente == 3)
                {
                    atualizar_infos_cliente(clientes, total_clientes, funcionarios, total_funcionario);
                }
                else if (opcao_cliente == 4)
                {
                    apagar_cliente(&clientes, &total_clientes, &capacidade_clientes, vendas, total_venda);
                }

            } while (opcao_cliente != 5);

            break;
        }
        case 3: // venda
        {
            int opcao_vendas;
            do
            {
                opcao_vendas = menu_vendas();

                if (opcao_vendas == 1)
                {
                    if (total_venda == capacidade_venda)
                    {
                        capacidade_venda += alocar;

                        Venda *temp = (Venda *)realloc(vendas, capacidade_venda * sizeof(Venda));
                        if (temp == NULL)
                        {
                            printf("Erro de memoria\n");
                            exit(0);
                        }
                        vendas = temp;
                    }

                    if (total_venda < capacidade_venda)
                    {
                        if (cadastro_venda(vendas, total_venda, funcionarios, total_funcionario, clientes, total_clientes) == 1)
                        {
                            total_venda++;
                            printf("\nCadastro de venda realizado com sucesso!\n");
                        }
                    }
                }
                else if (opcao_vendas == 2)
                {
                    leitura_venda(vendas, total_venda, funcionarios, total_funcionario, clientes, total_clientes);
                }
                else if (opcao_vendas == 3)
                {
                    atualizar_infos_venda(vendas, total_venda, funcionarios, total_funcionario, clientes, total_clientes);
                }
                else if (opcao_vendas == 4)
                {
                    apagar_venda(&vendas, &total_venda, &capacidade_venda);
                }
                else if (opcao_vendas == 5)
                {
                    consulta_vendas_funcionario(vendas, total_venda, funcionarios, total_funcionario, clientes, total_clientes);
                }
                else if (opcao_vendas == 6)
                {
                    consulta_compras_cliente(vendas, total_venda, clientes, total_clientes, funcionarios, total_funcionario);
                }

            } while (opcao_vendas != 7);
            break;
        }
        case 4: // listar dados de todos os funcionarios
        {
            listar_todos_funcionarios(funcionarios, total_funcionario);
            break;
        }

        case 5: // listar dados de todos os clintes
        {
            listar_todos_clientes(clientes, total_clientes);
            break;
        }
        case 6: // listar dados de todas as vendas
        {
            listar_todas_vendas(vendas, total_venda);
            break;
        }
        case 7: // gerar relatorios txt
        {
            int opcao_gerar_arquivo_txt;
            do
            {

                opcao_gerar_arquivo_txt = menu_gerar_txt();
                if (opcao_gerar_arquivo_txt < 1 || opcao_gerar_arquivo_txt > 4)
                    printf("\nOpcao digitada invalida\n");

                if (opcao_gerar_arquivo_txt == 1)
                {
                    if (gerar_arquivo_txt_produto_frequencia(vendas, total_venda) == 1)
                    {
                        printf("\nArquivo gerado com sucesso!\n");
                    }
                }
                else if (opcao_gerar_arquivo_txt == 2)
                {
                    if (gerar_arquivo_txt_funcionario_periodo(vendas, total_venda, funcionarios, total_funcionario, clientes, total_clientes) == 1)
                    {
                        printf("\nArquivo gerado com sucesso!\n");
                    }
                }
                else if (opcao_gerar_arquivo_txt == 3)
                {
                    if (gerar_arquivo_txt_genero(vendas, total_venda, clientes, total_clientes) == 1)
                    {
                        printf("\nArquivo gerado com sucesso.\n");
                    }
                }
                else if (opcao_gerar_arquivo_txt == 4)
                {
                    printf("\n\nVoltando ao menu principal!\n\n");
                    break;
                }
            } while (opcao_gerar_arquivo_txt != 4);
            break;
        }
        }
    } while (opcao_geral != 8);

    // Salva os dados nos arquivos binários antes de encerrar
    salvar_dados(funcionarios, total_funcionario, clientes, total_clientes, vendas, total_venda);

    printf("\n\nSaindo do Programa...\n\n");

    free(funcionarios);
    free(clientes);
    free(vendas);

    return 0;
}

// Binario==========================================

void carregar_dados(Funcionarios **f, int *tf, int *cf, Cliente **c, int *tc, int *cc, Venda **v, int *tv, int *cv)
{
    FILE *arq_f = fopen("../funcionarios.bin", "rb");
    if (arq_f == NULL)
    {
        printf("\nErro na leitura arquivo binario funcionarios\n");
        exit(1);
    }

    if (arq_f)
    {
        Funcionarios temp;
        while (fread(&temp, sizeof(Funcionarios), 1, arq_f) == 1)
        {
            if (*tf == *cf)
            {
                *cf += alocar;
                *f = (Funcionarios *)realloc(*f, (*cf) * sizeof(Funcionarios));
            }
            (*f)[*tf] = temp;
            (*tf)++;
        }
        fclose(arq_f);
    }

    FILE *arq_c = fopen("../clientes.bin", "rb");
    if (arq_c == NULL)
    {
        printf("\nErro na leitura arquivo binario clientes\n");
        exit(1);
    }
    if (arq_c)
    {
        Cliente temp;
        while (fread(&temp, sizeof(Cliente), 1, arq_c) == 1)
        {
            if (*tc == *cc)
            {
                *cc += alocar;
                *c = (Cliente *)realloc(*c, (*cc) * sizeof(Cliente));
            }
            (*c)[*tc] = temp;
            (*tc)++;
        }
        fclose(arq_c);
    }

    FILE *arq_v = fopen("../vendas.bin", "rb");
    if (arq_v == NULL)
    {
        printf("\nErro na leitura arquivo binario vendas\n");
        exit(1);
    }
    if (arq_v)
    {
        Venda temp;
        while (fread(&temp, sizeof(Venda), 1, arq_v) == 1)
        {
            if (*tv == *cv)
            {
                *cv += alocar;
                *v = (Venda *)realloc(*v, (*cv) * sizeof(Venda));
            }
            (*v)[*tv] = temp;
            (*tv)++;
        }
        fclose(arq_v);
    }
}

void salvar_dados(Funcionarios *f, int tf, Cliente *c, int tc, Venda *v, int tv)
{
    FILE *arq_f = fopen("../funcionarios.bin", "wb");
    if (arq_f)
    {
        fwrite(f, sizeof(Funcionarios), tf, arq_f);
        fclose(arq_f);
    }

    FILE *arq_c = fopen("../clientes.bin", "wb");
    if (arq_c)
    {
        fwrite(c, sizeof(Cliente), tc, arq_c);
        fclose(arq_c);
    }

    FILE *arq_v = fopen("../vendas.bin", "wb");
    if (arq_v)
    {
        fwrite(v, sizeof(Venda), tv, arq_v);
        fclose(arq_v);
    }
}

// Funções Gerais ======================================================================================================

int menu_geral()
{
    int opcao;
    printf("\n====Escolha qual area voce quer acessar====\n");
    printf("1-Area Funcionarios\n");
    printf("2-Area Clientes\n");
    printf("3-Area Vendas\n");
    printf("4-Listar Dados de Todos os Funcionarios\n");
    printf("5-Listar Dados de Todos os Clientes\n");
    printf("6-Listar Dados de vendas\n");
    printf("7-Criar Relatorio TXT\n");
    printf("8-Sair do App\n");
    printf("Qual a opcao escolhida? ");
    scanf("%d", &opcao);
    return opcao;
}

int cancelar_operacao()
{
    int opcao_cancelar;
    do
    {
        printf("\nVoce deseja cancelar essa operacao?\n");
        printf("1-Nao, prosseguir\n");
        printf("2-Sim, retornar\n");

        printf("Qual a opcao escolhida: ");
        scanf("%d", &opcao_cancelar);
        if (opcao_cancelar > 2 || opcao_cancelar < 1)
        {
            printf("\nEscolha uma opcao valida...\n");
        }
    } while (opcao_cancelar > 2 || opcao_cancelar < 1);

    return opcao_cancelar;
}

int busca_cpf_geral(Funcionarios *v_funcionario, int num_funcionario, Cliente *v_cliente, int num_cliente, char *cpf_procurado)
{
    for (int pf = 0; pf < num_funcionario; pf++)
    {
        if (strcmp(v_funcionario[pf].cpf_funcionario, cpf_procurado) == 0)
            return 1;
    }
    for (int pc = 0; pc < num_cliente; pc++)
    {
        if (strcmp(v_cliente[pc].cpf_cliente, cpf_procurado) == 0)
            return 2;
    }
    return 0;
}

// Comeco funcionario===================================================================================================

int menu_funcionarios()
{
    printf("\nEscolha uma opcao de alteracao para os funcionarios: \n");
    printf("1-Cadastro Novo Funcionario\n");
    printf("2-Visualizar Informacoes de cadastro de funcionario\n");
    printf("3-Atualizar Cadastro do Funcionario\n");
    printf("4-Apagar Cadastro do Funcionario\n");
    printf("5-Voltar para menu\n");
    int opcao;
    printf("Escolha uma opcao: ");
    scanf(" %d", &opcao);
    return opcao;
}

int verificar_nome_fun(Funcionarios *funci)
{
    int i = 0, flag = 0;
    while (funci->nome_funcionario[i] != '\0')
    {
        if (funci->nome_funcionario[i] >= '1' && funci->nome_funcionario[i] <= '9')
        {
            flag = 1;
            break;
        }
        i++;
    }
    return flag;
}

int verificar_cpf_fun(Funcionarios *funci)
{
    int i = 0;
    if (funci->cpf_funcionario[0] == '\0')
        return 1;

    while (funci->cpf_funcionario[i] != '\0')
    {
        if (!isdigit(funci->cpf_funcionario[i]))
        {
            return 1;
        }
        i++;
    }
    if (i != 11)
    {
        printf("Erro: CPF deve ter exatamente 11 digitos.\n");
        return 1;
    }
    return 0;
}

int verificar_cargo_fun(Funcionarios *func)
{
    int flag = 0, i = 0;
    while (func->cargo_funcionario[i] != '\0')
    {
        if (func->cargo_funcionario[i] >= '1' && func->cargo_funcionario[i] <= '9')
        {
            flag = 1;
            break;
        }
        i++;
    }
    return flag;
}

int cadastro_funcio(Funcionarios *v_funcionario, int i, Cliente *v_cliente, int total_cli)
{

    if (cancelar_operacao() == 2)
    {
        printf("\nOperacao de cadastro cancelada.\n");
        return 0;
    }

    int verifnomefun;
    do
    {
        printf("\nEscreva o nome do Funcionario: ");
        scanf(" %59[^\n]", v_funcionario[i].nome_funcionario);

        char sobra = getchar();
        if (sobra != '\n')
        {
            printf("\nErro: Nome longo demais!\n");
            while (getchar() != '\n')
                ;
            verifnomefun = 1;
        }
        else
        {
            verifnomefun = verificar_nome_fun(&v_funcionario[i]);
            if (verifnomefun == 1)
            {
                printf("Nome Digitado invalido (contem numeros), tente novamente.\n");
            }
        }
    } while (verifnomefun == 1);

    int verifcpffun = 0;
    do
    {
        printf("Escreva o cpf do funcionario (11 digitos): ");
        scanf(" %[^\n]", v_funcionario[i].cpf_funcionario);
        verifcpffun = verificar_cpf_fun(&v_funcionario[i]);

        if (verifcpffun == 0)
        {
            if (busca_cpf_geral(v_funcionario, i, v_cliente, total_cli, v_funcionario[i].cpf_funcionario) != 0)
            {
                printf("Erro: Este CPF ja esta cadastrado no sistema!\n");
                verifcpffun = 1;
            }
        }
    } while (verifcpffun == 1);

    int verifcargo = 0;
    do
    {
        printf("Escreva o cargo do funcionario: ");
        scanf(" %29[^\n]", v_funcionario[i].cargo_funcionario);

        char teste = getchar();
        if (teste != '\n')
        {
            printf("Cargo Excede Limite de caracteres\n");
            while (getchar() != '\n')
                ;
            verifcargo = 1;
        }
        else
        {
            verifcargo = verificar_cargo_fun(&v_funcionario[i]);
            if (verifcargo == 1)
            {
                printf("Cargo Invalido (Possui Numeros), tente novamente\n");
            }
        }
    } while (verifcargo == 1);

    int verifsalario = 0;
    do
    {
        printf("Escreva o valor do salario do funcionario: ");
        if (scanf(" %f", &v_funcionario[i].salario_funcionario) == 1)
        {
            int sobra = getchar();
            if (sobra != '\n' && sobra != ' ')
            {
                printf("Erro: Entrada invalida. Nao use letras ou virgulas.\n");
                while (getchar() != '\n')
                    ;
                verifsalario = 1;
            }
            else
            {
                verifsalario = 0;
            }
        }
        else
        {
            printf("Erro: Voce nao digitou um numero valido.\n");
            while (getchar() != '\n')
                ;
            verifsalario = 1;
        }
    } while (verifsalario == 1);

    return 1;
}

void apagar_funcionario(Funcionarios **v_funcionario, int *t_funcionario, int *cap_funcionario, Venda *v_venda, int t_vendas)
{
    if (*t_funcionario == 0)
    {
        printf("\nNenhum funcionario cadastrado para apagar.\n");
        return;
    }
    if (cancelar_operacao() == 2)
    {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    char cpf[12];
    int flag_busca;
    printf("\nDigite o cpf do funcionario que deseja remover: ");
    scanf("%s", cpf);

    // RESTRIÇÃO: Verificar se o funcionário está em alguma venda
    for (int i = 0; i < t_vendas; i++)
    {
        if (strcmp(v_venda[i].cpf_funcionario, cpf) == 0)
        {
            printf("\nErro: Funcionario nao pode ser removido pois esta associado a uma ou mais vendas.\n");
            return;
        }
    }

    Funcionarios *alvo = busca_funcionario(*v_funcionario, *t_funcionario, cpf, &flag_busca);

    if (alvo != NULL)
    {
        int indice_alvo = alvo - (*v_funcionario);
        for (int j = indice_alvo; j < (*t_funcionario - 1); j++)
        {
            (*v_funcionario)[j] = (*v_funcionario)[j + 1];
        }

        (*t_funcionario)--;

        if (*cap_funcionario - *t_funcionario > alocar)
        {
            *cap_funcionario -= alocar;
            Funcionarios *temp = (Funcionarios *)realloc(*v_funcionario, (*cap_funcionario) * sizeof(Funcionarios));
            if (temp == NULL && *cap_funcionario > 0)
            {
                printf("Erro de memoria\n");
                exit(0);
            }
            *v_funcionario = temp;
        }
        printf("\nSucesso: Funcionario removido.\n");
    }
    else
        printf("\nErro: Funcionario nao encontrado\n");
}

Funcionarios *busca_funcionario(Funcionarios *vf, int n, char *cpf, int *flag)
{
    *flag = 1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(vf[i].cpf_funcionario, cpf) == 0)
        {
            *flag = 0;
            return &vf[i];
        }
    }
    return NULL;
}

void leitura_funcionario(Funcionarios *v_funcionario, int t_funcionarios)
{
    if (t_funcionarios == 0)
    {
        printf("\nNenhum funcionario cadastrado para visualizar.\n");
        return;
    }
    if (cancelar_operacao() == 2)
    {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    char cpf_achar[12];
    int flag = 0;
    int *Flag = &flag;
    Funcionarios *funcionario_achado;
    do
    {
        printf("\nDigite o CPF (somente numeros sem barras ou tracos) do funcionario que deseja ler: ");
        scanf(" %s", cpf_achar);
        while(getchar()!='\n');
        funcionario_achado = busca_funcionario(v_funcionario, t_funcionarios, cpf_achar, Flag);

        if (flag == 1){
            printf("\nFuncionario nao encontrado!\n");
            printf("Deseja cancelar a busca? (1-sim/2-nao)\n");
            int opcao_cancelamento;
            scanf("%d", &opcao_cancelamento);
            while(getchar()!='\n');
            if(opcao_cancelamento <1 || opcao_cancelamento>2) printf("Digite um valor valido\n");
            if(opcao_cancelamento==1) return;
        }


    } while (flag == 1);

    if (flag == 0)
    {
        printf("\nNome : %s\n", funcionario_achado->nome_funcionario);
        printf("Cpf : %s\n", funcionario_achado->cpf_funcionario);
        printf("Cargo : %s\n", funcionario_achado->cargo_funcionario);
        printf("Salario : %.2f\n\n", funcionario_achado->salario_funcionario);
    }
}

void atualizar_infos_funcionarios(Funcionarios *v_funcionario, int t_funcionarios, Cliente *v_cliente, int t_clientes)
{
    if (t_funcionarios == 0)
    {
        printf("\nNenhum funcionario cadastrado para atualizar.\n");
        return;
    }
    if (cancelar_operacao() == 2)
    {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    char cpf_achar[12];
    int flag = 0;
    int *Flag = &flag;
    Funcionarios *funcionario_achado;
    do
    {
        printf("Digite o cpf (somente numeros) do funcionario que deseja atualizar: ");
        scanf(" %s", cpf_achar);
        funcionario_achado = busca_funcionario(v_funcionario, t_funcionarios, cpf_achar, Flag);
    } while (flag == 1);

    if (flag == 0)
    {
        int verifcpffun = 0;
        char novo_cpf[12];
        do
        {
            printf("Digite o novo cpf do funcionario (11 digitos): ");
            scanf(" %s", novo_cpf);
            while (getchar() != '\n')
                ;
            if (strcmp(novo_cpf, funcionario_achado->cpf_funcionario) != 0 && busca_cpf_geral(v_funcionario, t_funcionarios, v_cliente, t_clientes, novo_cpf) != 0)
            {
                printf("Erro: Este CPF ja esta cadastrado no sistema!\n");
                verifcpffun = 1;
            }
            else
            {
                strcpy(funcionario_achado->cpf_funcionario, novo_cpf);
                verifcpffun = verificar_cpf_fun(funcionario_achado);
            }
        } while (verifcpffun == 1);

        int verifnomefun;
        do
        {
            printf("\nDigite o nome atualizado do Funcionario: ");
            scanf(" %59[^\n]", funcionario_achado->nome_funcionario);
            char sobra = getchar();
            if (sobra != '\n')
            {
                printf("\nErro: Nome longo demais! Use no maximo 59 caracteres.\n");
                while (getchar() != '\n')
                    ;
                verifnomefun = 1;
            }
            else
            {
                verifnomefun = verificar_nome_fun(funcionario_achado);
                if (verifnomefun == 1)
                {
                    printf("\nNome Digitado invalido (contem numeros), tente novamente.\n");
                }
            }
        } while (verifnomefun == 1);

        int verifcargo = 0;
        do
        {
            printf("Digite o cargo atualizado do funcionario: ");
            scanf(" %29[^\n]", funcionario_achado->cargo_funcionario);
            char teste = getchar();
            if (teste != '\n')
            {
                printf("\nCargo Excede Limite de caracteres\n");
                while (getchar() != '\n')
                    ;
                verifcargo = 1;
            }
            else
            {
                verifcargo = verificar_cargo_fun(funcionario_achado);
                if (verifcargo == 1)
                {
                    printf("Cargo Invalido (Possui Numeros),tente novamente\n");
                }
            }
        } while (verifcargo == 1);

        int verifsalario = 0;
        do
        {
            printf("Digite o valor atualizado do salario do funcionario:");
            if (scanf(" %f", &funcionario_achado->salario_funcionario) == 1)
            {
                int sobra = getchar();
                if (sobra != '\n' && sobra != ' ')
                {
                    printf("Erro: Entrada invalida. Nao use letras ou virgulas.\n");
                    while (getchar() != '\n')
                        ;
                    verifsalario = 1;
                }
                else
                {
                    verifsalario = 0;
                }
            }
            else
            {
                printf("Erro: Voce nao digitou um numero valido.\n");
                while (getchar() != '\n')
                    ;
                verifsalario = 1;
            }
            printf("\n");
        } while (verifsalario == 1);
    }
}

void listar_todos_funcionarios(Funcionarios *v_funcionario, int num_func)
{
    if (num_func == 0)
    {
        printf("\nNenhum Funcionario cadastrado. Cadastre um ou mais funcionarios para listar os dados existentes.\n");
        printf("==================================\n");
        return;
    }

    else
    {
        printf("=================================DADOS DE TODOS OS FUNCIONARIOS=================================\n");
        for (int i = 0; i < num_func; i++)
        {
            printf("\nNome: %s\n", v_funcionario[i].nome_funcionario);
            printf("Cpf: %s\n", v_funcionario[i].cpf_funcionario);
            printf("Cargo: %s\n", v_funcionario[i].cargo_funcionario);
            printf("Salario: %.2f\n\n", v_funcionario[i].salario_funcionario);
            printf("=================================\n");
        }
        return;
    }
}

// Começo cliente======================================================================================================

int menu_clientes()
{
    printf("\nEscolha uma opcao:\n");
    printf("1-Cadastro Novo Cliente\n");
    printf("2-Visualziar Informacoes de Cadastro de Cliente\n");
    printf("3-Atualizar Cadastro do Cliente\n");
    printf("4-Apagar Cadastro do Cliente\n");
    printf("5-Voltar para menu\n");
    int opcao;
    printf("Escolha uma opcao: ");
    scanf(" %d", &opcao);
    return opcao;
}

int verificar_cpf_cliente(Cliente *cliente)
{
    int i = 0;
    if (cliente->cpf_cliente[0] == '\0')
        return 1;

    while (cliente->cpf_cliente[i] != '\0')
    {
        if (!isdigit(cliente->cpf_cliente[i]))
        {
            return 1;
        }
        i++;
    }
    if (i != 11)
    {
        printf("O CPF deve ter exatamente 11 digitos.\n");
        return 1;
    }
    return 0;
}

int cadastro_cliente(Cliente *v_cliente, int i, Funcionarios *v_funcionario, int total_funci)
{
    if (cancelar_operacao() == 2)
    {
        printf("Operacao de cadastro cancelada.\n");
        return 0;
    }
    int flag=0;
    do{
        flag=0;
        printf("\nEscreva o nome do Cliente: ");
        scanf(" %59[^\n]", v_cliente[i].nome_cliente);
        while (getchar() != '\n');

        for(int j=0; v_cliente[i].nome_cliente[j] != '\0'; j++){
            if(isdigit(v_cliente[i].nome_cliente[j])){
                flag = 1;
                printf("Erro: O nome nao deve conter numeros.\n");
                break;
            }
            else break;
        }
    }while(flag==1);

    int verif_cpf_cli = 0;
    do
    {
        printf("Escreva o cpf do cliente (somente 11 numeros): ");
        scanf(" %11s", v_cliente[i].cpf_cliente);
        while (getchar() != '\n')
            ;

        verif_cpf_cli = verificar_cpf_cliente(&v_cliente[i]);

        if (verif_cpf_cli == 0)
        {
            if (busca_cpf_geral(v_funcionario, total_funci, v_cliente, i, v_cliente[i].cpf_cliente) != 0)
            {
                printf("Erro: Este CPF ja esta cadastrado no sistema (Cliente ou Funcionario).\n");
                verif_cpf_cli = 1;
            }
        }
    } while (verif_cpf_cli == 1);

    printf("Escreva o telefone do cliente (somente numeros): ");
    while(scanf("%11lld", &v_cliente[i].telefone_cliente)!=1){
        printf("\nErro! Digite apenas numeros: ");
        while (getchar() != '\n');
    }
    while(getchar() != '\n');
    do
    {
        printf("Escreva o genero (M/F): ");
        scanf(" %1s", v_cliente[i].genero_cliente);
        while (getchar() != '\n')
            ;

        if (v_cliente[i].genero_cliente[0] >= 'a' && v_cliente[i].genero_cliente[0] <= 'z')
        {
            v_cliente[i].genero_cliente[0] = v_cliente[i].genero_cliente[0] - 32;
        }

        if (v_cliente[i].genero_cliente[0] != 'M' && v_cliente[i].genero_cliente[0] != 'F')
        {
            printf("Erro: Opcao invalida. Digite M ou F.\n");
        }

    } while (v_cliente[i].genero_cliente[0] != 'M' && v_cliente[i].genero_cliente[0] != 'F');

    return 1;
}

void leitura_cliente(Cliente *v_cliente, int t_clientes)
{

    if (t_clientes == 0)
    {
        printf("\nNenhum cliente cadastrado para visualizar.\n");
        return;
    }
    if (cancelar_operacao() == 2)
    {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    char cpf_alvo[12];
    int flag = 0;
    int *Flag = &flag;
    Cliente *cliente_achado;
    do
    {
        printf("Digite o cpf (somente numeros sem barras ou tracos) do cliente que deseja ler os dados: ");
        scanf(" %[^\n]", cpf_alvo);
        cliente_achado = busca_cliente(v_cliente, t_clientes, cpf_alvo, Flag);
    } while (flag == 1);

    if (flag == 0)
    {
        printf("\nNome: %s\n", cliente_achado->nome_cliente);
        printf("Cpf: %s\n", cliente_achado->cpf_cliente);
        printf("Telefone: %lld\n", cliente_achado->telefone_cliente);
        if (cliente_achado->genero_cliente[0] == 'M')
            printf("Genero: Masculino\n\n");
        else
            printf("Genero: Feminino\n\n");
    }
}

Cliente *busca_cliente(Cliente *vc, int n, char cpf_alvo[12], int *Flag)
{
    *Flag = 1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(vc[i].cpf_cliente, cpf_alvo) == 0)
        {
            *Flag = 0;
            return &vc[i];
        }
    }
    printf("Erro: Cliente nao encontrado, tente novamente\n");
    return NULL;
}

void apagar_cliente(Cliente **v_cliente, int *t_cliente, int *cap_cliente, Venda *v_venda, int t_vendas)
{

    if (*t_cliente == 0)
    {
        printf("\nNenhum cliente cadastrado para apagar.\n");
        return;
    }
    if (cancelar_operacao() == 2)
    {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    char cpf[12];
    int flag_busca;
    printf("\nDigite o cpf do cliente que deseja remover: ");
    scanf("%s", cpf);

    for (int i = 0; i < t_vendas; i++)
    {
        if (strcmp(v_venda[i].cpf_cliente, cpf) == 0)
        {
            printf("\nErro: Cliente nao pode ser removido pois esta associado a uma ou mais vendas.\n");
            return;
        }
    }

    Cliente *alvo = busca_cliente(*v_cliente, *t_cliente, cpf, &flag_busca);

    if (alvo != NULL)
    {
        int indice_alvo = alvo - (*v_cliente);
        for (int j = indice_alvo; j < (*t_cliente - 1); j++)
        {
            (*v_cliente)[j] = (*v_cliente)[j + 1];
        }

        (*t_cliente)--;

        if (*cap_cliente - *t_cliente > alocar)
        {
            *cap_cliente -= alocar;
            Cliente *temp = (Cliente *)realloc(*v_cliente, (*cap_cliente) * sizeof(Cliente));
            if (temp == NULL && *cap_cliente > 0)
            {
                printf("Erro de memoria\n");
                exit(0);
            }
            *v_cliente = temp;
        }
        printf("\nSucesso: Cliente removido.\n");
    }
    else
        printf("\nOperacao de remocao cancelada ou falhou.\n");
}

void atualizar_infos_cliente(Cliente *v_cliente, int t_clientes, Funcionarios *v_funcionario, int t_funcionarios)
{
    if (t_clientes == 0)
    {
        printf("\nNenhum cliente cadastrado para atualizar.\n");
        return;
    }
    if (cancelar_operacao() == 2)
    {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    char cpf_achar[12];
    int flag = 0;
    int *Flag = &flag;
    Cliente *cliente_achado;
    do
    {
        printf("\nDigite o cpf do cliente que deseja atualizar (somente numeros sem barras ou tracos): ");
        scanf(" %[^\n]", cpf_achar);
        cliente_achado = busca_cliente(v_cliente, t_clientes, cpf_achar, Flag);
    } while (flag == 1);

    if (flag == 0)
    {
        int verif_cpf_cli = 0;
        char novo_cpf_cli[12];
        do
        {
            printf("Digite o novo cpf do cliente (11 digitos): ");
            scanf(" %[^\n]", novo_cpf_cli);
            while (getchar() != '\n')
                ;

            if (strcmp(novo_cpf_cli, cliente_achado->cpf_cliente) != 0 &&
                busca_cpf_geral(v_funcionario, t_funcionarios, v_cliente, t_clientes, novo_cpf_cli))
            {
                printf("Erro: Este CPF ja esta cadastrado no sistema!\n");
                verif_cpf_cli = 1;
            }
            else
            {
                strcpy(cliente_achado->cpf_cliente, novo_cpf_cli);
                verif_cpf_cli = verificar_cpf_cliente(cliente_achado);
            }
        } while (verif_cpf_cli == 1);

        int verifnomecliente;
        do
        {
            printf("Digite o nome atualizado do cliente: ");
            scanf(" %59[^\n]", cliente_achado->nome_cliente);
            char sobra = getchar();
            if (sobra != '\n')
            {
                printf("Erro: Nome longo demais! Use no maximo 59 caracteres.\n");
                while (getchar() != '\n')
                    ;
                verifnomecliente = 1;
            }
            else
            {
                verifnomecliente = verificar_nome_cliente(cliente_achado);
                if (verifnomecliente == 1)
                {
                    printf("Nome Digitado invalido (contem numeros), tente novamente.\n");
                }
            }
        } while (verifnomecliente == 1);

        do
        {
            printf("Escreva o genero (M/F): ");
            scanf(" %1s", cliente_achado->genero_cliente);
            while (getchar() != '\n')
                ;

            if (cliente_achado->genero_cliente[0] >= 'a' && cliente_achado->genero_cliente[0] <= 'z')
            {
                cliente_achado->genero_cliente[0] = cliente_achado->genero_cliente[0] - 32;
            }

            if (cliente_achado->genero_cliente[0] != 'M' && cliente_achado->genero_cliente[0] != 'F')
            {
                printf("\nErro: Opcao invalida. Digite M ou F.\n");
            }
        } while (cliente_achado->genero_cliente[0] != 'M' && cliente_achado->genero_cliente[0] != 'F');

        printf("Escreva o telefone do cliente (somente numeros): ");
        while(scanf("%11lld", &cliente_achado->telefone_cliente)!=1){
            printf("\nErro! Digite apenas numeros: ");
            while (getchar() != '\n');
        }
        while(getchar() != '\n');
        printf("\n");
    }
}

int verificar_nome_cliente(Cliente *cli)
{
    int i = 0, flag = 0;
    while (cli->nome_cliente[i] != '\0')
    {
        if (cli->nome_cliente[i] >= '1' && cli->nome_cliente[i] <= '9')
        {
            flag = 1;
            break;
        }
        i++;
    }
    return flag;
}

void listar_todos_clientes(Cliente *v_clientes, int num_clientes)
{
    if (num_clientes == 0)
    {
        printf("\nNenhum cliente cadastrado. Cadastre um ou mais para listar os dados existentes.\n");
        printf("==================================\n");
        return;
    }

    else
    {
        printf("=================================DADOS DE TODOS OS CLIENTES=================================\n");
        for (int i = 0; i < num_clientes; i++)
        {
            printf("\nNome: %s\n", v_clientes[i].nome_cliente);
            printf("Cpf: %s\n", v_clientes[i].cpf_cliente);
            printf("Numero de telefone: %lld\n", v_clientes[i].telefone_cliente);
            if (v_clientes[i].genero_cliente[0] == 'M')
                printf("Genero: Masculino\n\n");
            else
                printf("Genero: Feminino\n\n");
            printf("=================================\n");
        }
    }
}

// começo vendas =========================================================================================

int menu_vendas()
{
    printf("\nEscolha uma opcao:\n");
    printf("1-Cadastrar Venda\n");
    printf("2-Consultar venda pelo codigo\n");
    printf("3-Atualizar Venda\n");
    printf("4-Apagar Venda\n");
    printf("5-Consultar todas as vendas de um funcionario\n");
    printf("6-Consultar todas as compras de um cliente\n");
    printf("7-Voltar para menu\n");

    int opcao;
    printf("Escolha uma opcao: ");
    scanf(" %d", &opcao);
    return opcao;
}

Venda *busca_venda(Venda *vv, int n, int codigo_alvo, int *Flag)
{
    *Flag = 1;
    for (int i = 0; i < n; i++)
    {
        if (vv[i].codigo_venda == codigo_alvo)
        {
            *Flag = 0;
            return &vv[i];
        }
    }
    printf("\nErro: Venda nao encontrada, tente novamente\n");
    return NULL;
}

int cadastro_venda(Venda *v_venda, int i, Funcionarios *v_funcionario, int total_fun, Cliente *v_cliente, int total_cli)
{
    // Verifica cancelamento inicial
    if (cancelar_operacao() == 2)
    {
        printf("\nOperacao de cadastro cancelada.\n");
        return 0;
    }

    int codigo;
    int flag = 0;

    // --- Validação do Código da Venda ---
    do
    {
        printf("\nDigite o codigo da venda: ");
        // Verifica se a entrada é um número
        if (scanf("%d", &codigo) != 1)
        {
            printf("Erro: Digite apenas numeros para o codigo.\n");
            while (getchar() != '\n')
                ; // Limpa buffer
            flag = 1;
            continue;
        }
        while (getchar() != '\n')
            ;

        int achou = 0;
        for (int j = 0; j < i; j++)
        {
            if (v_venda[j].codigo_venda == codigo)
            {
                achou = 1;
                break;
            }
        }

        if (achou)
        {
            printf("Erro: ja existe uma venda com esse codigo. Tente outro.\n");
            flag = 1;
        }
        else
        {
            flag = 0;
        }

    } while (flag == 1);

    v_venda[i].codigo_venda = codigo; // Atribui ao índice correto

    // --- Seleção do Produto ---
    do
    {
        printf("Qual foi o produto vendido? \n");
        printf("1- Camiseta\n2- Jaqueta\n3- Shorts\n4- Calca\n5- Vestido\n6- Top\n7- Body\n8- Croped\n");

        if (scanf("%d", &v_venda[i].produto) != 1)
        {
            printf("\nEntrada invalida! Digite o numero do produto.\n");
            while (getchar() != '\n')
                ;
            v_venda[i].produto = 9; // Força a repetição do loop
            continue;
        }
        while (getchar() != '\n')
            ;

        if (v_venda[i].produto < 1 || v_venda[i].produto > 8)
        {
            printf("\nNao temos esse produto. Selecione um produto existente.\n\n");
        }
    } while (v_venda[i].produto < 1 || v_venda[i].produto > 8);

    // --- Valor da Venda ---
    printf("Digite o valor da venda: ");
    while (scanf("%f", &v_venda[i].valor_venda) != 1)
    {
        printf("Erro: Digite um valor numerico (ex: 50.00): ");
        while (getchar() != '\n')
            ;
    }
    while (getchar() != '\n')
        ;

    // --- Data ---
    printf("Digite a data (dd mm aaaa): ");
    while (scanf("%d %d %d", &v_venda[i].dia, &v_venda[i].mes, &v_venda[i].ano) != 3)
    {
        printf("Erro: Formato invalido. Digite dd mm aaaa: ");
        while (getchar() != '\n')
            ;
    }
    while (getchar() != '\n')
        ;

    // --- CPF Funcionário ---
    while (1)
    {
        printf("Digite o CPF do funcionario responsavel: ");
        scanf(" %11s", v_venda[i].cpf_funcionario);
        while (getchar() != '\n')
            ;

        int retorno = busca_cpf_geral(v_funcionario, total_fun, v_cliente, total_cli, v_venda[i].cpf_funcionario);
        if (retorno == 1)
            break;
        else
        {
            int opcao;
            printf("CPF do Funcionario nao encontrado!\nDeseja cancelar o cadastro? (1-sim/2-nao): ");
            scanf("%d", &opcao);
            while (getchar() != '\n')
                ;
            if (opcao == 1)
                return 0;
        }
    }

    // --- CPF Cliente ---
    while (1)
    {
        printf("Digite o CPF do cliente: ");
        scanf(" %11s", v_venda[i].cpf_cliente);
        while (getchar() != '\n')
            ;

        int retorno = busca_cpf_geral(v_funcionario, total_fun, v_cliente, total_cli, v_venda[i].cpf_cliente);
        if (retorno == 2)
            break;
        else
        {
            int opcao;
            printf("CPF do Cliente nao encontrado!\nDeseja cancelar o cadastro? (1-sim/2-nao): ");
            scanf("%d", &opcao);
            while (getchar() != '\n')
                ;
            if (opcao == 1)
                return 0;
        }
    }

    printf("Digite a hora (hh:mm:ss): ");
    scanf(" %8s", v_venda[i].hora);
    while (getchar() != '\n')
        ;

    return 1;
}

void leitura_venda(Venda *v_venda, int t_vendas, Funcionarios *v_funcionario, int total_fun, Cliente *v_cliente, int total_clientes)
{
    if (t_vendas == 0)
    {
        printf("\nNenhuma venda cadastrada para visualizar.\n");
        return;
    }
    if (cancelar_operacao() == 2)
    {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    int codigo_alvo;
    int flag = 0;
    int *Flag = &flag;
    Venda *venda_achada;

    do
    {
        printf("\nDigite o codigo da venda que deseja ler: ");
        scanf("%d", &codigo_alvo);
        while (getchar() != '\n');
        venda_achada = busca_venda(v_venda, t_vendas, codigo_alvo, Flag);
    } while (flag == 1);

    if (flag == 0)
    {
        char nome_cliente[60];
        char genero_cli[2];
            for (int i = 0; i < t_vendas; i++) {
                for(int j=0; j<total_clientes; j++){
                    if (strcmp(v_venda[i].cpf_cliente, v_cliente[j].cpf_cliente) == 0) {
                        strcpy(nome_cliente, v_cliente[j].nome_cliente);
                        strcpy(genero_cli, v_cliente[j].genero_cliente);
                        break;
                    }
                }
            }

            char nome_vendedor[60];
            for (int i = 0; i < t_vendas; i++) {
                for(int j=0; j<total_fun; j++){
                    if (strcmp(v_venda[i].cpf_funcionario, v_funcionario[j].cpf_funcionario) == 0) {
                        strcpy(nome_vendedor, v_funcionario[j].nome_funcionario);
                        break;
                    }
                }
            }
        printf("\nCodigo: %d\n", venda_achada->codigo_venda);
        printf("Valor: %.2f\n", venda_achada->valor_venda);
        printf("CPF do funcionario responsavel: %s\n", venda_achada->cpf_funcionario);
        printf("Nome do funcionario responsavel: %s\n", nome_vendedor);
        printf("CPF do cliente: %s\n", venda_achada->cpf_cliente);
        printf("Nome do cliente: %s\n", nome_cliente);
        if(genero_cli[0]=='f' || genero_cli[0]=='F') printf("Genero do cliente: Feminino\n");
        if(genero_cli[0]=='m' || genero_cli[0]=='M') printf("Genero do cliente: Masculino\n");
        printf("Data: %d/%d/%d\n", venda_achada->dia, venda_achada->mes, venda_achada->ano);
        printf("Hora: %s\n", venda_achada->hora);
        if (venda_achada->produto == 1)
            printf("Produto vendido: camiseta.\n");
        else if (venda_achada->produto == 2)
            printf("Produto vendido: jaqueta.\n");
        else if (venda_achada->produto == 3)
            printf("Produto vendido: shorts.\n");
        else if (venda_achada->produto == 4)
            printf("Produto vendido: calca.\n");
        else if (venda_achada->produto == 5)
            printf("Produto vendido: vestido.\n");
        else if (venda_achada->produto == 6)
            printf("Produto vendido: top.\n");
        else if (venda_achada->produto == 7)
            printf("Produto vendido: body.\n");
        else if (venda_achada->produto == 8)
            printf("Produto vendido: croped.\n");
        printf("\n=================================\n");
    }
}

void apagar_venda(Venda **v_venda, int *t_venda, int *cap_venda)
{

    if (*t_venda == 0)
    {
        printf("\nNenhuma venda cadastrada para apagar.\n");
        return;
    }
    if (cancelar_operacao() == 2)
    {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    int codigo;
    int flag_busca;
    printf("\nDigite o codigo da venda que deseja remover: ");
    scanf("%d", &codigo);
    while (getchar() != '\n')
        ;

    Venda *alvo = busca_venda(*v_venda, *t_venda, codigo, &flag_busca);

    if (alvo != NULL)
    {
        int indice_alvo = alvo - (*v_venda);
        for (int j = indice_alvo; j < (*t_venda - 1); j++)
        {
            (*v_venda)[j] = (*v_venda)[j + 1];
        }

        (*t_venda)--;

        if (*cap_venda - *t_venda > alocar)
        {
            *cap_venda -= alocar;
            Venda *temp = (Venda *)realloc(*v_venda, (*cap_venda) * sizeof(Venda));
            if (temp == NULL && *cap_venda > 0)
            {
                printf("Erro de memoria\n");
                exit(0);
            }
            *v_venda = temp;
        }
        printf("\nSucesso: Venda removida.\n");
    }
    else
    {
        printf("\nOperacao de remocao cancelada.\n");
    }
}

void atualizar_infos_venda(Venda *v_venda, int t_vendas, Funcionarios *v_funcionario, int t_funcionarios, Cliente *v_cliente, int t_clientes)
{
    if (t_vendas == 0)
    {
        printf("\nNenhuma venda cadastrada para atualizar.\n");
        return;
    }
    if (cancelar_operacao() == 2)
    {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    int codigo_alvo;
    int flag = 0;
    int *Flag = &flag;
    Venda *venda_achada;

    do
    {
        printf("\nDigite o codigo da venda que deseja atualizar: ");
        scanf("%d", &codigo_alvo);
        while (getchar() != '\n')
            ;

        venda_achada = busca_venda(v_venda, t_vendas, codigo_alvo, Flag);

    } while (flag == 1);

    if (flag == 0)
    {
        printf("\nDigite o novo valor da venda: ");
        scanf("%f", &venda_achada->valor_venda);
        while (getchar() != '\n')
            ;

        printf("Digite a nova data (dd mm aaaa): ");
        scanf("%d %d %d", &venda_achada->dia, &venda_achada->mes, &venda_achada->ano);
        while (getchar() != '\n')
            ;

        while (1)
        {
            printf("Digite o novo CPF do funcionario responsavel: ");
            scanf(" %11s", venda_achada->cpf_funcionario);

            int retorno = busca_cpf_geral(v_funcionario, t_funcionarios, v_cliente, t_clientes, venda_achada->cpf_funcionario);
            if (retorno == 1)
                break;
            else
                printf("CPF nao pertence a um Funcionario. Tente de novo.\n");
        }

        while (1)
        {
            printf("Digite o novo CPF do cliente: ");
            scanf(" %11s", venda_achada->cpf_cliente);

            int retorno = busca_cpf_geral(v_funcionario, t_funcionarios, v_cliente, t_clientes, venda_achada->cpf_cliente);
            if (retorno == 2)
                break;
            else
                printf("CPF nao pertence a um Cliente. Tente de novo.\n");
        }

        printf("Digite a nova hora (hh:mm:ss): ");
        scanf(" %9s", venda_achada->hora);
        while (getchar() != '\n')
            ;

        do
        {
            printf("Digite o novo produto vendido: \n");
            printf("1- Camiseta\n2- Jaqueta\n3- Shorts\n4- Calca\n5- Vestido\n6- Top\n7- Body\n8- Croped\n");
            scanf("%d", &venda_achada->produto);
            if (venda_achada->produto > 8)
                printf("\nNao temos esse produto. Selecione um produto existente.\n\n");
        } while (venda_achada->produto > 8);

        printf("\nSucesso: Venda atualizada!\n");
    }
}

void listar_todas_vendas(Venda *v_venda, int num_vendas)
{
    if (num_vendas == 0)
    {
        printf("\nNenhuma venda cadastrado. Cadastre uma ou mais vendas para listar os dados existentes.\n");
        printf("==================================\n");
        return;
    }

    else
    {
        printf("=================================DADOS DE TODAS AS VENDAS=================================\n");
        for (int i = 0; i < num_vendas; i++)
        {
            printf("\nValor da venda: %.2f", v_venda[i].valor_venda);
            printf("\nCodigo da venda: %d", v_venda[i].codigo_venda);
            printf("\nCpf do funcionario responsavel: %s", v_venda[i].cpf_funcionario);
            printf("\nCpf do cliente comprador: %s", v_venda[i].cpf_cliente);
            printf("\nData: %d/%d/%d", v_venda[i].dia, v_venda[i].mes, v_venda[i].ano);
            printf("\nHora: %s", v_venda[i].hora);
            if (v_venda[i].produto == 1)
                printf("\nProduto vendido: camiseta.");
            if (v_venda[i].produto == 2)
                printf("\nProduto vendido: jaqueta.");
            if (v_venda[i].produto == 3)
                printf("\nProduto vendido: shorts.");
            if (v_venda[i].produto == 4)
                printf("\nProduto vendido: calca.");
            if (v_venda[i].produto == 5)
                printf("\nProduto vendido: vestido.");
            if (v_venda[i].produto == 6)
                printf("\nProduto vendido: top.");
            if (v_venda[i].produto == 7)
                printf("\nProduto vendido: body.");
            if (v_venda[i].produto == 8)
                printf("\nProduto vendido: croped.");
            printf("\n=================================\n");
        }
        return;
    }
}

void consulta_vendas_funcionario(Venda *v_vendas, int total_venda, Funcionarios *v_funcionarios, int total_funcionario, Cliente *v_clientes, int total_clientes)
{
    if (cancelar_operacao() == 2)
    {
        printf("\nOperacao de cadastro cancelada.\n");
        return;
    }

    Funcionarios teste;

    while (1)
    {
        printf("\nDigite o CPF do funcionario que deseja vizualizar as vendas (somente numeros): ");
        scanf(" %11s", teste.cpf_funcionario);

        int retorno = busca_cpf_geral(v_funcionarios, total_funcionario, v_clientes, total_clientes, teste.cpf_funcionario);
        if (retorno == 1)
            break; // Funcionario achado
        else
        {
            int opcao;
            printf("CPF do Funcionario nao encontrado!\nDeseja cancelar a busca? (1-sim/2-nao)");
            scanf("%d", &opcao);
            if (opcao == 1)
                return;
        }
    }

    int houve_venda = 0;
    for (int i = 0; i < total_venda; i++)
    {
        if (strcmp(teste.cpf_funcionario, v_vendas[i].cpf_funcionario) == 0)
        {
            char nome_vendedor[60];
            for (int j = 0; j < total_funcionario; j++) {
                if (strcmp(v_vendas[i].cpf_funcionario, v_funcionarios[j].cpf_funcionario) == 0) {
                    strcpy(nome_vendedor, v_funcionarios[j].nome_funcionario);
                    break;
                }
            }

            houve_venda = 1;
            printf("\n==========Vendas do(a) %s==========\n", nome_vendedor);
            printf("\nValor da venda: %.2f", v_vendas[i].valor_venda);
            printf("\nCodigo da venda: %d", v_vendas[i].codigo_venda);
            printf("\nCpf do funcionario responsavel: %s", v_vendas[i].cpf_funcionario);
            printf("\nCpf do cliente comprador: %s", v_vendas[i].cpf_cliente);
            printf("\nNome do cliente: %s", v_clientes[i].nome_cliente);
            printf("\nData: %d/%d/%d", v_vendas[i].dia, v_vendas[i].mes, v_vendas[i].ano);
            printf("\nHora: %s", v_vendas[i].hora);
            if (v_vendas[i].produto == 1)
                printf("\nProduto vendido: camiseta.");
            else if (v_vendas[i].produto == 2)
                printf("\nProduto vendido: jaqueta.");
            else if (v_vendas[i].produto == 3)
                printf("\nProduto vendido: shorts.");
            else if (v_vendas[i].produto == 4)
                printf("\nProduto vendido: calca.");
            else if (v_vendas[i].produto == 5)
                printf("\nProduto vendido: vestido.");
            else if (v_vendas[i].produto == 6)
                printf("\nProduto vendido: top.");
            else if (v_vendas[i].produto == 7)
                printf("\nProduto vendido: body.");
            else if (v_vendas[i].produto == 8)
                printf("\nProduto vendido: croped.");
            printf("\n=================================\n");
        }
    }
    if (houve_venda == 0)
    {
        printf("\nEste funcionario nao realizou nenhuma venda\n");
    }
}

void consulta_compras_cliente(Venda *v_vendas, int total_venda, Cliente *v_clientes, int total_clientes, Funcionarios *v_funcionarios, int total_funcionario)
{
    if (cancelar_operacao() == 2)
    {
        printf("\nOperacao de cadastro cancelada.\n");
        return;
    }

    Cliente teste;

    while (1)
    {
        printf("\nDigite o CPF do cliente que deseja vizualizar as compras (somente numeros): ");
        scanf(" %11s", teste.cpf_cliente);

        int retorno = busca_cpf_geral(v_funcionarios, total_funcionario, v_clientes, total_clientes, teste.cpf_cliente);
        if (retorno == 2)
            break; // Cliente achado
        else
        {
            int opcao;
            printf("Cliente nao encontrado!\nDeseja cancelar a busca? (1-sim/2-nao)");
            scanf("%d", &opcao);
            if (opcao == 1)
                return;
        }
    }

    int houve_compra = 0;

    for (int i = 0; i < total_venda; i++)
    {
        if (strcmp(teste.cpf_cliente, v_vendas[i].cpf_cliente) == 0)
        {
            houve_compra = 1;
            char nome_cliente[60];
            for (int j = 0; j < total_clientes; j++) {
                if (strcmp(v_vendas[i].cpf_cliente, v_clientes[j].cpf_cliente) == 0) {
                    strcpy(nome_cliente, v_clientes[j].nome_cliente);
                    break;
                }
            }

            printf("\n==========Compras do(a) %s==========\n", nome_cliente);
            printf("\nValor da venda: %.2f", v_vendas[i].valor_venda);
            printf("\nCodigo da venda: %d", v_vendas[i].codigo_venda);
            printf("\nCpf do funcionario responsavel: %s", v_vendas[i].cpf_funcionario);
            printf("\nNome do vendedor: %s", v_funcionarios[i].nome_funcionario);
            printf("\nCpf do cliente comprador: %s", v_vendas[i].cpf_cliente);
            printf("\nData: %02d/%02d/%02d", v_vendas[i].dia, v_vendas[i].mes, v_vendas[i].ano);
            printf("\nHora: %s", v_vendas[i].hora);
            if (v_vendas[i].produto == 1)
                printf("\nProduto vendido: camiseta.");
            else if (v_vendas[i].produto == 2)
                printf("\nProduto vendido: jaqueta.");
            else if (v_vendas[i].produto == 3)
                printf("\nProduto vendido: shorts.");
            else if (v_vendas[i].produto == 4)
                printf("\nProduto vendido: calca.");
            else if (v_vendas[i].produto == 5)
                printf("\nProduto vendido: vestido.");
            else if (v_vendas[i].produto == 6)
                printf("\nProduto vendido: top.");
            else if (v_vendas[i].produto == 7)
                printf("\nProduto vendido: body.");
            else if (v_vendas[i].produto == 8)
                printf("\nProduto vendido: croped.");
            printf("\n=================================\n");
        }
    }
    if (houve_compra == 0)
    {
        printf("\nInfelizmente o cliente ainda nao realizou nenhuma compra!\n");
    }
}

// Inicio gerar arquivos txt =====================================================================================
int menu_gerar_txt()
{
    int opcao = 0;
    printf("\n==========================Escolha qual relatorio deseja gerar==========================\n");
    printf("1-Relatorio de frequencia de venda de um produto por periodo\n");
    printf("2-Relatorio de um funcionario por periodo\n");
    printf("3-Relatorio de vendas feitas por genero\n");
    printf("4-Voltar para o menu principal\n");
    printf("Qual relatorio deseja gerar no momento: ");
    scanf(" %d", &opcao);
    return opcao;
}

int gerar_arquivo_txt_produto_frequencia(Venda *v_vendas, int total_venda)
{
    int dia_r1_inicio = 0, mes_r1_inicio = 0, ano_r1_incio = 0, dia_r1_fim = 0, mes_r1_fim = 0, ano_r1_fim = 0, cod_prod_r1 = 0, flag = 0;
    long long int data_inicio = 0, data_fim = 0;
    int cancel = cancelar_operacao();
    int num_vendas = 0, quantidade_vendida = 0;
    if (cancel == 2)
    {
        printf("\nOperacao cancelada\n");
        return 0;
    }
    do
    {
        while (getchar() != '\n')
            ;
        printf("\nQual produto voce deseja gerar um relatorio? \n");
        printf("\n1- Camiseta\n2- Jaqueta\n3- Shorts\n4- Calca\n5- Vestido\n6- Top\n7- Body\n8- Croped\nEscolha: ");
        scanf("%d", &cod_prod_r1);
        while (getchar() != '\n')
            ;
        if (cod_prod_r1 < 1 || cod_prod_r1 > 8)
            printf("\nNao temos esse produto. Selecione um produto existente.\n\n");
    } while (cod_prod_r1 < 1 || cod_prod_r1 > 8);

    do
    {

        printf("\nDigite a data inicial do relatorio no formato DD MM AAAA: ");

        if (scanf("%d %d %d", &dia_r1_inicio, &mes_r1_inicio, &ano_r1_incio) != 3)
        {
            printf("Erro: Digite apenas numeros para o codigo.\n");
            while (getchar() != '\n')
                ;
            flag = 1;
            continue;
        }
        flag = 0;
        data_inicio = (ano_r1_incio * 10000) + (mes_r1_inicio * 100) + dia_r1_inicio;
    } while (flag == 1);
    flag = 0;

    do
    {
        printf("\nDigite a data final do relatorio no formato DD MM AAAA: ");

        if (scanf("%d %d %d", &dia_r1_fim, &mes_r1_fim, &ano_r1_fim) != 3)
        {
            printf("Erro: Digite apenas numeros para o codigo.\n");
            while (getchar() != '\n')
                ;
            flag = 1;
            continue;
        }
        flag = 0;
        data_fim = (ano_r1_fim * 10000) + (mes_r1_fim * 100) + dia_r1_fim;
        while (getchar() != '\n')
            ;
        if (data_fim < data_inicio)
        {
            printf("\nData Final menor que inicial, tente novamente\n");
            flag = 1;
        }

    } while (flag == 1);

    FILE *relatorio1;

    relatorio1 = fopen("../relatorio_produto_por_periodo.txt", "w");
    if (relatorio1 == NULL)
    {
        printf("\nErro ao gerar relatorio\n");
        return 0;
    }

    fprintf(relatorio1, "============================================================================================\n");
    fprintf(relatorio1, "| %-10s | %-10s | %-11s | %-11s | %-10s | %-8s | %-10s |\n", "Valor (R$)", "Codigo", "CPF Func.", "CPF Cliente", "Data", "Hora", "Produto");
    fprintf(relatorio1, "============================================================================================\n");

    int encontrou = 0;

    for (int i = 0; i < total_venda; i++)
    {

        if (v_vendas[i].produto == cod_prod_r1)
        {
            num_vendas++;
            quantidade_vendida++;
            long long int data_venda = (v_vendas[i].ano * 10000) + (v_vendas[i].mes * 100) + v_vendas[i].dia;

            if (data_venda >= data_inicio && data_venda <= data_fim)
            {

                encontrou = 1;

                char nome_produto[15];
                switch (v_vendas[i].produto)
                {
                case 1:
                    strcpy(nome_produto, "Camiseta");
                    break;
                case 2:
                    strcpy(nome_produto, "Jaqueta");
                    break;
                case 3:
                    strcpy(nome_produto, "Shorts");
                    break;
                case 4:
                    strcpy(nome_produto, "Calca");
                    break;
                case 5:
                    strcpy(nome_produto, "Vestido");
                    break;
                case 6:
                    strcpy(nome_produto, "Top");
                    break;
                case 7:
                    strcpy(nome_produto, "Body");
                    break;
                case 8:
                    strcpy(nome_produto, "Croped");
                    break;
                }

                fprintf(relatorio1, "| %10.2f | %10d | %11s | %11s | %02d/%02d/%04d | %8s | %-10s |\n", v_vendas[i].valor_venda, v_vendas[i].codigo_venda, v_vendas[i].cpf_funcionario, v_vendas[i].cpf_cliente, v_vendas[i].dia, v_vendas[i].mes, v_vendas[i].ano, v_vendas[i].hora, nome_produto);
            }
        }
    }

    if (encontrou == 0)
    {
        fprintf(relatorio1, "| %-88s |\n", "Nenhuma venda deste produto foi encontrada no periodo selecionado.");
    }

    fprintf(relatorio1, "============================================================================================\n");

    fprintf(relatorio1, "\nRelatorio Final:");
    fprintf(relatorio1, "\nNumero de Vendas: %d || Quantidade de produtos vendidos: %d\n", num_vendas, quantidade_vendida);

    fclose(relatorio1);

    return 1;
}

int gerar_arquivo_txt_funcionario_periodo(Venda *v_vendas, int total_venda, Funcionarios *v_funcionarios, int total_funcionario, Cliente *v_clientes, int total_clientes)
{
    if (cancelar_operacao() == 2)
    {
        printf("\nOperacao cancelada\n");
        return 0;
    }

    char cpf_alvo[12];

    while (1)
    {
        printf("\nDigite o CPF do funcionario (somente numeros): ");
        scanf(" %11s", cpf_alvo);
        while (getchar() != '\n')
            ;

        if (busca_cpf_geral(v_funcionarios, total_funcionario, v_clientes, total_clientes, cpf_alvo) == 1)
        {
            break;
        }
        else
        {
            printf("\nCPF do Funcionario nao encontrado. Tente novamente.\n");
        }
    }

    int dia_inicio, mes_inicio, ano_inicio, dia_fim, mes_fim, ano_fim, flag = 0;
    long long int data_inicio = 0, data_fim = 0;

    do
    {
        printf("\nDigite a data inicial do relatorio no formato DD MM AAAA: ");
        if (scanf("%d %d %d", &dia_inicio, &mes_inicio, &ano_inicio) != 3)
        {
            printf("Erro: Digite apenas numeros.\n");
            while (getchar() != '\n')
                ;
            flag = 1;
            continue;
        }
        flag = 0;
        data_inicio = (ano_inicio * 10000) + (mes_inicio * 100) + dia_inicio;
    } while (flag == 1);

    flag = 0;

    do
    {
        printf("\nDigite a data final do relatorio no formato DD MM AAAA: ");
        if (scanf("%d %d %d", &dia_fim, &mes_fim, &ano_fim) != 3)
        {
            printf("Erro: Digite apenas numeros.\n");
            while (getchar() != '\n')
                ;
            flag = 1;
            continue;
        }
        flag = 0;
        data_fim = (ano_fim * 10000) + (mes_fim * 100) + dia_fim;
        while (getchar() != '\n')
            ;
        if (data_fim < data_inicio)
        {
            printf("\nData Final menor que inicial, tente novamente\n");
            flag = 1;
        }
    } while (flag == 1);

    FILE *relatorio2 = fopen("../relatorio_funcionario_por_periodo.txt", "w");
    if (relatorio2 == NULL)
    {
        printf("\nErro ao gerar relatorio\n");
        return 0;
    }

    fprintf(relatorio2, "============================================================================================\n");
    fprintf(relatorio2, "| %-10s | %-10s | %-11s | %-11s | %-10s | %-8s | %-10s |\n", "Valor (R$)", "Codigo", "CPF Func.", "CPF Cliente", "Data", "Hora", "Produto");
    fprintf(relatorio2, "============================================================================================\n");

    int encontrou = 0;
    int qtd_vendas = 0;
    float total_valor_vendido = 0;
    int genero_m = 0, genero_f = 0;

    for (int i = 0; i < total_venda; i++)
    {
        if (strcmp(v_vendas[i].cpf_funcionario, cpf_alvo) == 0)
        {
            long long int data_venda = (v_vendas[i].ano * 10000) + (v_vendas[i].mes * 100) + v_vendas[i].dia;

            if (data_venda >= data_inicio && data_venda <= data_fim)
            {
                encontrou = 1;
                qtd_vendas++;
                total_valor_vendido += v_vendas[i].valor_venda;

                for (int c = 0; c < total_clientes; c++)
                {
                    if (strcmp(v_clientes[c].cpf_cliente, v_vendas[i].cpf_cliente) == 0)
                    {
                        if (v_clientes[c].genero_cliente[0] == 'M')
                            genero_m++;
                        else if (v_clientes[c].genero_cliente[0] == 'F')
                            genero_f++;
                        break;
                    }
                }

                char nome_produto[15];
                switch (v_vendas[i].produto)
                {
                case 1:
                    strcpy(nome_produto, "Camiseta");
                    break;
                case 2:
                    strcpy(nome_produto, "Jaqueta");
                    break;
                case 3:
                    strcpy(nome_produto, "Shorts");
                    break;
                case 4:
                    strcpy(nome_produto, "Calca");
                    break;
                case 5:
                    strcpy(nome_produto, "Vestido");
                    break;
                case 6:
                    strcpy(nome_produto, "Top");
                    break;
                case 7:
                    strcpy(nome_produto, "Body");
                    break;
                case 8:
                    strcpy(nome_produto, "Croped");
                    break;
                }

                fprintf(relatorio2, "| %10.2f | %10d | %11s | %11s | %02d/%02d/%04d | %8s | %-10s |\n", v_vendas[i].valor_venda, v_vendas[i].codigo_venda, v_vendas[i].cpf_funcionario, v_vendas[i].cpf_cliente, v_vendas[i].dia, v_vendas[i].mes, v_vendas[i].ano, v_vendas[i].hora, nome_produto);
            }
        }
    }

    if (encontrou == 0)
    {
        fprintf(relatorio2, "| %-88s |\n", "Nenhuma venda deste funcionario foi encontrada no periodo selecionado.");
        fprintf(relatorio2, "============================================================================================\n");
    }
    else
    {
        fprintf(relatorio2, "============================================================================================\n");
        fprintf(relatorio2, "RESUMO DO FUNCIONARIO:\n");
        fprintf(relatorio2, "Total de vendas: %d\n", qtd_vendas);
        fprintf(relatorio2, "Valor total vendido: R$ %.2f\n", total_valor_vendido);
        fprintf(relatorio2, "Valor medio por venda: R$ %.2f\n", total_valor_vendido / qtd_vendas);

        if (genero_m > genero_f)
            fprintf(relatorio2, "Genero que mais comprou: Masculino\n");
        else if (genero_f > genero_m)
            fprintf(relatorio2, "Genero que mais comprou: Feminino\n");
        else
            fprintf(relatorio2, "Genero que mais comprou: Empate (M e F)\n");
    }

    fclose(relatorio2);
    return 1;
}

int gerar_arquivo_txt_genero(Venda *v_vendas, int total_venda, Cliente *v_clientes, int total_clientes)
{
    printf("\nDigite o genero que deseja filtrar as vendas\n");
    char genero_alvo;
    do
    {
        printf("Escreva o genero (M/F): ");
        scanf(" %c", &genero_alvo);
        while (getchar() != '\n')
            ;

        if (genero_alvo >= 'a' && genero_alvo <= 'z')
        {
            genero_alvo = genero_alvo - 32;
        }

        if (genero_alvo != 'M' && genero_alvo != 'F')
        {
            printf("Erro: Opcao invalida. Digite M ou F.\n");
        }

    } while (genero_alvo != 'M' && genero_alvo != 'F');

    int numero_vendas = 0, numero_clientes = 0;
    float valor_total_vendido = 0;

    for (int k = 0; k < total_clientes; k++)
    {
        if (v_clientes[k].genero_cliente[0] == genero_alvo)
        {
            numero_clientes++;
        }
    }

    for (int i = 0; i < total_venda; i++)
    {
        for (int j = 0; j < total_clientes; j++)
        {
            if (strcmp(v_vendas[i].cpf_cliente, v_clientes[j].cpf_cliente) == 0)
            {
                if (v_clientes[j].genero_cliente[0] == genero_alvo)
                {
                    numero_vendas++;
                    valor_total_vendido += v_vendas[i].valor_venda;
                }
                break;
            }
        }
    }

    FILE *relatorio3 = fopen("../relatorio_vendas_genero.txt", "w");
    if (relatorio3 == NULL)
    {
        printf("\nErro ao gerar relatorio\n");
        return 0;
    }

    fprintf(relatorio3, "========================================================\n");
    fprintf(relatorio3, "        RELATORIO DE VENDAS - GENERO: %c\n", genero_alvo);
    fprintf(relatorio3, "========================================================\n");
    fprintf(relatorio3, "Numero de clientes cadastrados: %d\n", numero_clientes);
    fprintf(relatorio3, "Quantidade de vendas realizadas: %d\n", numero_vendas);
    fprintf(relatorio3, "Valor total de vendas: R$ %.2f\n", valor_total_vendido);
    fprintf(relatorio3, "========================================================\n");

    fclose(relatorio3);

    return 1;
}
