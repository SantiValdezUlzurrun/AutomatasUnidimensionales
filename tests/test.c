#include "tester.h"

bool prueba() {
	//Prueba basica ejemplificando su uso
	return true;
}

int main() {
	tester_t examinador;
	tester_crear(&examinador);

	hacer_prueba(&examinador, prueba, "Prueba basica");

	veredicto(&examinador);
	return 0;
}
