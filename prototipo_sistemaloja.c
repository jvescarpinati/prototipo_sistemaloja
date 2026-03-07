#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    char cpf_funcionario[12]; //só se cadastra a venda se houver um funcionario associado
    char cpf_cliente[12]; // só se cadastra a venda se houver um cliente associado
    int dia;
    int mes;
    int ano;
    char hora[9];
} Venda;

int menu_geral();
int cancelar_operacao();
int busca_cpf_geral(Funcionarios *v_funcionario, int num_funcionario, Cliente *v_cliente, int num_cliente, char *cpf_procurado);

/*Comeco funcionario===================================================================================================*/
int menu_funcionarios();
int verificar_nome_fun(Funcionarios *funci);
int verificar_cpf_fun(Funcionarios *funci);
int verificar_cargo_fun(Funcionarios *func);
int cadastro_funcio(Funcionarios *v_funcionario, int i, Cliente *v_cliente, int total_cli);
void apagar_funcionario(Funcionarios **v_funcionario, int *t_funcionario, int *cap_funcionario, Venda *v_venda, int t_vendas);
Funcionarios *busca_funcionario(Funcionarios *vf, int n, char *cpf, int *flag);
void ler_info_func(Funcionarios *v_funcionario, int num_func);
void atualizar_infos_funcionarios(Funcionarios *v_funcionario, int t_funcionarios, Cliente *v_cliente, int t_clientes);

/*Começo clientes======================================================================================================*/
int menu_clientes();
int cadastro_cliente(Cliente *v_cliente, int i, Funcionarios *v_funcionario, int total_func);
int verificar_cpf_cliente(Cliente *cliente);
void leitura_cliente(Cliente *v_cliente, int t_clientes);
void apagar_cliente(Cliente **v_cliente, int *t_cliente, int *cap_cliente, Venda *v_venda, int t_vendas);
Cliente *busca_cliente(Cliente *vc, int n, char cpf_alvo[12], int *Flag);
void atualizar_infos_cliente(Cliente *v_cliente, int t_clientes, Funcionarios *v_funcionario, int t_funcionarios);
int verificar_nome_cliente(Cliente *cli);

//começo vendas========================================================================================================
int menu_vendas();
int cadastro_venda(Venda *v_venda, int i, Funcionarios *v_funcionario, int total_fun, Cliente *v_cliente, int total_cli);
void leitura_venda(Venda *v_venda, int t_vendas);
void apagar_venda(Venda **v_venda, int *t_venda, int *cap_venda);
void atualizar_infos_venda(Venda *v_venda, int t_vendas, Funcionarios *v_funcionario, int t_funcionarios, Cliente *v_cliente, int t_clientes);
Venda *busca_venda(Venda *vv, int n, int codigo_alvo, int *Flag);

int main()
{
    int opcao_geral;
    int capacidade_funcionario = 5, total_funcionario = 0;
    int capacidade_clientes = 5, total_clientes = 0;
    int capacidade_venda = 5, total_venda = 0;

    Funcionarios *funcionarios = (Funcionarios *) malloc(capacidade_funcionario * sizeof(Funcionarios));
    Cliente *clientes = (Cliente *) malloc(capacidade_clientes * sizeof(Cliente));
    Venda *vendas = (Venda *) malloc(capacidade_venda * sizeof(Venda));

    printf("====Seja Bem-Vindo====\n");
    do
    {
        opcao_geral = menu_geral();

        switch (opcao_geral)
        {
            case 1: //funcionario
            {
                int opcao_funcionario;
                do
                {
                    opcao_funcionario = menu_funcionarios();
                    if (opcao_funcionario == 1)
                    {
                        if (total_funcionario == capacidade_funcionario)
                        {
                            int numero_funcionario; 
                            printf("Quantos funcionarios deseja cadastrar? ");
                            scanf("%d", &numero_funcionario);
                            capacidade_funcionario += numero_funcionario;

                            Funcionarios *temp = (Funcionarios *) realloc(funcionarios, capacidade_funcionario * sizeof(Funcionarios));
                            if (temp == NULL) {
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
                        ler_info_func(funcionarios, total_funcionario);
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
                            int numero_cli; 
                            printf("Quantos clientes adicionais voce deseja cadastrar?\n");
                            scanf("%d", &numero_cli);
                            capacidade_clientes += numero_cli;

                            Cliente *temp = (Cliente *) realloc(clientes, capacidade_clientes * sizeof(Cliente));
                            if (temp == NULL) {
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
            case 3: //venda
            {
                int opcao_vendas;
                do
                {
                    opcao_vendas = menu_vendas();

                    if (opcao_vendas == 1)
                    {
                        if (total_venda == capacidade_venda)
                        {
                            int numero_venda; 
                            printf("Quantas vendas adicionais voce deseja cadastrar?\n");
                            scanf("%d", &numero_venda);
                            capacidade_venda += numero_venda;

                            Venda *temp = (Venda *) realloc(vendas, capacidade_venda * sizeof(Venda));
                            if (temp == NULL) {
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
                        leitura_venda(vendas, total_venda);
                    }
                    else if (opcao_vendas == 3)
                    {
                        atualizar_infos_venda(vendas, total_venda, funcionarios, total_funcionario, clientes, total_clientes);
                    }
                    else if (opcao_vendas == 4)
                    {
                        apagar_venda(&vendas, &total_venda, &capacidade_venda);
                    }

                } while (opcao_vendas != 5);
                break;
            }
        }
    } while (opcao_geral != 8);

    printf("\n\nSaindo do Programa...\n\n");
    
    free(funcionarios);
    free(clientes);
    free(vendas);

    return 0;
}

int menu_geral()
{
    int opcao;
    printf("\n====Escolha qual area voce quer acessar====\n");
    printf("1-Area Funcionarios\n");
    printf("2-Area Clientes\n");
    printf("3-Vendas\n");
    printf("4-Listar Dados de Todos os Funcionarios\n");
    printf("5-Listar Dados de Todos os Clientes\n");
    printf("6-Listar Dados de vendas\n");
    printf("7-Criar Relatorio TXT\n");
    printf("8-Sair do App\n");
    printf("Qual a opcao escolhida? ");
    scanf("%d", &opcao);
    return opcao;
}

int cancelar_operacao(){
    printf("\nVoce deseja cancelar essa operacao?\n");
    printf("1-Nao, prosseguir\n");
    printf("2-Sim, retornar\n");

    int opcao_cancelar;
    printf("Qual a opcao escolhida: ");
    scanf("%d", &opcao_cancelar);

    return opcao_cancelar;
}

int busca_cpf_geral(Funcionarios *v_funcionario, int num_funcionario, Cliente *v_cliente, int num_cliente, char *cpf_procurado){
    for (int pf = 0; pf < num_funcionario; pf++) {
        if (strcmp(v_funcionario[pf].cpf_funcionario, cpf_procurado) == 0) return 1;
    }
    for (int pc = 0; pc < num_cliente; pc++) {
        if (strcmp(v_cliente[pc].cpf_cliente, cpf_procurado) == 0) return 2;
    }
    return 0;
}

// Comeco funcionario===================================================================================================

int menu_funcionarios(){
    printf("\nEscolha uma opcao de alteracao para os funcionarios: \n");
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
    if (funci->cpf_funcionario[0] == '\0') return 1;

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

int cadastro_funcio(Funcionarios *v_funcionario, int i, Cliente *v_cliente, int total_cli){

    if(cancelar_operacao() == 2) {
        printf("\nOperacao de cadastro cancelada.\n");
        return 0;
    }

    int verifnomefun;
    do {
        printf("\nEscreva o nome do Funcionario: ");
        scanf(" %59[^\n]", v_funcionario[i].nome_funcionario);
        
        char sobra = getchar();
        if (sobra != '\n') {
            printf("\nErro: Nome longo demais!\n");
            while (getchar() != '\n');
            verifnomefun = 1;
        } else {
            verifnomefun = verificar_nome_fun(&v_funcionario[i]);
            if (verifnomefun == 1) {
                printf("Nome Digitado invalido (contem numeros), tente novamente.\n");
            }
        }
    } while (verifnomefun == 1);

    int verifcpffun = 0;
    do {
        printf("Escreva o cpf do funcionario (11 digitos): ");
        scanf(" %[^\n]", v_funcionario[i].cpf_funcionario);
        verifcpffun = verificar_cpf_fun(&v_funcionario[i]);

        if (verifcpffun == 0) {
            if (busca_cpf_geral(v_funcionario, i, v_cliente, total_cli, v_funcionario[i].cpf_funcionario)!=0) {
                printf("Erro: Este CPF ja esta cadastrado no sistema!\n");
                verifcpffun = 1;
            }
        }
    } while (verifcpffun == 1);

    int verifcargo = 0;
    do {
        printf("Escreva o cargo do funcionario: ");
        scanf(" %29[^\n]", v_funcionario[i].cargo_funcionario);
        
        char teste = getchar();
        if (teste != '\n') {
            printf("Cargo Excede Limite de caracteres\n");
            while (getchar() != '\n');
            verifcargo = 1;
        } else {
            verifcargo = verificar_cargo_fun(&v_funcionario[i]);
            if (verifcargo == 1) {
                printf("Cargo Invalido (Possui Numeros), tente novamente\n");
            }
        }
    } while (verifcargo == 1);

    int verifsalario = 0;
    do {
        printf("Escreva o valor do salario do funcionario: ");
        if (scanf(" %f", &v_funcionario[i].salario_funcionario) == 1) {
            int sobra = getchar();
            if (sobra != '\n' && sobra != ' ') {
                printf("Erro: Entrada invalida. Nao use letras ou virgulas.\n");
                while (getchar() != '\n');
                verifsalario = 1;
            } else {
                verifsalario = 0;
            }
        } else {
            printf("Erro: Voce nao digitou um numero valido.\n");
            while (getchar() != '\n');
            verifsalario = 1;
        }
    } while (verifsalario == 1);

    return 1;
}

void apagar_funcionario(Funcionarios **v_funcionario, int *t_funcionario, int *cap_funcionario, Venda *v_venda, int t_vendas)
{
    if (*t_funcionario==0) {
        printf("\nNenhum funcionario cadastrado para apagar.\n");
        return;
    }
    if (cancelar_operacao() == 2) {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    char cpf[12];
    int flag_busca;
    printf("\nDigite o cpf do funcionario que deseja remover: ");
    scanf("%s", cpf);

    // RESTRIÇÃO: Verificar se o funcionário está em alguma venda
    for (int i = 0; i < t_vendas; i++) {
        if (strcmp(v_venda[i].cpf_funcionario, cpf) == 0) {
            printf("\nErro: Funcionario nao pode ser removido pois esta associado a uma ou mais vendas.\n");
            return;
        }
    }

    Funcionarios *alvo = busca_funcionario(*v_funcionario, *t_funcionario, cpf, &flag_busca);

    if (alvo != NULL)
    {
        int indice_alvo=alvo-(*v_funcionario);
        for(int j=indice_alvo; j<(*t_funcionario-1); j++){
            (*v_funcionario)[j] = (*v_funcionario)[j+1];
        }

        (*t_funcionario)--;

        if(*t_funcionario>0){
            *cap_funcionario=*t_funcionario;

            Funcionarios *temp = (Funcionarios *) realloc(*v_funcionario, (*cap_funcionario) * sizeof(Funcionarios));
            if(temp==NULL){
                printf("Erro de memoria\n");
                exit(0);
            }
            *v_funcionario=temp;
        }
        printf("\nSucesso: Funcionario removido.\n");
    }
    else
        printf("\nErro: Funcionario nao encontrado\n");
}

Funcionarios *busca_funcionario(Funcionarios *vf, int n, char *cpf, int *flag)
{
    *flag = 1;
    for (int i = 0; i < n; i++) {
        if (strcmp(vf[i].cpf_funcionario, cpf) == 0) {
            *flag = 0;
            return &vf[i];
        }
    }
    return NULL;
}

void ler_info_func(Funcionarios *v_funcionario, int t_funcionarios)
{
    if (t_funcionarios==0) {
        printf("\nNenhum funcionario cadastrado para visualizar.\n");
        return;
    }
    if (cancelar_operacao() == 2) {
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
        funcionario_achado = busca_funcionario(v_funcionario, t_funcionarios, cpf_achar, Flag);

        if (flag == 1) printf("\nFuncionario nao encontrado!\n");

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
    if (t_funcionarios==0) {
        printf("\nNenhum funcionario cadastrado para atualizar.\n");
        return;
    }
    if (cancelar_operacao() == 2) {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    char cpf_achar[12];
    int flag = 0;
    int *Flag = &flag;
    Funcionarios *funcionario_achado;
    do
    {
        printf("\nDigite o cpf (somente numeros) do funcionario que deseja atualizar: ");
        scanf(" %s", cpf_achar);
        funcionario_achado = busca_funcionario(v_funcionario, t_funcionarios, cpf_achar, Flag);
    } while (flag == 1);

    if (flag == 0)
    {
        int verifcpffun = 0;
        char novo_cpf[12];
        do {
            printf("\nDigite o novo cpf do funcionario (11 digitos): ");
            scanf(" %s", novo_cpf);
            while (getchar() != '\n');
            if (strcmp(novo_cpf, funcionario_achado->cpf_funcionario) != 0 && busca_cpf_geral(v_funcionario, t_funcionarios, v_cliente, t_clientes, novo_cpf)!=0) {
                printf("\nErro: Este CPF ja esta cadastrado no sistema!\n");
                verifcpffun = 1;
            } else {
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
                while (getchar() != '\n');
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
                while (getchar() != '\n');
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
                    while (getchar() != '\n');
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
                while (getchar() != '\n');
                verifsalario = 1;
            }
            printf("\n");
        } while (verifsalario == 1);
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

int verificar_cpf_cliente(Cliente *cliente){
    int i=0;
    if(cliente->cpf_cliente[0]=='\0') return 1;

    while (cliente->cpf_cliente[i]!='\0'){
        if(!isdigit(cliente->cpf_cliente[i])){
            return 1;
        }
        i++;
    }
    if(i!=11){
        printf("\nO CPF deve ter exatamente 11 digitos.\n");
        return 1;
    }
    return 0;
}

int cadastro_cliente(Cliente *v_cliente, int i, Funcionarios *v_funcionario, int total_funci) {
    if(cancelar_operacao() == 2) {
        printf("\nOperacao de cadastro cancelada.\n");
        return 0;
    }

    printf("\nEscreva o nome do Cliente: ");
    scanf(" %59[^\n]", v_cliente[i].nome_cliente);
    while (getchar() != '\n');

    int verif_cpf_cli = 0;
    do{
        printf("Escreva o cpf do cliente (somente 11 numeros): ");
        scanf(" %11s", v_cliente[i].cpf_cliente);
        while (getchar() != '\n');

        verif_cpf_cli = verificar_cpf_cliente(&v_cliente[i]);

        if (verif_cpf_cli == 0) {
            if (busca_cpf_geral(v_funcionario, total_funci, v_cliente, i, v_cliente[i].cpf_cliente)!=0) {
                printf("Erro: Este CPF ja esta cadastrado no sistema (Cliente ou Funcionario).\n");
                verif_cpf_cli = 1;
            }
        }
    }while (verif_cpf_cli == 1);

    printf("Escreva o telefone do cliente (somente numeros): ");
    scanf("%11lld", &v_cliente[i].telefone_cliente);
    while (getchar() != '\n');

    do {
        printf("Escreva o genero (M/F): ");
        scanf(" %1s", v_cliente[i].genero_cliente);
        while (getchar() != '\n');

        if (v_cliente[i].genero_cliente[0] >= 'a' && v_cliente[i].genero_cliente[0] <= 'z') {
            v_cliente[i].genero_cliente[0] = v_cliente[i].genero_cliente[0] - 32;
        }

        if (v_cliente[i].genero_cliente[0] != 'M' && v_cliente[i].genero_cliente[0] != 'F') {
            printf("Erro: Opcao invalida. Digite M ou F.\n");
        }

    } while (v_cliente[i].genero_cliente[0] != 'M' && v_cliente[i].genero_cliente[0] != 'F');

    return 1;
}

void leitura_cliente(Cliente *v_cliente, int t_clientes){

    if (t_clientes == 0) {
        printf("\nNenhum cliente cadastrado para visualizar.\n");
        return;
    }
    if (cancelar_operacao() == 2) {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    char cpf_alvo[12];
    int flag = 0;
    int *Flag = &flag;
    Cliente *cliente_achado;
    do{
        printf("\nDigite o cpf (somente numeros sem barras ou tracos) do cliente que deseja ler os dados: ");
        scanf(" %[^\n]", cpf_alvo);
        cliente_achado = busca_cliente(v_cliente, t_clientes, cpf_alvo, Flag);
    } while (flag == 1);
    
    if (flag == 0){
        printf("\nNome: %s\n", cliente_achado->nome_cliente);
        printf("Cpf: %s\n", cliente_achado->cpf_cliente);
        printf("Telefone: %lld\n", cliente_achado->telefone_cliente);
        if(cliente_achado->genero_cliente[0] == 'M') printf("Genero: Masculino\n\n");
        else printf("Genero: Feminino\n\n");
    }
}

Cliente *busca_cliente(Cliente *vc, int n, char cpf_alvo[12], int *Flag){
    *Flag = 1;
    for(int i = 0; i < n; i++){
        if(strcmp(vc[i].cpf_cliente, cpf_alvo)==0){
            *Flag = 0;
            return &vc[i];
        }
    }
    printf("\nErro: Cliente nao encontrado, tente novamente\n");
    return NULL;
}

void apagar_cliente(Cliente **v_cliente, int *t_cliente, int *cap_cliente, Venda *v_venda, int t_vendas){

    if (*t_cliente == 0) {
        printf("\nNenhum cliente cadastrado para apagar.\n");
        return;
    }
    if (cancelar_operacao() == 2) {
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    char cpf[12];
    int flag_busca;
    printf("\nDigite o cpf do cliente que deseja remover: ");
    scanf("%s", cpf);

    // RESTRIÇÃO: Verificar se o cliente está em alguma venda
    for (int i = 0; i < t_vendas; i++) {
        if (strcmp(v_venda[i].cpf_cliente, cpf) == 0) {
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

        if(*t_cliente > 0){
            *cap_cliente = *t_cliente;

            Cliente *temp = (Cliente *) realloc(*v_cliente, (*cap_cliente) * sizeof(Cliente));
            if(temp == NULL){
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
    if (t_clientes == 0) {
        printf("\nNenhum cliente cadastrado para atualizar.\n");
        return;
    }
    if (cancelar_operacao() == 2) {
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
        do {
            printf("\nDigite o novo cpf do cliente (11 digitos): ");
            scanf(" %[^\n]", novo_cpf_cli);
            while (getchar() != '\n');

            if (strcmp(novo_cpf_cli, cliente_achado->cpf_cliente) != 0 &&
                busca_cpf_geral(v_funcionario, t_funcionarios, v_cliente, t_clientes, novo_cpf_cli)) {
                printf("\nErro: Este CPF ja esta cadastrado no sistema!\n");
                verif_cpf_cli = 1;
            } else {
                strcpy(cliente_achado->cpf_cliente, novo_cpf_cli);
                verif_cpf_cli = verificar_cpf_cliente(cliente_achado);
            }
        } while (verif_cpf_cli == 1);

        int verifnomecliente;
        do
        {
            printf("\nDigite o nome atualizado do cliente: ");
            scanf(" %59[^\n]", cliente_achado->nome_cliente);
            char sobra = getchar();
            if (sobra != '\n')
            {
                printf("\nErro: Nome longo demais! Use no maximo 59 caracteres.\n");
                while (getchar() != '\n');
                verifnomecliente = 1;
            }
            else
            {
                verifnomecliente = verificar_nome_cliente(cliente_achado);
                if (verifnomecliente == 1)
                {
                    printf("\nNome Digitado invalido (contem numeros), tente novamente.\n");
                }
            }
        } while (verifnomecliente == 1);

        do {
            printf("\nEscreva o genero (M/F): ");
            scanf(" %1s", cliente_achado->genero_cliente);
            while (getchar() != '\n');

            if (cliente_achado->genero_cliente[0] >= 'a' && cliente_achado->genero_cliente[0] <= 'z') {
                cliente_achado->genero_cliente[0] = cliente_achado->genero_cliente[0] - 32;
            }

            if (cliente_achado->genero_cliente[0] != 'M' && cliente_achado->genero_cliente[0] != 'F') {
                printf("\nErro: Opcao invalida. Digite M ou F.\n");
            }
        } while (cliente_achado->genero_cliente[0] != 'M' && cliente_achado->genero_cliente[0] != 'F');

        printf("\nEscreva o telefone do cliente (somente numeros): ");
        scanf("%11lld", &cliente_achado->telefone_cliente);
        while (getchar() != '\n');
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

//começo vendas========================================================================================================

int menu_vendas()
{
    printf("\nEscolha uma opcao:\n");
    printf("1-Cadastrar Venda\n");
    printf("2-Visualizar Informacoes de Venda\n");
    printf("3-Atualizar Venda\n");
    printf("4-Apagar Venda\n");
    printf("5-Voltar para menu\n");
    int opcao;
    printf("Escolha uma opcao: ");
    scanf(" %d", &opcao);
    return opcao;
}

Venda *busca_venda(Venda *vv, int n, int codigo_alvo, int *Flag){
    *Flag = 1;
    for (int i = 0; i < n; i++){
        if (vv[i].codigo_venda == codigo_alvo){
            *Flag = 0;
            return &vv[i];
        }
    }
    printf("\nErro: Venda nao encontrada, tente novamente\n");
    return NULL;
}

int cadastro_venda(Venda *v_venda, int i, Funcionarios *v_funcionario, int total_fun, Cliente *v_cliente, int total_cli){
    if (cancelar_operacao() == 2){
        printf("\nOperacao de cadastro cancelada.\n");
        return 0;
    }

    int codigo;
    int flag = 0;

    do{
        printf("\nDigite o codigo da venda: ");
        scanf("%d", &codigo);
        while (getchar() != '\n');

        int achou = 0;
        for (int j = 0; j < i; j++){
            if (v_venda[j].codigo_venda == codigo){
                achou = 1;
                break;
            }
        }

        if (achou){
            printf("Erro: ja existe uma venda com esse codigo. Tente outro.\n");
            flag = 1;
        }
        else{
            flag = 0;
        }

    } while (flag == 1);

    v_venda[i].codigo_venda = codigo;

    printf("Digite o valor da venda: ");
    scanf("%f", &v_venda[i].valor_venda);
    while (getchar() != '\n');

    printf("Digite a data (dd mm aaaa): ");
    scanf("%d %d %d", &v_venda[i].dia, &v_venda[i].mes, &v_venda[i].ano);
    while (getchar() != '\n');

    while(1){
        printf("Digite o CPF do funcionario responsavel: ");
        scanf(" %11s", v_venda[i].cpf_funcionario);

        int retorno = busca_cpf_geral(v_funcionario, total_fun, v_cliente, total_cli, v_venda[i].cpf_funcionario);
        if(retorno == 1) break; // Funcionario achado
        else{
            int opcao;
            printf("CPF do Funcionario nao encontrado!\nDeseja cancelar o cadastro? (1-sim/2-nao)");
            scanf("%d", &opcao);
            if(opcao == 1) return 0;
        }
    }

    while(1){
        printf("Digite o CPF do cliente: ");
        scanf(" %11s", v_venda[i].cpf_cliente);

        int retorno = busca_cpf_geral(v_funcionario, total_fun, v_cliente, total_cli, v_venda[i].cpf_cliente);
        if(retorno == 2) break; // Cliente achado
        else{
            int opcao;
            printf("CPF do Cliente nao encontrado!\nDeseja cancelar o cadastro? (1-sim/2-nao)");
            scanf("%d", &opcao);
            if(opcao == 1) return 0;
        }
    }
    
    printf("Digite a hora (hh:mm:ss): ");
    scanf(" %8s", v_venda[i].hora);
    while (getchar() != '\n');

    return 1;
}

void leitura_venda(Venda *v_venda, int t_vendas){
    if (t_vendas == 0){
        printf("\nNenhuma venda cadastrada para visualizar.\n");
        return;
    }
    if (cancelar_operacao() == 2){
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    int codigo_alvo;
    int flag = 0;
    int *Flag = &flag;
    Venda *venda_achada;

    do{
        printf("\nDigite o codigo da venda que deseja ler: ");
        scanf("%d", &codigo_alvo);
        while (getchar() != '\n');
        venda_achada = busca_venda(v_venda, t_vendas, codigo_alvo, Flag);
    } while (flag == 1);
    
    if (flag == 0){
        printf("\nCodigo: %d\n", venda_achada->codigo_venda);
        printf("Valor: %.2f\n", venda_achada->valor_venda);
        printf("CPF do funcionario responsavel: %s\n", venda_achada->cpf_funcionario);
        printf("CPF do cliente: %s\n", venda_achada->cpf_cliente);
        printf("Data: %d/%d/%d\n", venda_achada->dia, venda_achada->mes, venda_achada->ano);
        printf("Hora: %s\n\n", venda_achada->hora);
    }
}

void apagar_venda(Venda **v_venda, int *t_venda, int *cap_venda){

    if (*t_venda == 0){
        printf("\nNenhuma venda cadastrada para apagar.\n");
        return;
    }
    if (cancelar_operacao() == 2){
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    int codigo;
    int flag_busca;
    printf("\nDigite o codigo da venda que deseja remover: ");
    scanf("%d", &codigo);
    while (getchar() != '\n');

    Venda *alvo = busca_venda(*v_venda, *t_venda, codigo, &flag_busca);

    if (alvo != NULL){
        int indice_alvo = alvo - (*v_venda);
        for (int j = indice_alvo; j < (*t_venda - 1); j++){
            (*v_venda)[j] = (*v_venda)[j + 1];
        }

        (*t_venda)--;

        if(*t_venda > 0){
            *cap_venda = *t_venda;

            Venda *temp = (Venda *) realloc(*v_venda, (*cap_venda) * sizeof(Venda));
            if(temp == NULL){
                printf("Erro de memoria\n");
                exit(0);
            }
            *v_venda = temp;
        }
        printf("\nSucesso: Venda removida.\n");
    }
    else{
        printf("\nOperacao de remocao cancelada.\n");
    }
}

void atualizar_infos_venda(Venda *v_venda, int t_vendas, Funcionarios *v_funcionario, int t_funcionarios, Cliente *v_cliente, int t_clientes)
{
    if (t_vendas == 0){
        printf("\nNenhuma venda cadastrada para atualizar.\n");
        return;
    }
    if (cancelar_operacao() == 2){
        printf("\nRetornando ao menu anterior...\n");
        return;
    }

    int codigo_alvo;
    int flag = 0;
    int *Flag = &flag;
    Venda *venda_achada;

    do{
        printf("\nDigite o codigo da venda que deseja atualizar: ");
        scanf("%d", &codigo_alvo);
        while (getchar() != '\n');

        venda_achada = busca_venda(v_venda, t_vendas, codigo_alvo, Flag);

    } while (flag == 1);

    if (flag == 0){
        printf("\nDigite o novo valor da venda: ");
        scanf("%f", &venda_achada->valor_venda);
        while (getchar() != '\n');

        printf("Digite a nova data (dd mm aaaa): ");
        scanf("%d %d %d", &venda_achada->dia, &venda_achada->mes, &venda_achada->ano);
        while (getchar() != '\n');

        while(1){
            printf("Digite o novo CPF do funcionario responsavel: ");
            scanf(" %11s", venda_achada->cpf_funcionario);

            int retorno = busca_cpf_geral(v_funcionario, t_funcionarios, v_cliente, t_clientes, venda_achada->cpf_funcionario);
            if(retorno == 1) break;
            else printf("CPF nao pertence a um Funcionario. Tente de novo.\n");
        }

        while(1){
            printf("Digite o novo CPF do cliente: ");
            scanf(" %11s", venda_achada->cpf_cliente);

            int retorno = busca_cpf_geral(v_funcionario, t_funcionarios, v_cliente, t_clientes, venda_achada->cpf_cliente);
            if(retorno == 2) break;
            else printf("CPF nao pertence a um Cliente. Tente de novo.\n");
        }

        printf("Digite a nova hora (hh:mm:ss): ");
        scanf(" %9s", venda_achada->hora);
        while (getchar() != '\n');

        printf("\nSucesso: Venda atualizada!\n");
    }
}