import matplotlib.pyplot as plt
import os
import re
import subprocess

def parse_log_file(filepath):
    # Analiza el archivo de log para extraer el total de incrementos para los procesos con y sin sincronización.
    total_increments = {
        "sin_sincronizacion": None,
        "con_sincronizacion": None,
        "numero_iteraciones": None
    }

    with open(filepath, 'r') as file:
        lines = file.readlines()
        current_process = None
        for line in lines:
            if "tipo-proceso" in line:
                if "sin-sincronización" in line:
                    current_process = "sin_sincronizacion"
                elif "con-sincronización" in line:
                    current_process = "con_sincronizacion"
            elif "total-incrementos" in line:
                match = re.search(r'total-incrementos\s+(\d+)', line)
                if match:
                    total_increments[current_process] = int(match.group(1))
            elif "numero-iteraciones" in line:
                match = re.search(r'numero-iteraciones\s+(\d+)', line)
                if match:
                    total_increments["numero_iteraciones"] = int(match.group(1))
    
    return total_increments


def plot_increment_graph(data, output_filepath):
    # Grafica la comparación normalizada de los incrementos totales para los procesos con y sin sincronización.
    labels = ["Sin Sincronización", "Con Sincronización"]
    percentages = []
    total_increments_values = []

    for label in data.keys():
        total_increments = data[label]
        numero_iteraciones = total_increments["numero_iteraciones"]
        sin_sync_percentage = (total_increments["sin_sincronizacion"] / numero_iteraciones) * 100 if numero_iteraciones else 0
        con_sync_percentage = (total_increments["con_sincronizacion"] / numero_iteraciones) * 100 if numero_iteraciones else 0
        percentages = [sin_sync_percentage, con_sync_percentage]
        total_increments_values = [total_increments["sin_sincronizacion"], total_increments["con_sincronizacion"]]

    x = range(len(labels))
    width = 0.5

    fig, ax = plt.subplots()
    bar1 = ax.bar(x[0], percentages[0], width, label='Sin Sincronización', color='#6fa8dc')  # Azul más claro
    bar2 = ax.bar(x[1], percentages[1], width, label='Con Sincronización', color='#ffd966')  # Amarillo más claro

    # Añadir los valores porcentuales y el número de incrementos dentro de las barras
    ax.bar_label(bar1, labels=[f'{percentages[0]:.2f}%\n{total_increments_values[0]}' for _ in bar1], label_type='center', color='white')
    ax.bar_label(bar2, labels=[f'{percentages[1]:.2f}%\n{total_increments_values[1]}' for _ in bar2], label_type='center', color='black')

    ax.set_ylabel('Porcentaje de Integridad (%)')
    ax.set_title('Porcentaje de Incrementos con y sin Sincronización')
    ax.set_xticks(x)
    ax.set_xticklabels(labels)
    ax.legend()

    # Ajustar los límites del eje Y para que no sobrepasen el 100%
    y_min = max(0, min(percentages) * 0.99)
    y_max = min(100, max(percentages) * 1.01)
    ax.set_ylim([y_min, y_max])

    plt.xticks(rotation=0)
    plt.tight_layout()
    plt.savefig(output_filepath)
    plt.show()


def main():
    # Función principal para ejecutar el código en C, analizar los archivos de log y generar la gráfica.
    # Ejecutar el comando de C para generar el archivo de log
    c_command = "gcc -fopenmp incrementos.c -o incrementos && ./incrementos"
    n = 10
    m = 10000000
    num_threads = 2
    command = f"{c_command} {n} {m} {num_threads}"
    subprocess.run(command, shell=True)

    # Definir la carpeta y archivo de log
    log_dir = "registros"
    data = {}

    if not os.path.exists(log_dir):
        print(f"La carpeta '{log_dir}' no existe.")
        return

    # Encontrar el archivo de log más reciente
    log_files = [os.path.join(log_dir, f) for f in os.listdir(log_dir) if f.endswith(".log")]
    if not log_files:
        print("No se encontraron archivos de log.")
        return

    latest_log = max(log_files, key=os.path.getctime)
    total_increments = parse_log_file(latest_log)
    data[os.path.basename(latest_log)] = total_increments

    # Generar el nombre del gráfico con el mismo nombre del archivo de log
    output_graph = os.path.splitext(latest_log)[0] + ".png"
    plot_increment_graph(data, output_graph)


if __name__ == "__main__":
    main()
