#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "automata.h"


void automata_imprimir(automata_t* automata){

	unsigned int cant = automata->cantidad_celdas;
	for (unsigned int i = 0; i < cant; i++){
		for (unsigned int j = 0; j < cant; j++){
			printf(" %d ", automata->tabla[i * cant + j]);
		}
		printf("\n");
	}
}


void automata_instanciar(automata_t* automata, char* file, unsigned int celdas){

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

