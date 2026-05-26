#include <stdio.h>

#define MAX 50

/* Function to check whether page is present */
int search(int frames[], int capacity, int page)
{
    for(int i = 0; i < capacity; i++)
    {
        if(frames[i] == page)
            return i;
    }
    return -1;
}

/* ---------------- FIFO ---------------- */
void FIFO(int pages[], int n, int capacity)
{
    int frames[capacity];
    int index = 0;
    int faults = 0;

    for(int i = 0; i < capacity; i++)
        frames[i] = -1;

    printf("\n===== FIFO =====\n");

    for(int k = 0; k < n; k++)
    {
        int found = search(frames, capacity, pages[k]);

        if(found == -1)
        {
            frames[index] = pages[k];
            index = (index + 1) % capacity;
            faults++;
        }

        printf("Page %d -> ", pages[k]);

        for(int i = 0; i < capacity; i++)
        {
            if(frames[i] != -1)
                printf("%d ", frames[i]);
            else
                printf("- ");
        }

        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

/* ---------------- LRU ---------------- */
void LRU(int pages[], int n, int capacity)
{
    int frames[capacity];
    int recent[capacity];
    int faults = 0;
    int time = 0;

    for(int i = 0; i < capacity; i++)
    {
        frames[i] = -1;
        recent[i] = 0;
    }

    printf("\n===== LRU =====\n");

    for(int k = 0; k < n; k++)
    {
        int pos = search(frames, capacity, pages[k]);

        /* Page Hit */
        if(pos != -1)
        {
            time++;
            recent[pos] = time;
        }

        /* Page Fault */
        else
        {
            int lru = 0;

            for(int i = 1; i < capacity; i++)
            {
                if(recent[i] < recent[lru])
                    lru = i;
            }

            time++;
            frames[lru] = pages[k];
            recent[lru] = time;
            faults++;
        }

        printf("Page %d -> ", pages[k]);

        for(int i = 0; i < capacity; i++)
        {
            if(frames[i] != -1)
                printf("%d ", frames[i]);
            else
                printf("- ");
        }

        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

/* ---------------- OPTIMAL ---------------- */
void OPTIMAL(int pages[], int n, int capacity)
{
    int frames[capacity];
    int faults = 0;

    for(int i = 0; i < capacity; i++)
        frames[i] = -1;

    printf("\n===== OPTIMAL =====\n");

    for(int k = 0; k < n; k++)
    {
        int found = search(frames, capacity, pages[k]);

        /* Page Fault */
        if(found == -1)
        {
            int replace = -1;
            int farthest = k;

            for(int i = 0; i < capacity; i++)
            {
                int j;

                for(j = k + 1; j < n; j++)
                {
                    if(frames[i] == pages[j])
                    {
                        if(j > farthest)
                        {
                            farthest = j;
                            replace = i;
                        }
                        break;
                    }
                }

                /* Page not used again */
                if(j == n)
                {
                    replace = i;
                    break;
                }
            }

            /* Empty frame available */
            if(replace == -1)
                replace = 0;

            frames[replace] = pages[k];
            faults++;
        }

        printf("Page %d -> ", pages[k]);

        for(int i = 0; i < capacity; i++)
        {
            if(frames[i] != -1)
                printf("%d ", frames[i]);
            else
                printf("- ");
        }

        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

/* ---------------- MAIN ---------------- */
int main()
{
    int pages[MAX];
    int n, capacity;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");

    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter frame capacity: ");
    scanf("%d", &capacity);

    FIFO(pages, n, capacity);

    LRU(pages, n, capacity);

    OPTIMAL(pages, n, capacity);

    return 0;
}