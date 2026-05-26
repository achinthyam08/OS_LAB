#include <stdio.h>
#include <string.h>

#define MAX 50

int main() {
    int n, i, time = 0, completed = 0, idx = 0;

    int pid[MAX], at[MAX], bt[MAX], rt[MAX];
    int ct[MAX], tat[MAX], wt[MAX], res[MAX], started[MAX] = {0};
    char type[MAX][10];

    printf("Enter n: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nP%d\n", i + 1);
        scanf("%d %d %d %s", &pid[i], &at[i], &bt[i], type[i]);
        rt[i] = bt[i];
    }

    // Sort by arrival
    for (i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (at[i] > at[j]) {
                int t;
                t = at[i]; at[i] = at[j]; at[j] = t;
                t = bt[i]; bt[i] = bt[j]; bt[j] = t;
                t = pid[i]; pid[i] = pid[j]; pid[j] = t;
                char tmp[10];
                strcpy(tmp, type[i]);
                strcpy(type[i], type[j]);
                strcpy(type[j], tmp);
            }

    int sysQ[MAX], userQ[MAX], sf = 0, sr = -1, uf = 0, ur = -1;
    int current = -1;

    int gantt[MAX], g = 0;

    while (completed < n) {

        // Add processes
        while (idx < n && at[idx] <= time) {
            if (strcmp(type[idx], "system") == 0)
                sysQ[++sr] = idx;
            else
                userQ[++ur] = idx;
            idx++;
        }

        // Preemption
        if (current != -1 && strcmp(type[current], "user") == 0 && sf <= sr) {
            userQ[++ur] = current;
            current = -1;
        }

        // Select process
        if (current == -1) {
            if (sf <= sr) current = sysQ[sf++];
            else if (uf <= ur) current = userQ[uf++];
            else { time++; continue; }

            if (!started[current]) {
                res[current] = time - at[current];
                started[current] = 1;
            }
        }

        // Display queues
        printf("\nTime %d\nSystem: ", time);
        for (i = sf; i <= sr; i++) printf("P%d|", pid[sysQ[i]]);
        if (sf > sr) printf("Empty");

        printf("\nUser:   ");
        for (i = uf; i <= ur; i++) printf("P%d|", pid[userQ[i]]);
        if (uf > ur) printf("Empty");

        printf("\n");

        // Gantt
        gantt[g++] = pid[current];

        // Execute
        rt[current]--;
        time++;

        if (rt[current] == 0) {
            ct[current] = time;
            tat[current] = ct[current] - at[current];
            wt[current] = tat[current] - bt[current];
            completed++;
            current = -1;
        }
    }

    // Gantt chart
    printf("\nGantt:\n|");
    for (i = 0; i < g; i++) printf("P%d|", gantt[i]);

    printf("\n0");
    for (i = 1; i <= g; i++) printf(" %d", i);

    // Table
    float aw = 0, atat = 0, ar = 0;
    printf("\n\nPID AT BT CT TAT WT RT\n");

    for (i = 0; i < n; i++) {
        printf("%d %d %d %d %d %d %d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i], res[i]);
        aw += wt[i]; atat += tat[i]; ar += res[i];
    }

    printf("\nAvg WT=%.2f", aw / n);
    printf("\nAvg TAT=%.2f", atat / n);
    printf("\nAvg RT=%.2f\n", ar / n);

    return 0;
}
