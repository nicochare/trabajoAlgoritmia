#include <stdio.h>
#include <stdlib.h>
#include "procesamiento_datos.h"

void pruebaCompleta(char* RUTA, int k) {
    float aciertos = 0.0;
    tipoCola dataset;
    nuevaCola(&dataset);
    cargar_en_cola(RUTA, &dataset);
    normalizar_dataset(&dataset);

    int nElem = devolverCantidadElementos(dataset);
    Registro reg_buscado;
    tipoMaxMonticulo mm;
    nuevoMaxMonticulo(&mm, k);

    for (int i = 0; i < nElem; i++) {
        vaciarMaxMonticulo(&mm);
        // Tomo primer elemento, lo borro, hago el MM 
        reg_buscado = frente(dataset);
        desencolar(&dataset);
        cargar_datos(&dataset, &mm, reg_buscado, k);
        // y lo vuelvo a agregar (queda al final)
        encolar(&dataset, reg_buscado);
        
        if (algoritmo_knn(&mm, k) == reg_buscado.diabetes) {
            aciertos++;
        }
    }
    float porcentaje = (float)(aciertos / nElem) * 100.0; 
    printf("(k = %d) %% de acierto sin ENN: %f%%\n\n", k, porcentaje);

    algoritmo_enn(&dataset, k);

    nElem = devolverCantidadElementos(dataset);
    aciertos = 0.0;
    for (int i = 0; i < nElem; i++) {
        vaciarMaxMonticulo(&mm);
        // Tomo primer elemento, lo borro, hago el MM 
        reg_buscado = frente(dataset);
        desencolar(&dataset);
        cargar_datos(&dataset, &mm, reg_buscado, k);
        // y lo vuelvo a agregar (queda al final)
        encolar(&dataset, reg_buscado);
        
        if (algoritmo_knn(&mm, k) == reg_buscado.diabetes) {
            aciertos++;
        }
    }
    porcentaje = (float)(aciertos / nElem) * 100.0; 
    printf("(k = %d) %% de acierto con ENN: %f%%\n\n", k, porcentaje);
}

int main() {
    char* rutas[11] = {"diabetes_prediction_dataset2.csv", "diabetes_subset_50_50.csv", "filtered_diabetes_subset_50_50.csv", 
                    "diabetes_subset_55_45.csv", "filtered_diabetes_subset_55_45.csv", "diabetes_subset_60_40.csv", 
                    "filtered_diabetes_subset_60_40.csv", "diabetes_subset_65_35.csv", "filtered_diabetes_subset_65_35.csv", 
                    "diabetes_subset_70_30.csv", "filtered_diabetes_subset_70_30.csv"};
    

    printf("---RUTA: %s---\n", rutas[0]);
    for (int i = 1; i <= 100; i++) {
        pruebaCompleta(rutas[0], i);
    }
    printf("\n");
    return 0;
}