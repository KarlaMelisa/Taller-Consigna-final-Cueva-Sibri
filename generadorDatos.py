import csv
import random
from datetime import datetime, timedelta

# Define zonas y rango de datos
diaInicial = datetime(2024, 12, 26)
numDias = 30
zonas = ["quitumbe", "nayon", "cotocollao", "monteserrin", "alangasi"]

# Generador de valores aleatorios dentro de un rango
def randomFloat(valorMin, valorMax):
    return round(random.uniform(valorMin, valorMax), 1)

# Crea y escribe datos para 30 días en archivos separados por zona
for zona in zonas:
    with open(f"{zona}.csv", "w", newline="") as file:
        ingreso = csv.writer(file)
        ingreso.writerow([zona.upper(), ".", ".", ".", ".", ".", ".", "."])
        ingreso.writerow(["CO2", "SO2", "NO2", "PM2.5", "TEMPERATURA", "VELOCIDAD VIENTO", "HUMEDAD", "FECHA"])
        for dia in range(numDias):
            fecha = (diaInicial + timedelta(days=dia)).strftime("%Y-%m-%d")
            co2 = randomFloat(300, 1500)
            so2 = randomFloat(0, 70)
            no2 = randomFloat(0, 60)
            pm25 = randomFloat(0, 35)
            temperatura = randomFloat(-5, 31)
            veloViento = randomFloat(0, 15)
            humedad = randomFloat(10, 90)
            ingreso.writerow([co2, so2, no2, pm25, temperatura, veloViento, humedad, fecha])