import matplotlib.pyplot as plt
import os
import re
import subprocess

def parse_log_file(filepath):
    # Analiza el archivo de log para extraer los tiempos de cada tipo de proceso.
    tiempos = {}

    with open(filepath, 'r') as file:
        lines = file.readlines()
        for line in lines[1:]:  # Omitir la cabecera
            match = re.match(r'(\w+-\d*|secuencial)\t(\d+)\t([\d\.]+)', line)
            if match:
                tipo_proceso, dimension, tiempo = match.groups()
                tiempos[tipo_proceso] = float(tiempo)
    return tiempos, dimension

def plot_time_graph(data, dimension, output_filepath):
    # Grafica el tiempo de cómputo para cada tipo de proceso.
    labels = list(data.keys())
    tiempos = list(data.values())

    # Establecer los límites del eje Y (110% del máximo y 90% del mínimo)
    y_min = min(tiempos) * 0.9 if min(tiempos) * 0.9 > 0 else 0
    y_max = max(tiempos) * 1.1

    # Crear el gráfico de barras
    fig, ax = plt.subplots(figsize=(12, 8))  # Aumentar el tamaño del gráfico
    bars = ax.bar(labels, tiempos, color=['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728'])

    # Añadir los valores dentro de las barras
    ax.bar_label(bars, labels=[f'{t:.6f} s' for t in tiempos], label_type='edge', color='black')

    # Configurar etiquetas y título
    ax.set_xlabel('Tipo de Proceso')
    ax.set_ylabel('Tiempo de Computo (s)')
    ax.set_ylim([y_min, y_max])
    ax.set_title(f'Tiempo de computo destinado para la multiplicación de matrices cuadradas con dimensión N={dimension}\nen cada tipo de proceso', pad=20)
    plt.xticks(rotation=0)
    plt.subplots_adjust(top=0.85)  # Ajustar el espacio superior para evitar advertencias
    plt.savefig(output_filepath)
    plt.show()

def main():
    # Preguntar al usuario la dimensión de la matriz (N)
    N = input("Ingrese la dimension de la matriz (N): ")

    # Compilar y ejecutar el código en C
    compile_command = ["gcc", "multi-matrices.c", "-o", "multi_matrices", "-fopenmp"]
    execute_command = ["./multi_matrices"]

    try:
        subprocess.run(compile_command, check=True)
        subprocess.run(execute_command, input=f"{N}\n", text=True, check=True)
        print("\nPrograma de C corriendo.\n")
    except subprocess.CalledProcessError as e:
        print(f"Error al compilar o ejecutar el código en C: {e}")
        return

    # Definir la carpeta de registros
    log_dir = "registros"

    if not os.path.exists(log_dir):
        print(f"La carpeta '{log_dir}' no existe.")
        return

    # Encontrar el archivo de log más reciente
    log_files = [os.path.join(log_dir, f) for f in os.listdir(log_dir) if f.endswith(".log")]
    if not log_files:
        print("No se encontraron archivos de log.")
        return

    latest_log = max(log_files, key=os.path.getctime)
    tiempos, _ = parse_log_file(latest_log)

    # Generar el nombre del gráfico con el mismo nombre del archivo de log
    output_graph = os.path.splitext(latest_log)[0] + ".png"
    plot_time_graph(tiempos, N, output_graph)

if __name__ == "__main__":
    main()
