
#include <stdio.h>

#define MAX 10

int main() {
    int n, m;
    int allocation[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int available[MAX], work[MAX];
    int finish[MAX] = {0};
    int safeSequence[MAX];

    int request[MAX], process;

    // Input
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Maximum Demand Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for(int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    // Calculate Need = Max - Allocation
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
;;
    // 🔹 New Request
    printf("\nEnter process number making request: ");
    scanf("%d", &process);

    printf("Enter request for process P%d:\n", process);
    for(int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    // 🔸 Check Request ≤ Need
    for(int i = 0; i < m; i++) {
        if(request[i] > need[process][i]) {
            printf("Error: Request exceeds process need!\n");
            return 0;
        }
    }

    // 🔸 Check Request ≤ Available
    for(int i = 0; i < m; i++) {
        if(request[i] > available[i]) {
            printf("Resources not available. Process must wait.\n");
            return 0;
        }
    }

    // 🔸 Pretend Allocation
    for(int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Initialize work = available
    for(int i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;

    while(count < n) {
        int found = 0;

        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int j;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j])
                        break;
                }

                if(j == m) {
                    for(int k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nSystem is in UNSAFE state. Request cannot be granted.\n");

            // 🔸 Rollback
            for(int i = 0; i < m; i++) {
                available[i] += request[i];
                allocation[process][i] -= request[i];
                need[process][i] += request[i];
            }
            return 0;
        }
    }

    // ✅ Safe
    printf("\nSystem is in SAFE state.\nSafe sequence: ");
    for(int i = 0; i < n; i++) {
        printf("P%d", safeSequence[i]);
        if(i != n - 1)
            printf(" -> ");
    }
    printf("\n");

    printf("Request granted successfully.\n");

    return 0;
}
