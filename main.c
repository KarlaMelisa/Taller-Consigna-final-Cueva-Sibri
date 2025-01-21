#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    const char archivos[5][20] = {"alangasi.csv", "cotocollao.csv", "monteserrin.csv", "nayon.csv", "quitumbe.csv"};
    const char zonas[5][20] = {"ALANGASI", "COTOCOLLAO", "MONTESSERIN", "NAYON", "QUITUMBE"};
    struct Datos datos;
    struct Datos promedios[5];
    struct leerDatos leerDatos;
    struct leerDatos leerDatosHis;

    int op;
    do{   
        op = menu();
        switch (op){
        case 1:
            guardarDatos(zonas, archivos);
            break;
        case 2:
            monitoreo(archivos, zonas, &leerDatos);
            break;
        case 3:
            predicManana(archivos, &leerDatos, &datos);
            break;
        case 4:
            printPromedios(&leerDatosHis, archivos, zonas);
            break;
        case 5:
            recomendaciones();
            break;
        case 6:
            printf("Saliendo del programa\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (op >= 1 && op < 7);
    
    
    return 0;
}