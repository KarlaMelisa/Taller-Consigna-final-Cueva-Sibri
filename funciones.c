#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

struct leerDatos leerDatos;

int menu(){
    int opcion=0;    
    printf("--------------MENU DE SELECCION:-------------\n");
    printf("1. Ingreso de datos \n");
    printf("2. Monitoreo de contaminacion actual\n");
    printf("3. Predicción de datos en 24h\n");
    printf("4. Promedio de datos historicos\n");
    printf("5. Salir\n>> ");
    scanf("%d", &opcion);
    do{
        if (opcion < 1 || opcion > 5){
            printf("Opcion no valida, intente de nuevo\n>> ");
            scanf("%d", &opcion);
        }
    } while (opcion < 1 || opcion > 5);
    return opcion;
}

void ingresoDatos(FILE *fzona){
    struct Datos datos;
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
    printf("Fecha (aaaa-mm-dd): \n>> ");
    scanf("%s", datos.fecha);
    fprintf(fzona, "%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%s\n", datos.co2, datos.so2, datos.no2, datos.pm25, datos.temp, datos.viento, datos.hum, datos.fecha);
}

void guardarDatos( const char zonas[5][20], const char archivos[5][20]){
    int i=0;
    for (int i = 0; i < 5; i++){
        printf("-----------------INGRESO DATOS DE %s-----------------\n", archivos[i]);
        FILE *file = fopen(zonas[i], "a");
        if (file == NULL){
            printf("Error al abrir el archivo %s\n", zonas[i]);
            continue;
        }
        ingresoDatos(file);
        printf("Datos guardados correctamente\n");
        fclose(file);
    }
}

int leerArchivos(const char *filename, struct leerDatos *leerDatos){ //Funcion para leer los datos de los archivos
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("Error al abrir el archivo %s\n", filename);
        return 0;
    }
    int i = 0, numLineas=0;
    char buffer[256];
    while (fgets(buffer, 256, file) != NULL){
        numLineas++;
        if (numLineas > 2){
                if (sscanf(buffer, "%f,%f,%f,%f,%f,%f,%f", &leerDatos->co2[i], &leerDatos->so2[i], &leerDatos->no2[i], &leerDatos->pm25[i], &leerDatos->temp[i], &leerDatos->viento[i], &leerDatos->hum[i])==7) 
                i++;
                else{
                    printf("Error leyendo los datos del archivo\n");
                    break;
                }
            }
        }
    fclose(file);
    return i;   
}

float promedio(float datos[100], int i){ 
    float prom=0;
    for (int j=0; j<i; j++){
        prom+=datos[j];
    }
    prom=prom/i;
    return prom;
}

float calcularAPI(){
    
}

float predicManana(const char *archivo, struct leerDatos *leerDatos){ 

    int i= leerArchivos(archivo, leerDatos);
    float prom_co2 = calcPromPond(leerDatos->co2, i);
    float prom_so2 = calcPromPond(leerDatos->so2, i);
    float prom_no2 = calcPromPond(leerDatos->no2, i);
    float prom_pm25 = calcPromPond(leerDatos->pm25, i);
    float prom_temp = calcPromPond(leerDatos->temp, i);
    float prom_viento = calcPromPond(leerDatos->viento, i);
    float prom_hum = calcPromPond(leerDatos->hum, i);

    struct Datos proms = {prom_co2, prom_so2, prom_no2, prom_pm25, prom_temp, prom_viento, prom_hum, " "}; //Estructura con los promedios de los datos, none es la fecha que no se usa en calculos
    float api = calcAPI(&proms);
    return api;
}

void alerta(const char archivos[5][20], const char zonas[5][20]){
    float api=0;
    for (int i=0; i<5; i++){
        api=predicManana(archivos[i], &leerDatos);
        if (api>200){
            printf("\nALERTA DE PELIGRO: Los indices para manana en %s superan los limites para la salud.", zonas[i]);
        }
    }
}