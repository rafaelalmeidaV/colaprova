#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>

//estrutura das informa��es a 
//serem armazenadas no n� da lista
struct Embaixador{
	char nome[40];
	char curso[30];
	char ra[8];
	struct Embaixador* proximo;	
}; 

//define o n� inicial da lista
struct Embaixador *inicio= NULL;

//fun��o para carregar os embaixadores
//de um arquivo na lista encadeada

void leEmbaixadores(){
	
	//Tentar abrir o arquivo
	FILE *arquivo = NULL;
	char nome[40]; 
	
	arquivo=fopen("embaixadores.txt","r");
	
	if(arquivo!=NULL){
	//Enquanto houver dados:
	while(fscanf(arquivo,"%s",nome)!=EOF){ //para cada nome ele cria um novo embaixador
	
	   //colocar na lista encadeada	   
	   //Algoritmo de inser��o no inicio
	   //Criar um novo n�
	   struct Embaixador *novo = (struct Embaixador*)malloc(sizeof(struct Embaixador));
	   
	   
	   //colocar os dados lidos no novo n�
	   strcpy(novo->nome, nome);
	   
		// -> Ler o nome, ra, curso
		fscanf(arquivo,"%s",novo->ra);
		fscanf(arquivo,"%s",novo->curso);

		// -> Colocar no novo n�
	    novo->proximo=inicio;
	    inicio=novo;
	
	}
	
	fclose(arquivo);
	//fechar o arquivo
		
	}
	 
} 

/*
  Imprime os embaixadores do arquivo e que j� est�o na lista
   
*/

void listarEmbaixadores(){
	
	//obter um n� auxiliar
	struct Embaixador *aux = inicio;
	
	//enquanto houver elemento na lista
	while(aux!=NULL){
		int maior =0;

		//imprimir os dados de aux
		printf("\nNome:%s", aux->nome);
		printf("\nRA:%s", aux->ra);
		printf("\nCurso:%s", aux->curso);
		
		//atualiza aux passando ele para o 
		//pr�ximo elemento da lista
		aux = aux->proximo;
			
	}	
}

/*
Substituir um embaixador:
Deve ler o curso, e os dados do novo embaixador e realizar a

devida altera��o na lista;
*/

void substituir(){
	
	char curso[30];
	
	printf("\nCurso que recebera novo embaixador:");
	scanf("%s",curso);
	
	
	//buscar o curso na lista
	
	//obter um n� auxiliar
	struct Embaixador *aux = inicio;
	int encontrou = 0;
	
	//enquanto houver elemento na lista
	while(aux!=NULL){
	
		if(strcmp(aux->curso,curso)==0){
			printf("Nome do novo embaixador:");
			scanf("%s",aux->nome);
			printf("RA:");
			scanf("%s",aux->ra);
			encontrou = 1;
			break; //encerra a busca 
			       //se encontrar os dados a serem alterados 
		}
	   //continua buscando nos pr�ximos elementos
	   aux = aux->proximo;
	}
	if(!encontrou){
		printf("Curso n�o encontrado");
	}
}
/*

�resetar� o arquivo �embaixadores.txt� com os dados

atualizados da lista.

*/

void resetar(){
		//Tentar abrir o arquivo
	FILE *arquivo = NULL;
	char nome[40]; 
	
	arquivo=fopen("embaixadores.txt","r");
	
	if(arquivo!=NULL){
			//obter um n� auxiliar
	struct Embaixador *aux = inicio;
	
	//enquanto houver elemento na lista
	while(aux!=NULL){
		
		//imprimir os dados de aux
		fprintf(arquivo,"%s\n", aux->nome);
		fprintf(arquivo,"%s\n", aux->ra);
		fprintf(arquivo,"%s\n", aux->curso);
		
		//atualiza aux passando ele para o 
		//pr�ximo elemento da lista
		aux = aux->proximo;
			
	}	
	fclose(arquivo);	
	}
}
int main(){
	
	leEmbaixadores();
	listarEmbaixadores();
	substituir();
	listarEmbaixadores();
	
}

