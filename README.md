# systems-administration_OpenMP

## Ejercicio 1

Esta sección contiene scripts para evaluar el rendimiento de la ejecución secuencial y paralelizada del cálculo factorial de un número N. Se utilizan programas escritos en C para realizar los cálculos y un script de Python para generar un gráfico que compara los tiempos de ejecución. 

### Contenido

- `factorial_secuencial.c`: Código en C para calcular el factorial de un número N de manera secuencial.

- `factorial_openmp.c`: Código en C para calcular el factorial de un número N de manera paralelizada utilizando OpenMP.

- `generate_execution_graph.py`: Script en Python que ejecuta los programas C, genera un archivo .log con los tiempos de ejecución, y crea un gráfico para visualizar los resultados.

- `requirements.txt`: Lista de dependencias necesarias para ejecutar el script en Python.

### Requisitos

- **Python 3**
- **Entorno virtual de Python** (`venv`)
- **GCC** con soporte para OpenMP
- Paquetes de Python: `matplotlib`, `pandas`
- Para instalar las dependencias de Python, se recomienda utilizar el entorno virtual en conjunto con `requirements.txt`

### Instrucciones de Uso

1. **Actualizar el Sistema**:
   ```bash
   sudo apt update && sudo apt upgrade
   ```

2. **Instalar el Entorno Virtual**:
   ```bash
   sudo apt-get install python3-venv
   ```

3. **Crear un Entorno Virtual**:
   ```bash
   python3 -m venv venv
   source venv/bin/activate
   ```

4. **Instalar Dependencias**:
   ```bash
   pip install -r requirements.txt
   ```

5. **Compilar los Programas en C**:
   Asegúrate de tener `gcc` instalado y compila los programas.

   ```bash
   gcc factorial_secuencial.c -o factorial_secuencial
   gcc factorial_openmp.c -o factorial_openmp -fopenmp
   ```

6. **Ejecutar el Script en Python**:
   Ejecuta el script `generate_execution_graph.py` para calcular los tiempos de ejecución y generar el gráfico comparativo:

   ```bash
   python generate_execution_graph.py
   ```

   El script te pedirá que ingreses el valor de `N` para calcular el factorial, luego ejecutará los programas secuenciales y paralelizados con diferentes números de hilos.

7. **Resultados**:
   - El archivo de log generado se guardará en la carpeta `registro` con un nombre que contiene el valor de `N` y la fecha actual.
   - Se generará un gráfico en formato `.png` que muestra los tiempos de ejecución para cada proceso.

### Estructura del Archivo de Log

El archivo execution_time.log tiene un formato tabular (`tsv`) y contiene la siguiente información:

```markdown
| tipo-proceso     | n-factorial | tiempo-ejecución |
|------------------|-------------|------------------|
| secuencial       | 100000      | 4.016176         |
| paralelo-1hilos  | 100000      | 4.011657         |
| paralelo-2hilos  | 100000      | 2.048726         |
| paralelo-4hilos  | 100000      | 2.039414         |
| paralelo-8hilos  | 100000      | 2.060040         |
```

### Visualización del Gráfico

El gráfico generado se guardará en la carpeta registro con un nombre que contiene el valor de N y la fecha actual.
![Gráfico generado por el programa con n=100000](ejercicio-1/registro/execution_time-100000N-factorial_15-11-2024.png)

### Respuesta

El análisis del gráfico muestra que el tiempo de ejecución disminuye cuando se utilizan más de un hilo, pero después de 2 hilos ya no se observa una reducción significativa del tiempo de ejecución. Esto se debe a que el sistema utilizado para la prueba (una máquina virtual Debian) solo tiene 2 núcleos disponibles, lo cual limita la capacidad de aprovechar más hilos.

Sin embargo, se puede observar que el proceso no paralelizado comparado con el que utiliza 2 hilos presenta una reducción en el tiempo de ejecución de aproximadamente la mitad. Esto indica que la paralelización con 2 hilos puede aprovechar mejor los recursos disponibles, distribuyendo el trabajo de forma más eficiente.

Por otro lado, el proceso secuencial (no paralelizado) y el proceso que utiliza 1 hilo tienen un tiempo de ejecución similar, lo cual sugiere que ambos utilizan los recursos del sistema de manera parecida y tienen un costo computacional similar.

Finalmente, se puede hipotetizar que con un mayor número de hilos y suficiente cantidad de núcleos disponibles, el tiempo de cómputo podría reducirse significativamente, mostrando los beneficios de la paralelización a gran escala.

## Ejercicio 2

Este ejercicio consiste en una simulación de incrementos en valores aleatorios dentro de un arreglo de N elementos. Se implementa el proceso de incremento de manera paralelizada utilizando OpenMP y se compara el rendimiento y la integridad de los datos con y sin sincronización.

### Contenido

- `incrementos.c`: Código en C que crea un arreglo de N números inicializados en cero. Paraleliza el proceso en el cual cada hilo incrementa un valor aleatorio del arreglo durante M iteraciones. Se implementan versiones con y sin sincronización para observar los efectos de las condiciones de carrera.

- `incrementos_grafica.py`: Script en Python que ejecuta el programa en C, genera un archivo .log con los resultados del proceso de incrementos, y crea un gráfico que compara la integridad del incremento con y sin sincronización.

- `requirements.txt`: Lista de dependencias necesarias para ejecutar el script en Python.

### Requisitos

- **Python 3**
- **Entorno virtual de Python** (`venv`)
- **GCC** con soporte para OpenMP
- Paquetes de Python: `matplotlib`
- Para instalar las dependencias de Python, se recomienda utilizar el entorno virtual en conjunto con `requirements.txt`

### Instrucciones de Uso

1. **Actualizar el Sistema**:
   ```bash
   sudo apt update && sudo apt upgrade
   ```

2. **Instalar el Entorno Virtual**:
   ```bash
   sudo apt-get install python3-venv
   ```

3. **Crear un Entorno Virtual**:
   ```bash
   python3 -m venv venv
   source venv/bin/activate
   ```

4. **Instalar Dependencias**:
   ```bash
   pip install -r requirements.txt
   ```

5. **Compilar los Programas en C**:
   Asegúrate de tener `gcc` instalado y compila los programas.

   ```bash
   gcc -fopenmp incrementos.c -o incrementos
   ```

6. **Ejecutar el Script en Python**:
   Ejecuta el script `incrementos_grafica.py` para realizar el proceso de incrementos y generar el gráfico comparativo:

   ```bash
   python incrementos_grafica.py
   ```

   El script ejecutará el programa C, generará un archivo `.log` con los resultados y creará un gráfico que compara los incrementos con y sin sincronización.

8. **Resultados**:
   - El archivo de log generado se guardará en la carpeta `registros` con un nombre que contiene los valores de `N`, `M`, el número de hilos y la fecha actual.
   - Se generará un gráfico en formato `.png` que muestra la integridad de los incrementos con y sin sincronización.

### Estructura del Archivo de Log

El archivo `.log` generado contiene la siguiente información:

```markdown
#
tipo-proceso    sin-sincronización
numero-hilos    2
numero-iteraciones    10000000
tiempo-demora    0.418960
total-incrementos    9977185
resultado-incremento    arreglo[0]    14
...
#
tipo-proceso    con-sincronización
numero-hilos    2
numero-iteraciones    10000000
tiempo-demora    0.499188
total-incrementos    10000000
resultado-incremento    arreglo[0]    14
...
#
numero-inconsistencias    22815
```

### Visualización del Gráfico

El gráfico generado se guardará en la carpeta `registros` con un nombre que contiene los valores de `N`, `M`, el número de hilos y la fecha actual.
![Gráfico generado por el programa con n=10, m=10000000 y dos hilos](ejercicio-2/registro/incremento_n10-m10000000_hilos-2_16-11-2024.png)

### Respuesta

El análisis del gráfico muestra que, al no usar sincronización, los incrementos en el arreglo presentan inconsistencias debido a las condiciones de carrera. Esto se traduce en un número de incrementos menor al esperado, ya que diferentes hilos intentan actualizar los mismos elementos del arreglo simultáneamente sin ningún tipo de protección.

Por otro lado, cuando se utiliza sincronización, los incrementos son consistentes y el total de incrementos coincide con el valor esperado. Sin embargo, esto implica un costo de tiempo mayor, ya que la sincronización añade una sobrecarga debido a la necesidad de asegurar el acceso exclusivo a los elementos del arreglo.

Este ejercicio muestra la importancia de la sincronización al paralelizar operaciones que modifican estructuras de datos compartidas, así como el compromiso entre rendimiento y consistencia que se debe tener en cuenta al trabajar con sistemas paralelos.

## Ejercicio 3



