#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "automata.h"
#define COLOR "\e[107m  \e[0m"
#define NADA "\e[40m  \e[0m"
#define FPS 10
#define USPORFRAME 10000 //micro segundos por frame


#ifndef USE_MIPS
const unsigned char REGLA_30[8] =  {0, 0, 0, 1, 1, 1, 1, 0};
const unsigned char REGLA_126[8] = {0, 1, 1, 1, 1, 1, 1, 0};
const unsigned char REGLA_110[8] = {0, 1, 1, 0, 1, 1, 1, 0};

unsigned char proximo_regla(const unsigned char regla[],
							unsigned char *a,
							unsigned int i, unsigned int j,
							unsigned int N){
	unsigned char izq = a[i * N + (j - 1) % N];
	unsigned char der = a[i * N + (j + 1) % N];
	unsigned char act = a[i * N + j];
	
	if (izq == 1 && act == 1 && der == 1){
		return regla[0];
	} else if (izq == 1 && act == 1){
		return regla[1];
	} else if (izq == 1 && der == 1){
		return regla[2];
	} else if (izq == 1){
		return regla[3];
	} else if (act == 1 && der == 1){
		return regla[4];
	} else if (act == 1){
		return regla[5];
	} else if (der == 1){
		return regla[6];
	}
	return regla[7];
}

unsigned char proximo(unsigned char *a,
					  unsigned int i, unsigned int j,
					  unsigned char regla,
					  unsigned int N){
	
	if (regla == 30){
		return proximo_regla(REGLA_30, a, i, j, N);
	} else if (regla == 126){
		return proximo_regla(REGLA_126, a, i, j, N);
	}
	return proximo_regla(REGLA_110, a, i, j, N);
}
#endif

void automata_instanciar(automata_t* automata, 
						 char* file,
						 unsigned int celdas,
						 unsigned char regla){
	
	automata->regla = regla;
	automata->cantidad_celdas = celdas;
	automata->tabla = calloc(automata->cantidad_celdas * automata->cantidad_celdas, sizeof(unsigned char));	
	if (!automata->tabla)	return;

	FILE* archivo = fopen(file ,"r");
	if (!archivo) {
		free(automata->tabla);
		automata->tabla = NULL;
		return;
	}

	for (int i = 0; i < automata->cantidad_celdas; i++){
		unsigned int p = 0;
		fscanf(archivo, "%1u", &p);
		automata->tabla[i] = (unsigned char)p;
	}

	fclose(archivo);
}

void automata_avanzar(automata_t* automata){
	
	unsigned int cant = automata->cantidad_celdas;
	for (unsigned int i = 0; i < cant - 1; i++){
		for (unsigned int j = 0; j < cant; j++){
	
			automata->tabla[(i + 1) * cant + j] = proximo(automata->tabla,
														  i, j,
														  automata->regla,
														  cant);
		}
	}
}

void automata_imprimir(automata_t* automata){
	unsigned int cant = automata->cantidad_celdas;
	for (unsigned int i = 0; i < cant; i++){
		for (unsigned int j = 0; j < cant; j++){
			printf("%s", (automata->tabla[i * cant + j] == 0)? NADA : COLOR);	
		}	
		printf("\n");
		usleep(FPS * USPORFRAME);
	}
}



void automata_guardar(automata_t* automata, char* salida){

	strcat(salida, ".pbm");
	FILE* aGuardar = fopen(salida, "w");
	fprintf(aGuardar, "P1\n");
	fprintf(aGuardar, "%u %u\n", automata->cantidad_celdas, automata->cantidad_celdas);
	
	unsigned int cant = automata->cantidad_celdas;
	for (unsigned int i = 0; i < cant; i++){
		for (unsigned int j = 0; j < cant; j++){
			
			fprintf(aGuardar, "%1u ", automata->tabla[i * cant + j]);	
		}
		fprintf(aGuardar, "\n");
	}
	fclose(aGuardar);
}

void automata_destruir(automata_t* automata){
	free(automata->tabla);
}

