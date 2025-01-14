import random
import csv
from datetime import datetime, timedelta

# Define zonas y rango de datos
diaInicial = datetime(2024, 12, 26)
numDias = 30

# Generador de valores aleatorios dentro de un rango
def randomFloat(valorMin, valorMax):
    return round(random.uniform(valorMin, valorMax), 1)

# Crea datos para 30 dias
datos= []
for dia in range(numDias):
    fecha = (diaInicial + timedelta(days=dia)).strftime("%Y-%m-%d")
    for zona in range(1,6):
        co2 = randomFloat(350, 1500)
        so2 = randomFloat(0, 500)
        no2 = randomFloat(5, 60)
        pm25 = randomFloat(5, 100)
        temperatura = randomFloat(-10, 30)
        veloViento = randomFloat(0, 50)
        humedad = randomFloat(20, 90)
        datos.append([co2, so2, no2, pm25, temperatura, veloViento, humedad, fecha])

# Escribe datos en diferentes archivos CSV dependiento del sector
with open("quitumbe.csv", "w", newline="") as file:
    ingreso = csv.writer(file)
    ingreso.writerow(["QUITUMBE", ".", ".", ".", ".", ".", ".", "."])
    ingreso.writerow(["CO2", "SO2", "NO2", "PM2.5", "TEMPERATURA", "VELOCIDAD VIENTO", "HUMEDAD", "FECHA"])
    ingreso.writerows(datos)
with open("nayon.csv", "w", newline="") as file:
    ingreso = csv.writer(file)
    ingreso.writerow(["NAYON", ".", ".", ".", ".", ".", ".", "."])
    ingreso.writerow(["CO2", "SO2", "NO2", "PM2.5", "TEMPERATURA", "VELOCIDAD VIENTO", "HUMEDAD", "FECHA"])
    ingreso.writerows(datos)
with open("cotocollao.csv", "w", newline="") as file:
    ingreso = csv.writer(file)
    ingreso.writerow(["COTOCOLLAO", ".", ".", ".", ".", ".", ".", "."])
    ingreso.writerow(["CO2", "SO2", "NO2", "PM2.5", "TEMPERATURA", "VELOCIDAD VIENTO", "HUMEDAD", "FECHA"])
    ingreso.writerows(datos)
with open("monteserrin.csv", "w", newline="") as file:
    ingreso = csv.writer(file)
    ingreso.writerow(["MONTESERRIN", ".", ".", ".", ".", ".", ".", "."])
    ingreso.writerow(["CO2", "SO2", "NO2", "PM2.5", "TEMPERATURA", "VELOCIDAD VIENTO", "HUMEDAD", "FECHA"])
    ingreso.writerows(datos)
with open("alangasi.csv", "w", newline="") as file:
    ingreso = csv.writer(file)
    ingreso.writerow(["ALANGASI", ".", ".", ".", ".", ".", ".", "."])
    ingreso.writerow(["CO2", "SO2", "NO2", "PM2.5", "TEMPERATURA", "VELOCIDAD VIENTO", "HUMEDAD", "FECHA"])
    ingreso.writerows(datos)
print("Datos generados y guardados exitosamente.")