#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    const char archivos[5][20] = {"alangasi.csv", "cotocollao.csv", "monteserrin.csv", "nayon.csv", "quitumbe.csv"};
    const char zonas[5][20] = {"ALANGASI", "COTOCOLLAO", "MONTESSERIN", "NAYON", "QUITUMBE"};
    struct Datos datos;
    struct Datos promedios;
    struct leerDatos leerDatos;

    do{
        int op = menu();
        switch (op){
        case 1:
            guardarDatos(zonas, archivos);
            break;
        case 2:
            monitoreo(archivos, zonas, &leerDatos, &promedios);
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (1);
    
    
    return 0;
}