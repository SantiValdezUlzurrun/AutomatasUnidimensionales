#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <getopt.h>

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
	// ./autocel [-hV]
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

void leer_argumentos(int argc, char* argv[], config_t* config){

	static struct option opciones_largas[] = {
		{"help", no_argument, 0, 'h'},
		{"output", required_argument, 0, 'o'},
		{"version", no_argument, 0, 'V'},
		{0, 0, 0, 0}
	};

	int opt;
	
	while((opt = getopt_long(argc, argv, "o:Vh", opciones_largas, NULL)) != -1 ) {
		
		switch(opt){

			case 'o':
				if(argc != 6){
					fprintf(stderr,"Error en los argumentos: Insuficiente información. Consulta las ayudas con ./tp1 -h\n");
					config->argumentos_equivocados = true;
					return;
				}
				obtener_configuracion(config, argv, 5);

			break;		

			case 'h':
				config->ayuda = true;
			break;

			case 'V':
				config->version = true;
			break;

			default:
				fprintf(stderr,"Error en los argumentos: Insuficiente información. Consulta las ayudas con ./autocel -h\n");
			break;
		}

	}
	if (argc == 4){

		obtener_configuracion(config, argv, 3);
	}
}

int main(int argc, char* argv[]){
	
	config_t configuracion = {false, false, false, false, 0, 0, "", ""};
	leer_argumentos(argc, argv, &configuracion);
	printf("overflow: %d\nargumentos_equivocados: %d\nayuda: %d\nversion: %d\nregla: %d\nceldas: %d\narchivo_entrada: %s\narchivo_salida: %s\n",
			configuracion.overflow,
			configuracion.argumentos_equivocados,
			configuracion.ayuda,
			configuracion.version,
			configuracion.regla,
			configuracion.celdas,
			configuracion.archivo_entrada,
			configuracion.archivo_salida);
	return 0;
}
