#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id, at, bt, rt, ct, wt, tat;
    int type; // 0 = system, 1 = user
} Process;

Process p[MAX];

int gantt_pid[MAX];
int gantt_time[MAX];
int g_index = 0;

// Sort by arrival time
void sortByArrival(int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

// Sort by Process ID
void sortByID(int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].id > p[j].id) {
                Process temp = p[i];
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

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);
        p[i].id = i;

        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);

        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);

        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        p[i].rt = p[i].bt;
    }

    sortByArrival(n);

    int time = 0, completed = 0;

    int current = -1;

    while (completed < n) {
        int highest = -1;

        // Select process (system priority)
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (highest == -1)
                    highest = i;
                else {
                    if (p[i].type < p[highest].type)
                        highest = i;
                    else if (p[i].type == p[highest].type &&
                             p[i].at < p[highest].at)
                        highest = i;
                }
            }
        }

        if (highest == -1) {
            time++;
            continue;
        }

        // Gantt chart (compressed)
        if (g_index == 0 || gantt_pid[g_index - 1] != p[highest].id) {
            gantt_pid[g_index] = p[highest].id;
            gantt_time[g_index] = time;
            g_index++;
        }

        // Execute
        p[highest].rt--;
        time++;

        // Completion
        if (p[highest].rt == 0) {
            p[highest].ct = time;
            completed++;
        }
    }

    gantt_time[g_index] = time;

    // Calculate WT and TAT
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    sortByID(n);
    // Output Table
    printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               (p[i].type == 0) ? "System" : "User",
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].wt,
               p[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");

    printf("|");
    for (int i = 0; i < g_index; i++) {
        printf(" P%d |", gantt_pid[i]);
    }

    printf("\n%d", gantt_time[0]);
    for (int i = 1; i <= g_index; i++) {
        printf("    %d", gantt_time[i]);
    }

    printf("\n");

    return 0;
}
