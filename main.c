#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    const char archivos[5][20] = {"alangasi.csv", "cotocollao.csv", "monteserrin.csv", "nayon.csv", "quitumbe.csv"};
    const char zonas[5][20] = {"ALANGASI", "COTOCOLLAO", "MONTESSERIN", "NAYON", "QUITUMBE"};
    struct Datos datos;

    do{
        int op = menu();
        switch (op){
        case 1:
            guardarDatos(archivos, zonas);
            break;
        case 2:

            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (1);
    
    
    return 0;
}