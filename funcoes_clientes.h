typedef struct
{
    char cpf_cliente[12];
    char nome_cliente[60];
    long long int telefone_cliente;
    char genero_cliente[2]; // M (masculino) ou F(feminino)
} Cliente;

int menu_clientes();

void cadastro_cliente(Cliente *fim_cliente);

int verificar_cpf_cliente(Cliente *cliente);

void leitura_cliente(Cliente *inicio, Cliente *fim);

void apagar_cliente(Cliente *inicio, Cliente **fim);

Cliente *busca_cliente(Cliente *inicio, Cliente *fim, char cpf_alvo[12], int *Flag);

void atualizar_infos_cliente(Cliente *inicio, Cliente *fim);

int verificar_nome_cliente(Cliente *cli);