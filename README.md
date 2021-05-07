# Automata Celular Unidimensional

Implementacion en C de automatas celulares unidimensionales para MIPS32

## Aplicacion

Se trata de una version en lenguaje C de un programa que computa
automatas celulares para reglas arbitrarias. El programa recibira por como
argumentos el numero de regla R, la cantidad de celdas de una fila N y
el nombre de un archivo de texto con el contenido del estado inicial del
automata, y escribira un archivo .PBM representando la evolucion del
automata celular en una matriz de NxN . El archivo de estado inicial debe
contener una lınea con N dıgitos binarios, con 1 representando una celda
ocupada y 0 una vacıa. De haber errores, los mensajes de error deberan salir
exclusivamente por stderr

## Uso

```bash
$ autcel -h
Uso:
autcel -h
autcel -V
autcel R N inputfile [-o outputprefix]
Opciones:
	-h, --help Imprime este mensaje.
	-V, --version Da la version del programa.
	-o Prefijo de los archivos de salida.
Ejemplos:
	autcel 30 80 inicial -o evolucion
	Calcula la evolucion del automata "Regla 30",
	en un mundo unidimensional de 80 celdas, por 80 iteraciones.
	El archivo de salida se llamara evolucion.pbm.
	Si no se da un prefijo para los archivos de salida,
	el prefijo sera el nombre del archivo de entrada.
```
