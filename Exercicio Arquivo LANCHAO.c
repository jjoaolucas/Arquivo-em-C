#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

/*
==== DESENVOLVIDO POR: =====
=    JOÃO LUCAS DA SILVA   =
=    BRENO OLIVEIRA        =
============================*/

typedef struct{
	int cod;
	float preco;
	char nome[60], tipoPao[60];
}lanches;

int menuPrincipal(){
	int opcao;

	printf("\n========== MENU ==========\n");
	printf("\n1 - Cadastrar Lanches\n");
	printf("2 - Listar Lanches Cadastrados\n");
	printf("3 - Consultar Lanches pelo nome \n");
	printf("4 - Consultar Lanches pelo tipo de pao \n");
	printf("5 - Alterar o preco de um Lanche\n");
	printf ("6 - Excluir lanche\n");
	printf("0 - Sair\n");
	printf("\n==========================\n");
	printf("\nOpcao: ");
	scanf("%d", &opcao);
	
	return opcao;
}

void cadastrarLanches(){
	FILE *arq;
	lanches lanche;
	
	arq = fopen("lanchao.bin","ab");
	
	if(arq == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
		do
		{
			system("cls");
			printf("\n====================================");
			printf("\n=         TELA DE CADASTRO         =");
			printf("\n====================================\n");
			
			printf("\nCodigo do lanche: ");
			scanf("%d", &lanche.cod);
			
			printf("Nome do lanche: "); fflush(stdin);
			gets(lanche.nome);
			
			printf("Tipo de pao: "); fflush(stdin);
			gets(lanche.tipoPao);
			
			printf("Preco do lanche: R$");
			scanf("%f", &lanche.preco);
			
			fwrite(&lanche, sizeof(lanches), 1, arq);
			
			printf("\n====================================");
			printf("\n= Lanche cadastrado com sucesso !! =");
			printf("\n====================================\n");
			
			printf("\nDeseja cadastrar outro lanche <s/n> ? \n");
			
		}while(toupper(getche())=='S');
		
		fclose(arq);
	}
}
void listarLanches(){
	FILE *arq;
	lanches lanche;
	
	arq = fopen("lanchao.bin","rb");
	
	if(arq == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else{
			system("cls");
			printf("\n====================================");
			printf("\n=        LANCHES CADASTRADOS       =");
			printf("\n====================================\n");
		while(fread(&lanche,sizeof(lanches),1,arq)==1){
			printf ("\nCodigo: %d\n" , lanche.cod);
			printf ("Nome: %s\n" ,lanche.nome);
			printf ("Tipo de pao: %s\n" , lanche.tipoPao);
			printf ("Preco: R$%.2f\n" , lanche.preco);
			printf("\n====================================\n");
		}
		
		printf("\nPressione qualquer tecla para voltar ao menu... ");
		
		if(toupper(getche())==' ')
			fclose(arq);
	}
	
}

void consultarLanches(){
	FILE *arq;
	lanches lanche;
	char busca[50]; int pos=0;
	arq = fopen("lanchao.bin","rb");
	
	if(arq == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else{
			system("cls");
			printf("\n====================================");
			printf("\n=    CONSULTAR LANCHE PELO NOME    =");
			printf("\n====================================");
			
				printf ("\n\nInforme o nome do lanche: ");fflush(stdin);
				gets(busca);
				while(fread(&lanche,sizeof(lanches),1,arq)==1){
					if(strcmp(busca,lanche.nome)==0){
						pos=2;
						printf ("\nCodigo: %d\n" , lanche.cod);
						printf ("Nome: %s\n" ,lanche.nome);
						printf ("Tipo de pao: %s\n" , lanche.tipoPao);
						printf ("Preco: R$%.2f\n" , lanche.preco);
						printf("\n====================================\n");
					}
				}
				if (pos == 0){
					printf("\n===========================");
					printf("\n=  Lanche nao cadastrado  =\n");
					printf("===========================\n");
				}
					
			
				printf("\nPressione qualquer tecla para voltar ao menu... ");
		
				if(toupper(getche())==' ')
					fclose(arq);	
	}
	
}

void consultarPeloTipoPao(){
	FILE *arq;
	lanches lanche;
	char busca[50];
	int pos = 0;
	
	arq = fopen("lanchao.bin","rb");
	
	if(arq == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
		system("cls");
		printf("\n====================================");
		printf("\n=    CONSULTAR PELO TIPO DO PAO    =");
		printf("\n====================================\n");
		printf("\nTipo de pao deseja buscar: "); fflush(stdin);
		gets(busca);
		
		while(fread(&lanche, sizeof(lanches), 1, arq) == 1)
		{
			if(strcmp(busca,lanche.tipoPao) == 0)
			{
				pos = 1;
				printf("\nCodigo: %d", lanche.cod);
				printf("\nNome: %s", lanche.nome);
				printf("\nPreco: R$%.2f\n", lanche.preco);
				printf("\n====================================\n");
			}
		}
		if(pos == 0)
		{
			printf("\n=========================================================");
			printf("\n=  Nao encontrado nenhum lanche com esse tipo de pao !  =\n");
			printf("=========================================================\n");
		}
		
		printf("\nPressione qualquer tecla para voltar ao menu... ");
		
		if(toupper(getche())==' ')
			fclose(arq);
	}
}

int busca(FILE *arq,char nome[])
{
	lanches lanche;
	rewind(arq);
	fread(&lanche,sizeof(lanches),1,arq);
	while(!feof(arq) && strcmp(nome,lanche.nome)!=0)
	  fread(&lanche,sizeof(lanches),1,arq);
	if(!feof(arq))  
	   return(ftell(arq)-sizeof(lanches));
	else
	   return -1;   
}

void alterar()
{
	FILE *arq;
	lanches lanche;
	int pos;
	char buscar[50];
	arq = fopen("lanchao.bin","rb+");
	system ("cls");
	if(arq == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else{
		system("cls");
		printf("\n====================================");
		printf("\n=      ALTERAR PRECO DO LANCHE     =");
		printf("\n====================================\n");
		printf("\nInforme o nome do lanche: "); fflush(stdin);
		gets(buscar);
		while(strcmp(buscar,"\0")!=0)
		{
			pos=busca(arq,buscar);
			if(pos==-1){
				printf("\n===========================");
				printf("\n=  Lanche nao cadastrado  =\n");
				printf("===========================\n");
			}
			else
			{
				fseek(arq,pos,0);
				fread(&lanche,sizeof(lanches),1,arq);
				printf("\nNome do lanche: %s",lanche.nome);
				printf("\nPreco: R$%.2f\n",lanche.preco);
				printf("\nDeseja alterar o preco <s/n> ? \n");
				if(toupper(getche())=='S')
				{
					printf("\n\nNovo Preco: ");
					scanf ("%f" , &lanche.preco);
					fseek(arq,pos,0);
					fwrite(&lanche,sizeof(lanches),1,arq);
					printf("\n========================================");
					printf("\n= Preco do lanche alterado com sucesso =");
					printf("\n========================================\n");
					
				}
			} 
			printf("\nInforme o nome do lanche ou <ENTER> para cancelar: "); fflush(stdin);
			gets(buscar);
			
		}
		system("cls");
		fclose(arq);
	}
	
}

void excluirLanche()
{
	FILE *arquivo = fopen("lanchao.bin" , "rb");
	lanches lanche;
	int pos;
	char nome[50], opc;
	if(arquivo == NULL)
		printf ("Erro ao abrir o arquivo");
	else
	{
		system("cls");
		printf("\n====================================");
		printf("\n=          EXCLUIR LANCHE          =");
		printf("\n====================================\n");
		printf ("\nExcluir lanche ou <ENTER> para cancelar: ");fflush(stdin);
		gets(nome);
		while(strcmp(nome,"\0")!=0){
			pos=busca(arquivo,nome);
			if (pos == -1){
				printf("\n===========================");
				printf("\n=  Lanche nao cadastrado  =\n");
				printf("===========================\n");
			}
			else
			{
				fseek(arquivo,pos,0);
				fread(&lanche,sizeof(lanches),1,arquivo);
				printf ("\nCodigo do lanche: %d" , lanche.cod);
				printf ("\nNome do lanche: %s" , lanche.nome);
				printf ("\nTipo de pao: %s" , lanche.tipoPao);
				printf ("\nPreco: R$%.2f\n\n" , lanche.preco);
				printf ("Deseja excluir <s/n>?\n");
				scanf(" %c" , &opc);
				if(toupper(opc)=='S'){
					FILE *temp = fopen("auxiliar.bin", "wb");
					rewind(arquivo);
					fread(&lanche,sizeof(lanches),1,arquivo);
					while(!feof(arquivo)){
						if(strcmp(nome,lanche.nome)!=0)
							fwrite(&lanche,sizeof(lanches),1,temp);
						fread(&lanche,sizeof(lanches),1,arquivo);
					}
					fclose(arquivo);
					fclose(temp);
					remove("lanchao.bin");
					rename("auxiliar.bin" , "lanchao.bin");
					printf("\n====================================");
					printf("\n=  Lanche excluido com sucesso !!  =");
					printf("\n====================================\n");
				}
			}
			printf ("\nExcluir lanche ou <ENTER> para cancelar: ");fflush(stdin);
			gets(nome);
		}
	}
}


main(){
	int op;
	op = menuPrincipal();
	while (op != 0){
		switch (op){
			case 1: cadastrarLanches();
					system("cls");
					break;
			case 2: listarLanches();
					system("cls");
					break;
			case 3: consultarLanches();
					system("cls");
					break;
			case 4: system("cls");
					consultarPeloTipoPao();
					system("cls");
					break;
			case 5: system("cls");
                    alterar();
                    break;
            case 6: excluirLanche();
					system("cls");
					break;
			default: system("cls");
					 printf("\n========================================");
					 printf("\n=   Opcao invalida, tente novamente!   =");
					 printf("\n========================================\n");
		}
		op = menuPrincipal();
	}
	system("cls");
	printf("\n==========================");
	printf ("\n=  PROGRAMA ENCERRADO!  =");
	printf("\n==========================\n");
};
