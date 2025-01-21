#ifndef FUNCIONES_H
#define FUNCIONES_H

struct Datos{
    float co2;
    float so2;
    float no2;
    float pm25;
    float temp;
    float viento;
    float hum;
    char fecha[10];
};

struct leerDatos {
    float co2[100];
    float so2[100];
    float no2[100];
    float pm25[100];
    float temp[100];
    float viento[100];
    float hum[100];
};

int menu();
void guardarDatos( const char zonas[5][20], const char archivos[5][20]);
void monitoreo(const char archivos[5][20], const char zonas[5][20], struct leerDatos *leerDatos);
void predicManana(const char archivos[5][20], struct leerDatos *leerDatos, struct Datos *predicciones);
void printPromedios(struct leerDatos *leerDatosHis, const char archivos[5][20], const char zonas[5][20]);
void recomendaciones();
#endif // FUNCIONES_H