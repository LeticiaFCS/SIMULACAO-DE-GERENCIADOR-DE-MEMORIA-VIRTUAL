#include "variaveis_globais.h"
#include "frames.h"
#include "paginas.h"

int lru[FRAMES_MEMORIA+2];

void inicializa_lru();
bool memoria_cheia();
bool memoria_vazia();
int front_lru();
bool push_lru(int valor);
bool pop_lru();
int pos_lru(int valor);
bool remove_lru(int valor);
void acesso_lru(int valor);
void imprime_lru();


void inicializa_lru(){
	lru[COMECO_LRU] = lru[FIM_LRU] = -1;
}
bool memoria_vazia(){
	if(lru[COMECO_LRU] == -1)
		return 1;
	return 0;
}
bool memoria_cheia(){
	if(memoria_vazia())
		return 0;
	if(lru[COMECO_LRU] == lru[FIM_LRU])
		return 1;
	return 0;
}
int front_lru(){
	if(memoria_vazia())
		return -1;
	return lru[ lru[COMECO_LRU] ];
}
bool push_lru(int valor){
	if(memoria_cheia())
		return 0;
	if(memoria_vazia())
		lru[COMECO_LRU] = lru[FIM_LRU] = 0;
	
	lru[ lru[FIM_LRU] ] = valor;	
	lru[FIM_LRU]  = (lru[FIM_LRU] + 1) % FRAMES_MEMORIA;
	
	return 1;
}
bool pop_lru(){
	if(memoria_vazia())
		return 0;	
	
	if(lru[FIM_LRU] == lru[COMECO_LRU] + 1)
		inicializa_lru();
	else if(lru[FIM_LRU] == 0 && lru[COMECO_LRU] == (FRAMES_MEMORIA - 1))
		inicializa_lru();
	else
		lru[COMECO_LRU]  = (lru[COMECO_LRU] + 1) % FRAMES_MEMORIA;
	
	return 1;
}
int pos_lru(int valor){
	if(memoria_vazia())
		return -1;
	int pos;
	if( lru[COMECO_LRU] < lru[FIM_LRU]){
		for(pos = lru[COMECO_LRU]; pos < lru[FIM_LRU]; pos++)
			if( lru[pos] == valor )
				return pos;
	} else {
		for(pos = lru[COMECO_LRU]; pos < FRAMES_MEMORIA; pos++)
			if( lru[pos] == valor )
				return pos;
		
		for(pos = 0; pos < lru[FIM_LRU]; pos++)
			if( lru[pos] == valor )
				return pos;
	}
	return -1;
}



bool remove_lru(int valor){
	int pos = pos_lru(valor);
	if(pos == -1)
		return false;
	if(pos == lru[COMECO_LRU]){
		pop_lru();
	} else {
		int i;
		if( lru[COMECO_LRU] < lru[FIM_LRU] || (pos < lru[COMECO_LRU]) ){
			for(i = pos; i < lru[FIM_LRU] - 1; i++)
				lru[i] = lru[i+1];
		} else {		
			for(i = pos; i < FRAMES_MEMORIA; i++)
				lru[i] = lru[(i+1) % FRAMES_MEMORIA];
			for(i = 0; i < lru[FIM_LRU] - 1; i++)
				lru[i] = lru[i+1];									
		}
		lru[FIM_LRU] = (FRAMES_MEMORIA + lru[FIM_LRU] - 1) % FRAMES_MEMORIA;		
	}
	return true;

}

void acesso_lru(int valor){
	if(remove_lru(valor))
		push_lru(valor);
}
void imprime_lru(){
	if(memoria_vazia())
		printf("\tLRU vazio\n");
	else {
		printf("\tLRU\n");
		printf("\t\tposicao\t\tprocesso\tpagina\n");
		if( lru[COMECO_LRU] < lru[FIM_LRU]){
			int i;
			for(i = lru[COMECO_LRU]; i < lru[FIM_LRU]; i++){
				int pos = lru[i];
				
				frame_t atual = int_para_frame(memoria_principal[pos]);
				if(atual.P == 0)
					/*printf("\t\tposicao = %d: vazio\n", i);*/printf("\t\t%d\t\tvazio\n", i);
				else
					/*printf("\t\tposicao = %d: processo = %d, pagina = %d\n", i, atual.processo, atual.pagina);*/
					printf("\t\t%d\t\t%d\t\t%d\n", i, atual.processo, atual.pagina);
					
			}
		} else {
			int i;
			for(i = lru[COMECO_LRU]; i < FRAMES_MEMORIA; i++){
				int pos = lru[i];
				
				frame_t atual = int_para_frame(memoria_principal[pos]);
				if(atual.P == 0)
					/*printf("\t\tposicao = %d: vazio\n", i);*/printf("\t\t%d\t\tvazio\n", i);
				else
					/*printf("\t\tposicao = %d: processo = %d, pagina = %d\n", i, atual.processo, atual.pagina);*/
					printf("\t\t%d\t\t%d\t\t%d\n", i, atual.processo, atual.pagina);
					
			}
			for(i = 0; i < lru[FIM_LRU]; i++){
				int pos = lru[i];
				
				frame_t atual = int_para_frame(memoria_principal[pos]);
				if(atual.P == 0)
					/*printf("\t\tposicao = %d: vazio\n", i);*/printf("\t\t%d\t\tvazio\n", i);
				else
					/*printf("\t\tposicao = %d: processo = %d, pagina = %d\n", i, atual.processo, atual.pagina);*/
					printf("\t\t%d\t\t%d\t\t%d\n", i, atual.processo, atual.pagina);
					
			}		
		}	
		
	}
	puts(" ");
}
