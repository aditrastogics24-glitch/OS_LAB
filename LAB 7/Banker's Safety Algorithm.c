#include <stdio.h>

#define MAX 10

int main() {
    int n, m;
    int allocation[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int available[MAX], work[MAX];
    int finish[MAX] = {0};
    int safeSequence[MAX];
    
    // Input number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Input Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Max Matrix
    printf("Enter Maximum Demand Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("Enter Available Resources:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
        work[i] = available[i]; // initialize work
    }

    // Calculate Need Matrix = Max - Allocation
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

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
                    // Process can finish
                    for(int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("System is in an UNSAFE state (Deadlock possible)\n");
            return 0;
        }
    }

    // If all processes finish
    printf("System is in a SAFE state.\nSafe sequence is: ");
    for(int i = 0; i < n; i++) {
        printf("P%d", safeSequence[i]);
        if(i != n - 1)
            printf(" -> ");
    }
    printf("\n");

    return 0;
}