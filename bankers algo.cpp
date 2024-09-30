#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int num_processes;
int num_resources;
int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

// Function to check if the system is in a safe state
int isSafeState(int work[], int finish[]) {
    int i, j;
    int count = 0;

    while (count < num_processes) {
        int found = 0;
        for (i = 0; i < num_processes; i++) {
            if (finish[i] == 0) {
                int can_allocate = 1;
                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }
                if (can_allocate) {
                    for (j = 0; j < num_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (!found) {
            return 0; // System is not in a safe state
        }
    }
    return 1; // System is in a safe state
}

// Function to request resources for a process
void requestResources(int process) {
    int request[MAX_RESOURCES];
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int i, j;

    printf("Enter the request for Process %d:\n", process + 1);
    for (i = 0; i < num_resources; i++) {
        printf("Resource %d: ", i + 1);
        scanf("%d", &request[i]);
    }

    for (i = 0; i < num_resources; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Request exceeds maximum claim.\n");
            return;
        }
    }

    for (i = 0; i < num_resources; i++) {
        if (request[i] > available[i]) {
            printf("Process %d must wait. Request exceeds available resources.\n", process + 1);
            return;
        }
    }

    for (i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    for (i = 0; i < num_resources; i++) {
        work[i] -= request[i];
    }

    for (i = 0; i < num_resources; i++) {
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
        available[i] -= request[i];
    }

    if (isSafeState(work, finish)) {
        printf("Request granted. Process %d is in a safe state.\n", process + 1);
    } else {
        printf("Request denied. Process %d must wait.\n", process + 1);
        // Roll back the changes if the request is denied
        for (i = 0; i < num_resources; i++) {
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
            available[i] += request[i];
        }
    }
}

int main() {
    int i, j;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the available resources:\n");
    for (i = 0; i < num_resources; i++) {
        printf("Resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum demand for each process:\n");
    for (i = 0; i < num_processes; i++) {
        printf("For Process %d:\n", i + 1);
        for (j = 0; j < num_resources; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &maximum[i][j]);
            need[i][j] = maximum[i][j];
        }
    }

    printf("Enter the current allocation of resources to each process:\n");
    for (i = 0; i < num_processes; i++) {
        printf("For Process %d:\n", i + 1);
        for (j = 0; j < num_resources; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &allocation[i][j]);
            need[i][j] -= allocation[i][j];
            available[j] -= allocation[i][j];
        }
    }

    int process;
    printf("Enter the process making a request (1 to %d): ", num_processes);
    scanf("%d", &process);

    if (process < 1 || process > num_processes) {
        printf("Invalid process number.\n");
        return 1;
    }

    requestResources(process - 1);

    return 0;
}
