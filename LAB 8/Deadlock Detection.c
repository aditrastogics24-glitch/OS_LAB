#include <stdio.h>

#define MAX 10

int main() {
    int n, m;
    int allocation[MAX][MAX], request[MAX][MAX];
    int available[MAX], work[MAX];
    int finish[MAX] = {0};

    // Input
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Request Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
        work[i] = available[i];
    }

    // Step 1: Initialize finish[]
    for(int i = 0; i < n; i++) {
        int zero = 1;
        for(int j = 0; j < m; j++) {
            if(allocation[i][j] != 0) {
                zero = 0;
                break;
            }
        }
        if(zero)
            finish[i] = 1;
    }

    // Step 2: Detection Algorithm
    int found = 1;

    while(found) {
        found = 0;

        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int j;
                for(j = 0; j < m; j++) {
                    if(request[i][j] > work[j])
                        break;
                }

                if(j == m) {
                    // Process can finish
                    for(int k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    finish[i] = 1;
                    found = 1;
                }
            }
        }
    }

    // Step 3: Check deadlock
    int deadlock = 0;

    for(int i = 0; i < n; i++) {
        if(finish[i] == 0) {
            printf("Process P%d is DEADLOCKED\n", i);
            deadlock = 1;
        }
    }

    if(!deadlock)
        printf("No deadlock detected. System is safe.\n");

    return 0;
}