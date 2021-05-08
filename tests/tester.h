#ifndef TESTER_H_
#define TESTER_H_

#include <stdbool.h>
#include <stdio.h>

typedef struct tester {
	unsigned int pruebas_pasadas;
	unsigned int pruebas_totales;
} tester_t;


void tester_crear(tester_t* tester);


void hacer_prueba(tester_t* tester, bool (*prueba) (void), char* explicacion);


void veredicto(tester_t* tester);


#endif /* TESTER_H_ */
