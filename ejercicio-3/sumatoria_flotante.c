#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void sequential_sum(float *arr, int size) {
    double start_time = omp_get_wtime();
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    double end_time = omp_get_wtime();
    printf("Secuencial\t%.4f\n", end_time - start_time);
}

void parallel_sum(float *arr, int size, int threads) {
    double start_time = omp_get_wtime();
    float sum = 0.0;
    #pragma omp parallel for reduction(+:sum) num_threads(threads)
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    double end_time = omp_get_wtime();
    printf("Paralela-%d\t%.4f\n", threads, end_time - start_time);
}

int main() {
    int N;
    printf("Ingrese el valor de N: ");
    scanf("%d", &N);

    srand(time(NULL));
    float *arr = (float*) malloc(N * sizeof(float));
    for (int i = 0; i < N; i++) {
        arr[i] = (float) rand() / RAND_MAX;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char filename[100];
    snprintf(filename, sizeof(filename), "registros/sumatoria-flotante_n%d_%02d-%02d-%04d.log", N, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    freopen(filename, "w", stdout);
    printf("Version\tTiempo\n");

    sequential_sum(arr, N);
    parallel_sum(arr, N, 2);
    parallel_sum(arr, N, 4);
    parallel_sum(arr, N, 8);

    free(arr);
    return 0;
}
