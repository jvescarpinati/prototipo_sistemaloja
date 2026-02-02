#include <stdio.h>
typedef struct
{
    char cpf_cliente[12];
    char nome_cliente[60];
    long long int telefone_cliente;
    char genero_cliente[2]; // M (masculino) ou F(feminino)
} Cliente;
