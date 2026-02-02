typedef struct
{
    char cpf_funcionario[12];
    char nome_funcionario[60];
    float salario_funcionario;
    char cargo_funcionario[30];

} Funcionarios;

int menu_funcionarios();

int verificar_nome_fun(Funcionarios *funci);

int verificar_cpf_fun(Funcionarios *funci);

int verificar_cargo_fun(Funcionarios *func);

void cadastro_funcio(Funcionarios *fim);

void apagar_funcionario(Funcionarios *inicio, Funcionarios **fim);

Funcionarios *busca_funcionario(Funcionarios *inicio, Funcionarios *fim, char cpf_achar[12], int *Flag);

void ler_info_func(Funcionarios *inicio, Funcionarios *fim);

void atualizar_infos_funcionarios(Funcionarios *inicio, Funcionarios *fim);

