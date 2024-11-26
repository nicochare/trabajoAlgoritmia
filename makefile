PARAMS = -Wall -g

all: main

modulo_algoritmo: algoritmo_knn.c
	gcc $(PARAMS) -c algoritmo_knn.c

modulo_lectura: lectura_datos.c
	gcc $(PARAMS) -c lectura_datos.c

modulo_procesamiento: procesamiento_datos.c
	gcc $(PARAMS) -c procesamiento_datos.c

modulo_minmonticulo: min_monticulo.c
	gcc $(PARAMS) -c min_monticulo.c

modulo_registro: registro.c
	gcc $(PARAMS) -c registro.c

main: main.c lectura_datos.o algoritmo_knn.o procesamiento_datos.o min_monticulo.o registro.o
	gcc $(PARAMS) main.c -o main.o algoritmo_knn.o lectura_datos.o procesamiento_datos.o min_monticulo.o registro.o -lm