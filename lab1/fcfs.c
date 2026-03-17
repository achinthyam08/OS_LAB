#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], wt[n], tat[n], rt[n];


    for(int i = 0; i < n; i++) {
        printf("P%d arrival time: ", i+1);
        scanf("%d", &at[i]);
        printf("P%d burst time: ", i+1);
        scanf("%d", &bt[i]);
    }
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if (at[i]>at[j]){
                int temp;
                temp=at[i]; at[i]=at[j]; at[j]=temp;
                temp=bt[i]; bt[i]=bt[j]; bt[j]=temp;
            }}}


    ct[0] = at[0] + bt[0];
    wt[0] = 0;
    rt[0] = 0;
    tat[0] = bt[0];

    for(int i = 1; i < n; i++) {

        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = wt[i];   // FCFS response = waiting
    }

    float avg_wt=0, avg_tat=0, avg_rt=0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
        avg_rt += rt[i];
    }

    printf("\nAverage WT = %.2f", avg_wt/n);
    printf("\nAverage TAT = %.2f", avg_tat/n);
    printf("\nAverage RT = %.2f\n", avg_rt/n);

    return 0;
}
