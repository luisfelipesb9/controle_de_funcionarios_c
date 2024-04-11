#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "Interface.h"
#include "OpcoesMenu.h"
#include <conio.h>

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Caixa(int x, int y, int Largura, int Altura, int Tipo)
{
    int i, j;
    unsigned char C[][6] = {{218, 196, 191, 179, 192, 217},
        {201, 205, 187, 186, 200, 188}
    };
    gotoxy(x, y);
    printf("%c", C[Tipo][0]);
    for(i = 0; i < Largura; i++) printf("%c", C[Tipo][1]);
    printf("%c", C[Tipo][2]);
    for(j = 0; j < Altura; j++)
    {
        gotoxy(x, y + j + 1);
        printf("%c", C[Tipo][3]);
        for(i = 0; i < Largura; i++) printf(" ");
        printf("%c", C[Tipo][3]);
    }
    gotoxy(x, y + j + 1);
    printf("%c", C[Tipo][4]);
    for(i = 0; i < Largura; i++) printf("%c", C[Tipo][1]);
    printf("%c", C[Tipo][5]);
}

void textcoloreback (int letras, int fundo) /*para mudar a cor de fundo mude o background*/
{
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),letras + (fundo << 4));
}

int Menu(int x[], int y[], char Opcoes[][20], int n)
{
    int i, Opcao = 0, Tecla;
    tipocursor(0);
    textcoloreback(LIGHT_GRAY, BLACK);
    for (i = 0; i < n; i++)
    {
        gotoxy(x[i], y[i]);
        printf("%s", Opcoes[i]);
    }
    do
    {
        textcoloreback(BLACK, BROWN);
        gotoxy(x[Opcao], y[Opcao]);
        printf("%s", Opcoes[Opcao]);
        Tecla = getTecla();
        textcoloreback(LIGHT_GRAY, BLACK);
        gotoxy(x[Opcao], y[Opcao]);
        printf("%s", Opcoes[Opcao]);
        if(Tecla == TEC_ESQ) Opcao--;
        if(Tecla == TEC_DIR) Opcao++;
        if(Tecla == TEC_CIMA) Opcao--;
        if(Tecla == TEC_BAIXO) Opcao++;
        if(Tecla == TEC_ENTER)
        {
            tipocursor(1);
            return Opcao;
        }
        if(Opcao < 0) Opcao = n - 1;
        if(Opcao >= n) Opcao = 0;
    }
    while(Tecla != TEC_ESC);
    tipocursor(1);
    return -1;
}

int getTecla()
{
    int ch;
    ch = getch();
    if(ch == 224)
    {
        ch = getch() + 1000;
    }
    return ch;
}

void tipocursor (int cursor)
{
    HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CURSOR;
    BOOL result;
    CURSOR.dwSize = 1;
    if(cursor == 0)
        CURSOR.bVisible = FALSE;
    else
        CURSOR.bVisible = TRUE;
    result=SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}


int Selecao(int x, int y, int Largura, int Altura, char Opcoes[][100], int n)
{
    int i, Opcao = 0, Tecla, Primeiro = 0;
    tipocursor(0);
    textcoloreback(LIGHT_GRAY, BLACK);
    for (i = 0; i < Altura && i < n; i++)
    {
        gotoxy(x, y + i);
        printf("%*s", -Largura, Opcoes[i + Primeiro]);
    }
    do
    {
        textcoloreback(BLACK, BROWN);
        gotoxy(x, y + Opcao - Primeiro);
        printf("%*s", -Largura, Opcoes[Opcao]);
        Tecla = getTecla();
        textcoloreback(LIGHT_GRAY, BLACK);
        gotoxy(x, y + Opcao - Primeiro);
        printf("%*s", -Largura, Opcoes[Opcao]);
        if(Tecla == TEC_ESQ) Opcao--;
        if(Tecla == TEC_DIR) Opcao++;
        if(Tecla == TEC_CIMA) Opcao--;
        if(Tecla == TEC_BAIXO) Opcao++;
        if(Tecla == TEC_ENTER)
        {
            tipocursor(1);
            return Opcao;
        }
        if(Opcao < 0) Opcao = 0;//n - 1;
        if(Opcao >= n) Opcao = n-1;//0;
        if(Opcao - Primeiro < 0 || Opcao >= Altura + Primeiro)
        {
            if(Opcao - Primeiro < 0) Primeiro--;
            else Primeiro++;
            for (i = 0; i < Altura && i < n; i++)
            {
                gotoxy(x, y + i);
                printf("%*s", -Largura, Opcoes[i + Primeiro]);
            }
        }
    }
    while(Tecla != TEC_ESC);
    tipocursor(1);
    return -1;
}

void AtivarCadastro() {
    int Opcao;
    Funcionario F;
    Opcao = MenuInicial(); // Obtém a opção do menu inicial

    if (Opcao == 1) {
        // Código para inserir um novo funcionário
        TelaCadastro();
        F = DigitarCadastro();
        InserirCadastro(F);
    } else if (Opcao == 5) {
        // Código para listar os funcionários
        ListarCadastro();
    } else {
        // Código para pesquisar um funcionário pelo código
        char Opcoes[100][100];
        int n = CarregarFuncionarios(Opcoes);
        Caixa(9, 9, 60, 8, 0);
        int p = Selecao(10, 10, 60, 8, Opcoes, n);
        TelaCadastro();
        int Codigo;
        sscanf(Opcoes[p], "%d", &Codigo);
        F = PesquisarCadastro(Codigo);
        ImprimirCadastro(F);
    }
}
