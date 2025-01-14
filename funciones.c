#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int menu(){
    int opcion=0;    
    printf("----------MENU DE SELECCION:----------\n");
    printf("1. Ingreso de datos\n");
    printf("2. Monitoreo de contaminacion actual\n");
    printf("3. Predicción de datos en 24h\n");
    printf("4. Promedio de datos historicos\n");
    printf("5. Salir\n");
    scanf("%d", &opcion);
    do{
        if (opcion < 1 || opcion > 5){
            printf("Opcion no valida, intente de nuevo\n");
            scanf("%d", &opcion);
        }
    } while (opcion < 1 || opcion > 5);
    return opcion;
}

void ingresarDatos(FILE *fzona){
    FILE *fzona = fopen(fzona, "a");
    if (fzona == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }
    struct Datos datos;
    printf("-----------------INGRESO DE DATOS-----------------\n");
    printf("Nivel de Co2: \n>> ");
    scanf("%f", &datos.co2);
    printf("Nivel de So2: \n>> ");
    scanf("%f", &datos.so2);
    printf("Nivel de No2: \n>> ");
    scanf("%f", &datos.no2);
    printf("Nivel de PM2.5: \n>> ");
    scanf("%f", &datos.pm25);
    printf("Temperatura en grados celsius: \n>> ");
    scanf("%f", &datos.temp);
    printf("Velocidad del viento en km/h: \n>> ");
    scanf("%f", &datos.viento);
    printf("Humedad: \n>> ");
    scanf("%f", &datos.hum);
    fprintf(fzona, "%f,%f,%f,%f,%f,%f,%f\n", datos.co2, datos.so2, datos.no2, datos.pm25, datos.temp, datos.viento, datos.hum);
    fclose(fzona);
}