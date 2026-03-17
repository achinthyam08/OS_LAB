#include <stdio.h>
#include <limits.h>

int main() {

    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n];

    for(int i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", i+1);
        scanf("%d", &bt[i]);
    }

    printf("\nChoose Scheduling Type:");
    printf("\n1. SJF Non-Preemptive");
    printf("\n2. SJF Preemptive (SRTF)");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    switch(choice) {


        case 1: {
            int completed[n], ct[n], wt[n], tat[n], rt[n];
            int time = 0, count = 0;

            for(int i = 0; i < n; i++)
                completed[i] = 0;

            while(count < n) {

                int idx = -1;
                int min = INT_MAX;

                for(int i = 0; i < n; i++) {
                    if(at[i] <= time && !completed[i] && bt[i] < min) {
                        min = bt[i];
                        idx = i;
                    }
                }

                if(idx != -1) {
                    time += bt[idx];
                    ct[idx] = time;
                    tat[idx] = ct[idx] - at[idx];
                    wt[idx] = tat[idx] - bt[idx];
                    rt[idx] = wt[idx];   // Non-preemptive
                    completed[idx] = 1;
                    count++;
                } else {
                    time++;
                }
            }

            float avg_wt=0, avg_tat=0, avg_rt=0;

            printf("\nProcess\tAT\tBT\tWT\tTAT\tRT\n");
            for(int i=0;i<n;i++){
                printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                i+1, at[i], bt[i], wt[i], tat[i], rt[i]);

                avg_wt += wt[i];
                avg_tat += tat[i];
                avg_rt += rt[i];
            }

            printf("\nAverage WT = %.2f", avg_wt/n);
            printf("\nAverage TAT = %.2f", avg_tat/n);
            printf("\nAverage RT = %.2f\n", avg_rt/n);
            break;
        }


        case 2: {
            int rt[n], wt[n], tat[n], ct[n], response[n];
            int first_exec[n];

            for(int i = 0; i < n; i++) {
                rt[i] = bt[i];
                first_exec[i] = -1;
            }

            int complete = 0, time = 0;

            while(complete < n) {

                int idx = -1;
                int min = INT_MAX;

                for(int i = 0; i < n; i++) {
                    if(at[i] <= time && rt[i] > 0 && rt[i] < min) {
                        min = rt[i];
                        idx = i;
                    }
                }

                if(idx != -1) {

                    if(first_exec[idx] == -1)
                        first_exec[idx] = time;

                    rt[idx]--;
                    time++;

                    if(rt[idx] == 0) {
                        complete++;
                        ct[idx] = time;
                        tat[idx] = ct[idx] - at[idx];
                        wt[idx] = tat[idx] - bt[idx];
                        response[idx] = first_exec[idx] - at[idx];
                    }

                } else {
                    time++;
                }
            }

            float avg_wt=0, avg_tat=0, avg_rt=0;

            printf("\nProcess\tAT\tBT\tWT\tTAT\tRT\n");
            for(int i=0;i<n;i++){
                printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                i+1, at[i], bt[i], wt[i], tat[i], response[i]);

                avg_wt += wt[i];
                avg_tat += tat[i];
                avg_rt += response[i];
            }

            printf("\nAverage WT = %.2f", avg_wt/n);
            printf("\nAverage TAT = %.2f", avg_tat/n);
            printf("\nAverage RT = %.2f\n", avg_rt/n);
            break;
        }

        default:
            printf("Invalid Choice!\n");
    }

    return 0;
}
