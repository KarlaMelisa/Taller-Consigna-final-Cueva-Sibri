#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

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
    printf("Nivel de Co2 en ppm: \n>> ");
    scanf("%f", &datos.co2);
    printf("Nivel de So2 en µg/m³: \n>> ");
    scanf("%f", &datos.so2);
    printf("Nivel de No2 en µg/m³: \n>> ");
    scanf("%f", &datos.no2);
    printf("Nivel de PM2.5 en µg/m³: \n>> ");
    scanf("%f", &datos.pm25);
    printf("Temperatura en grados celsius: \n>> ");
    scanf("%f", &datos.temp);
    printf("Velocidad del viento en km/h: \n>> ");
    scanf("%f", &datos.viento);
    printf("Humedad en porcentaje: \n>> ");
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

void predicciones(struct Datos promedios, const char zonas[20]){
    struct Datos min = {200,0,0,0,18,0,30};
    struct Datos max = {1000,40,25,15,30,10,70};
    printf("-----------------MONITOREO DE DATOS ULTIMOS 30 DIAS EN %s-----------------\n", zonas);    
    if (promedios.co2 < min.co2 || promedios.co2 > max.co2) {
        printf("Promedio de CO2 fuera del rango: %.1f\n", promedios.co2);
    }
    if (promedios.so2 < min.so2 || promedios.so2 > max.so2) {
        printf("Promedio de SO2 fuera del rango: %.1f\n", promedios.so2);
    }
    if (promedios.no2 < min.no2 || promedios.no2 > max.no2) {
        printf("Promedio de NO2 fuera del rango: %.1f\n", promedios.no2);
    }
    if (promedios.pm25 < min.pm25 || promedios.pm25 > max.pm25) {
        printf("Promedio de PM2.5 fuera del rango: %.1f\n", promedios.pm25);
    }
    if (promedios.temp < min.temp || promedios.temp > max.temp) {
        printf("Promedio de temperatura fuera del rango: %.1f\n", promedios.temp);
    }
    if (promedios.viento < min.viento || promedios.viento > max.viento) {
        printf("Promedio de velocidad del viento fuera del rango: %.1f\n", promedios.viento);
    }
    if (promedios.hum < min.hum || promedios.hum > max.hum) {
        printf("Promedio de humedad fuera del rango: %.1f\n", promedios.hum);
    }
}

void monitoreo(const char archivos[5][20], const char zonas[5][20], struct leerDatos *leerDatos, struct Datos *promedios){
    for (int j=0; j<5; j++){
        int i= leerArchivos(archivos[j], leerDatos);
        float prom_co2 = promedio(leerDatos->co2, i);
        float prom_so2 = promedio(leerDatos->so2, i);
        float prom_no2 = promedio(leerDatos->no2, i);
        float prom_pm25 = promedio(leerDatos->pm25, i);
        float prom_temp = promedio(leerDatos->temp, i);
        float prom_viento = promedio(leerDatos->viento, i);
        float prom_hum = promedio(leerDatos->hum, i);

        promedios[j].co2 = prom_co2;
        promedios[j].so2 = prom_so2;
        promedios[j].no2 = prom_no2;
        promedios[j].pm25 = prom_pm25;
        promedios[j].temp = prom_temp;
        promedios[j].viento = prom_viento;
        promedios[j].hum = prom_hum;
        strcpy(promedios[j].fecha, " ");
        predicciones(*promedios,zonas[j]);
    }
}


