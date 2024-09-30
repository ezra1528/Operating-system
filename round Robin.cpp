#include <stdio.h>

// Function to perform Round Robin scheduling
void roundRobinScheduling(int burst_time[], int n, int quantum) {
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    int time = 0; // Current time
    while (1) {
        int done = 1; // Assume all processes are done
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0; // There are remaining processes
                if (remaining_time[i] > quantum) {
                    // Execute the process for the quantum time
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    // Execute the remaining time for the process
                    time += remaining_time[i];
                    remaining_time[i] = 0;
                    printf("Process %d completed at time %d\n", i + 1, time);
                }
            }
        }
        if (done == 1) {
            break; // All processes are done
        }
    }
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    int burst_time[n];

    // Input burst times for each process
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    // Perform Round Robin scheduling
    roundRobinScheduling(burst_time, n, quantum);

    return 0;
}
