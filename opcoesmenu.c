#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include "Interface.h"
#include "OpcoesMenu.h"
FILE*fp;
struct CadastroFuncionarios funcionario;
void TelaCadastro()
{
    Caixa(10,5,90,20,1);
    gotoxy(15,8);
    printf("CODIGO:");
    Caixa(22,7,10,1,0);
    gotoxy(15,11);
    printf("NOME:");
    Caixa(20,10,45,1,0);
    gotoxy(15,14);
    printf("CPF:");
    Caixa(19,13,20,1,0);
    gotoxy(50,14);
    printf("DATA DE NASCIMENTO:");
    Caixa(69,13,20,1,0);
    gotoxy(15,17);
    printf("TELEFONE:");
    Caixa(24,16,20,1,0);
    gotoxy(50,17);
    printf("EMAIL:");
    Caixa(56,16,34,1,0);
    gotoxy(15,20);
    printf("ENDERECO:");
    Caixa(24,19,45,1,0);
    gotoxy(15,23);
    printf("CARGO:");
    Caixa(21,22,25,1,0);
    gotoxy(50,23);
    printf("SALARIO:");
    Caixa(58,22,15,1,0);
}

Funcionario DigitarCadastro()
{
    Funcionario F;
    gotoxy(23,8);
    scanf("%d",&F.Codigo);
    gotoxy(21,11);
    getchar();
    scanf("%[^\n]", F.Nome);
    gotoxy(20,14);
    scanf("%s", F.CPF);
    gotoxy(70,14);
    scanf("%s", F.DataNascimento);
    gotoxy(25,17);
    scanf("%s", F.Telefone);
    gotoxy(57,17);
    getchar();
    scanf("%s", F.Email);
    gotoxy(25,20);
    getchar();
    scanf("%[^\n]", F.Endereco);
    gotoxy(22,23);
    getchar();
    scanf("%[^\n]", F.Cargo);
    gotoxy(59,23);
    scanf("%lf",&F.Salario);
    return F;
}


void ImprimirCadastro(Funcionario F)
{
    printf("\n");
    gotoxy(23,8);
    printf("%04d", F.Codigo);
    gotoxy(21,11);
    printf("%s", F.Nome);
    gotoxy(20,14);
    printf("%s", F.CPF);
    gotoxy(70,14);
    printf("%s", F.DataNascimento);
    gotoxy(25,17);
    printf("%s", F.Telefone);
    gotoxy(57,17);
    printf("%s", F.Email);
    gotoxy(25,20);
    printf("%s", F.Endereco);
    gotoxy(22,23);
    printf("%s", F.Cargo);
    gotoxy(59,23);
    printf("R$ %.2lf", F.Salario);
    getchar();
}

Funcionario PesquisarCadastro(int codigo) {
    Funcionario F;
    int encontrado = 0;

    rewind(fp);
    while (fread(&F, sizeof(Funcionario), 1, fp) == 1) {
        if (F.Codigo == codigo) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        return F;
    } else {
        F.Codigo = -1; // Código indicativo de que não foi encontrado
        return F;
    }
}

Funcionario AlterarCadastro(int codigo) {
    FILE *tempFP;
    Funcionario F;
    tempFP = fopen("temp.txt", "wb+");

    if (tempFP == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        exit(1);
    }

    // Copiar todos os registros, exceto o que será alterado
    rewind(fp);
    while (fread(&F, sizeof(Funcionario), 1, fp) == 1) {
        if (F.Codigo != codigo) {
            fwrite(&F, sizeof(Funcionario), 1, tempFP);
        }
    }

    // Adicionar o novo registro
    TelaCadastro();
    DigitarCadastro();
    F.Codigo = codigo;
    fwrite(&F, sizeof(Funcionario), 1, tempFP);

    // Fechar os arquivos
    fclose(fp);
    fclose(tempFP);

    // Renomear o arquivo temporário para substituir o original
    remove("Trabalho.txt");
    rename("temp.txt", "Trabalho.txt");

    // Reabrir o arquivo principal
    fp = fopen("Trabalho.txt", "rb+");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo principal.\n");
        exit(1);
    }

    return F;
}

Funcionario ExcluirCadastro(int codigo) {
    Funcionario F;
    fseek(fp, 0, SEEK_SET);

    while (fread(&F, sizeof(Funcionario), 1, fp)) {
        if (F.Codigo == codigo) {
            F.Codigo = -1;
            fseek(fp, -sizeof(Funcionario), SEEK_CUR);
            fwrite(&F, sizeof(Funcionario), 1, fp);
            break; // Saia do loop após encontrar e excluir o cadastro
        }
    }

    // Fechar o arquivo uma vez após o loop
    fclose(fp);

    // Renomear o arquivo temporário para substituir o original
    remove("Trabalho.txt");
    rename("temp.txt", "Trabalho.txt");

    // Reabrir o arquivo principal
    fp = fopen("Trabalho.txt", "rb+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo principal.\n");
        exit(1);
    }

    return F; // Retorne F após reabrir o arquivo
}


int CarregarFuncionarios() {
    struct CadastroFuncionarios F;  // Corrigir o tipo da estrutura

    fseek(fp, 0, SEEK_SET);

    // Cabeçalho da tabela
    printf("%-10s%-40s\n", "Código", "Nome");
    printf("----------------------------------------\n");

    int n = 0;
    while (fread(&F, sizeof(struct CadastroFuncionarios), 1, fp)) {
        if (F.Codigo != -1) {
            // Exibir linha da tabela com código e nome
            printf("%-10d%-40s\n", F.Codigo, F.Nome);
            n++;
        }
    }

    // Rodapé da tabela
    printf("----------------------------------------\n");

    return n;
}


void InserirCadastro(Funcionario F)
{
    fp=fopen("Trabalho.txt", "rb+");
    if(fp==NULL)
    {
        fp=fopen("Trabalho.txt", "wb+");
        if(fp==NULL)
        {
            printf("Erro em Trabalho.txt\n");
            exit(1);
        }
    }
    fseek(fp, 0, SEEK_END);
    fwrite(&F, sizeof(Funcionario), 1, fp);
    fclose(fp);
}

void Listarmanos(Funcionario F)
{
    system("CLS");
    TelaCadastro();
    gotoxy(23,8);
    printf("%04d", F.Codigo);
    gotoxy(21,11);
    printf("%s", F.Nome);
    gotoxy(20,14);
    printf("%s", F.CPF);
    gotoxy(70,14);
    printf("%s", F.DataNascimento);
    gotoxy(25,17);
    printf("%s", F.Telefone);
    gotoxy(57,17);
    printf("%s", F.Email);
    gotoxy(25,20);
    printf("%s", F.Endereco);
    gotoxy(22,23);
    printf("%s", F.Cargo);
    gotoxy(59,23);
    printf("R$ %.2lf", F.Salario);
    getchar();
}

void ListarCadastro()
{
    fp=fopen("Trabalho.txt", "rb+");
    if(fp==NULL)
    {
        fp = fopen("Trabalho.txt", "wb+");
        if(fp==NULL)
        {
            printf("Erro em Trabalho.txt\n");
            exit(1);
        }
    }
    Funcionario F;
    fseek(fp, 0, SEEK_SET);
    while (fread(&F, sizeof(F), 1, fp))
    {
        if (F.Codigo != -1)
        {
            CarregarFuncionarios();
            Caixa(9, 9, 60, 8, 0);
            Listarmanos(F);
            printf("\n\n");
        }
    }
}


int MenuInicial()
{
    Caixa(10,8,62,3,1);
    int x[] = {14,22,35,45,55,65};
    int y[] = {10,10,10,10,10,10};
    char Opcoes[][20] = {"NOVO", "PESQUISAR", "ALTERAR", "EXCLUIR", "LISTAR", "SAIR"};
    int Opcao = Menu(x,y,Opcoes,6);
    if(Opcao==0)
        return 1;
    else if(Opcao==1)
        return 2;
    else if(Opcao==2)
        return 3;
    else if(Opcao==3)
        return 4;
    else if(Opcao==4)
        return 5;
    else if(Opcao==5)
        return 6;
return 0;
}


int CaixaExcluir()
{
    int x[] = {47,53};
    int y[] = {28,28};
    char Opcoes[][20] = {"SIM", "NAO"};
    int Opcao = Menu(x,y,Opcoes,2);
    if(Opcao==0)
        return 1;
    else if(Opcao==1)
        return 2;
    return 0;
}
