#include <stdio.h>
#include<math.h>

#define MAX 10

typedef struct {
    int id, bt, deadline, period, share;
    int ct, wt, tat, done;
} Process;


int checkRM(Process p[], int n) {
    float U = 0;

    for (int i = 0; i < n; i++)
        U += (float)p[i].bt / p[i].period;

    float bound = n * (pow(2, (float)1/n) - 1);

    printf("\n[RM] Utilization = %.3f, Bound = %.3f\n", U, bound);

    if (U <= bound)
        return 1;
    else
        return 0;
}
int checkEDF(Process p[], int n) {
    float U = 0;

    for (int i = 0; i < n; i++)
        U += (float)p[i].bt / p[i].period;

    printf("[EDF] Utilization = %.3f\n", U);

    if (U <= 1.0)
        return 1;
    else
        return 0;
}
int checkPRO(Process p[], int n) {
    int total = 0;

    for (int i = 0; i < n; i++)
        total += p[i].share;

    printf("[PROPORTIONAL] Total Share = %d\n", total);

    if (total > 0)
        return 1;
    else
        return 0;
}

void reset(Process p[], int n) {
    for (int i = 0; i < n; i++)
        p[i].done = 0;
}

void EDF(Process p[], int n) {
    int time = 0, completed = 0;

    reset(p, n);

    while (completed < n) {
        int idx = -1;
        int minD = 9999;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].deadline < minD) {
                minD = p[i].deadline;
                idx = i;
            }
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = 1;

        completed++;
    }

    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");
    printf("ID   BT   Deadline   CT   WT   TAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d   %d    %d          %d    %d    %d\n",
               p[i].id, p[i].bt, p[i].deadline,
               p[i].ct, p[i].wt, p[i].tat);
    }
}

void RMS(Process p[], int n) {
    int time = 0, completed = 0;

    reset(p, n);

    while (completed < n) {
        int idx = -1;
        int minP = 9999;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].period < minP) {
                minP = p[i].period;
                idx = i;
            }
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = 1;

        completed++;
    }

    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    printf("ID   BT   Period   CT   WT   TAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d   %d    %d        %d    %d    %d\n",
               p[i].id, p[i].bt, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
    }
}


void PROPORTIONAL(Process p[], int n) {
    int time = 0, completed = 0;

    reset(p, n);

    while (completed < n) {
        int idx = -1;
        int maxShare = -1;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].share > maxShare) {
                maxShare = p[i].share;
                idx = i;
            }
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = 1;

        completed++;
    }

    printf("\n===== Proportional Share Scheduling =====\n");
    printf("ID   BT   Share   CT   WT   TAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d   %d    %d       %d    %d    %d\n",
               p[i].id, p[i].bt, p[i].share,
               p[i].ct, p[i].wt, p[i].tat);
    }
}


int main() {
    int n;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");

    for (int i = 0; i < n; i++) {
        p[i].id = i;

        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);

        printf("Share (for Proportional): ");
        scanf("%d", &p[i].share);
    }
    if (checkRM(p, n)){
        printf("RM Scheduling: SCHEDULABLE \n");
        RMS(p,n);}
    else
        printf("RM Scheduling: NOT SCHEDULABLE \n");

    if (checkEDF(p, n)){
        printf("EDF Scheduling: SCHEDULABLE \n");
        EDF(p,n);}
    else
        printf("EDF Scheduling: NOT SCHEDULABLE \n");

    if (checkPRO(p, n)){
        printf("Proportional Scheduling: VALID \n");
        PROPORTIONAL(p,n);}
    else
        printf("Proportional Scheduling: INVALID \n");

    return 0;
}
