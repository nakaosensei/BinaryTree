#include <stdio.h>
#include "arvore_binaria.h"

void teste1(){

	No *arvore = NULL;
	ab_inserir(&arvore, 20);
	ab_inserir(&arvore, 10);
	ab_inserir(&arvore, 30);
	ab_inserir(&arvore, 5);
	ab_inserir(&arvore, 15);
	ab_inserir(&arvore, 11);
	ab_inserir(&arvore, 16);
	

	printf("Altura: %d\n", ab_altura(arvore));
	printf("Total de Vertices: %d\n", ab_total_vertices(arvore));

	printf("\n--PreOrdem----\n");	
	ab_pre_ordem(arvore);
	printf("\n--EmOrdem--\n");	
	ab_em_ordem(arvore);
	printf("\n--PosOrdem-\n");	
	ab_pos_ordem(arvore);
	ab_destruir(&arvore);
}

int teste2(){

	No *arvore = NULL;
	ab_inserir(&arvore, 20);
	ab_inserir(&arvore, 10);
	ab_inserir(&arvore, 30);
	ab_inserir(&arvore, 40);
	ab_inserir(&arvore, 25);
	ab_inserir(&arvore, 15);
	ab_inserir(&arvore, 5);
		
	printf("Altura: %d\n", ab_altura(arvore));
	printf("Total de Vertices: %d\n", ab_total_vertices(arvore));

	printf("\n--PreOrdem----\n");	
	ab_pre_ordem(arvore);
	printf("\n--EmOrdem--\n");	
	ab_em_ordem(arvore);
	printf("\n--PosOrdem-\n");	
	ab_pos_ordem(arvore);

	ab_remover(&arvore, 5);
	ab_remover(&arvore, 20);
	ab_remover(&arvore, 15);
	ab_remover(&arvore, 10);
	ab_remover(&arvore, 30);
	ab_remover(&arvore, 25);
	ab_remover(&arvore, 40);
	printf("%p\n", arvore);


	ab_inserir(&arvore, 20);
	ab_inserir(&arvore, 10);
	ab_inserir(&arvore, 30);
	ab_inserir(&arvore, 40);
	ab_inserir(&arvore, 25);
	ab_inserir(&arvore, 15);
	ab_inserir(&arvore, 5);

	ab_destruir(&arvore);
}

void teste3(){
	No *arvore = NULL;
	printf("\nArvore original\n");
	ab_inserir(&arvore, 30);
	ab_inserir(&arvore, 10);
	ab_inserir(&arvore, 40);
	ab_inserir(&arvore, 5);
	ab_inserir(&arvore, 20);
	ab_inserir(&arvore, 15);
	ab_inserir(&arvore, 25);
	ab_inserir(&arvore, 50);
	ab_inserir(&arvore, 60);
	ab_imprime(&arvore);
	int var=50;
	printf("\nArvore com %d removido\n",var);
	ab_remover(&arvore, var);
	ab_imprime(&arvore);
	printf("%d\n",ab_altura(arvore));
	printf("%d\n",ab_total_vertices(arvore));
	ab_imprime(&arvore);
	ab_destruir(&arvore);
	ab_imprime(&arvore);
}

int main(){
	teste3();
	return 0;
}