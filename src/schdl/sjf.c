#include "process.h"

/* ============================================================
 * Student implementation area
 * ============================================================ */
void sjf_schedule(Process p[], int n)
{
    int time = 0;
    int completed = 0;
    int done[n];
    Process result[n];

    for (int i = 0; i < n; i++)
        done[i] = 0;

    while (completed < n)
    {
        int idx = -1;
        int min_bt = 1000000;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && p[i].arrival_time <= time)
            {
                if (p[i].burst_time < min_bt)
                {
                    min_bt = p[i].burst_time;
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            time++;
            continue;
        }

        done[idx] = 1;
        p[idx].waiting_time = time - p[idx].arrival_time;
        time += p[idx].burst_time;
        p[idx].turnaround_time = time - p[idx].arrival_time;

        result[completed++] = p[idx];
    }

    for (int i = 0; i < n; i++)
        p[i] = result[i];
}

/* ============================================================
 * DO NOT MODIFY MAIN
 * ============================================================ */
#ifndef UNIT_TEST
int main(void)
{
    int n;
    printf("Número de procesos: ");
    scanf("%d", &n);

    Process p[n];
    read_processes(p, n);
    init_processes(p, n);

    sjf_schedule(p, n);

    print_results(p, n, "SJF Scheduling");
    return 0;
}
#endif