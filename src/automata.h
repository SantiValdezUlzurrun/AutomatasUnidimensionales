#ifndef AUTOMATA_H
#define AUTOMATA_H

typedef struct automata {
	unsigned int cantidad_celdas;
	unsigned char* tabla;
	unsigned char regla;
} automata_t;

unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j, unsigned char regla, unsigned int N);


void automata_instanciar(automata_t* automata, char* file, unsigned int celdas, unsigned char regla);

void automata_avanzar(automata_t* automata);

void automata_imprimir(automata_t* automata);

void automata_guardar(automata_t* automata, char* salida);

void automata_destruir(automata_t* automata);

#endif /* AUTOMATA_H */
