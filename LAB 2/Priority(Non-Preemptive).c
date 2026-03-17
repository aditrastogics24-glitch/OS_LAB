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

    int at[n], bt[n], pr[n], ct[n], tat[n], wt[n], rt[n];
    int visited[n], pid[n];
    int order[n];      // Process execution order
    int timeLine[n+1]; // Timeline for Gantt chart

    int time=0, completed=0, k=0;
    float avgTAT=0, avgWT=0, avgRT=0;

    // Input process details
    for(int i=0;i<n;i++)
    {
        pid[i]=i+1;
        visited[i]=0;

        printf("\nArrival Time for P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Burst Time for P%d: ",i+1);
        scanf("%d",&bt[i]);

        printf("Priority for P%d: ",i+1);
        scanf("%d",&pr[i]);
    }

    timeLine[0] = 0;

    // Scheduling loop
    while(completed<n)
    {
        int index=-1;
        int highest=9999;

        // Find highest priority process among arrived
        for(int i=0;i<n;i++)
        {
            if(at[i]<=time && visited[i]==0)
            {
                if(pr[i]<highest)
                {
                    highest=pr[i];
                    index=i;
                }
            }
        }

        if(index!=-1)
        {
            order[k] = pid[index];

            int startTime = time;
            rt[index] = startTime - at[index]; // Response Time

            time += bt[index];
            timeLine[k+1] = time;

            ct[index] = time;
            tat[index] = ct[index] - at[index]; // Turnaround Time
            wt[index] = tat[index] - bt[index]; // Waiting Time

            avgTAT += tat[index];
            avgWT += wt[index];
            avgRT += rt[index];

            visited[index]=1;
            completed++;
            k++;
        }
        else
        {
            time++; // CPU idle
        }
    }

    // Print table
    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i], rt[i]);
    }

    // Print Gantt Chart
    ganttChart(order, timeLine, k);

    // Print averages
    printf("\nAverage TAT: %.2f\n", avgTAT/n);
    printf("Average WT: %.2f\n", avgWT/n);
    printf("Average RT: %.2f\n", avgRT/n);

    return 0;
}