import matplotlib.pyplot as plt
import os
import re
import pandas as pd
import subprocess

def parse_log_file(filepath):
    # Analiza el archivo de log para extraer los tiempos de cada proceso.
    data = {}
    with open(filepath, 'r') as file:
        lines = file.readlines()
        for line in lines[1:]:  # Omitir la primera línea que es el encabezado
            version, tiempo = line.strip().split('\t')
            data[version] = float(tiempo)
    return data

def plot_execution_times(data, output_filepath, n_value):
    # Grafica los tiempos de ejecución para cada tipo de proceso.
    labels = list(data.keys())
    times = list(data.values())
    colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728']  # Colores diferentes para cada barra

    y_min = min(times) * 0.9 if min(times) * 0.9 > 0 else 0
    y_max = max(times) * 1.1

    fig, ax = plt.subplots(figsize=(12, 8))  # Aumentar el tamaño del gráfico
    bars = ax.bar(labels, times, color=colors)

    # Añadir los tiempos sobre o dentro de las barras usando bar_label
    ax.bar_label(bars, labels=[f'{time:.4f} s' for time in times], label_type='edge', color='black')

    ax.set_ylabel('Tiempo de computo (s)')
    ax.set_ylim([y_min, y_max])
    ax.set_title(f'Tiempo de computo para la sumatoria de números flotantes con arreglo N={n_value}\nen cada tipo de proceso', pad=20)
    plt.xticks(rotation=0)
    plt.subplots_adjust(top=0.85)  # Ajustar el espacio superior para evitar advertencias
    plt.savefig(output_filepath)
    plt.show()

def main():
    # Valor de N
    N = int(input("Ingrese el valor de N: "))

    # Revisar si existe el archivo de log más reciente y eliminarlo si existe
    log_dir = "registros"
    if not os.path.exists(log_dir):
        os.makedirs(log_dir)

    latest_log = os.path.join(log_dir, f"sumatoria-flotante_n{N}_latest.log")
    if os.path.exists(latest_log):
        os.remove(latest_log)

    # Compilar y ejecutar el programa en C
    subprocess.run(["gcc", "sumatoria_flotante.c", "-o", "sumatoria_flotante", "-fopenmp"])
    subprocess.run(["./sumatoria_flotante"], input=f"{N}\n", text=True)
    print("\nPrograma de C corriendo.\n")

    # Encontrar el archivo de log generado
    log_files = [os.path.join(log_dir, f) for f in os.listdir(log_dir) if f.endswith(".log")]
    if not log_files:
        print("No se encontraron archivos de log.")
        return

    latest_log = max(log_files, key=os.path.getctime)
    data = parse_log_file(latest_log)

    # Generar el nombre del gráfico con el mismo nombre del archivo de log
    output_graph = os.path.splitext(latest_log)[0] + ".png"
    plot_execution_times(data, output_graph, N)

if __name__ == "__main__":
    main()
