//--------------------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include "headers.h"
#include <time.h>
#include <string.h>
#define max_Chaves 200

/*
Feito por:
Gabriel Matheus da Rocha de Oliveira, 17/0103498
Guilherme Braga Pinto, 17/0162290
Last Update: 08/12/2018
UnB- CIC
*/

//--------------------------------------------------------------------------------------------

int main (){

	FILE *fp;
	FILE *fpw;
	FILE *fpw2;
	FILE *fpresult;
	BTree *tree;

    struct Aluno pessoas;
    struct Aluno pessoas_novas[max_Chaves];
    int conta_chaves_novas = 0;
    int chaves_novas[max_Chaves][8];

	fp = fopen ("lista.txt", "r");
	fpw = fopen ("Resultado_Index.txt", "w");
	fpw2 = fopen("Resultado_Indices_ArvoreB", "w");
	fpresult = fopen("Resultado_dados", "w");
	int Linha_Index = 1;
	int option;

	int linhas, i, k, num;

	Escreve_Menu(1);
	scanf("%d", &num);
	//num = num*2;

	int order;

	Escreve_Menu(2);
	scanf("%d%*c", &order);

	tree = New_tree(order);

	char linha[108];
	char indice_prim[num][8];
	char nome_texto[num][30];
	char matricula_texto[num][6];
	char Curso_texto[num][3];
	char turma_aux[num][2];
	node_posicao pos;
	

	int l = 0;

//--------------------------------LEITURA---------------------------------------

	for(k=0; k<num ; k++){
	    for(i = 0; i<8; i++){
        	indice_prim[k][i] = ' ';     
    	 }
    	 for(i = 0; i < 5; i ++){
    	 	matricula_texto[k][i] = ' ';
    	 }
    	 for(i = 0; i < 30; i++){
    	 	nome_texto[k][i] = ' ';
    	 }
	}

	for(k = 0; k < num; k++){

		memset(linha, ' ', sizeof(linha));
		fgets(linha, 108, fp);
		linha[108] = '\0';

		for(i = 0; i<108; i++){                          // vai tudo para uma nova struct, armazenaremos o que for adicionado no futuro
			printf("%c", linha[i]);
		}
		printf("\n");
		
		//memset(nome_texto, ' ', sizeof(nome_texto));

		for(i=0 ; i<6; i++){
			matricula_texto[k][i] = ' ';
        }

		for(i = 0; i < 3 ; i++){
        Curso_texto[k][i] = linha[i+48];                            //definimos o curso 
        }
        Curso_texto[k][2] = '\0';
	
		l=0;
	    for(i = 0; i < 30; i++){
	        nome_texto[k][i] = linha[i];
	        if( (linha[i] <= 'Z') && (linha[i] >= 'A') && (l < 3) ) {          
	          indice_prim[k][l] = linha[i];
	          l++;
	        }
		}
		for(i=0 ; i<5; i++){
			matricula_texto[k][i] = linha[i+41];
			indice_prim[k][i+l] = linha[i+41];
		}
		matricula_texto[k][5] = '\0';
		turma_aux[k][0] = linha[52];                       // definimos cada item da struct de aluno
		turma_aux[k][1] = '\0';

		nome_texto[k][29] = '\0';

		for(i = 0; i < 30; i++){
			pessoas.nome[i] = nome_texto[k][i];
		}
		for(i=0 ; i<5; i++){
			pessoas.matricula[i] = matricula_texto[k][i]; 
		}
		pessoas.matricula[5] = '\0';
		for(i=0 ; i<3; i++){
			pessoas.Curso[i] = Curso_texto[k][i];
		}
		pessoas.Curso[3] = '\0';

		indice_prim[k][8] = '\0';

		strcpy(pessoas.Turma, turma_aux[k]);
		printf("!!!!!PESSOAS.TURMA = %s!!!!", pessoas.Turma);
		
		printf("Nome: %s\n", pessoas.nome);
		printf("Matricula: %s\n", pessoas.matricula);
		printf("Curso: %s\n", pessoas.Curso);
		printf("Turma: %s\n", turma_aux[k]);                 // ao final. confirmamos e printamos
		


		printf("o indice e: %s\n", indice_prim[k]);
		pos = Insert_arvoreb(tree, indice_prim[k], pessoas);
		fprintf(fpw, "Chave: %s representa as seguintes informações:\n\n", indice_prim[k]);
		fprintf(fpw, "Nome: %s\nMatricula:%s\nCurso: %s\nTurma: %s\n\n",pessoas.nome, pessoas.matricula, pessoas.Curso, pessoas.Turma);
		
		
	}
	fclose(fp);
	fclose(fpw);
//--------------------------------FIM DA LEITURA---------------------------------------

	//PRINTANDO OS INDICES PRIMARIOS
	printf("\n");
	
	for(k = 0; k<num; k++){
		for(i=0; i<8; i++){

			printf("%c", indice_prim[k][i]);

		}
		printf("\n"); 
	}

	char Chave[8];
	int linha_aux;

//--------------------------------MENU---------------------------------------
	
	printf("\033[1;34m");


	while(1){

		Escreve_Menu(3);

		printf("\033[0m");	
		scanf("%d", &option);

//--------------------------------ACHANDO CHAVES NA ARVORE B---------------------------------------

		if(option == 1){

			Escreve_Menu(4);
			scanf("%s", Chave);
			Chave[8] = '\0'; 
			printf("Chave a ser buscada: %s\n", Chave);
			pos = arvoreb_find(tree, Chave);

		if (pos.node == NULL) {

			printf("\033[0;31m");
			printf("\nA CHAVE %s não foi encontrada na B-Tree\n", Chave);         // recuperamos a chave, retornamos quando possivel
			printf("\033[0m");
			}
		else {

			printf("\033[0;32m");
			printf("\nA CHAVE %s foi encontrada associada as informações:\nnome: %s\nmatricula: %s\ncurso: %s\nturma: %s\n",
			         Chave, pos.node->Chaves[pos.index]->pessoas.nome, pos.node->Chaves[pos.index]->pessoas.matricula,
			         pos.node->Chaves[pos.index]->pessoas.Curso, pos.node->Chaves[pos.index]->pessoas.Turma);
			printf("\033[0m");
			}

		}

//--------------------------------INSERINDO NA ARVORE B---------------------------------------

		if(option == 2){
			
			Escreve_Menu(5);
			scanf("%s", Chave);
			getchar();

			for(k=0; k<8; k++){
				chaves_novas[conta_chaves_novas][k] = Chave[k];
			}
		
			Escreve_Menu(6);                //adicionaremos um registro
      		printf("Nome:\n");
      		memset(pessoas.nome, ' ', sizeof(pessoas.nome));
      		scanf("%[^\n]", pessoas.nome);                           // coletamos informaões e a atribuimos à uma estrutura auxiliar
      		getchar();
      		strcpy(pessoas_novas[conta_chaves_novas].nome, pessoas.nome);
      		printf("%s\n", pessoas.nome);
      		printf("Matricula\n");
      		scanf("%[^\n]", pessoas.matricula);
      		getchar();
      		strcpy(pessoas_novas[conta_chaves_novas].matricula, pessoas.matricula);
      		printf("%s\n", pessoas.matricula);
      		printf("Curso\n");
      		scanf("%s", pessoas.Curso);
      		getchar();
      		strcpy(pessoas_novas[conta_chaves_novas].Curso, pessoas.Curso);
      		printf("%s\n", pessoas.Curso);
      		pessoas.Curso[2] = '\0';
      		pessoas_novas[conta_chaves_novas].Curso[2] = '\0';
      		printf("Turma:\n");
      		scanf("%c", &pessoas.Turma[0]);
      		getchar();
      		strcpy(pessoas_novas[conta_chaves_novas].Turma, pessoas.Turma);
      		printf("%s", pessoas.Turma);

			pos = Insert_arvoreb(tree, Chave, pessoas);

			conta_chaves_novas++;            // inserimos e incrementamos o contador de pessoas novas

		}

//--------------------------------REMOVENDO DA ARVORE B---------------------------------------

		if(option == 3){

		Escreve_Menu(7);
		scanf("%s", Chave);
		Chave[8] = '\0';           // tentamos ver se a chave a ser retirada pertence as chaves novas

		for(i=0; i<conta_chaves_novas; i++){
			if((Chave[0] == chaves_novas[i][0]) && (Chave[1] == chaves_novas[i][1]) && (Chave[2] == chaves_novas[i][2])){
				for(int z = 0; z<8; z++){
					chaves_novas[i][z] = ' ';
				}
			memset(pessoas_novas[i].Curso, ' ', 3);
			memset(pessoas_novas[i].Turma, ' ', 2);
			memset(pessoas_novas[i].matricula, ' ', 6);
			memset(pessoas_novas[i].nome, ' ', 30); 
			conta_chaves_novas--;
			// mantemos o numero de chaves novas
			}
		}
		 
		
		for(i=0; i<num; i++){
			if((Chave[0] == indice_prim[i][0]) && (Chave[1] == indice_prim[i][1]) && (Chave[2] == indice_prim[i][2])){
				for(int z = 0; z<8; z++){
					indice_prim[i][z] = 0;
				}
			}
		} 
		
		// ZERAMOS OS INDICES QUE RETIRAMOS

		pos = arvoreb_remove(tree, Chave);
		if (pos.node == NULL) {

			printf("\033[0;31m");
			printf("\nA CHAVE %s não foi encontrada na B-Tree\n", Chave);
			printf("\033[0m");
			//fprintf(fpw, "A CHAVE %s não foi encontrada na B-Tree\n", Chave);
			}
		else {

			printf("\033[0;32m");
			printf("\nA CHAVE %s foi removida com sucesso\n", Chave);
			printf("\033[0m");
			
			}

		
		}
		
		if(option == 4){        // fim de execução

//--------------------------------PRINTANDO AS CHAVES---------------------------------------
			for(k = 0; k<num; k++){
		

				fprintf(fpw2, "%s", indice_prim[k]);

		
				fprintf(fpw2, "\n"); 
			} // printando indices

			printf("\n\nFinal da execução!\n\n");
			
			for(k = 0; k<conta_chaves_novas; k++){
				for(i=0; i<8; i++){		
					fprintf(fpw2, "%c\n\n", chaves_novas[k][i]);
					
				}
				printf("\033[0;32m");
				printf("Nova chave adicionada nesta execução:\n");
				printf("Nome: %s\nmatricula: %s\ncurso: %s\nturma: %s\n",pessoas_novas[k].nome, pessoas_novas[k].matricula, pessoas_novas[k].Curso, pessoas_novas[k].Turma);
				printf("\033[0m");
				fprintf(fpw2, "\n");

			} // printando novos indices e mostrando o que teve de novo

			for(k = 0; k<num; k++){
				for(i=0; i<8; i++){
					Chave[i] = indice_prim[k][i];
				}
				Chave[8] = '\0';
				pos = arvoreb_find(tree, Chave);
				if((Chave[0] != 0) && (Chave[3] != 0)){ 
					fprintf(fpresult, "\n\n%s\nnome: %s\nmatricula: %s\ncurso: %s\nturma: %s\n",
 	            			Chave, pos.node->Chaves[pos.index]->pessoas.nome, pos.node->Chaves[pos.index]->pessoas.matricula,
		        			pos.node->Chaves[pos.index]->pessoas.Curso, pos.node->Chaves[pos.index]->pessoas.Turma);
				}

			} // printando da arvore original

			if(conta_chaves_novas != 0){
				for(k = 0; k<conta_chaves_novas; k++){
					for(i=0; i<8; i++){
						Chave[i] = chaves_novas[k][i];
					}
					Chave[8] = '\0';
					pos = arvoreb_find(tree, Chave);
					if((Chave[0] != 0) && (Chave[3] != 0)){ 
						fprintf(fpresult, "\n\n%s\nnome: %s\nmatricula: %s\ncurso: %s\nturma: %s\n",
 	            			Chave, pos.node->Chaves[pos.index]->pessoas.nome, pos.node->Chaves[pos.index]->pessoas.matricula,
		        			pos.node->Chaves[pos.index]->pessoas.Curso, pos.node->Chaves[pos.index]->pessoas.Turma);
						fprintf(fpresult, "\n");
					}
				} // printando o que temos de novo
			}
//--------------------------------PRINTANDO AS CHAVES---------------------------------------






			break;
		}

	}

		
   	arvoreb_delete_h(tree);
  	fclose(fpw2);
  	fclose(fpresult);
  	return 0;
}

//--------------------------------FIM---------------------------------------
