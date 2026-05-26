#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int available[MAX];

    // Input Allocation
    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    // Input Max
    printf("\nEnter Max Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Input Available
    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    // Compute Need = Max - Allocation
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    //  NEW REQUEST INPUT
    int process;
    int request[MAX];

    printf("\nEnter process number making request: ");
    scanf("%d", &process);

    printf("Enter request vector:\n");
    for(int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    // Step 1: Check Request <= Need
    for(int i = 0; i < m; i++) {
        if(request[i] > need[process][i]) {
            printf("\nError: Request exceeds maximum need.\n");
            return 0;
        }
    }

    // Step 2: Check Request <= Available
    for(int i = 0; i < m; i++) {
        if(request[i] > available[i]) {
            printf("\nResources not available. Process must wait.\n");
            return 0;
        }
    }

    // Step 3: Pretend Allocation
    for(int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    //  SAFETY ALGORITHM
    int work[MAX], safeSequence[MAX];
    bool finish[MAX];

    for(int i = 0; i < m; i++)
        work[i] = available[i];

    for(int i = 0; i < n; i++)
        finish[i] = false;

    int count = 0;

    while(count < n) {
        bool found = false;

        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                int j;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j])
                        break;
                }

                if(j == m) {
                    for(int k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found) {
            printf("\nSystem will be in UNSAFE STATE.\n");

            //  ROLLBACK
            for(int i = 0; i < m; i++) {
                available[i] += request[i];
                allocation[process][i] -= request[i];
                need[process][i] += request[i];
            }

            printf("Request cannot be granted.\n");
            return 0;
        }
    }

    // SAFE
    printf("\nRequest can be granted.\n");
    printf("System is in SAFE STATE\nSafe Sequence: ");

    for(int i = 0; i < n; i++) {
        printf("P%d", safeSequence[i]);
        if(i != n - 1)
            printf(" -> ");
    }
    printf("\n");

    return 0;
}
