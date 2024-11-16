// multi-matrices.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAX 1000 // Ajusta el valor si necesitas valores mayores

void calcular_secuencial(double **A, double **B, double **C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void calcular_paralelo(double **A, double **B, double **C, int N, int num_hilos) {
    #pragma omp parallel for num_threads(num_hilos) schedule(dynamic)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int N;
    printf("Ingrese la dimension de la matriz (N): ");
    scanf("%d", &N);

    double tiempo_sec, tiempo_par;

    // Reservar memoria para matrices
    double **A = malloc(N * sizeof(double *));
    double **B = malloc(N * sizeof(double *));
    double **C = malloc(N * sizeof(double *));
    for (int i = 0; i < N; ++i) {
        A[i] = malloc(N * sizeof(double));
        B[i] = malloc(N * sizeof(double));
        C[i] = malloc(N * sizeof(double));
    }

    // Llenar matrices A y B con valores aleatorios
    srand(time(NULL));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = rand() % MAX;
            B[i][j] = rand() % MAX;
        }
    }

    // Obtener la fecha actual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char log_filename[100];
    snprintf(log_filename, sizeof(log_filename), "registros/multi-matrices_n%d_%02d-%02d-%d.log", N, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Calculo secuencial
    double start, end;
    start = omp_get_wtime();
    calcular_secuencial(A, B, C, N);
    end = omp_get_wtime();
    tiempo_sec = end - start;
    printf("Tiempo secuencial: %f s\n", tiempo_sec);

    // Escribir resultado secuencial en el archivo de log
    FILE *log_file = fopen(log_filename, "a");
    if (log_file == NULL) {
        printf("Error al abrir el archivo de log\n");
        return -1;
    }
    fprintf(log_file, "tipo-proceso\tdimension-matriz\ttiempo\n");
    fprintf(log_file, "secuencial\t%d\t%f\n", N, tiempo_sec);
    fclose(log_file);

    // Calculo paralelo usando OpenMP con diferentes numeros de hilos
    int hilos[] = {2, 4, 8};
    for (int i = 0; i < 3; ++i) {
        int num_hilos = hilos[i];
        start = omp_get_wtime();
        calcular_paralelo(A, B, C, N, num_hilos);
        end = omp_get_wtime();
        tiempo_par = end - start;
        printf("Tiempo paralelo con %d hilos: %f s\n", num_hilos, tiempo_par);

        log_file = fopen(log_filename, "a");
        if (log_file == NULL) {
            printf("Error al abrir el archivo de log\n");
            return -1;
        }
        fprintf(log_file, "paralelo-%d\t%d\t%f\n", num_hilos, N, tiempo_par);
        fclose(log_file);
    }

    // Liberar memoria
    for (int i = 0; i < N; ++i) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    return 0;
}
