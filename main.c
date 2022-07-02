#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

#include "lru.h" 

 

 
void inserir_pagina(int processo, int pagina);

void simulacao_gerenciador_memoria(); 

//TO DO contador de page faults
int main(){
	inicializa_lru();	
	memset( working_set, -1, sizeof(working_set) );
	simulacao_gerenciador_memoria();
	
	return 0;
}

long int diferenca_tempo(struct timeval inicio, struct timeval fim){

	return fim.tv_sec * 1000000 + fim.tv_usec
		 - (inicio.tv_sec * 1000000 + inicio.tv_usec);

}
 
/*void print_estado(){*/
/*	puts("");*/
/*	printf("Memoria principal: \n");*/
/*	int i, j;*/
/*	for(i = 0; i < FRAMES_MEMORIA; i++){*/
/*		frame_t atual = int_para_frame(memoria_principal[i]);*/
/*		if(atual.P == 0)*/
/*			printf("\tposicao = %d: vazio\n", i);*/
/*		else*/
/*			printf("\tposicao = %d: processo = %d, pagina = %d\n", i, atual.processo, atual.pagina);*/
/*	}*/
/*	puts("");*/
/*	*/
/*	*/
/*	puts("");*/
/*	*/
/*	printf("Working set dos processos\n");*/
/*	for(i = 0; i < criados; i++){*/
/*		printf(" processo %d\n\t", i);*/
/*		for(j=0; j<WORKING_SET_LIMIT; j++)*/
/*			if(working_set[i][j] != -1)*/
/*				printf("%d ", working_set[i][j]);*/
/*		puts("");*/
/*	}*/
/*	puts("");*/
/*	puts("-----------------------------------------------------------------------------------------------------------");*/
   

/*}*/


void simulacao_gerenciador_memoria(){
	
	struct timeval tempo_inicio, tempo_atual, tempo_anterior;
	
	gettimeofday(&tempo_inicio, NULL);
	gettimeofday(&tempo_anterior, NULL);
	gettimeofday(&tempo_atual, NULL);
	
	criados = 0;
	int i; 
	
	while(diferenca_tempo(tempo_inicio, tempo_atual) < TEMPO_SIMULACAO){
		gettimeofday(&tempo_atual, NULL);
		while(diferenca_tempo(tempo_anterior, tempo_atual) < 3000000){
			gettimeofday(&tempo_atual, NULL);
		}
		gettimeofday(&tempo_anterior, NULL);
		if(criados < LIM_PROCESSOS){
			printf("Processo %d criado\n", criados);
			criados++;
		}	
		for(i = 0; i < criados; i++){
			int pagina = rand() % LIM_PAGINAS;
			inserir_pagina(i, pagina);
			printf("\tProcesso %d alocou a pagina %d\n\n", i, pagina);
			int j;
			puts("\tTabela de paginas: ");
			printf("\t\tpagina\tP\tM\tendereco\n");
			for(j=0; j<LIM_PAGINAS; j++){
				pagina_t pagina = int_para_pagina(tabela_de_paginas[i][j]);
				if(pagina.P){
					printf("\t\t%d\t%d\t%d\t%d\n", j, pagina.P, pagina.M, pagina.endereco);
				}
			}
			puts("");
			puts("");
			imprime_lru();	
		}
		
		puts("-------------------------------------------------------------------------");
	}
}


void remove_frame(frame_t f){
	tabela_de_paginas[ f.processo ][ f.pagina ] = 0;
	int i;
	for(i=0; i<WORKING_SET_LIMIT; i++)
		if(working_set[f.processo][i] == f.pagina)
			working_set[f.processo][i] = -1;
}

void insere_frame(frame_t f, int pos){
	memoria_principal[pos] = frame_para_int(f);
	pagina_t p;
	p.P = 1;
	p.M = 0;
	p.endereco = pos;		
	tabela_de_paginas[f.processo][f.pagina] = pagina_para_int(p);	
	int i;
	for(i=0; i<WORKING_SET_LIMIT; i++)
		if(working_set[f.processo][i] == -1){
			working_set[f.processo][i] = f.pagina;
			break;
		}
}


void inserir_pagina(int processo, int pagina){
	pagina_t p = int_para_pagina( tabela_de_paginas[processo][pagina] );
	
	if(p.P == 1){ // acesso
		acesso_lru(p.endereco);
		
	} else { //inserir pagina na MP
		int i;
		bool working_set_cheio = true;
		for(i = 0; i < WORKING_SET_LIMIT; i++)
			if(working_set[processo][i] == -1)
				working_set_cheio = false;

		
		if(working_set_cheio){
			int pagina_a_remover = working_set[processo][0];
			int endereco_pagina_remover = int_para_pagina( tabela_de_paginas[processo][pagina_a_remover] ).endereco;
			remove_lru(endereco_pagina_remover);
			frame_t f_remover = int_para_frame( memoria_principal[endereco_pagina_remover] );
			remove_frame(f_remover);
		}
						
		int pos;
		if( memoria_cheia() ){
			pos = front_lru();
			pop_lru();
			frame_t f_pop = int_para_frame( memoria_principal[pos] );
			remove_frame(f_pop);
		}  else {
			for(pos = 0; pos < FRAMES_MEMORIA; pos++){
				if( int_para_frame( memoria_principal[pos] ).P == 0 )
					break;
			}
		}
		
		push_lru(pos);
		
		frame_t f;
		f.P = 1;
		f.processo = processo;
		f.pagina = pagina;
		insere_frame(f, pos);
		
	}

}


