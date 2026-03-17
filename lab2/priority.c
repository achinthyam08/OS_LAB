#include <stdio.h>

struct Process {
    int pid, at, bt, pr;
    int rt, ct, tat, wt;
    int first;
};

int main() {

    int n,time=0,completed=0;
    struct Process p[10];
    int i,idx,highest;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++) {

        printf("\nProcess %d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        printf("Priority: ");
        scanf("%d",&p[i].pr);

        p[i].pid=i+1;
        p[i].rt=p[i].bt;
        p[i].first=-1;
    }

    int gantt[100], gtime[100];
    int k=0;

    gtime[k]=0;

    while(completed<n) {

        highest=9999;
        idx=-1;

        for(i=0;i<n;i++) {
            if(p[i].at<=time && p[i].rt>0) {
                if(p[i].pr<highest) {
                    highest=p[i].pr;
                    idx=i;
                }
            }
        }

        if(idx!=-1) {

            if(p[idx].first==-1)
                p[idx].first=time;

            gantt[k]=p[idx].pid;

            p[idx].rt--;
            time++;

            gtime[++k]=time;

            if(p[idx].rt==0) {

                completed++;

                p[idx].ct=time;
                p[idx].tat=p[idx].ct-p[idx].at;
                p[idx].wt=p[idx].tat-p[idx].bt;
            }
        }
        else
            time++;
    }

    printf("\nGantt Chart:\n");

    printf(" ");

    for(i=0;i<k;i++)
        printf("----");

    printf("-\n|");

    for(i=0;i<k;i++)
        printf(" P%d |",gantt[i]);

    printf("\n ");

    for(i=0;i<k;i++)
        printf("----");

    printf("-\n");

    for(i=0;i<=k;i++)
        printf("%d    ",gtime[i]);

    float avgwt=0,avgtat=0,avgrt=0;

    printf("\n\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++) {

        int response=p[i].first-p[i].at;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].pr,p[i].ct,p[i].tat,p[i].wt,response);

        avgwt+=p[i].wt;
        avgtat+=p[i].tat;
        avgrt+=response;
    }

    printf("\nAverage Waiting Time = %.2f",avgwt/n);
    printf("\nAverage Turnaround Time = %.2f",avgtat/n);
    printf("\nAverage Response Time = %.2f",avgrt/n);

    return 0;
}
