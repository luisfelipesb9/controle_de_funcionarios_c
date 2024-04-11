#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

struct CadastroFuncionarios
{
    int Codigo;
    char Nome[51];
    char CPF[15];
    char DataNascimento[11];
    char Telefone[14];
    char Email[31];
    char Endereco[51];
    char Cargo[21];
    double Salario;

};

void Listarmanos();
typedef struct CadastroFuncionarios Funcionario;
void ImprimirCadastro(Funcionario F);
Funcionario DigitarCadastro();
Funcionario PesquisarCadastro(int Codigo);
void InserirCadastro(Funcionario F);
Funcionario AlterarCadastro(int Codigo);
Funcionario ExcluirCadastro(int Codigo);
void ListarCadastro();
void TelaCadastro();
int MenuInicial();
int CaixaExcluir();
int CarregarFuncionarios();

#endif // FUNCOES_H_INCLUDED
