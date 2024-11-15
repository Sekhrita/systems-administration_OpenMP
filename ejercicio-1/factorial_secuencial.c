#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
    int N;
    printf("Ingrese el valor de N: ");
    scanf("%d", &N);

    // Validación del valor de N
    if (N < 1) {
        printf("N debe ser mayor o igual a 1.\n");
        return 1;
    }

    // Reservar memoria para almacenar los resultados
    unsigned long long *resultados = (unsigned long long *)malloc(N * sizeof(unsigned long long));
    if (resultados == NULL) {
        printf("Error al reservar memoria.\n");
        return 1;
    }

    // Medir el tiempo de ejecución secuencial
    clock_t start = clock();

    // Calcular el factorial de cada número de 1 a N
    for (int i = 1; i <= N; i++) {
        resultados[i - 1] = factorial(i);
    }

    clock_t end = clock();

    // Calcular y mostrar el tiempo de ejecución
    double tiempo_ejecucion = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución (secuencial): %.6f segundos\n", tiempo_ejecucion);

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
    fprintf(log_file, "secuencial\t%d\t%.6f\n", N, tiempo_ejecucion);
    fclose(log_file);

    // Liberar la memoria
    free(resultados);

    return 0;
}
