#include<stdio.h>

// Function to print Gantt Chart
void ganttChart(int order[], int time[], int k)
{
    printf("\nGantt Chart:\n|");
    for(int i=0;i<k;i++)
        printf(" P%d |", order[i]);

    printf("\n%d", time[0]);
    for(int i=1;i<=k;i++)
        printf("   %d", time[i]);

    printf("\n");
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);

    int at[n], bt[n], pr[n], rt[n];
    int ct[n], tat[n], wt[n], resp[n], pid[n];
    int completed=0, time=0;

    int order[1000];      // Gantt chart execution order
    int timeLine[1001];   // Timeline for Gantt chart
    int k=0;              // Gantt chart size

    float avgTAT=0, avgWT=0, avgRT=0;

    // Input processes
    for(int i=0;i<n;i++)
    {
        pid[i]=i+1;

        printf("\nArrival Time for P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Burst Time for P%d: ",i+1);
        scanf("%d",&bt[i]);

        printf("Priority for P%d: ",i+1);
        scanf("%d",&pr[i]);

        rt[i] = bt[i];  // remaining time
        resp[i] = -1;   // to check first response
    }

    timeLine[0] = 0;

    // Scheduling loop
    while(completed < n)
    {
        int index = -1;
        int highest = 9999;

        // Find process with highest priority at current time
        for(int i=0;i<n;i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                if(pr[i] < highest)
                {
                    highest = pr[i];
                    index = i;
                }
                else if(pr[i] == highest) // tie breaker by arrival time
                {
                    if(at[i] < at[index])
                        index = i;
                }
            }
        }

        if(index != -1)
        {
            // First response time
            if(resp[index] == -1)
                resp[index] = time;

            order[k] = pid[index];
            k++;
            time++;           // run for 1 unit
            rt[index]--;

            timeLine[k] = time;

            if(rt[index] == 0)
            {
                ct[index] = time;
                tat[index] = ct[index] - at[index];
                wt[index] = tat[index] - bt[index];

                avgTAT += tat[index];
                avgWT += wt[index];
                avgRT += resp[index] - at[index];

                completed++;
            }
        }
        else
        {
            // CPU idle
            order[k] = 0; // 0 = idle
            k++;
            time++;
            timeLine[k] = time;
        }
    }

    // Print process table
    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i], resp[i]-at[i]);
    }

    // Print Gantt Chart
    printf("\nNote: '0' in Gantt Chart represents idle CPU.\n");
    ganttChart(order, timeLine, k);

    // Print averages
    printf("\nAverage TAT: %.2f\n", avgTAT/n);
    printf("Average WT: %.2f\n", avgWT/n);
    printf("Average RT: %.2f\n", avgRT/n);

    return 0;
}