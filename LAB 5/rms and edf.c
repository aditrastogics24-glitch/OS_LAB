#include <stdio.h>
#include <math.h>

struct Process {
    int id;
    int burst;
    int deadline;
    int period;
    int completion;
    int waiting;
    int turnaround;
};

void sortProcesses(struct Process p[], int n, char key) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int a, b;
            if (key == 'd') { 
                a = p[i].deadline; b = p[j].deadline;
            } else if (key == 'p') { 
                a = p[i].period; b = p[j].period;
            } else { 
                a = p[i].id; b = p[j].id;
            }
            if (a > b) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i;
        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);
        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);
    }

    // ===== EDF Scheduling =====
    double utilization = 0.0;
    for (int i = 0; i < n; i++) {
        utilization += (double)p[i].burst / p[i].period; 
    }

    printf("\n====== Earliest Deadline First (EDF) Scheduling ======\n");
    printf("CPU Utilization: %.2f\n", utilization);
    if (utilization <= 1.0)
        printf("Schedulable (Utilization <= 1)\n");
    else
        printf("Not Schedulable\n");

    sortProcesses(p, n, 'd'); 
    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].burst;
        p[i].completion = time;
        p[i].turnaround = p[i].completion;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }
    sortProcesses(p, n, 'i');

    printf("ID  BF  Deadline  CT  WT  TAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d   %d   %d         %d   %d   %d\n",
               p[i].id, p[i].burst, p[i].deadline,
               p[i].completion, p[i].waiting, p[i].turnaround);
    }

    // ===== RMS Scheduling =====
    utilization = 0.0;
    for (int i = 0; i < n; i++) {
        utilization += (double)p[i].burst / p[i].period;
    }
    double rm_bound = n * (pow(2.0, 1.0 / n) - 1);

    printf("\n====== Rate Monotonic Scheduling (RMS) ======\n");
    printf("CPU Utilization: %.2f\n", utilization);
    printf("RM Bound: %.4f\n", rm_bound);
    if (utilization <= rm_bound)
        printf("Schedulable (Utilization <= RM Bound)\n");
    else
        printf("Not Schedulable\n");

    sortProcesses(p, n, 'p'); 
    time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].burst;
        p[i].completion = time;
        p[i].turnaround = p[i].completion;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }
    sortProcesses(p, n, 'i'); 

    printf("ID  BF  Period  CT  WT  TAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d   %d   %d      %d   %d   %d\n",
               p[i].id, p[i].burst, p[i].period,
               p[i].completion, p[i].waiting, p[i].turnaround);
    }

    return 0;
}