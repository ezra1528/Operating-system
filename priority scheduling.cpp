#include <stdio.h>

// Structure to represent a process
struct Process {
    int process_id;
    int burst_time;
    int priority;
};

// Function to perform priority scheduling
void priorityScheduling(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n];
    waiting_time[0] = 0;

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }

    // Calculate the total waiting time and turnaround time
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Calculate and display the average waiting time and turnaround time
    double average_waiting_time = (double)total_waiting_time / n;
    double average_turnaround_time = (double)total_turnaround_time / n;

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, processes[i].priority, waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time: %.2lf\n", average_waiting_time);
    printf("Average Turnaround Time: %.2lf\n", average_turnaround_time);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input burst times and priorities for each process
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    // Sort the processes based on priority (higher value means higher priority)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Perform priority scheduling
    priorityScheduling(processes, n);

    return 0;
}
