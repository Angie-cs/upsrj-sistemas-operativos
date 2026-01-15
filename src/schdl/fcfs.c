#include <stdio.h>
#include "process.h"

int main() {
    int n;
    printf("Número de procesos: ");
    scanf("%d", &n);

    Process p[n];
    read_processes(p, n);
    init_processes(p, n);

    // TODO: Aquí va la lógica del scheduler
    
    int time = 0;

   for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time) {
            // Si el CPU está ocioso, avanzar hasta la llegada del proceso
            time = p[i].arrival_time;
        }

        // Mostrar estado antes de ejecutar
        printf("Tiempo %d: Ejecutando P%d (BT=%d)\n",
               time, p[i].id, p[i].burst_time);

        // Calcular tiempos
        p[i].waiting_time = time - p[i].arrival_time;
        time += p[i].burst_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
        p[i].completed = 1;

        // Mostrar estado después de ejecutar
        printf("   -> P%d terminó en tiempo %d\n", p[i].id, time);
    }

    print_results(p, n, "FCFS Scheduling");
    return 0;
}