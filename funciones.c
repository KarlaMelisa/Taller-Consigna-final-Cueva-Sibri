#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

struct Datos min = {100,0,0,0,0,0,30};
struct Datos max = {1000,40,25,15,36,10,70};

int menu(){
    int opcion=0;    
    printf("--------------MENU DE SELECCION:-------------\n");
    printf("1. Ingreso de datos \n");
    printf("2. Monitoreo de contaminacion actual\n");
    printf("3. Prediccion de datos en 24h\n");
    printf("4. Promedio de datos historicos\n");
    printf("5. Recomendaciones\n");
    printf("6. Salir\n>> ");
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
    do{
    printf("Nivel de Co2 en ppm: \n>> ");
    scanf("%f", &datos.co2);
        if (datos.co2 < min.co2 || datos.co2 > 2000){
            printf("Nivel de Co2 fuera de rango, intente de nuevo\n");
        }
    } while (datos.co2 < min.co2 || datos.co2 > 2000);

    do{
    printf("Nivel de So2 en µg/m³: \n>> ");
    scanf("%f", &datos.so2);
    if (datos.so2 < min.so2 || datos.so2 > 60){
        printf("Nivel de So2 fuera de rango, intente de nuevo\n");
    }
    } while (datos.so2 < min.so2 || datos.so2 > 60);
    
    do{
        printf("Nivel de No2 en µg/m³: \n>> ");
        scanf("%f", &datos.no2);
        if (datos.no2 < min.no2 || datos.no2 > 50){
            printf("Nivel de No2 fuera de rango, intente de nuevo\n");
        }
    } while (datos.no2 < min.no2 || datos.no2 > 50);
    
    do{
         printf("Nivel de PM2.5 en µg/m³: \n>> ");
        scanf("%f", &datos.pm25);
        if (datos.pm25 < min.pm25 || datos.pm25 > 25){
            printf("Nivel de PM2.5 fuera de rango, intente de nuevo\n");
        }
    } while (datos.pm25 < min.pm25 || datos.pm25 > 25);

    do{
        printf("Temperatura en °C: \n>> ");
        scanf("%f", &datos.temp);
        if (datos.temp < 10 || datos.temp > 40){
            printf("Temperatura fuera de rango, intente de nuevo\n");
        }
    } while (datos.temp < 10 || datos.temp > 40);
    
    do{
        printf("Velocidad del viento en km/h: \n>> ");
        scanf("%f", &datos.viento);
        if (datos.viento < min.viento || datos.viento > 30){
            printf("Velocidad del viento fuera de rango, intente de nuevo\n");
        }
    } while (datos.viento < min.viento || datos.viento > 30);

    do{
        printf("Humedad en porcentaje: \n>> ");
        scanf("%f", &datos.hum);
        if (datos.hum < min.hum || datos.hum > 80){
            printf("Humedad fuera de rango, intente de nuevo\n");
        }
    } while (datos.hum < min.hum || datos.hum > 80);
    
    printf("Fecha (aaaa-mm-dd): \n>> ");
    scanf("%s", datos.fecha);
    fprintf(fzona, "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%s\n", datos.co2, datos.so2, datos.no2, datos.pm25, datos.temp, datos.viento, datos.hum, datos.fecha);
}

void guardarDatos( const char zonas[5][20], const char archivos[5][20]){
    int i=0;
    for (int i = 0; i < 5; i++){
        printf("-----------------INGRESO DATOS DE %s-----------------\n", zonas[i]);
        FILE *file = fopen(archivos[i], "a");
        if (file == NULL){
            printf("Error al abrir el archivo %s\n", archivos[i]);
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

float promedioPonderado(float datos[100], int i) {
    float prom = 0;
    float totalPeso = 0;
    for (int j = 0; j < i; j++) {
        float peso = (float)(j + 1) / i; // Peso creciente para días más recientes
        prom += datos[j] * peso;
        totalPeso += peso;
    }
    prom = prom / totalPeso;
    return prom;
}

// Función para predecir datos para las próximas 24 horas
void predicManana(const char archivos[5][20], struct leerDatos *leerDatos, struct Datos *predicciones) {
    FILE *file = fopen("predicciones.txt", "w");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    
    const char zonas[5][20] = {"ALANGASI", "COTOCOLLAO", "MONTESSERIN", "NAYON", "QUITUMBE"};
    for (int j = 0; j < 5; j++) {
        int numDatos = leerArchivos(archivos[j], leerDatos);
        predicciones[j].co2 = promedioPonderado(leerDatos->co2, numDatos);
        predicciones[j].so2 = promedioPonderado(leerDatos->so2, numDatos);
        predicciones[j].no2 = promedioPonderado(leerDatos->no2, numDatos);
        predicciones[j].pm25 = promedioPonderado(leerDatos->pm25, numDatos);
        predicciones[j].temp = promedioPonderado(leerDatos->temp, numDatos);
        predicciones[j].viento = promedioPonderado(leerDatos->viento, numDatos);
        predicciones[j].hum = promedioPonderado(leerDatos->hum, numDatos);
        strcpy(predicciones[j].fecha, " "); 
        printf("-------------------------PREDICCION PARA MANANA DE %s-------------------------\n", zonas[j]);
        printf("CO2: %.2f\n", predicciones[j].co2);
        printf("SO2: %.2f\n", predicciones[j].so2);
        printf("NO2: %.2f\n", predicciones[j].no2);
        printf("PM2.5: %.2f\n", predicciones[j].pm25);
        printf("Temperatura: %.2f\n", predicciones[j].temp);
        printf("Viento: %.2f\n", predicciones[j].viento);
        printf("Humedad: %.2f\n", predicciones[j].hum);
        fprintf(file,"-------------------------PREDICCION PARA MANANA DE %s-------------------------\n", zonas[j]);
        fprintf(file, "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", predicciones[j].co2, predicciones[j].so2, predicciones[j].no2, predicciones[j].pm25, predicciones[j].temp, predicciones[j].viento, predicciones[j].hum);
    }
    fclose(file);
}

void rangos(struct Datos promedios, const char zonas[20], struct Datos min, struct Datos max){
    FILE *file = fopen("monitoreo.txt", "a");
    if (file == NULL) {
        printf("Error al abrir el archivo \n");
        return;
    }

    printf("-----------------MONITOREO DE DATOS ULTIMOS 30 DIAS EN %s-----------------\nDatos en alerta de peligro:\n", zonas);

    fprintf(file, "-----------------MONITOREO DE DATOS ULTIMOS 30 DIAS EN %s-----------------\nDatos en alerta de peligro:\n", zonas);

    if (promedios.co2 < min.co2 || promedios.co2 > max.co2) {
        printf("CO2 fuera del rango: %.2f\n", promedios.co2);
        fprintf(file, "CO2 fuera del rango: %.2f\n", promedios.co2);
    }
    if (promedios.so2 < min.so2 || promedios.so2 > max.so2) {
        printf("SO2 fuera del rango: %.2f\n", promedios.so2);
        fprintf(file, "SO2 fuera del rango: %.2f\n", promedios.so2);
    }
    if (promedios.no2 < min.no2 || promedios.no2 > max.no2) {
        printf("NO2 fuera del rango: %.2f\n", promedios.no2);
        fprintf(file, "NO2 fuera del rango: %.2f\n", promedios.no2);
    }
    if (promedios.pm25 < min.pm25 || promedios.pm25 > max.pm25) {
        printf("PM2.5 fuera del rango: %.2f\n", promedios.pm25);
        fprintf(file, "PM2.5 fuera del rango: %.2f\n", promedios.pm25);
    }
if (promedios.temp < min.temp || promedios.temp > max.temp) {
        printf("Temperatura fuera del rango: %.2f\n", promedios.temp);
        fprintf(file, "Temperatura fuera del rango: %.2f\n", promedios.temp);
    }
    if (promedios.viento < min.viento || promedios.viento > max.viento) {
        printf("Velocidad del viento fuera del rango: %.2f\n", promedios.viento);
        fprintf(file, "Velocidad del viento fuera del rango: %.2f\n", promedios.viento);
    }
    if (promedios.hum < min.hum || promedios.hum > max.hum) {
        printf("Humedad fuera del rango: %.2f\n", promedios.hum);
        fprintf(file, "Humedad fuera del rango: %.2f\n", promedios.hum);
    }

    fclose(file);

}


void printPromedios(struct leerDatos *leerDatosHis, const char archivos[5][20], const char zonas[5][20]){
    for (int j = 0; j < 5; j++) {
        int numDatos = leerArchivos(archivos[j], leerDatosHis);
        if (numDatos > 0) {
            struct Datos promediosHis;
            promediosHis.co2 = promedio(leerDatosHis->co2, numDatos);
            promediosHis.so2 = promedio(leerDatosHis->so2, numDatos);
            promediosHis.no2 = promedio(leerDatosHis->no2, numDatos);
            promediosHis.pm25 = promedio(leerDatosHis->pm25, numDatos);
            promediosHis.temp = promedio(leerDatosHis->temp, numDatos);
            promediosHis.viento = promedio(leerDatosHis->viento, numDatos);
            promediosHis.hum = promedio(leerDatosHis->hum, numDatos);

            printf("-----------------PROMEDIOS DE DATOS HISTORICOS EN %s-----------------\n", zonas[j]);
            printf("CO2: \n>>%.2f\n", promediosHis.co2);
            printf("SO2: \n>>%.2f\n", promediosHis.so2);
            printf("NO2: \n>>%.2f\n", promediosHis.no2);
            printf("PM2.5: \n>>%.2f\n", promediosHis.pm25);
            printf("Temperatura: \n>>%.2f\n", promediosHis.temp);
            printf("Velocidad del Viento: \n>>%.2f\n", promediosHis.viento);
            printf("Humedad: \n>>%.2f\n", promediosHis.hum);
        } else {
            printf("No se encontraron datos en el archivo %s\n", archivos[j]);
        }
    }
}

void monitoreo(const char archivos[5][20], const char zonas[5][20], struct leerDatos *leerDatos){
    for (int j=0; j<5; j++){
        int i= leerArchivos(archivos[j], leerDatos);
        float prom_co2 = promedio(leerDatos->co2, i);
        float prom_so2 = promedio(leerDatos->so2, i);
        float prom_no2 = promedio(leerDatos->no2, i);
        float prom_pm25 = promedio(leerDatos->pm25, i);
        float prom_temp = promedio(leerDatos->temp, i);
        float prom_viento = promedio(leerDatos->viento, i);
        float prom_hum = promedio(leerDatos->hum, i);

        struct Datos promediosMoni[5];
        promediosMoni[j].co2 = prom_co2;
        promediosMoni[j].so2 = prom_so2;
        promediosMoni[j].no2 = prom_no2;
        promediosMoni[j].pm25 = prom_pm25;
        promediosMoni[j].temp = prom_temp;
        promediosMoni[j].viento = prom_viento;
        promediosMoni[j].hum = prom_hum;
        strcpy(promediosMoni[j].fecha, " ");
        rangos(promediosMoni[j],zonas[j], min, max);
    }
}

void recomendaciones(){
    printf("Recomendaciones para prevenir la contaminacion del aire:\n1. FACTORES GLOBALES:\nTecnologias limpias: Incentivar el uso de energias renovables y vehiculos electricos.\nMonitoreo global: Fomentar el uso de tecnologias para recopilar datos sobre la calidad del aire.\n\n2. FACTORES CULTURALES:\nEducacion ambiental: Sensibilizar a las comunidades sobre la importancia de la calidad del aire.\nPracticas sostenibles: Fomentar el uso de tradiciones culturales que protejan el medio ambiente.\nMovilidad sostenible: Promover el uso de transporte publico limpio y bicicletas.\n\n3. FACTORES SOCIALES:\nParticipacion comunitaria: Involucrar a las comunidades en la toma de decisiones sobre la contaminacion.\nReduccion de residuos: Promover el reciclaje y evitar la quema de basura.\n\n4. FACTORES AMBIENTALES:\nProtección de ecosistemas: Restaurar bosques y humedales que absorban contaminantes.\nAgricultura sostenible: Reducir el uso de pesticidas y fertilizantes químicos.\nReforestacion urbana: Plantar arboles para mejorar la calidad del aire en ciudades.\n");
}
