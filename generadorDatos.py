import random
import csv
from datetime import datetime, timedelta

# Define zonas y rango de datos
zonas = ["Quitumbe", "Nayon", "Cotocollao", "Monteserrin", "Calderon"]
diaInicial = datetime(2024, 12, 26)
numDias = 30

# Generador de valores aleatorios dentro de un rango
def randomFloat(valorMin, valorMax, decimales=1):
    return round(random.uniform(valorMin, valorMax), decimales)

# Crea datos para 30 dias
datos= []
for dia in range(numDias):
    fecha = (diaInicial + timedelta(days=dia)).strftime("%Y-%m-%d")
    for zona in zonas:
        co2 = randomFloat(350, 450)
        so2 = randomFloat(0, 20)
        no2 = randomFloat(5, 60)
        pm25 = randomFloat(5, 100)
        temperatura = randomFloat(-10, 30)
        veloViento = randomFloat(0, 50)
        humedad = randomFloat(20, 90)
        datos.append([zona, co2, so2, no2, pm25, temperatura, veloViento, humedad, fecha])

# Escribe datos en archivo CSV
with open("datos.csv", "w", newline="") as file:
    ingreso = csv.writer(file)
    ingreso.writerow(["ZONA", "CO2", "SO2", "NO2", "PM2.5", "TEMPERATURA", "VELOCIDAD VIENTO", "HUMEDAD", "FECHA"])
    ingreso.writerows(datos)

print("Datos generados y guardados exitosamente en 'datos.csv'.")