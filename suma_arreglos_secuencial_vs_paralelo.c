#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>        // Importante para usar las funciones de OpenMP

#define N 1000000       // Tamaño de los arreglos, ajústalo según quieras

int main() {
    int *A, *B, *C;
    A = (int*) malloc(N * sizeof(int));
    B = (int*) malloc(N * sizeof(int));
    C = (int*) malloc(N * sizeof(int));

    srand((unsigned)time(NULL));

    // Llenar arreglos con valores aleatorios
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 100; 
        B[i] = rand() % 100;
    }

    // -------------------------
    // 1) Suma SECUENCIAL
    // -------------------------
    double start_seq = omp_get_wtime();  // inicio tiempo secuencial

    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }

    double end_seq = omp_get_wtime();    // fin tiempo secuencial
    double tiempo_secuencial = end_seq - start_seq;

    // Imprimir los primeros 5 resultados para verificar
    printf("=== Suma SECUENCIAL ===\n");
    for (int i = 0; i < 5; i++) {
        printf("A[%d] = %d, B[%d] = %d, C[%d] = %d\n", 
                i, A[i], i, B[i], i, C[i]);
    }
    printf("Tiempo de ejecucion secuencial: %.6f segundos\n\n", tiempo_secuencial);

    // -------------------------
    // 2) Suma PARALELA con OpenMP
    // -------------------------
    // Opcional: mostrar cuántos hilos se usan
    #pragma omp parallel
    {
        #pragma omp master
        {
            int total_hilos = omp_get_num_threads();
            printf("Usando %d hilos (threads) en OpenMP\n\n", total_hilos);
        }
    }

    double start_par = omp_get_wtime();  // inicio tiempo paralelo

    // Suma paralela
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }

    double end_par = omp_get_wtime();    // fin tiempo paralelo
    double tiempo_paralelo = end_par - start_par;

    // Imprimir primeros 5 resultados de la versión paralela
    printf("=== Suma PARALELA (OpenMP) ===\n");
    for (int i = 0; i < 5; i++) {
        printf("A[%d] = %d, B[%d] = %d, C[%d] = %d\n", 
                i, A[i], i, B[i], i, C[i]);
    }
    printf("Tiempo de ejecucion paralelo:   %.6f segundos\n\n", tiempo_paralelo);

    // Comparación final
    printf("=== COMPARACION DE TIEMPOS ===\n");
    printf("Secuencial: %.6f s\n", tiempo_secuencial);
    printf("Paralelo:   %.6f s\n", tiempo_paralelo);

    // Liberar memoria
    free(A);
    free(B);
    free(C);

    return 0;
}
