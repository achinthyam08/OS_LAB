#include <stdio.h>

int main() {
    int n, m, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int Allocation[n][m], Request[n][m], Available[m];
    int Finish[n], Work[m];

    // Input Allocation
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }

    // Input Request
    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &Request[i][j]);
        }
    }

    // Input Available
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &Available[i]);
    }

    // Step 1(a): Work = Available
    for(i = 0; i < m; i++) {
        Work[i] = Available[i];
    }

    // Step 1(b): Initialize Finish
    for(i = 0; i < n; i++) {
        int zero = 1;
        for(j = 0; j < m; j++) {
            if(Allocation[i][j] != 0) {
                zero = 0;
                break;
            }
        }
        if(zero)
            Finish[i] = 1; // true
        else
            Finish[i] = 0; // false
    }

    // Step 2 & 3: Detection loop
    int found;
    do {
        found = 0;
        for(i = 0; i < n; i++) {
            if(Finish[i] == 0) { // not finished
                int can_allocate = 1;

                for(j = 0; j < m; j++) {
                    if(Request[i][j] > Work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }

                if(can_allocate) {
                    // Work = Work + Allocation[i]
                    for(j = 0; j < m; j++) {
                        Work[j] += Allocation[i][j];
                    }
                    Finish[i] = 1;
                    found = 1;
                }
            }
        }
    } while(found);

    // Step 4: Check deadlock
    int deadlock = 0;
    printf("\nDeadlocked Processes:\n");
    for(i = 0; i < n; i++) {
        if(Finish[i] == 0) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0) {
        printf("No Deadlock Detected");
    }

    printf("\n");
    return 0;
}
