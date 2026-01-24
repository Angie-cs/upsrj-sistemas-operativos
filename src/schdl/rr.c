#include <stdio.h>
#include "process.h"

/* ============================================================
 * Student implementation area
 * ============================================================ */

void rr_schedule(Process p[], int n, int quantum)
{
    int time = 0;
    int completed = 0;

    int remaining[n];

    for (int i = 0; i < n; i++)
    {
        remaining[i] = p[i].burst_time;
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
        p[i].completed = 0;
    }

    while (completed < n)
    {
        int executed = 0;

        for (int i = 0; i < n; i++)
        {
            if (remaining[i] > 0 && p[i].arrival_time <= time)
            {
                executed = 1;

                if (remaining[i] > quantum)
                {
                    time += quantum;
                    remaining[i] -= quantum;
                }
                else
                {
                    time += remaining[i];
                    remaining[i] = 0;

                    p[i].turnaround_time =
                        time - p[i].arrival_time;

                    p[i].waiting_time =
                        p[i].turnaround_time - p[i].burst_time;

                    p[i].completed = 1;
                    completed++;
                }
            }
        }

        /* Si nadie pudo ejecutarse, avanzar tiempo */
        if (!executed)
            time++;
    }
}

/* ============================================================
 * DO NOT MODIFY MAIN
 * ============================================================ */
#ifndef UNIT_TEST
int main(void)
{
    int n;
    int quantum;

    printf("Número de procesos: ");
    scanf("%d", &n);

    printf("Quantum: ");
    scanf("%d", &quantum);

    Process p[n];
    read_processes(p, n);
    init_processes(p, n);

    rr_schedule(p, n, quantum);

    print_results(p, n, "RR Scheduling");
    return 0;
}
#endif