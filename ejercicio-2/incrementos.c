#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void increment_without_sync(int *array, int N, int M) {
    int i;
    #pragma omp parallel for
    for (i = 0; i < M; i++) {
        int index = rand() % N;
        array[index]++;  // Incremento sin protección
    }
}

void increment_with_sync(int *array, int N, int M) {
    int i;
    #pragma omp parallel for
    for (i = 0; i < M; i++) {
        int index = rand() % N;
        #pragma omp critical
        {
            array[index]++;  // Incremento protegido
        }
    }
}

int main() {
    int N, M, num_threads;
    int i;

    // Pedir al usuario los valores de N, M y el número de hilos
    printf("Ingrese el valor de N (tamaño del arreglo): ");
    scanf("%d", &N);
    printf("Ingrese el valor de M (número de iteraciones): ");
    scanf("%d", &M);
    printf("Ingrese el número de hilos a utilizar: ");
    scanf("%d", &num_threads);

    // Establecer el número de hilos
    omp_set_num_threads(num_threads);

    int array[N];
    int array_with_sync[N];
    for (i = 0; i < N; i++) {
        array[i] = 0;
        array_with_sync[i] = 0;
    }

    // Inicialización de la semilla para números aleatorios
    srand(42);

    // Obtener la fecha actual para el nombre del archivo de log
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char filename[150];
    snprintf(filename, sizeof(filename), "registros/incremento_n%d-m%d_hilos-%d_%02d-%02d-%d.log", N, M, num_threads, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Crear la carpeta "registros" si no existe
    system("mkdir -p registros");

    // Abrir archivo de log
    FILE *log_file = fopen(filename, "w");
    if (log_file == NULL) {
        perror("Error al crear el archivo de log");
        return 1;
    }

    // Incremento sin sincronización
    double start_time = omp_get_wtime();
    increment_without_sync(array, N, M);
    double end_time = omp_get_wtime();
    double time_without_sync = end_time - start_time;

    // Contar el total de incrementos realizados sin sincronización
    int total_without_sync = 0;
    for (i = 0; i < N; i++) {
        total_without_sync += array[i];
    }

    // Escribir resultados en el archivo de log
    fprintf(log_file, "#\n");
    fprintf(log_file, "tipo-proceso    sin-sincronización\n");
    fprintf(log_file, "numero-hilos    %d\n", num_threads);
    fprintf(log_file, "numero-iteraciones    %d\n", M);
    fprintf(log_file, "tiempo-demora    %f\n", time_without_sync);
    fprintf(log_file, "total-incrementos    %d\n", total_without_sync);
    for (i = 0; i < N; i++) {
        if (array[i] != 0) {
            fprintf(log_file, "resultado-incremento    arreglo[%d]    %d\n", i, array[i]);
        }
    }

    // Reiniciar el arreglo a cero
    for (i = 0; i < N; i++) {
        array[i] = 0;
    }

    // Incremento con sincronización
    start_time = omp_get_wtime();
    increment_with_sync(array_with_sync, N, M);
    end_time = omp_get_wtime();
    double time_with_sync = end_time - start_time;

    // Contar el total de incrementos realizados con sincronización
    int total_with_sync = 0;
    for (i = 0; i < N; i++) {
        total_with_sync += array_with_sync[i];
    }

    // Escribir resultados en el archivo de log
    fprintf(log_file, "#\n");
    fprintf(log_file, "tipo-proceso    con-sincronización\n");
    fprintf(log_file, "numero-hilos    %d\n", num_threads);
    fprintf(log_file, "numero-iteraciones    %d\n", M);
    fprintf(log_file, "tiempo-demora    %f\n", time_with_sync);
    fprintf(log_file, "total-incrementos    %d\n", total_with_sync);
    for (i = 0; i < N; i++) {
        if (array_with_sync[i] != 0) {
            fprintf(log_file, "resultado-incremento    arreglo[%d]    %d\n", i, array_with_sync[i]);
        }
    }

    // Comparar el total de incrementos y contar inconsistencias
    int inconsistencies = total_with_sync - total_without_sync;
    fprintf(log_file, "#\n");
    fprintf(log_file, "numero-inconsistencias    %d\n", inconsistencies);

    // Cerrar archivo de log
    fclose(log_file);

    return 0;
}
