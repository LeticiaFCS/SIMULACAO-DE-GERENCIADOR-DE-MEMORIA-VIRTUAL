typedef struct frame_t{
	int P;
	int processo;
	int pagina;
} frame_t;

frame_t int_para_frame(int valor);

int frame_para_int(frame_t f);

void imprime_frame(frame_t f);

frame_t int_para_frame(int valor){

	frame_t f;
		
	// primeiro bit
	f.P = valor % 2;
	if(f.P == 0) // frame livre
		return f;
		
	valor /= 2;
	
	// cinco proximos bits 
	int bit, pot2 = 1;
	f.processo = 0;
	for(bit = 0; bit < 5; bit++){
		if(valor % 2 == 1)
			f.processo += pot2;
		pot2 *= 2;
		valor /= 2;
	}
	
	// seis proximos bits 
	pot2 = 1;
	f.pagina = 0;
	for(bit = 0; bit < 6; bit++){
		if(valor % 2 == 1)
			f.pagina += pot2;
		pot2 *= 2;
		valor /= 2;
	}
	
	return f;
}

int frame_para_int(frame_t f){
	int valor = 0;
	valor += f.pagina << 6;
	valor += f.processo << 1;
	valor += f.P;
	return valor;
}


void imprime_frame(frame_t f){
	printf("P = %d, processo = %d, pagina = %d\n", f.P, f.processo, f.pagina);
}	


