#include <stdio.h>
#include "conio.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h> 
#include <unistd.h>
// #include <windows.h>

#define TF 5
// Defini��o da estrutura de um aluno.
struct TpAluno
{
    char RA[13];	 // RA do aluno (m�ximo de 12 caracteres, +1 para o caractere nulo). 
    char Nome[30];   // Nome do aluno (m�ximo de 29 caracteres, +1 para o caractere nulo).
};
// Defini��o da estrutura de uma disciplina.
struct TpDisciplina
{
    int CodDisc;
    char Disciplina[20];
};
// Estrutura que armazena o relacionamento entre aluno e disciplina.
struct TpNota
{
    char RA[13];
    int CodDisc;
    float Nota;
};
// Fun��es principais
void Executar (void);// Fun��o que executa o programa principal.
char Escolha (void);  // Fun��o para capturar a escolha do menu principal.

// FUNÇOES DE MENU
char MenuAluno (void); // Fun��o para menu de op��es de alunos.
char MenuNota(void); // Fun��o para menu de notas.
char MenuDisciplina (void);  // Fun��o para menu de disciplinas.
char MenuOrdena(char op, int TL); // Fun��o para menu de ordena��o.
char MenuConfirmaAltera (void); // Fun��o para confirmar altera��o.

// FUNCOES DE VERIFICACAO
int VerificaAluno (TpAluno Vet[TF], int TL, char Aux[], int deci);// Verifica a exist�ncia do aluno.
int VerificaDisciplina (TpDisciplina Vet[TF], int TL, int Aux, int deci);
int VerificaNota (TpNota Vet[TF], int TL, char RaAux[13], int CodAux, int deci);

// FUNCOES DE CADADTRO
void CadastraAluno (TpAluno Vet[TF], int &TL, char Aux[]);// Cadastra um novo aluno.
void CadastrarNota (TpNota VetNota[TF], int &TLNota, TpAluno VetAluno[TF], int TLAluno, TpDisciplina VetDisc[TF], int TLDisc);
void CadastrarDisciplina (TpDisciplina Vet[TF], int &TL);

// MENSAGEM DE VETOR CHEIO
void CadCheio (int decisao); // Exibe mensagem de vetor cheio.

// FUNCOES DE EXIBIR VETOR
void ExibirAluno (TpAluno Vetor[TF], int Tl); // Exibe a lista de alunos.

// FUNCOES DE ORDENAR
void OrdenarAluno (TpAluno Vetor[TF], int TL, char op); // Ordena a lista de alunos.

// FUNCAO PRA CRIAR UM AUX
void CriaRAAux(char Aux[]); // Fun��o que cria um RA auxiliar.
void CriaDiscAux (int &Aux);

// FUNCOES DE ALTERAR DADOS
void AlterarAluno (TpAluno Vetor[TF], int TL);  // Fun��o que altera o nome de um aluno.
// Fun��o principal (entry point)
int main (void)
{
	// Define a localidade para Portugu�s-Brasil 
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    clrscr();
    textcolor(15);// Define a cor do texto.
    Executar();
    return 0;
}
// Fun��o que desenha a moldura na tela (layout do painel)
void Moldura( int CI, int LI, int CF, int LF, int CorT, int CorF)
{
	int i;
	textcolor(CorT);
	textbackground(CorF);
	gotoxy(CI,LI); printf("%c",201); // Canto superior esquerdo.
	gotoxy(CF,LI);printf("%c",187);// Canto superior direito
	gotoxy(CI,LF);printf("%c",200); // Canto inferior esquerdo.
	gotoxy(CF,LF);printf("%c",188);// Canto inferior direito.
		// Desenha as linhas horizontais (superior e inferior).
	for(i=CI+1; i<CF; i++ ){
		gotoxy(i,LI); printf("%c",205);
//		Sleep(10);
		gotoxy(i,LF);printf("%c",205);
	}
 	// Desenha as linhas verticais (esquerda e direita).
	for(i=LI+1; i<LF; i++){
		gotoxy(CI,i); printf("%c",186);
//		Sleep(10);
		gotoxy(CF,i); printf("%c",186);
	}
	
	textcolor(7);  // Reseta a cor do texto.
	textbackground(0); // Reseta a cor de fundo.
	
}
// Fun��o que define o layout do painel principal.
void PainelPrincipal(void)
{
	clrscr();
	Moldura(10,1,115,30,0,2);  // Desenha a moldura principal.
	Moldura(11,2,114,4,0,2);// Desenha uma segunda moldura dentro da principal.
	textcolor(15);// Define a cor do texto.
	gotoxy(50,3);printf("ALUNOES E DISCIPLINAS");// T�tulo no painel.

	// Molduras internas.
	Moldura(11,5,50,26,0,2);
	Moldura(11,27,114,29,0,8);
	
	textcolor(14);
	gotoxy(12,28);
	printf("MENSAGEM:");// Campo de mensagem no painel.
}
// Fun��o para captura de escolha do menu principal.
char Escolha(void){
	textcolor(15);
	gotoxy(23,6);printf (" MENU ESCOLHA");// T�tulo do menu.
	// Op��es do menu.
	gotoxy(13,10);printf ("[A] - Alnuos");
	gotoxy(13,11);printf ("[B] - Disciplinas");
	gotoxy(13,12);printf ("[C] - Notas de Alunos");
	gotoxy(13,13);printf("[D] - Entradas prontas");
    gotoxy(13,14);printf ("[ESC] - SAIR");
	gotoxy(21,28); return toupper(getche()); // Captura a escolha do usu�rio.
}
// Fun��o que insere entradas autom�ticas para alunos (RA e nome).
void Entradas(TpAluno vet[TF], int &TLAlunos) {
    int i = 0, cont = 1;// Contador e controle de RA.
    char raStr[10]; // Para converter o RA em string
    
    for(i = 0; i < TF; i++) {
        strcpy(vet[i].Nome, "Bryan"); // Copia a string "Bryan" para o campo Alunos
        
        // Converte o RA em string e copia para o campo RA
        sprintf(raStr, "%d", cont + i);
        strcpy(vet[i].RA, raStr);
        
        cont++;
        TLAlunos++;
    }
}
// Fun��o principal que executa o sistema.
void Executar (void)
{
    int TLAluno=0, TLDisc=0, TLNotas=0, CodAux, cont; // Vari�veis de controle.
    char opEscolha, op, RAaux[13], opAux; // Vari�veis para capturar op��es do menu.
	PainelPrincipal(); // Chama o painel principal.
    TpAluno Alunos[TF];  // Vetor de alunos.
    TpDisciplina Disciplina[TF];  // Vetor de disciplinas.
    TpNota Notas[TF];// Vetor de notas.
    
     // Loop principal do programa.
    do
    {
        clrscr();
    	PainelPrincipal(); 
        opEscolha = Escolha();  // Captura a escolha do menu principal.
        switch (opEscolha)
        {
            case 'A':// Menu de alunos.
                clrscr();
                do 
                {
                	clrscr();
                	PainelPrincipal();   
                    textcolor(15);
                    op = MenuAluno(); // Chama o menu de alunos.
                    switch (op)
                    {
                        case 'A':  // Cadastrar aluno.
                            clrscr();
                            PainelPrincipal();
                            if (TLAluno < TF)
                            {
                            	
                                CriaRAAux(RAaux);// Cria um RA auxiliar.
                                while (TLAluno < TF && strcasecmp(RAaux, "\0") != 0)
                                {
                                    if (!VerificaAluno(Alunos, TLAluno, RAaux, 1))  
                                        CadastraAluno(Alunos, TLAluno, RAaux);// Cadastra o aluno.
                                    else
                                    {
                                        textcolor(4);
                                      	gotoxy(21,28); printf ("ALNUO JA CADASTRADO!!\n");
                                        // Sleep(1500);
                                        textcolor(15);
                                    }
                                    if (TLAluno == TF)
                                        CadCheio(1);
                                    else 
                                        CriaRAAux(RAaux);// Cria um novo RA auxiliar.
                                }
                            }
                            else    
                                CadCheio(1);// Se o vetor estiver cheio.
                            gotoxy(57,6); getch();
                            break;
                        case 'B':  // Exibir alunos.
                            clrscr();
                            ExibirAluno(Alunos, TLAluno); // Exibe a lista de alunos.
                            getch();
                            break;
                        case 'C'://Ordena aluno
                            clrscr();
                            opAux = MenuOrdena(1, TLAluno);
                            PainelPrincipal(); 
                            OrdenarAluno(Alunos, TLAluno, opAux);
                            getch();
                            break;
                        case 'D': //Alterar Nome do aluno
                            clrscr();
                            AlterarAluno(Alunos, TLAluno);
                            getch ();
                            break;
                    } 
                } while (op != 27); // Sai do menu de alunos.
                getch();
                break;
            case 'B'://Diciplina 
                clrscr();
                PainelPrincipal();
                do 
                {
                    textcolor(15);
                    op = MenuDisciplina();
                    switch (op)
                    {
                        case 'A':
                            clrscr();
                            PainelPrincipal();
                            CadastrarDisciplina(Disciplina, TLDisc);
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
            case 'C'://Nota do aluno 
                clrscr();
                PainelPrincipal(); 
                do 
                {
                    op = MenuNota();
                    switch (op)
                    {
                        case 'A':
                            clrscr();
                            PainelPrincipal(); 
                            CadastrarNota(Notas, TLNotas, Alunos, TLAluno, Disciplina, TLDisc);
                            sleep(1.5);
                            // getch();
                            break;
                    }
                } while (op != 27);
                break;
        	case 'D'://inserir nomes 
        		if(cont < 1){
	        		Entradas(Alunos,TLAluno);
	        		cont++;
	        		textcolor(10);
	        		gotoxy(21,28);printf("Entradas inseridas com sucesso");
	        		// Sleep(1500);
                    sleep(1.5);
					clrscr();	
        		}else{
        			textcolor(4);
        			gotoxy(21,28);printf("Entradas j� foram inseridas!!!");
        			// Sleep(1500);
                    usleep(1500);
        			clrscr();
        		}
        		textcolor(15);
        		break;
        }
    } while (opEscolha != 27);
}


//Menu alunos
char MenuAluno (void)
{
    clrscr();
    PainelPrincipal();
	gotoxy(13,6);printf ("------------ MENU ALUNO ------------\n");
	
    gotoxy(13,10); printf ("[A] - Cadastrar Aluno");
    gotoxy(13,11); printf ("[B] - Exibir Alunos");
    gotoxy(13,12);printf ("[C] - Ordenar Alunos");
    gotoxy(13,13);printf ("[D] - Alterar Nome de Aluno");
    gotoxy(13,14);printf ("[E] - Excluir Aluno");
    gotoxy(13,15); printf ("[ESC] - SAIR");
    gotoxy(21,28);return toupper(getche());
}
// Menu Disciplinas
char MenuDisciplina (void)
{
    gotoxy(12,6); printf ("----------- MENU DISCIPLINA ---------");
    
    gotoxy(13,10);printf ("[A] - Cadastrar Disciplina");
    gotoxy(13,11);printf ("[B] - Exibir Disciplinas");
    gotoxy(13,12);printf ("[C] - Ordenar Disciplinas");
    gotoxy(13,13);printf ("[D] - Alterar dados de Disciplinas");
    gotoxy(13,14);printf ("[E] - Excluir Disciplina");
    gotoxy(21,28); return toupper(getche());
}
//Menu Notas
char MenuNota(void)
{
    clrscr();
    PainelPrincipal();
   	gotoxy(13,6);printf ("------------ MENU NOTAS ------------\n");
   	
    gotoxy(13,11); printf ("[A] - Cadastrar Nota\n");
    gotoxy(13,12); printf ("[B] - Exibir nota\n");
   	gotoxy(13,13);  printf ("[C] - Alterar Notas\n");
    gotoxy(13,14); printf ("[D] - Excluir Notas\n");
    gotoxy(13,15); printf ("[ENTER] - SAIR");
    gotoxy(21,28);return toupper(getch());
}
//Exibir alunos que est�o cadastrados 
void Exibir (TpAluno Vetor[TF], int Tl, int decisao)
{
    int i, j;
    if (Tl)
    {
        switch (decisao)
        {
            case 1:
                break;
            case 2:
                for (i=0;i<Tl;i++)
                {
                    printf ("COD DISC.: %s\n", Vetor[i].RA);
                    printf ("NOME: %s\n", Vetor[i].Nome);
                    printf ("------------------------------------\n");
                }
            break;
        }
    }
    else   
    {
        textcolor(4);
        gotoxy(21,28); printf ("Não há Alunos cadastrados!!\n"); //Caso n�o exista alunos castrados no vetor.
    }
    textcolor(15); //Reseta a cor para white 
}
//ordena os alunos pelo RA ou pelo Nome 
void Ordenar (TpAluno Vetor[TF], int TL, char op)
{
    int i, j;
    TpAluno VetAux;
    clrscr();
    switch(op)// op  de ordana��o 
    {
        case 'A': //Ordenar pelo RA 
            for(i=0;i<TL;i++)
                for (j=i+1;j<TL;j++)
                    if (strcasecmp(Vetor[i].RA, Vetor[j].RA) > 0)
                    {
                        VetAux = Vetor[i];
                        Vetor[i] = Vetor[j];
                        Vetor[j] = VetAux;
                    }
            textcolor(10);
            printf ("DADOS ORDENADOS!!\n");
            break;
        case 'B'://Ordenar pelo Nome 
            for (i=0;i<TL;i++)
                for (j=i+1;j<TL;j++)
                    if (strcasecmp (Vetor[i].Nome, Vetor[j].Nome) > 0)
                    {
                        VetAux = Vetor[i];
                        Vetor[i] = Vetor[j];
                        Vetor[j] = VetAux;
                    }
            textcolor(10);
            printf ("DADOS ORDENADOS!!\n");
            break;
        case 'C':
            textcolor(4);
            printf ("Não há Dados cadastrados\n");//Caso n�o exista alunos cadastrados no vetor.
            sleep (1.7);
            // Sleep (1700);
            break;
    }
}
// verificar aluno 
int VerificaAluno (TpAluno Vet[TF], int TL, char Aux[], int deci)
{
    int pos=0;
    while (pos < TL && strcmp(Vet[pos].RA, Aux) != 0)
        pos++;
    switch (deci){
    
	    case 1:// Falso e verdadeiro,  onde retorna um valor 1 caso exista no vetor , ou retorne falso 0 n�o exite no vetor.
	        if (pos < TL)
	            return 1;
	        else 
	            return 0;
	        break; 
	    case 2: //Retornando a sua posi��o.
	        if (pos < TL)
	            return pos;
	        else 
	            return -1;  //Retorna uma posi��o do vetor que n�o exite      
	        break;
    }
}


//Cadastrar alunos 
void CadastraAluno (TpAluno Vet[TF], int &TL, char Aux[])
{
	
    if (TL<TF)
    {
    	//Insere os nomes dos alunos 
        strcpy (Vet[TL].RA, Aux);
        gotoxy(53,7);printf ("NOME DO ALUNO: ");
        gotoxy(68,7);gets(Vet[TL].Nome); 
        TL++; // incrementa o valor l�gico do vetor
        textcolor(10);
        gotoxy(21,28); printf ("CADASTRADO COM SUCESSO!!\n");
        sleep(1.7);
        // Sleep(1500);//Tempo de 1,5 segundos
        textcolor(15);//reseta a cor 
    }
    else
    {
    	//Cadastro cheio 
        textcolor(4);
        gotoxy(21,28); printf ("CADASTRO CHEIO!!\n");
        sleep(1.7);
        // Sleep(1500);
    }
    textcolor(15);
}
//Cadastro cheio 
void CadCheio (int decisao){
    switch (decisao){
	    case 1:
	        textcolor(4);
	        gotoxy(21,28); printf ("CADASTRO DE ALUNO CHEIO!!\n");//Printa quando o vetor estiver cheio
	        // Sleep(1500);
	        textcolor(15);
	        break;
	    case 2:
	        textcolor(4);
	        gotoxy(21,28); printf ("CADASTRO DE DISCIPLINAS CHEIO!!\n");//Printa quando o vetor estiver cheio
	        // Sleep(1500);
	        textcolor(15);
	        break;
    }
}
//Menu de ordena��o 
char MenuOrdena(char op, int TL)
{
	
    if (TL)
    {
        switch (op){
            case 1://Ordenar alunos 
                clrscr();
                PainelPrincipal(); 
                gotoxy(12,6);printf ("--------- MENU ORDENA ALUNO ---------");
                gotoxy(13,11);printf ("[A] - RA\n");
                gotoxy(13,12);printf ("[B] - NOME\n");
              	gotoxy(12,28); printf ("Opção: ");
                break;
            case 2://ordenar disciplinas
                clrscr();
                PainelPrincipal(); 
               	gotoxy(12,6) ;printf ("-------- MENU ORDENA DISCPLINA -------");
               	gotoxy(13,11); printf ("[A] - COD. DA DISCIPLINA\n");
               	gotoxy(13,11); printf ("[B] - NOME DA DISCIPLINA\n");
              	gotoxy(12,28); printf ("Opção: ");
                break;
        }
        return toupper(getch());
    }
    else    
        return 'C';
}
//Exibe aluno 
void ExibirAluno (TpAluno Vetor[TF], int Tl)
{
    int i, j;
    if (Tl)
    {
        for (i=0;i<Tl;i++)
        {
            printf ("RA: ");
            for(j=0;j<strlen(Vetor[i].RA);j++)
            {
                printf ("%c", Vetor[i].RA[j]);
                sleep(1);
            }
            printf("\n");
            printf ("NOME: ");
            for (j=0;j<strlen(Vetor[i].Nome);j++)
            {
                printf ("%c", Vetor[i].Nome[j]);
                sleep(1);
            }
            printf ("\n");
            printf ("------------------------------------\n");
        }
    }
    else   
    {
        textcolor(4);
        gotoxy(21,28); printf ("Não há Alunos cadastrados!!\n");
        sleep(1.5);
        // Sleep(1500);
    }
    textcolor(15);
}
//Fun��o que ordena aluno
void OrdenarAluno (TpAluno Vetor[TF], int TL, char op)
{
    int i, j;
    TpAluno VetAux;
    clrscr();
    switch(op)
    {
        case 'A'://Ordena pelo RA
        	PainelPrincipal(); 
            for(i=0;i<TL;i++)
                for (j=i+1;j<TL;j++)
                    if (strcasecmp(Vetor[i].RA, Vetor[j].RA) > 0)
                    {
                        VetAux = Vetor[i];
                        Vetor[i] = Vetor[j];
                        Vetor[j] = VetAux;
                    }
            textcolor(10);
           	gotoxy(21,28); printf ("DADOS ORDENADOS!!\n");
            break;
        case 'B'://Ordena pelo nome 
        	PainelPrincipal(); 
            for (i=0;i<TL;i++)
                for (j=i+1;j<TL;j++)
                    if (strcasecmp (Vetor[i].Nome, Vetor[j].Nome) > 0)
                    {
                        VetAux = Vetor[i];
                        Vetor[i] = Vetor[j];
                        Vetor[j] = VetAux;
                    }
            textcolor(10);
           	gotoxy(21,28); printf ("DADOS ORDENADOS!!\n");
        //    Sleep(1500);
            break;
        case 'C'://Quando n�o existe dados no vetor
        	PainelPrincipal(); 
            textcolor(4);
            gotoxy(21,28);printf ("Não há Dados cadastrados\n");
			// Sleep(1500);
            break;
    }
}
//Criar um RA auxiliar. 
void CriaRAAux(char Aux[])
{
	PainelPrincipal();
    gotoxy(53,6);printf ("RA: ");
    fflush(stdin);
    gotoxy(57,6);gets(Aux);
}
//Alterar aluno  
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
            gotoxy(53,7); printf ("NOVO NOMEDO ALUNO: ");
            gets (NomeAux);
            if (MenuConfirmaAltera() == 'S')
            {
                strcpy(Vetor[pos].Nome, NomeAux);
                textcolor (10);
                gotoxy(21,28);printf ("NOME ALTERADO COM SUCESSO!!\n");
            }
            else    
            {
                textcolor (4);
                gotoxy(21,28);printf ("ALTERAÇÃO CANCELADA!!\n");
            }
        }
        else
        {
            textcolor(4);
            gotoxy(21,28);printf ("ALUNO %s NÃO ENCONTRADO!!\n", RAaux);
        }
    }
    else    
    {
        textcolor(4);
        gotoxy(21,28);printf ("NÃO HÁ CADASTROS DE ALUNOS!!\n");
    }
}
//Menu para confirmar altera��o 
char MenuConfirmaAltera (void)
{
    gotoxy(12,6) ;printf ("CONFIRMA A ALTERAÇÃO?\n");
    gotoxy(13,11);printf ("[S] - SIM\n");
   gotoxy(13,12);printf ("[N] - NÃo\n");
    gotoxy(21,28);return toupper(getch());
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
            if (!VerificaNota(VetNota, TLNota, RAaux, CodAux, 1))
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
                gotoxy(21,28); printf ("NOTA DE ALUNO JA CADASTRADO!!\n");
                textcolor(WHITE);
                printf ("----- ALUNO -----\n");
                printf ("RA: %s\n", RAaux);
                printf ("NOME: %s\n", VetAluno[posAluno].Nome);
                printf ("----- DISCIPLINA -----\n");
                printf ("COD DA DISCIPLINA: %d\n", CodAux);
                printf ("DISCIPLINA: %s\n", VetDisc[posDisc].Disciplina);
                printf ("----- NOTA -------\n");
                printf ("NOTA: %.1f", VetNota[posNota].Nota);
                sleep(5);
                // Sleep(5000);
            }
        }
        else
        {
            textcolor(RED);
            gotoxy(21,28); printf ("DISCIPLINA NAO ENCONTRADA!!\n");
            sleep(1.7);
            // Sleep(1700);
            textcolor(WHITE);
        }
    }
    else    
    {
        textcolor(RED);
        gotoxy(21,28); printf ("ALUNO NAO ENCONTRADO!!\n");
        sleep(1.7);
        // Sleep(1700);
        textcolor(WHITE);
    }
}

void CadastrarDisciplina (TpDisciplina Vet[TF], int &TL)
{
    int Aux;
    if (TL < TF)
    {
        clrscr();
        PainelPrincipal();
        gotoxy(13,8); printf ("[0] - SAIR\n");
        CriaDiscAux(Aux);
        while (TL < TF && Aux != 0)
        {
            if (!VerificaDisciplina(Vet, TL, Aux, 1))
            {
                Vet[TL].CodDisc = Aux;
                gotoxy(53,7); printf ("NOME DA DISCIPLINA: ");
                fflush(stdin);
                gotoxy(73,7); gets(Vet[TL].Disciplina);
                TL++;
                textcolor(GREEN);
                gotoxy(21,28); printf ("DISCIPLINA CADASTRADA COM SUCESSO!!\n");
                sleep(1.7);
                // Sleep(1700);
                textcolor(WHITE);
            }
            else    
            {
                textcolor(RED);
                gotoxy(21,28); printf ("DISCIPLINA JA CADASTRADA!!\n");
                sleep(1.7);
                // Sleep(1700);
                textcolor(WHITE);
            }
            clrscr();
            PainelPrincipal();
            gotoxy(13,8); printf ("[0] - SAIR\n");
            CriaDiscAux(Aux);
        }
    }
    else    
    {
        textcolor(RED);
        gotoxy(21,28); printf ("CADASTRO DE DISCIPLINA CHEIO!!\n");
        sleep(1.7);
        // Sleep(1700);
        textcolor(WHITE);
    }
}

void CriaDiscAux (int &Aux)
{
    gotoxy(53,6); printf ("COD DA DISCIPLINA: ");
    gotoxy(72,6); scanf ("%d", &Aux);
}

int VerificaDisciplina (TpDisciplina Vet[TF], int TL, int Aux, int deci)
{
    int pos=0;
    while (pos < TL && Aux != Vet[pos].CodDisc)
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
//void CadastrarNota(TpNota VTN[TF], int &TLNota){
//	 
//	 int pos, 
//	 printf("\nCadastrar notas");
//	 
//}
