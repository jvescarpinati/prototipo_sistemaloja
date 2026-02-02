#include <stdio.h>
typedef struct
{
    char cpf_funcionario[12];
    char nome_funcionario[60];
    float salario_funcionario;
    char cargo_funcionario[30];

} Funcionarios;

int menu_funcionarios()
{
    printf("Escolha uma opcao de alteracao para os funcionarios: \n");
    printf("1-Cadastro Novo Funcionario\n");
    printf("2-Visualziar Informacoes de cadastro de funcionario\n");
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

void cadastro_funcio(Funcionarios *fim){
    int verifnomefun;
    do
    {
        printf("\nEscreva o nome do Funcionario: ");
        scanf(" %59[^\n]", fim->nome_funcionario);
        char sobra = getchar();
        if (sobra != '\n')
        {
            printf("\nErro: Nome longo demais! Use no maximo 59 caracteres.\n");
            while (getchar() != '\n');
            verifnomefun = 1;
        }
        else
        {
            verifnomefun = verificar_nome_fun(fim);

            if (verifnomefun == 1)
            {
                printf("\nNome Digitado invalido (contem numeros), tente novamente.\n");
            }
        }
    } while (verifnomefun == 1);

    int verifcpffun = 0;

    do
    {
        printf("\nEscreva o cpf do funcionario sem espacos pontos e tracos: ");
        scanf(" %[^\n]", fim->cpf_funcionario);
        if (strlen(fim->cpf_funcionario) > 11)
        {
            printf("\nCpf Invalido, possui numeros em execesso, tente novamente\n");
            verifcpffun = 1;
        }
        else if (strlen(fim->cpf_funcionario) < 11)
        {
            printf("\nCpf com numeros em falta, tente novamente\n");
            verifcpffun = 1;
        }
        else
        {
            verifcpffun = verificar_cpf_fun(fim);
            if (verifcpffun == 1)
            {
                printf("\nCpf Digitado invalido (contem letras), tente novamente.\n");
            }
        }
    } while (verifcpffun == 1);

    int verifcargo = 0;

    do
    {
        printf("\nEscreva o cargo do funcionario: ");
        scanf(" %29[^\n]", fim->cargo_funcionario);
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
            verifcargo = verificar_cargo_fun(fim);
            if (verifcargo == 1)
            {
                printf("\nCargo Invalido (Possui Numeros),tente novamente\n");
            }
        }
    } while (verifcargo == 1);

    int verifsalario = 0;

    do
    {
        printf("\nEscreva o valor do salario do funcionario:");
        if (scanf(" %f", &fim->salario_funcionario) == 1)
        {
            int sobra = getchar();
            if (sobra != '\n' && sobra != ' ')
            {
                printf("\nErro: Entrada invalida. Nao use letras ou virgulas.\n");

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
            printf("\nErro: Voce nao digitou um numero valido.\n");
            while (getchar() != '\n')
                ;
            verifsalario = 1;
        }
    } while (verifsalario == 1);
}

void apagar_funcionario(Funcionarios *inicio, Funcionarios **fim)
{
    char cpf[12];
    int flag_busca;
    printf("Digite o cpf do funcionario que deseja remover: ");
    scanf("%s", cpf);

    Funcionarios *alvo = busca_funcionario(inicio, *fim, cpf, &flag_busca);

    if (alvo != NULL)
    {
        Funcionarios *fun;
        for (fun = alvo; fun < (*fim - 1); fun++)
        {
            *fun = *(fun + 1);
        }

        (*fim)--;
        printf("\nSucesso: Funcionario removido.\n");
    }

    else
        printf("\nOperacao de remocao cancelada.\n");
}

Funcionarios *busca_funcionario(Funcionarios *inicio, Funcionarios *fim, char cpf_achar[12], int *Flag)
{
    Funcionarios *usuario_achado;
    Funcionarios *inicio2 = inicio;
    *Flag = 0;
    for (inicio2 = inicio2; inicio2 < fim; inicio2++)
    {
        if (strcmp(inicio2->cpf_funcionario, cpf_achar) == 0)
        {
            usuario_achado = inicio2;
            return usuario_achado;
        }
    }
    printf("\nErro: Usuario nao encontrado, tente novamente\n");
    *Flag = 1;
    return NULL;
}

void ler_info_func(Funcionarios *inicio, Funcionarios *fim)
{
    char cpf_achar[12];
    int flag = 0;
    int *Flag = &flag;
    Funcionarios *funcionario_achado;
    do
    {
        printf("\nDigite o cpf (somente numeros sem barras ou tracos) do funcionario que deseja ler os dados do cadastro: ");
        scanf(" %[^\n]", cpf_achar);
        funcionario_achado = busca_funcionario(inicio, fim, cpf_achar, Flag);
    } while (flag == 1);
    if (flag == 0)
    {
        printf("\nNome : %s\n", funcionario_achado->nome_funcionario);
        printf("Cpf : %s\n", funcionario_achado->cpf_funcionario);
        printf("Cargo : %s\n", funcionario_achado->cargo_funcionario);
        printf("Salario : %.2f\n\n", funcionario_achado->salario_funcionario);
    }
}

void atualizar_infos_funcionarios(Funcionarios *inicio, Funcionarios *fim)
{
    char cpf_achar[12];
    int flag = 0;
    int *Flag = &flag;
    Funcionarios *funcionario_achado;
    do
    {
        printf("\nDigite o cpf (somente numeros sem barras ou tracos) do funcionario que deseja atualizar os dados do cadastro: ");
        scanf(" %[^\n]", cpf_achar);
        funcionario_achado = busca_funcionario(inicio, fim, cpf_achar, Flag);
    } while (flag == 1);
    if (flag == 0)
    {
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
            printf("\nDigite o cargo atualizado do funcionario: ");
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
                    printf("\nCargo Invalido (Possui Numeros),tente novamente\n");
                }
            }
        } while (verifcargo == 1);

        int verifsalario = 0;

        do
        {
            printf("\nDigite o valor atualizado do salario do funcionario:");
            if (scanf(" %f", &funcionario_achado->salario_funcionario) == 1)
            {
                int sobra = getchar();
                if (sobra != '\n' && sobra != ' ')
                {
                    printf("\nErro: Entrada invalida. Nao use letras ou virgulas.\n");

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
                printf("\nErro: Voce nao digitou um numero valido.\n");
                while (getchar() != '\n')
                    ;
                verifsalario = 1;
            }
            printf("\n");
        } while (verifsalario == 1);
    }
}