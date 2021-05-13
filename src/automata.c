#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "automata.h"


void inicializar_matriz(int cantidad_celdas,int matriz[cantidad_celdas][cantidad_celdas]){
	for (int i = 0; i < cantidad_celdas; i++){
	    for (int j = 0; j < cantidad_celdas; j++){
            matriz[i][j]= 0;
        }    
    }
}

void imprimir_matriz(int cantidad_celdas,int matriz[cantidad_celdas][cantidad_celdas]){
	for (int i = 0; i < cantidad_celdas; i++){
		for (int j = 0; j < cantidad_celdas; j++){
			printf(" %d ", matriz[i][j]);
		}	
		printf("\n");
	}
}


char** instanciar_matriz(char* file, int cantidad_celdas){

	int matriz[cantidad_celdas][cantidad_celdas];
	inicializar_matriz(cantidad_celdas, matriz);

	FILE* archivo = fopen(file ,"r");
	if(!archivo) return NULL;


	for (int i = 0; i < cantidad_celdas; ++i){
		fscanf(archivo, "%1d",& matriz[0][i]);
	}


	fclose(archivo);
	return matriz;
}

