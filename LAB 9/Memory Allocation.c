#include <stdio.h>

#define MAX 20

void firstFit(int bsize[], int m, int psize[], int n) {
    int allocation[n], i, j;
    for (i = 0; i < n; i++) allocation[i] = -1;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (bsize[j] >= psize[i]) {
                allocation[i] = j;
                bsize[j] -= psize[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i + 1, psize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int bsize[], int m, int psize[], int n) {
    int allocation[n], i, j;
    for (i = 0; i < n; i++) allocation[i] = -1;

    for (i = 0; i < n; i++) {
        int bestIdx = -1;
        for (j = 0; j < m; j++) {
            if (bsize[j] >= psize[i]) {
                if (bestIdx == -1 || bsize[bestIdx] > bsize[j])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            bsize[bestIdx] -= psize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i + 1, psize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int bsize[], int m, int psize[], int n) {
    int allocation[n], i, j;
    for (i = 0; i < n; i++) allocation[i] = -1;

    for (i = 0; i < n; i++) {
        int worstIdx = -1;
        for (j = 0; j < m; j++) {
            if (bsize[j] >= psize[i]) {
                if (worstIdx == -1 || bsize[worstIdx] < bsize[j])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            bsize[worstIdx] -= psize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i + 1, psize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int m, n, i, choice;
    int bsize[MAX], psize[MAX], tempBsize[MAX];

    printf("Enter number of blocks: ");
    scanf("%d", &m);
    printf("Enter size of each block: \n");
    for (i = 0; i < m; i++) scanf("%d", &bsize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter size of each process: \n");
    for (i = 0; i < n; i++) scanf("%d", &psize[i]);

    do {
        // Reset block sizes for each run
        for(i = 0; i < m; i++) tempBsize[i] = bsize[i];

        printf("\n--- Memory Allocation Menu ---");
        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: firstFit(tempBsize, m, psize, n); break;
            case 2: bestFit(tempBsize, m, psize, n); break;
            case 3: worstFit(tempBsize, m, psize, n); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
