#ifndef AUTOMATA_H
#define AUTOMATA_H

typedef struct automata {
	unsigned int cantidad_celdas;
	unsigned char* tabla;
} automata_t;


void automata_imprimir(automata_t* automata);

void automata_instanciar(automata_t* automata, char* file, unsigned int celdas);

void automata_guardar(automata_t* automata, char* salida);

void automata_destruir(automata_t* automata);

#endif /* AUTOMATA_H */
