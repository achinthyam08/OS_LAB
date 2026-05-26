#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main() {
    int n, m; // n = processes, m = resources

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int available[MAX];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Max Matrix
    printf("\nEnter Max Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate Need Matrix = Max - Allocation
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Safety Algorithm
    int work[MAX];
    bool finish[MAX];
    int safeSequence[MAX];
    int count = 0;

    // Step 1: Initialize
    for(int i = 0; i < m; i++)
        work[i] = available[i];

    for(int i = 0; i < n; i++)
        finish[i] = false;

    // Step 2–4
    while(count < n) {
        bool found = false;

        for(int i = 0; i < n; i++) {
            if(finish[i] == false) {
                int j;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j])
                        break;
                }

                // If all needs can be satisfied
                if(j == m) {
                    // Work = Work + Allocation[i]
                    for(int k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        // If no process found
        if(found == false) {
            printf("\nSystem is in UNSAFE STATE (Deadlock possible)\n");
            return 0;
        }
    }

    // Safe state
    printf("\nSystem is in SAFE STATE\nSafe Sequence: ");
    for(int i = 0; i < n; i++) {
        printf("P%d", safeSequence[i]);
        if(i != n - 1)
            printf(" -> ");
    }
    printf("\n");

    return 0;
}
