import os
import subprocess
import matplotlib.pyplot as plt
import pandas as pd
from datetime import datetime

def main():
    # Valor de N
    N = int(input("Ingrese el valor de N: "))

    # Revisar si existe el archivo "execution_time.log" y eliminarlo si existe
    log_file = "execution_time.log"
    if os.path.exists(log_file):
        os.remove(log_file)

    # Compilar los programas en C
    subprocess.run(["gcc", "factorial_secuencial.c", "-o", "factorial_secuencial"])
    subprocess.run(["gcc", "factorial_openmp.c", "-o", "factorial_openmp", "-fopenmp"])

    # Ejecutar los programas en C secuencial y paralelizado
    subprocess.run(["./factorial_secuencial"], input=f"{N}\n", text=True)
    for hilos in [1, 2, 4, 8]:
        subprocess.run(["./factorial_openmp"], input=f"{N}\n{hilos}\n", text=True)

    # Leer el archivo "execution_time.log" para generar el gráfico
    if not os.path.exists(log_file):
        print("No se generó el archivo de log.")
        return

    # Leer el archivo .log en un DataFrame
    df = pd.read_csv(log_file, sep='\t')

    # Cambiar el nombre al archivo .log
    fecha_actual = datetime.now().strftime("%d-%m-%Y")
    nuevo_nombre = f"execution_time-{N}N-factorial_{fecha_actual}.log"
    registro_dir = "registro"
    if not os.path.exists(registro_dir):
        os.makedirs(registro_dir)
    nuevo_log_path = os.path.join(registro_dir, nuevo_nombre)
    os.rename(log_file, nuevo_log_path)

    # Generar el gráfico
    plt.figure(figsize=(10, 6))
    plt.bar(df['tipo-proceso'], df['tiempo-ejecución'], color='skyblue')
    plt.xlabel('Tipo de Proceso')
    plt.ylabel('Tiempo de Ejecución (segundos)')
    plt.title(f'Tiempo de ejecución del factorial N({N}) para cada proceso')
    plt.xticks(rotation=45)
    plt.tight_layout()
    grafico_nombre = nuevo_nombre.replace(".log", ".png")
    plt.savefig(os.path.join(registro_dir, grafico_nombre))
    plt.show()

if __name__ == "__main__":
    main()
