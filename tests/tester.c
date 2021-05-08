#include "tester.h"

void tester_crear(tester_t* tester){
	tester->pruebas_pasadas = 0;
	tester->pruebas_totales = 0;
}

void hacer_prueba(tester_t* tester, bool (*prueba) (void), char* explicacion){
	tester->pruebas_totales++;

	bool aprobo = prueba();

	if (aprobo) {

		tester->pruebas_pasadas++;
	}
	printf("\n");
	printf("%s:\n", explicacion);
	printf("Prueba numero %d resultado: %s\n", tester->pruebas_totales, (aprobo? "aprobada" : "desaprobada"));
}

void veredicto(tester_t* tester){
	printf("\n");
	printf("		.:: RESULTADOS DE LAS PRUEBAS ::.		\n");
	printf("De %d pruebas se aprobaron %d\n", tester->pruebas_totales, tester->pruebas_pasadas);
	printf("De %d pruebas se desaprobaron %d\n", tester->pruebas_totales, (tester->pruebas_totales - tester->pruebas_pasadas));
}


