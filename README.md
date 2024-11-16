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

El archivo `execution_time-100000N-factorial_15-11-2024.log` tiene un formato tabular (`tsv`) y contiene la siguiente información:

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

![Gráfico generado por el programa con n=10, m=10000000 y dos hilos](ejercicio-2/registros/incremento_n10-m10000000_hilos-2_16-11-2024.png)

### Respuesta

El análisis del gráfico muestra que, al no usar sincronización, los incrementos en el arreglo presentan inconsistencias debido a las condiciones de carrera. Esto se traduce en un número de incrementos menor al esperado, ya que diferentes hilos intentan actualizar los mismos elementos del arreglo simultáneamente sin ningún tipo de protección.

Por otro lado, cuando se utiliza sincronización, los incrementos son consistentes y el total de incrementos coincide con el valor esperado. Sin embargo, esto implica un costo de tiempo mayor, ya que la sincronización añade una sobrecarga debido a la necesidad de asegurar el acceso exclusivo a los elementos del arreglo.

Este ejercicio muestra la importancia de la sincronización al paralelizar operaciones que modifican estructuras de datos compartidas, así como el compromiso entre rendimiento y consistencia que se debe tener en cuenta al trabajar con sistemas paralelos.

## Ejercicio 3

Este ejercicio consiste en la sumatoria de valores flotantes dentro de un arreglo de `N` elementos generados aleatoriamente. Se implementa la sumatoria de manera secuencial y paralelizada utilizando OpenMP, y se compara el tiempo de cómputo en ambos casos, probando la versión paralelizada con diferentes números de hilos.

### Contenido

- `sumatoria_flotante.c`: Código en C que genera un arreglo de `N` números flotantes aleatorios entre 0 y 1. Implementa la suma de los elementos del arreglo de forma secuencial y paralelizada con 2, 4 y 8 hilos, utilizando OpenMP.

- `graficar_sumatoria_flotante.py`: Script en Python que compila y ejecuta el programa en C, genera un archivo `.log` con los resultados del proceso de sumatoria, y crea un gráfico que compara el tiempo de cómputo en cada tipo de proceso (secuencial y paralelizado).

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
   gcc -fopenmp sumatoria_flotante.c -o sumatoria_flotante
   ```

6. **Ejecutar el Script en Python**:
   Ejecuta el script `graficar_sumatoria_flotante.py` para realizar la sumatoria y generar el gráfico comparativo:

   ```bash
   python graficar_sumatoria_flotante.py
   ```

   - El script solicitará el valor de `N` y compilará el programa en C, generará un archivo `.log` con los resultados y creará un gráfico que muestra el tiempo de cómputo en cada tipo de proceso.

8. **Resultados**:
   - El archivo de `log` generado se guardará en la carpeta registros con un nombre que contiene el valor de `N` y la fecha actual.

   - Se generará un gráfico en formato `.png` que muestra el tiempo de cómputo para la sumatoria de los valores flotantes en cada tipo de proceso (secuencial y paralelizado con diferentes hilos).

### Estructura del Archivo de Log

El archivo `sumatoria-flotante_n10000000_16-11-2024.log` tiene un formato tabular (`tsv`) y contiene la siguiente información:

```markdown
| Version    | Tiempo |
|------------|--------|
| Secuencial | 0.0297 |
| Paralela-2 | 0.0150 |
| Paralela-4 | 0.0149 |
| Paralela-8 | 0.0155 |
```

### Visualización del Gráfico

El gráfico generado se guardará en la carpeta registros con un nombre que contiene el valor de N y la fecha actual. Muestra el tiempo de cómputo para la sumatoria de los valores flotantes en cada tipo de proceso (secuencial y paralelizado).

![Gráfico generado por el programa con n=10, m=10000000 y con procesos secuencial, paralelizado 2 hilos, paralelizados 4 hilos y paralelizados 8 hilos](ejercicio-3/registros/sumatoria-flotante_n10000000_16-11-2024.png)

### Respuesta

La reducción en OpenMP permite evitar condiciones de carrera al sumar los valores del arreglo, ya que cada hilo tiene su propia variable privada para acumular la suma parcial. Al final del proceso, las sumas parciales se combinan automáticamente en una única variable global, garantizando que no haya conflictos de acceso concurrente entre los hilos. Esto asegura que el resultado final sea correcto y que todos los valores se sumen sin perder ninguna contribución debido a la concurrencia.

En el gráfico generado, se observa que el tiempo de cómputo disminuye al pasar de un proceso secuencial a uno paralelo con 2 hilos. Sin embargo, no hay una variación significativa en el tiempo al aumentar a 4 y 8 hilos. Esto se debe a que la máquina virtual utilizada tiene solo 2 núcleos, lo cual limita la capacidad de paralelización efectiva más allá de los 2 hilos, haciendo que el tiempo de ejecución sea aproximadamente similar en los procesos paralelizados con 2 o más hilos en este caso.

### Ejercicio 4



