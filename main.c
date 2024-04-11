#include "arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "Interface.h"
#include "OpcoesMenu.h"


int main (){
    // Abre o arquivo para inicialização do projeto.
    FILE*fp;
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
    // Primeira tela, interface do programa.
    textcoloreback(RED,BLACK);
    Superkilo();
    int Opcao, codigo, confirmacao;
    Funcionario F;
    // Variáveis necessárias de entrada
    do
    {
        textcoloreback(RED,BLACK);
        system ("CLS");
        Opcao=MenuInicial();
        {
            if (Opcao == 1)
            {
            AtivarCadastro(); // Chama a função AtivarCadastro() para inserir ou listar funcionários
        }
                        else if( Opcao == 5){
            ListarCadastro(); // Chama a função AtivarCadastro() para inserir ou listar funcionários
        }
         else if(Opcao == 6)
            {
                gotoxy(11,13);
                printf("\n          Saindo...\n");
                getchar();
            }
            else if(Opcao == 2)
            {
                Caixa(10,8,62,3,1);
                gotoxy(12,10);
                printf("Digite o codigo do funcionario:\n");
                gotoxy(44,10);
                scanf("%d", &codigo);
                F=PesquisarCadastro(codigo);
                if(F.Codigo== -1)
                {
                    Caixa(10,8,62,3,1);
                    gotoxy(31,10);
                    printf("Codigo nao encontrado!!!\n");
                    gotoxy(1,20);
                    system("Pause");
                }
                else
                {
                    TelaCadastro();
                    ImprimirCadastro(F);
                    gotoxy(12,28);
                    system("Pause");
                }
            }
            else if(Opcao == 3)
            {
                Caixa(10,8,62,3,1);
                gotoxy(12,10);
                printf("Digite o codigo do funcionario:\n");
                gotoxy(44,10);
                scanf("%d", &codigo);
                F=PesquisarCadastro(codigo);
                if(F.Codigo== -1)
                {
                    Caixa(10,8,62,3,1);
                    gotoxy(31,10);
                    printf("Codigo nao encontrado!!!\n");
                    gotoxy(1,20);
                    system("Pause");
                }
                else
                {
                    TelaCadastro();
                    ImprimirCadastro(F);
                    Caixa(10,27,90,1,1);
                    gotoxy(15,28);
                    printf("Tem certeza que deseja alterar?\n");
                    int resposta=CaixaExcluir();
                    if(resposta==1)
                    {
                        system("CLS");
                        TelaCadastro();
                        DigitarCadastro();
                        F=AlterarCadastro(codigo);
                    }
                    else getchar();
                }
            }
            else if(Opcao == 4)
            {
                Caixa(10,8,62,3,1);
                gotoxy(12,10);
                printf("Digite o codigo do funcionario:\n");
                gotoxy(44,10);
                scanf("%d", &codigo);
                F=PesquisarCadastro(codigo);
                if(F.Codigo== -1)
                {
                    Caixa(10,8,62,3,1);
                    gotoxy(31,10);
                    printf("Codigo nao encontrado!!!\n");
                    gotoxy(1,20);
                    system("Pause");
                }
                else{
                    TelaCadastro();
                    ImprimirCadastro(F);
                    Caixa(10,27,90,1,1);
                    gotoxy(15,28);
                    printf("Tem certeza que deseja excluir?\n");
                    confirmacao=CaixaExcluir();
                    if(confirmacao == 1)
                    {
                        F=ExcluirCadastro(codigo);
                    }

                }
            }
            }
        }while (Opcao != 6);
    fclose(fp);
    return 0;
}
