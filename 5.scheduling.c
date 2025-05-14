#include <stdio.h>

#define MAX 10

// Structure for Process
typedef struct {
    int pid, bt, at, wt, tat, rt, prio;
} Process;

void FCFS(Process p[], int n) {
    int time = 0;
    p[0].wt = 0;
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }
    printf("\n--- FCFS Scheduling ---\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
        printf("P%d - WT: %d, TAT: %d\n", p[i].pid, p[i].wt, p[i].tat);
    }
}

void SJF_Preemptive(Process p[], int n) {
    int bt[20], complete = 0, t = 0, min = 999, shortest = 0, finish_time;
    int check = 0;
    for (int i = 0; i < n; i++)
        bt[i] = p[i].bt;

    printf("\n--- SJF Preemptive ---\n");
    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((p[j].at <= t) && (bt[j] < min) && bt[j] > 0) {
                min = bt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        bt[shortest]--;
        min = bt[shortest];
        if (min == 0)
            min = 999;

        if (bt[shortest] == 0) {
            complete++;
            finish_time = t + 1;
            p[shortest].wt = finish_time - p[shortest].bt - p[shortest].at;
            if (p[shortest].wt < 0)
                p[shortest].wt = 0;
        }
        t++;
    }

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
        printf("P%d - WT: %d, TAT: %d\n", p[i].pid, p[i].wt, p[i].tat);
    }
}

void Priority_NonPreemptive(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].prio > p[j].prio) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    p[0].wt = 0;
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }

    printf("\n--- Priority Scheduling (Non-Preemptive) ---\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
        printf("P%d - Priority: %d, WT: %d, TAT: %d\n", p[i].pid, p[i].prio, p[i].wt, p[i].tat);
    }
}

void RoundRobin(Process p[], int n, int quantum) {
    int rem_bt[MAX], t = 0;
    for (int i = 0; i < n; i++)
        rem_bt[i] = p[i].bt;

    printf("\n--- Round Robin Scheduling ---\n");
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0;
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    p[i].wt = t - p[i].bt;
                    rem_bt[i] = 0;
                }
            }
        }
        if (done)
            break;
    }

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
        printf("P%d - WT: %d, TAT: %d\n", p[i].pid, p[i].wt, p[i].tat);
    }
}

int main() {
    Process p[MAX];
    int n, choice, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority of Process P%d: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].prio);
    }

    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. FCFS\n2. SJF (Preemptive)\n3. Priority (Non-Preemptive)\n4. Round Robin\nChoice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            FCFS(p, n);
            break;
        case 2:
            SJF_Preemptive(p, n);
            break;
        case 3:
            Priority_NonPreemptive(p, n);
            break;
        case 4:
            printf("Enter Time Quantum: ");
            scanf("%d", &quantum);
            RoundRobin(p, n, quantum);
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}


// How to Compile & Run:
// On Linux / WSL / CodeBlocks:
// bash
// Copy code
// gcc scheduling.c -o scheduling
// ./scheduling
// 📌 Sample Input:
// less
// Copy code
// Enter number of processes: 3
// Enter Arrival Time, Burst Time, and Priority of Process P1: 0 5 2
// Enter Arrival Time, Burst Time, and Priority of Process P2: 1 3 1
// Enter Arrival Time, Burst Time, and Priority of Process P3: 2