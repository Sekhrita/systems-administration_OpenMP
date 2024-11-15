#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>

// Función para calcular el factorial de un número
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int N, num_hilos;
    printf("Ingrese el valor de N: ");
    scanf("%d", &N);
    printf("Ingrese el número de hilos (1, 2, 4, 8): ");
    scanf("%d", &num_hilos);

    // Validación del valor de N y número de hilos
    if (N < 1) {
        printf("N debe ser mayor o igual a 1.\n");
        return 1;
    }
    if (num_hilos != 1 && num_hilos != 2 && num_hilos != 4 && num_hilos != 8) {
        printf("El número de hilos debe ser 1, 2, 4 o 8.\n");
        return 1;
    }

    // Reservar memoria para almacenar los resultados
    unsigned long long *resultados = (unsigned long long *)malloc(N * sizeof(unsigned long long));
    if (resultados == NULL) {
        printf("Error al reservar memoria.\n");
        return 1;
    }

    // Configurar el número de hilos
    omp_set_num_threads(num_hilos);

    // Medir el tiempo de ejecución paralelo
    double start = omp_get_wtime();

    // Calcular el factorial de cada número de 1 a N en paralelo con schedule dynamic
    #pragma omp parallel for schedule(dynamic)
    for (int i = 1; i <= N; i++) {
        resultados[i - 1] = factorial(i);
    }

    double end = omp_get_wtime();

    // Calcular y mostrar el tiempo de ejecución
    double tiempo_ejecucion = end - start;
    printf("Tiempo de ejecución (paralelo con %d hilos): %.6f segundos\n", num_hilos, tiempo_ejecucion);

    // Escribir el tiempo de ejecución en un archivo .log
    FILE *log_file = fopen("execution_time.log", "a");
    if (log_file == NULL) {
        printf("Error al abrir el archivo de registro.\n");
        free(resultados);
        return 1;
    }

    // Escribir el encabezado si el archivo está vacío
    fseek(log_file, 0, SEEK_END);
    if (ftell(log_file) == 0) {
        fprintf(log_file, "tipo-proceso\tn-factorial\ttiempo-ejecución\n");
    }

    // Escribir los resultados en formato de tabla
    fprintf(log_file, "paralelo-%dhilos\t%d\t%.6f\n", num_hilos, N, tiempo_ejecucion);
    fclose(log_file);

    // Liberar la memoria
    free(resultados);

    return 0;
}
