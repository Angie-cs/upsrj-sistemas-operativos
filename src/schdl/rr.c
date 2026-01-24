#include <stdio.h>
#include "process.h"

/* ============================================================
 * Student implementation area
 * ============================================================ */
void rr_schedule(Process p[], int n, int quantum)
{
    int time = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time &&
                p[i].remaining_time > 0) {

                int exec_time =
                    (p[i].remaining_time > quantum)
                    ? quantum
                    : p[i].remaining_time;

                p[i].remaining_time -= exec_time;
                time += exec_time;

                for (int j = 0; j < n; j++) {
                    if (j != i &&
                        p[j].arrival_time <= time &&
                        p[j].remaining_time > 0) {
                        p[j].waiting_time += exec_time;
                    }
                }

                if (p[i].remaining_time == 0) {
                    p[i].completed = 1;
                    p[i].turnaround_time =
                        time - p[i].arrival_time;
                    completed++;
                }
            }
        }
    }
}

/* ============================================================
 * DO NOT MODIFY MAIN
 * ============================================================ */
#ifndef UNIT_TEST
int main(void)
{
    int n, quantum;

    printf("Número de procesos: ");
    scanf("%d", &n);

    printf("Quantum: ");
    scanf("%d", &quantum);

    Process p[n];
    read_processes(p, n);
    init_processes(p, n);

    rr_schedule(p, n, quantum);

    print_results(p, n, "Round Robin Scheduling");
    return 0;
}
#endif
