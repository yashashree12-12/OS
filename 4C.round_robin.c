#include <stdio.h>

int main() {
    int i, n, tq, bt[10], rt[10], wt[10], tat[10], time = 0;
    int remain, flag = 0;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &n);
    remain = n;

    for (i = 0; i < n; i++) {
        printf("Enter Burst Time for P[%d]: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    while (remain != 0) {
        flag = 0;
        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    wt[i] = time - bt[i];
                    tat[i] = wt[i] + bt[i];
                    rt[i] = 0;
                    remain--;
                    avg_wt += wt[i];
                    avg_tat += tat[i];
                }
            }
        }
    }

    printf("\nProcess\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P[%d]\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}

// gcc round_robin.c -o round_robin
// ./round_robin