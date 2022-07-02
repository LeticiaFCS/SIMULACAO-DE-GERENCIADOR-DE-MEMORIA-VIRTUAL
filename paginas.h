typedef struct pagina_t{
	int P;
	int M;
	int endereco;
} pagina_t;

pagina_t int_para_pagina(int valor);

int pagina_para_int(pagina_t p);

void imprime_pagina(pagina_t p);

pagina_t int_para_pagina(int valor){
	pagina_t p;
		
	// primeiro bit
	p.P = valor % 2;
	if(p.P == 0) // pagina nao alocada
		return p;
	valor /= 2;
	
	//proximos bit
	p.M = valor % 2;		
	valor /= 2;
	
	// seis proximos bits 
	int bit, pot2 = 1;
	p.endereco = 0;
	for(bit = 0; bit < 6; bit++){
		if(valor % 2 == 1)
			p.endereco += pot2;
		pot2 *= 2;
		valor /= 2;
	}
		
	return p;
}

/*

	010000 | 0 | 1
	1 + FRAMES_MEMORIA = 65
*/

int pagina_para_int(pagina_t p){
	int valor = 0;
	valor += p.endereco << 2;
	valor += p.M << 1;
	valor += p.P;
	return valor;
}

void imprime_pagina(pagina_t p){
	printf("P = %d, M =  %d, endereco = %d\n", p.P, p.M, p.endereco);
}

