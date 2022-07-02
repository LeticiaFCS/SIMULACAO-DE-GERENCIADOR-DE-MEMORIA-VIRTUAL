/*
	5 | 2 | P = 1
	1+4+FRAMES_MEMORIA+256 = 325
	000101 | 00010 | 1
	5 << 6
	+ 2 << 1
	+ 1
*/
void teste_conversoes_frame(int valor){
	frame_t f = int_para_frame(valor);
	imprime_frame(f);
	int novoValor = frame_para_int(f);
	if(valor == novoValor)
		printf("Conversoes frame funcionando\n");
	else
		printf("Conversoes frame nao funcionando\n");
}

/*

	010000 | 0 | 1
	1 + FRAMES_MEMORIA = 65
*/

void teste_conversoes_pagina(int valor){
	pagina_t p = int_para_pagina(valor);
	imprime_pagina(p);
	int novoValor = pagina_para_int(p);
	if(valor == novoValor)
		printf("Conversoes pagina funcionando\n");
	else
		printf("Conversoes pagina nao funcionando\n");
}
void testeLRU(){
	printf("mem vazia? %d\n", memoria_vazia());
	printf("mem cheia? %d\n", memoria_cheia());
	for(int i = 1; i <= FRAMES_MEMORIA; i++){
		push_lru(i);
		printf("posicao do %d no lru: %d\n", i, pos_lru(i));
		imprime_lru();
	}
	acesso_lru(2);
	imprime_lru();
	pop_lru();
	push_lru(FRAMES_MEMORIA+1);
	imprime_lru();
	acesso_lru(4);
	imprime_lru();
	acesso_lru(3);
	imprime_lru();

}

