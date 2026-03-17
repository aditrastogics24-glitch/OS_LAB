#include <stdio.h>

#define MAX 100

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[MAX], bt[MAX], rt[MAX], pid[MAX];
    int ct[MAX], wt[MAX], tat[MAX], rt_time[MAX];
    int first_exec[MAX];

    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nEnter AT and BT for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
        first_exec[i] = -1;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(at[i] > at[j]) {
                int temp;
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = rt[i]; rt[i] = rt[j]; rt[j] = temp;
                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
            }
        }
    }

    int time = at[0], completed = 0;
    int q[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};

    int g_p[MAX], g_t[MAX], g = 0;

    q[rear++] = 0;
    visited[0] = 1;

    while(completed < n) {
        int i = q[front++];

        if(first_exec[i] == -1)
            first_exec[i] = time;

        g_p[g] = pid[i];

        int exec = (rt[i] > tq) ? tq : rt[i];
        time += exec;
        rt[i] -= exec;

        g_t[g] = time;
        g++;

        for(int j = 0; j < n; j++) {
            if(at[j] <= time && !visited[j]) {
                q[rear++] = j;
                visited[j] = 1;
            }
        }

        if(rt[i] > 0) {
            q[rear++] = i;
        } else {
            ct[i] = time;
            completed++;
        }

        if(front == rear) {
            for(int j = 0; j < n; j++) {
                if(!visited[j]) {
                    time = at[j];
                    q[rear++] = j;
                    visited[j] = 1;
                    break;
                }
            }
        }
    }

    printf("\nGantt Chart:\n|");
    for(int i = 0; i < g; i++) {
        printf(" P%d |", g_p[i]);
    }

    printf("\n%d", at[0]);
    for(int i = 0; i < g; i++) {
        printf("   %d", g_t[i]);
    }

    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("\n\nProcess\tAT\tBT\tCT\tWT\tTAT\tRT\n");

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt_time[i] = first_exec[i] - at[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], wt[i], tat[i], rt_time[i]);

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt_time[i];
    }

    printf("\nAverage WT = %.2f", total_wt/n);
    printf("\nAverage TAT = %.2f", total_tat/n);
    printf("\nAverage RT = %.2f\n", total_rt/n);

    return 0;
}