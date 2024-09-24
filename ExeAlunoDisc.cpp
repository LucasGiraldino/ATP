#include <stdio.h>
#include "conio.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TF 5

struct TpAluno
{
    char RA[13];
    char Nome[30];
};

struct TpDisciplina
{
    int CodDisc;
    char Disciplina[20];
};

struct TpNota
{
    char RA[13];
    int CodDisc;
    float Nota;
};
void Executar (void);
char Escolha (void);

// FUNÇOES DE MENU
char MenuAluno (void);
char MenuNota(void);
char MenuDisciplina (void);
char MenuOrdena(char op, int TL);
char MenuConfirmaAltera (void);

// FUNCOES DE VERIFICACAO
int VerificaAluno (TpAluno Vet[TF], int TL, char Aux[], int deci);
int VerificaDisciplina (TpDisciplina Vet[TF], int TL, int Aux, int deci);
int VerificaNota (TpNota Vet[TF], int TL, char RaAux[13], int CodAux, int deci);

// FUNCOES DE CADADTRO
void CadastraAluno (TpAluno Vet[TF], int &TL, char Aux[]);
void CadastrarNota (TpNota VetNota[TF], int &TLNota, TpAluno VetAluno[TF], int TLAluno, TpDisciplina VetDisc[TF], int TLDisc);

// MENSAGEM DE VETOR CHEIO
void CadCheio (int decisao);

// FUNCOES DE EXIBIR VETOR
void ExibirAluno (TpAluno Vetor[TF], int Tl);

// FUNCOES DE ORDENAR
void OrdenarAluno (TpAluno Vetor[TF], int TL, char op);

// FUNCAO PRA CRIAR UM AUX
void CriaRAAux(char Aux[]);
void CriaDiscAux (int &Aux);

// FUNCOES DE ALTERAR DADOS
void AlterarAluno (TpAluno Vetor[TF], int TL);

// FUNCAO DE EXCLUIR 
void ExcluirAluno (TpAluno Vet[TF], int &TL);

int main (void)
{
    clrscr();
    textcolor(WHITE);
    Executar();
    return 0;
}

void Executar (void)
{
    int TLAluno=0, TLDisc=0, TLNotas=0, CodAux;
    char opEscolha, op, RAaux[13], opAux;
    TpAluno Alunos[TF];
    TpDisciplina Disciplina[TF];
    TpNota Notas[TF];
    do
    {
        opEscolha = Escolha();
        switch (opEscolha)
        {
            case 'A':
                clrscr();   
                do 
                {
                    textcolor(WHITE);
                    op = MenuAluno();
                    switch (op)
                    {
                        case 'A':
                            clrscr();
                            if (TLAluno < TF)
                            {
                                CriaRAAux(RAaux);
                                while (TLAluno < TF && strcasecmp(RAaux, "\0") != 0)
                                {
                                    if (!VerificaAluno(Alunos, TLAluno, RAaux, 1))  
                                        CadastraAluno(Alunos, TLAluno, RAaux);
                                    else
                                    {
                                        textcolor(RED);
                                        printf ("ALNUO JA CADASTRADO!!\n");
                                        textcolor(WHITE);
                                    }
                                    if (TLAluno == TF)
                                        CadCheio(1);
                                    else 
                                        CriaRAAux(RAaux);
                                }
                            }
                            else    
                                CadCheio(1);
                            getch();
                            break;
                        case 'B':
                            clrscr();
                            ExibirAluno(Alunos, TLAluno);
                            getch();
                            break;
                        case 'C':
                            clrscr();
                            opAux = MenuOrdena(1, TLAluno);
                            OrdenarAluno(Alunos, TLAluno, opAux);
                            getch();
                            break;
                        case 'D':
                            clrscr();
                            AlterarAluno(Alunos, TLAluno);
                            getch ();
                            break;
                        case 'E':
                            clrscr ();
                            ExcluirAluno(Alunos, TLAluno);
                            getch();
                            break;
                    } 
                } while (op != 27);
                getch();
                break;
            case 'B':
                clrscr();
                do 
                {
                    textcolor(WHITE);
                    op = MenuDisciplina();
                    switch (op)
                    {
                        case 'A':
                            clrscr();
                            getch();
                            break;
                        case 'B':
                            clrscr();
                            getch();
                            break;
                        case 'C':
                            clrscr();
                            getch();
                            break;
                    }
                } while (op != 27);
                getch();
                break;
                case 'C':
                    clrscr();
                    do 
                    {
                        op = MenuNota();
                        switch (op)
                        {
                            case 'A':
                                clrscr();
                                CadastrarNota(Notas, TLNotas, Alunos, TLAluno, Disciplina, TLDisc);
                                getch();
                                break;
                        }
                    } while (op != 27);
                    break;
        }
    } while (opEscolha != 27);
}


char Escolha (void)
{
    printf ("------------ MENU ESCOLHA -----------\n");
    printf ("[A] - Alnuos\n");
    printf ("[B] - Disciplinas\n");
    printf ("[C] - Notas de Alunos\n");
    return toupper(getche());
}

char MenuAluno (void)
{
    printf ("------------ MENU ALUNO ------------\n");
    printf ("[A] - Cadastrar Aluno\n");
    printf ("[B] - Exibir Alunos\n");
    printf ("[C] - Ordenar Alunos\n");
    printf ("[D] - Alterar Nome de Aluno\n");
    printf ("[E] - Excluir Aluno\n");
    return toupper(getche());
}

char MenuDisciplina (void)
{
    printf ("------------ MENU DISCIPLINA ------------\n");
    printf ("[A] - Cadastrar Disciplina\n");
    printf ("[B] - Exibir Disciplinas\n");
    printf ("[C] - Ordenar Disciplinas\n");
    printf ("[D] - Alterar dados de Disciplinas\n");
    printf ("[E] - Excluir Disciplina\n");
    return toupper(getche());
}

char MenuNota(void)
{
    printf ("------------ MENU NOTAS ------------\n");
    printf ("[A] - Cadastrar Nota\n");
    printf ("[B] - Exibir nota\n");
    printf ("[C] - Alterar Notas\n");
    printf ("[D] - Excluir Notas\n");
    return toupper(getch());
}

void Ordenar (TpAluno Vetor[TF], int TL, char op)
{
    int i, j;
    TpAluno VetAux;
    clrscr();
    switch(op)
    {
        case 'A':
            for(i=0;i<TL;i++)
                for (j=i+1;j<TL;j++)
                    if (strcasecmp(Vetor[i].RA, Vetor[j].RA) > 0)
                    {
                        VetAux = Vetor[i];
                        Vetor[i] = Vetor[j];
                        Vetor[j] = VetAux;
                    }
            textcolor(GREEN);
            printf ("DADOS ORDENADOS!!\n");
            break;
        case 'B':
            for (i=0;i<TL;i++)
                for (j=i+1;j<TL;j++)
                    if (strcasecmp (Vetor[i].Nome, Vetor[j].Nome) > 0)
                    {
                        VetAux = Vetor[i];
                        Vetor[i] = Vetor[j];
                        Vetor[j] = VetAux;
                    }
            textcolor(GREEN);
            printf ("DADOS ORDENADOS!!\n");
            break;
        case 'C':
            textcolor(RED);
            printf ("Não há Dados cadastrados\n");
            break;
    }
}

int VerificaAluno (TpAluno Vet[TF], int TL, char Aux[], int deci)
{
    int pos=0;
    while (pos < TL && strcmp(Vet[pos].RA, Aux) != 0)
        pos++;
    switch (deci)
    {
    case 1:
        if (pos < TL)
            return 1;
        else 
            return 0;
        break; 
    case 2:
        if (pos < TL)
            return pos;
        else 
            return -1;       
        break;
    }

}

int VerificaDisciplina (TpDisciplina Vet[TF], int TL, int Aux, int deci)
{
    int pos=0;
    while (pos < TL && Vet[pos].CodDisc != Aux)
        pos++;
    switch (deci)
    {
        case 1:
            if (pos<TL)
                return 1;
            else    
                return 0;
            break;
        case 2:
            if (pos < TL)
                return pos;
            else    
                return -1;
            break;
    }
}

int VerificaNota (TpNota Vet[TF], int TL, char RaAux[13], int CodAux, int deci)
{
    int pos=0;
    while (pos < TL && strcasecmp(RaAux, Vet[pos].RA) != 0 && Vet[pos].CodDisc != CodAux)
        pos++;
    switch (deci)
    {
        case 1:
            if (pos < TL)
                return 1;
            else 
                return 0;
            break;
        case 2:
            if (pos<TL)
                return pos;
            else    
                return -1;
            break;
    }
}

void CadastraAluno (TpAluno Vet[TF], int &TL, char Aux[])
{
    if (TL<TF)
    {
        strcpy (Vet[TL].RA, Aux);
        printf ("NOME DO ALUNO: ");
        gets(Vet[TL].Nome); 
        TL++;
        textcolor(GREEN);
        printf ("CADASTRADO COM SUCESSO!!\n");
        textcolor(WHITE);
        printf ("---------------------------------\n");
    }
    else
    {
        textcolor(RED);
        printf ("CADASTRO CHEIO!!\n");
    }
    textcolor(WHITE);
}

void CadCheio (int decisao)
{
    switch (decisao)
    {
    case 1:
        textcolor(RED);
        printf ("CADASTRO DE ALUNO CHEIO!!\n");
        textcolor(WHITE);
        break;
    case 2:
        textcolor(RED);
        printf ("CADASTRO DE DISCIPLINAS CHEIO!!\n");
        textcolor(WHITE);
        break;
    }
}

char MenuOrdena(char op, int TL)
{
    if (TL)
    {
        switch (op)
        {
            case 1:
                clrscr();
                printf ("------------ MENU ORDENA ALUNO ------------\n");
                printf ("[A] - RA\n");
                printf ("[B] - NOME\n");
                printf ("Opção: ");
                break;
            case 2:
                clrscr();
                printf ("------------ MENU ORDENA DISCPLINA --------\n");
                printf ("[A] - COD. DA DISCIPLINA\n");
                printf ("[B] - NOME DA DISCIPLINA\n");
                printf ("Opção: ");
                break;
        }
        return toupper(getch());
    }
    else    
        return 'C';
}

void ExibirAluno (TpAluno Vetor[TF], int Tl)
{
    int i;
    if (Tl)
    {
        for (i=0;i<Tl;i++)
        {
            printf ("RA: %s\n", Vetor[i].RA);
            printf ("NOME: %s\n", Vetor[i].Nome);
            printf ("------------------------------------\n");
        }
    }
    else   
    {
        textcolor(RED);
        printf ("Não há Alunos cadastrados!!\n");
    }
    textcolor(WHITE);
}

void OrdenarAluno (TpAluno Vetor[TF], int TL, char op)
{
    int i, j;
    TpAluno VetAux;
    clrscr();
    switch(op)
    {
        case 'A':
            for(i=0;i<TL;i++)
                for (j=i+1;j<TL;j++)
                    if (strcasecmp(Vetor[i].RA, Vetor[j].RA) > 0)
                    {
                        VetAux = Vetor[i];
                        Vetor[i] = Vetor[j];
                        Vetor[j] = VetAux;
                    }
            textcolor(GREEN);
            printf ("DADOS ORDENADOS!!\n");
            break;
        case 'B':
            for (i=0;i<TL;i++)
                for (j=i+1;j<TL;j++)
                    if (strcasecmp (Vetor[i].Nome, Vetor[j].Nome) > 0)
                    {
                        VetAux = Vetor[i];
                        Vetor[i] = Vetor[j];
                        Vetor[j] = VetAux;
                    }
            textcolor(GREEN);
            printf ("DADOS ORDENADOS!!\n");
            break;
        case 'C':
            textcolor(RED);
            printf ("Não há Dados cadastrados\n");
            break;
    }
}

void CriaRAAux(char Aux[])
{
    printf ("RA: ");
    fflush(stdin);
    gets(Aux);
}

void CriaDiscAux (int &Aux)
{
    printf ("COD DA DISCIPLINA: ");
    scanf ("%d", &Aux);
}

void AlterarAluno (TpAluno Vetor[TF], int TL)
{
    char RAaux[13], NomeAux[30];
    int pos;

    if (TL)
    {
        CriaRAAux(RAaux);
        pos = VerificaAluno(Vetor, TL, RAaux, 2);
        if (VerificaAluno(Vetor, TL, RAaux, 1))
        {
            printf ("NOVO NOMEDO ALUNO: ");
            gets (NomeAux);
            if (MenuConfirmaAltera() == 'S')
            {
                strcpy(Vetor[pos].Nome, NomeAux);
                textcolor (GREEN);
                printf ("NOME ALTERADO COM SUCESSO!!\n");
            }
            else    
            {
                textcolor (RED);
                printf ("ALTERAÇÃo CANCELADA!!\n");
            }
        }
        else
        {
            textcolor(RED);
            printf ("ALUNO %s NÃO ENCONTRADO!!\n", RAaux);
        }
    }
    else    
    {
        textcolor(RED);
        printf ("NÃO HÁ CADASTROS DE ALUNOS!!\n");
    }
}

char MenuConfirmaAltera (void)
{
    printf ("CONFIRMA A ALTERAÇÃO?\n");
    printf ("[S] - SIM\n");
    printf ("[N] - NÃo\n");
    return toupper(getch());
}

void ExcluirAluno (TpAluno Vet[TF], int &TL)
{
    int pos;
    char Aux[13], op;
    if (TL)
    {
        CriaRAAux(Aux);
        pos = VerificaAluno(Vet, TL, Aux, 2); // Acha a posição parametro 2
        if (VerificaAluno(Vet, TL, Aux, 1)) // Verifica se tem parametro 1
        {
            printf("DESEJA EXCLUIR: \n");
            printf ("RA: %s\n", Aux);
            printf ("NOME: %s\n", Vet[pos].Nome);
            printf ("[S] - SIM\n");
            printf ("[N] - NÃO\n");
            printf ("Opção: ");
            op = toupper(getche());
            if (op == 'S')
            {
                for (; pos<TL-1;pos++)
                    Vet[pos] = Vet[pos+1];
                textcolor(GREEN);
                printf ("\nALUNO EXCLUÍDO COM SUCESSO!!\n");
                TL--;
            }
            else    
            {
                textcolor(RED);
                printf ("EXCLUSÃO CANCELADA\n");
            }
        }
        else    
        {
            textcolor(RED);
            printf ("ALUNO NÃO ENCONTRADO!!\n");
        }
    }
    else    
    {
        textcolor(RED);
        printf ("NÃO HÁ ALUNOS CADASTRADOS\n");
    }
}

void CadastrarNota (TpNota VetNota[TF], int &TLNota, TpAluno VetAluno[TF], int TLAluno, TpDisciplina VetDisc[TF], int TLDisc)
{
    char RAaux[13];
    int posAluno, CodAux, posDisc, posNota;

    CriaRAAux(RAaux);
    if (VerificaAluno(VetAluno, TLAluno, RAaux, 1))
    {
        CriaDiscAux(CodAux);
        posAluno = VerificaAluno(VetAluno, TLAluno, RAaux, 2);
        if (VerificaDisciplina(VetDisc, TLDisc, CodAux, 1))
        {
            posDisc = VerificaDisciplina(VetDisc, TLDisc, CodAux, 2);
            if (VerificaNota(VetNota, TLNota, RAaux, CodAux, 1))
            {
                printf ("----- ALUNO -----\n");
                printf ("RA: %s\n", RAaux);
                printf ("NOME: %s\n", VetAluno[posAluno].Nome);
                printf ("----- DISCIPLINA -----\n");
                printf ("COD DA DISCIPLINA: %d\n", CodAux);
                printf ("DISCIPLINA: %s\n", VetDisc[posDisc].Disciplina);
                printf ("-------------------------\n");
                printf ("NOTA: ");
                scanf ("%f", &VetNota[TLNota].Nota);
                VetNota[TLNota].CodDisc = VetDisc[posDisc].CodDisc;
                strcpy(VetNota[TLNota].RA, RAaux);
                TLNota++;
            }
            else    
            {
                posNota = VerificaNota(VetNota, TLNota, RAaux, CodAux, 2);
                textcolor(RED);
                printf ("NOTA DE ALUNO JA CADASTRADO!!\n");
                textcolor(WHITE);
                printf ("----- ALUNO -----\n");
                printf ("RA: %s\n", RAaux);
                printf ("NOME: %s\n", VetAluno[posAluno].Nome);
                printf ("----- DISCIPLINA -----\n");
                printf ("COD DA DISCIPLINA: %d\n", CodAux);
                printf ("DISCIPLINA: %s\n", VetDisc[posDisc].Disciplina);
                printf ("----- NOTA -------\n");
                printf ("NOTA: %.1f", VetNota[posNota].Nota);
            }
        }
        else
        {
            textcolor(RED);
            printf ("DISCIPLINA NAO ENCONTRADA!!\n");
        }
    }
    else    
    {
        textcolor(RED);
        printf ("ALUNO NAO ENCONTRADO!!\n");
    }
}