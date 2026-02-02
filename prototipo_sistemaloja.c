#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*   printf("\n");
    int opcao_cancelar;
    do{
        opcao_cancelar=cancelar_operacao();
        if (opcao_cancelar!=1 && opcao_cancelar!=2) {
            printf("Opcao invalida! Tente novamente.\n\n");
        }
    }while(opcao_cancelar!=1 && opcao_cancelar!=2);
    
    if(opcao_cancelar==2) return 0;
    else{*/

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
    char data[10];
    char hora[8];

} Venda;

int menu_geral();

int cancelar_operacao();

/*Comeco funcionario==================================================================================================================================================*/

int menu_funcionarios();

int verificar_nome_fun(Funcionarios *funci);

int verificar_cpf_fun(Funcionarios *funci);

int verificar_cargo_fun(Funcionarios *func);

int cadastro_funcio(Funcionarios *fim);

void apagar_funcionario(Funcionarios *inicio, Funcionarios **fim);

Funcionarios *busca_funcionario(Funcionarios *inicio, Funcionarios *fim, char cpf_achar[12], int *Flag);

void ler_info_func(Funcionarios *inicio, Funcionarios *fim);

void atualizar_infos_funcionarios(Funcionarios *inicio, Funcionarios *fim);

/*Fim funcionario=====================================================================================================================================

Começo clientes=====================================================================================================================================*/

int menu_clientes();

int cadastro_cliente(Cliente *fim_cliente);

int verificar_cpf_cliente(Cliente *cliente);

void leitura_cliente(Cliente *inicio, Cliente *fim);

void apagar_cliente(Cliente *inicio, Cliente **fim);

Cliente *busca_cliente(Cliente *inicio, Cliente *fim, char cpf_alvo[12], int *Flag);

void atualizar_infos_cliente(Cliente *inicio, Cliente *fim);

int verificar_nome_cliente(Cliente *cli);

int main()
{
    int opcao_geral;

    Funcionarios funcionarios[5], *inicio_funcionario, *fim_funcionario;
    inicio_funcionario = funcionarios;
    fim_funcionario = inicio_funcionario;

    Cliente clientes[5], *inicio_cliente, *fim_cliente;
    inicio_cliente = &clientes[0];
    fim_cliente = inicio_cliente;


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
                    if (fim_funcionario < (inicio_funcionario + 5))
                    {
                        if(cadastro_funcio(fim_funcionario)==1){
                            printf("\n");
                            fim_funcionario++;
                        }
                    }
                }
                else if (opcao_funcionario == 2)
                {
                    ler_info_func(inicio_funcionario, fim_funcionario);
                }
                else if (opcao_funcionario == 3)
                {
                    atualizar_infos_funcionarios(inicio_funcionario, fim_funcionario);
                }
                else if (opcao_funcionario == 4)
                {
                    apagar_funcionario(inicio_funcionario, &fim_funcionario);
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
                    if(fim_cliente<(inicio_cliente+5)){
                        if(cadastro_cliente(fim_cliente)==1){
                        printf("\n");
                        fim_cliente++;
                        }
                    }
                }

                if(opcao_cliente==2){
                    leitura_cliente(inicio_cliente, fim_cliente);
                }

                if(opcao_cliente==3){
                    atualizar_infos_cliente(inicio_cliente, fim_cliente);
                }

                if(opcao_cliente==4){
                    apagar_cliente(inicio_cliente, &fim_cliente);
                }

            } while (opcao_cliente != 5);
            
            break;
        }
        
    }
}
while (opcao_geral != 8)
    ;

printf("\n\nSaindo do Programa...\n\n");

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
// Comeco funcionario==================================================================================================================================================*/

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

int cadastro_funcio(Funcionarios *fim){
    if(cancelar_operacao() == 2) {
        printf("Operacao de cadastro abortada.\n");
        return 0;
    }

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

    return 1;
}

void apagar_funcionario(Funcionarios *inicio, Funcionarios **fim)
{
    if (inicio == fim) {
        printf("Nenhum funcionario cadastrado para apagar.\n");
        return; 
    }
    if (cancelar_operacao() == 2) {
        printf("Retornando ao menu anterior...\n");
        return;
    }

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
    if (inicio == fim) {
        printf("Nenhum funcionario cadastrado para visualizar.\n");
        return; 
    }
    if (cancelar_operacao() == 2) {
        printf("Retornando ao menu anterior...\n");
        return;
    }

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
    if (inicio == fim) {
        printf("Nenhum funcionario cadastrado para atualizar.\n");
        return; 
    }
    if (cancelar_operacao() == 2) {
        printf("Retornando ao menu anterior...\n");
        return;
    }

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

// Fim funcionario=====================================================================================================================================
// Começo cliente======================================================================================================================================

int menu_clientes()
{   
    printf("Escolha uma opcao:\n");
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

int cadastro_cliente(Cliente *fim_cliente) {
    
   if(cancelar_operacao() == 2) {
        printf("Operacao de cadastro abortada.\n");
        return 0;
    }

    printf("\nEscreva o nome do Cliente: ");
    scanf(" %59[^\n]", fim_cliente->nome_cliente);
    while (getchar() != '\n');

    int verif_cpf_cli = 0;
    do {
        printf("Escreva o cpf do cliente (somente 11 numeros): ");
        scanf(" %11s", fim_cliente->cpf_cliente);
        while (getchar() != '\n');

        verif_cpf_cli = verificar_cpf_cliente(fim_cliente);
        
        if (verif_cpf_cli == 1) {
            printf("CPF Invalido, tente novamente.\n");
        }
    } while (verif_cpf_cli == 1);

    printf("Escreva o telefone do cliente (somente numeros): ");
    scanf("%11lld", &fim_cliente->telefone_cliente);
    while (getchar() != '\n');

    do {
        printf("Escreva o genero (M/F): ");
        scanf(" %1s", fim_cliente->genero_cliente);
        while (getchar() != '\n');
        
        if (fim_cliente->genero_cliente[0] >= 'a' && fim_cliente->genero_cliente[0] <= 'z') {
            fim_cliente->genero_cliente[0] = fim_cliente->genero_cliente[0] - 32;
        }
        
        if (fim_cliente->genero_cliente[0] != 'M' && fim_cliente->genero_cliente[0] != 'F') {
            printf("Erro: Opcao invalida. Digite M ou F.\n");
        }
    } while (fim_cliente->genero_cliente[0] != 'M' && fim_cliente->genero_cliente[0] != 'F');

    printf("\nSucesso: Cliente cadastrado!\n");
    
    return 1;
}

void leitura_cliente(Cliente *inicio, Cliente *fim){

    if (inicio == fim) {
        printf("Nenhum cliente cadastrado para visualizar.\n");
        return; 
    }
    if (cancelar_operacao() == 2) {
        printf("Retornando ao menu anterior...\n");
        return;
    }

    char cpf_alvo[12];
    int flag = 0;
    int *Flag = &flag;
    Cliente *cliente_achado;
    do{
        printf("\nDigite o cpf (somente numeros sem barras ou tracos) do cliente que deseja ler os dados do cadastro: ");
        scanf(" %[^\n]", cpf_alvo);
        cliente_achado = busca_cliente(inicio, fim, cpf_alvo, Flag);
    } while (flag == 1);
    if (flag == 0){
        printf("\nNome: %s\n", cliente_achado->nome_cliente);
        printf("Cpf: %s\n", cliente_achado->cpf_cliente);
        printf("Telefone: %lld\n", cliente_achado->telefone_cliente);
        if(*cliente_achado->genero_cliente == 'M' || *cliente_achado->genero_cliente == 'm') printf("Genero: Masculino\n\n");
        else printf("Genero: Feminino\n\n");
    }
}  

Cliente *busca_cliente(Cliente *inicio, Cliente *fim, char cpf_alvo[12], int *Flag){
    Cliente *cliente_achado;
    *Flag=0;

    for(Cliente *i=inicio; i<fim; i++){
        if(strcmp(i->cpf_cliente, cpf_alvo)==0){
            cliente_achado=i;
            return cliente_achado;
        }
    }
    printf("\nErro: Cliente nao encontrado, tente novamente\n");
    *Flag=1;
    return NULL;
}

void apagar_cliente(Cliente *inicio, Cliente **fim){

    if (inicio == fim) {
        printf("Nenhum cliente cadastrado para apagar.\n");
        return; 
    }
    if (cancelar_operacao() == 2) {
        printf("Retornando ao menu anterior...\n");
        return;
    }

    char cpf[12];
    int flag_busca;
    printf("Digite o cpf do cliente que deseja remover: ");
    scanf("%s", cpf);

    Cliente *alvo = busca_cliente(inicio, *fim, cpf, &flag_busca);

    if (alvo != NULL)
    {
        Cliente *cliente;
        for (cliente = alvo; cliente < (*fim - 1); cliente++)
        {
            *cliente = *(cliente + 1);
        }

        (*fim)--;
        printf("\nSucesso: Cliente removido.\n");
    }

    else
        printf("\nOperacao de remocao cancelada.\n");
}

void atualizar_infos_cliente(Cliente *inicio, Cliente *fim)
{

    if (inicio == fim) {
        printf("Nenhum cliente cadastrado para atualizar.\n");
        return; 
    }
    if (cancelar_operacao() == 2) {
        printf("Retornando ao menu anterior...\n");
        return;
    }

    char cpf_achar[12];
    int flag = 0;
    int *Flag = &flag;
    Cliente *cliente_achado;
    do
    {
        printf("\nDigite o cpf do cliente que deseja atualizar os dados do cadastro (somente numeros sem barras ou tracos): ");
        scanf(" %[^\n]", cpf_achar);
        cliente_achado = busca_cliente(inicio, fim, cpf_achar, Flag);
    } while (flag == 1);
    if (flag == 0)
    {
        int verifnomecliente;
        do
        {
            printf("\nDigite o nome atualizado do cliente: ");
            scanf(" %59[^\n]", cliente_achado->nome_cliente);
            char sobra = getchar();
            if (sobra != '\n')
            {
                printf("\nErro: Nome longo demais! Use no maximo 59 caracteres.\n");
                while (getchar() != '\n')
                    ;
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

    }

    do {
        printf("Escreva o genero (M/F): ");
        scanf(" %1s", cliente_achado->genero_cliente);
        while (getchar() != '\n');
        
        if (cliente_achado->genero_cliente[0] >= 'a' && cliente_achado->genero_cliente[0] <= 'z') {
            cliente_achado->genero_cliente[0] = cliente_achado->genero_cliente[0] - 32;
        }
        
        if (cliente_achado->genero_cliente[0] != 'M' && cliente_achado->genero_cliente[0] != 'F') {
            printf("Erro: Opcao invalida. Digite M ou F.\n");
        }
    } while (cliente_achado->genero_cliente[0] != 'M' && cliente_achado->genero_cliente[0] != 'F');

    printf("Escreva o telefone do cliente (somente numeros): ");
    scanf("%11lld", &cliente_achado->telefone_cliente);
    while (getchar() != '\n');

    printf("\n");
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