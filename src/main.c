#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <getopt.h>
#include "automata.h"

#define ERROR_LECTURA -1
#define ERROR_LEC_INT 1
#define MAXIMO_ARCHIVO 100

const char VERSION[] = "1.0.0";

extern char *optarg;
extern int optind, opterr, optopt;


typedef struct config{
	bool overflow;
	bool argumentos_equivocados;
	bool ayuda;
	bool version;
	unsigned int regla;
	unsigned int celdas;
	char archivo_entrada[MAXIMO_ARCHIVO];
	char archivo_salida[MAXIMO_ARCHIVO];
} config_t;

unsigned int leer_uint(char* string){
	long resultado = strtol(string, NULL, 10);
	if(resultado > UINT_MAX || errno == ERANGE || resultado <= 1){
		return ERROR_LEC_INT;
	}
	return (unsigned int) resultado;
}


void mensaje_ayuda(){
	
	// Uso 
	// ./autocel <R> <N> <inputfile> [-o <outputprefix>]
	// ./autocel [-h|-V]
	//
	// Convenciones: https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap12.html
	printf("$ autocel -h\n");
	printf("Uso:\n");
	printf("  autocel -h\n");
	printf("  autocel -V\n");
	printf("  autocel R N inputfile [-o outputprefix]\n");
	printf("Opciones:\n");
	printf("  -h, --help     Imprime este mensaje.\n");
	printf("  -V, --version  Da la version del programa.\n");
	printf("  -o  Prefijo de los archivos de salida.\n");
	printf("Ejemplos:\n");
	printf("  autocel 30 80 inicial -o evolucion\n");
	printf("  Calcula la evolucion del automata 'Regla 30',\n");
	printf("  en un mundo unidimensional de 80 celdas, por 80 iteraciones.\n");
	printf("  El archivo de salida se llamara evolucion.pbm.\n");
	printf("  Si no se da un prefijo para los archivos de salida,\n");
	printf("  el prefijo sera el nombre del archivo de entrada\n");
}

void mensaje_version(){
	printf("%s\n", VERSION);
}

void obtener_configuracion(config_t* config, char* argv[], unsigned int i_salida){


	config->regla = leer_uint(argv[1]);
	if(config->regla == ERROR_LEC_INT){
		fprintf(stderr,"El parámetro ingresado: (%s) no es válido.\n",argv[1]);
		config->argumentos_equivocados = true;
		return;
	}

	config->celdas = leer_uint(argv[2]);
	if(config->celdas == ERROR_LEC_INT){
		fprintf(stderr,"El parámetro ingresado: (%s) no es válido.\n",argv[2]);
		config->argumentos_equivocados = true;
		return;
	}

	strcpy(config->archivo_entrada, argv[3]);
	strcpy(config->archivo_salida, argv[i_salida]);	

}


config_t leer_argumentos(int argc, char* argv[]){

	static struct option opciones_largas[] = {
		{"help", no_argument, 0, 'h'},
		{"output", required_argument, 0, 'o'},
		{"version", no_argument, 0, 'V'},
		{0, 0, 0, 0}
	};
	config_t config = {false, false, false, false, 0, 0, "", ""};
	int opt;
	
	while((opt = getopt_long(argc, argv, "o:Vh", opciones_largas, NULL)) != -1 ) {
		
		switch(opt){

			case 'o':
				if(argc != 6){	
					config.argumentos_equivocados = true;
					return config;
				}
				obtener_configuracion(&config, argv, 5);
				return config;
			break;		

			case 'h':
				config.ayuda = true;
				return config;
			break;

			case 'V':
				config.version = true;	
				return config;
			break;	
		}

	}
	if (argc == 4){

		obtener_configuracion(&config, argv, 3);
		return config;
	}
	config.argumentos_equivocados = true;
	return config;
}

int main(int argc, char* argv[]){
	
	
	config_t configuracion = leer_argumentos(argc, argv);	
	
	if(configuracion.overflow){
		return ERROR_LECTURA;
	}

	if(configuracion.ayuda){
		mensaje_ayuda();
	}

	if(configuracion.version){
		mensaje_version();
	}

	if(configuracion.argumentos_equivocados){
		fprintf(stderr,"Error en los argumentos ingresados. Consulta las ayudas con ./tp1 -h\n");
		return ERROR_LECTURA;
	}
	
	automata_t automata;
	automata_instanciar(&automata, configuracion.archivo_entrada, configuracion.celdas);
	if (!automata.tabla) {
		fprintf(stderr, "Error al reservar memoria.");
		return -1;
	}

	automata_guardar(&automata, configuracion.archivo_salida);

	automata_destruir(&automata);
	return 0;
}
