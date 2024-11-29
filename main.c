#include "procesamiento_datos.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define TAMANIODATASET 100000
#define RUTA "diabetes_prediction_dataset.csv"

int obtener_k() {
    int k = 0;
    while (k < 1 || k > TAMANIODATASET) {
        printf("Por favor, introduce la K a utilizar: ");
        scanf("%d", &k);
    }
    return k;
}

// TODO: NECESARIO eliminar el elemento que se este comparando del maxmon y reagregarlo al final
// TODO: NECESARIO ver la forma de mantener el 
//       elemento X en cola hasta el final del analisis y luego borrar ese en especifico.

void algoritmo_enn(tipoCola* c, int k, tipoMaxMonticulo* mm_limpio) {
    int nElem = devolverCantidad(*c);
    int* borrados = NULL;
    int nBorrados = 0;
    Registro reg_buscado;
    tipoMaxMonticulo mm;
    
    nuevoMaxMonticulo(&mm, k);

    printf("\nN° registros antes de aplicar ENN: %d\n", nElem);
    for (int i = 0; i < nElem; i++) {
        for (int j = 0; j < k; j++) {

            // Tomo primer elemento, lo borro, hago el MM 
            reg_buscado = frente(*c);
            desencolar(c);
            cargar_datos(c, &mm, reg_buscado, k);
            // y lo vuelvo a agregar (queda al final)
            encolar(c, reg_buscado);

            if (algoritmo_knn(&mm, k) == mm.array[i].reg.diabetes) {
                float distancia = mm.array[i].distancia;
                Registro reg = mm.array[i].reg;
                insertarMaxMonticulo(mm_limpio, reg, distancia);
            } else {
                nBorrados++;
                borrados = (int*)realloc(borrados, nBorrados * sizeof(int));
                borrados[nBorrados - 1] = i;
            }
        }
    }

    // TODO: Hace falta hacer esto? creo que se puede borrar total nos importa el n° de elementos borrados nomas, no realmente borrarlos
            // Lo dejo comentado abajo x las dudas, de ultima descomentamos
    // TODO: También se puede borrar la variable int* borrados si no los borramos de la cola
    
    // for (int i = 0; i < nBorrados; i++) {
        // funcion que borra el elemento borrados[i] de la cola "tipoCola* c"
    // }

    free(borrados);
    nElem -= nBorrados;
    printf("N° registros después de aplicar ENN: %d\n", nElem);
}


int main() {
    Registro* conjuntoDeEjemplos = (Registro*)malloc(5*sizeof(Registro));
    
    // Apartado 1
    tipoCola dataset;
    nuevaCola(&dataset);
    cargar_en_cola(RUTA, &dataset);

    // Apartado 2
    normalizar_dataset(&dataset);

    // Apartado 3
    tipoMaxMonticulo mm;
    nuevoMaxMonticulo(&mm, TAMANIODATASET);

    // Apartado 4
    printf("\n\nClasificación de un ejemplo nuevo mediante K-NN para K=1\n");
    printf("Se utilizará un ejemplo de paciente con los siguientes datos:\n");
    printf("    - Genero:              Hombre\n");
    printf("    - Edad:                37\n");
    printf("    - Hipertension:        No\n");
    printf("    - Enfermedad Cardíaca: No\n");
    printf("    - Historial fumador:   Alguna vez lo fue\n");
    printf("    - BMI:                 25.72\n");
    printf("    - Niveles HbA1c:       3.5\n");
    printf("    - Niveles Glucosa:     149\n\n");
    
    Registro reg_buscado = new_registro(0.0, 37.0, 0.0, 0.0, 6.0, 25.72, 3.5, 149.0);
    int k = 1;
    normalizar_registro(&reg_buscado);
    cargar_datos(&dataset, &mm, reg_buscado, k);
    bool resultado = algoritmo_knn(&mm, k);
    interpretacion_resultado(resultado);

    // Apartado 5
    printf("\n\nClasificación de un conjunto de ejemplos mediante K-NN para K=1\n");
    
    int i = 0;
    while (i < 5) {
        reg_buscado = conjuntoDeEjemplos[i];
        normalizar_registro(&reg_buscado);

        cargar_datos(&dataset, &mm, reg_buscado, k);
        resultado = algoritmo_knn(&mm, k);
        interpretacion_resultado(resultado);
        i++;
    }

    // Apartado 6
    printf("\n\nClasificación de un ejemplo nuevo mediante K-NN para K=k\n");
    printf("Se utilizará un ejemplo de paciente con los siguientes datos:\n");
    printf("    - Genero:              Hombre\n");
    printf("    - Edad:                37\n");
    printf("    - Hipertension:        No\n");
    printf("    - Enfermedad Cardíaca: No\n");
    printf("    - Historial fumador:   Alguna vez lo fue\n");
    printf("    - BMI:                 25.72\n");
    printf("    - Niveles HbA1c:       3.5\n");
    printf("    - Niveles Glucosa:     149\n\n");
    
    k = obtener_k();
    
    reg_buscado = new_registro(0.0, 37.0, 0.0, 0.0, 6.0, 25.72, 3.5, 149.0);
    normalizar_registro(&reg_buscado);    
    
    cargar_datos(&dataset, &mm, reg_buscado, k);
    resultado = algoritmo_knn(&mm, k);
    interpretacion_resultado(resultado);

    // Apartado 7
    printf("\n\nClasificación de un conjunto de ejemplos mediante K-NN para K=k\n");
    
    k = obtener_k();
    
    i = 0;
    while (i < 5) {
        reg_buscado = conjuntoDeEjemplos[i];
        normalizar_registro(&reg_buscado);

        cargar_datos(&dataset, &mm, reg_buscado, k);
        resultado = algoritmo_knn(&mm, 1);
        interpretacion_resultado(resultado);
        i++;
    }

    // Apartado 8
    
    
    return 0;
}