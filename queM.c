// que 3

#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
} Process;

void roundRobin(Process processes[], int n, int time_quantum) {
    int remaining_processes = n;
    int current_time = 0;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    
    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) {
                int execute_time = (processes[i].remaining_time < time_quantum) ? processes[i].remaining_time : time_quantum;
                processes[i].remaining_time -= execute_time;
                current_time += execute_time;
                
                if (processes[i].remaining_time == 0) {
                    remaining_processes--;
                    int turnaround_time = current_time - processes[i].arrival_time;
                    int waiting_time = turnaround_time - processes[i].burst_time;
                    total_turnaround_time += turnaround_time;
                    total_waiting_time += waiting_time;
                    printf("Process %d completed (Turnaround Time: %d, Waiting Time: %d)\n", processes[i].process_id, turnaround_time, waiting_time);
                }
            }
        }
    }
    
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];
    int time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n > MAX_PROCESSES || n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].process_id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    roundRobin(processes, n, time_quantum);

    return 0;
}
// que 7 

#include <stdio.h>

#define MAX_PROCESSES 10
#define INF 9999

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_completed;
} Process;

int findShortestJob(Process processes[], int n, int current_time) {
    int shortest_job_index = -1;
    int shortest_burst = INF;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].is_completed == 0) {
            if (processes[i].burst_time < shortest_burst) {
                shortest_burst = processes[i].burst_time;
                shortest_job_index = i;
            }
        }
    }

    return shortest_job_index;
}

void sjfPreemptive(Process processes[], int n) {
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int completed_processes = 0;
    int current_time = 0;

    while (completed_processes < n) {
        int shortest_job_index = findShortestJob(processes, n, current_time);

        if (shortest_job_index == -1) {
            current_time++;
            continue;
        }

        if (processes[shortest_job_index].start_time == -1) {
            processes[shortest_job_index].start_time = current_time;
        }

        processes[shortest_job_index].remaining_time--;

        if (processes[shortest_job_index].remaining_time == 0) {
            processes[shortest_job_index].completion_time = current_time + 1;
            processes[shortest_job_index].turnaround_time = processes[shortest_job_index].completion_time - processes[shortest_job_index].arrival_time;
            processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;
            total_turnaround_time += processes[shortest_job_index].turnaround_time;
            total_waiting_time += processes[shortest_job_index].waiting_time;
            processes[shortest_job_index].is_completed = 1;
            completed_processes++;
        }

        current_time++;
    }

    printf("Process\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n > MAX_PROCESSES || n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].process_id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].is_completed = 0;
    }

    sjfPreemptive(processes, n);

    return 0;
}
// que 11 
#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int n_processes, n_resources;

void initialize() {
    printf("Enter the number of processes: ");
    scanf("%d", &n_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &n_resources);

    printf("Enter the available resources: ");
    for (int i = 0; i < n_resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum resources required by each process:\n");
    for (int i = 0; i < n_processes; i++) {
        printf("For process %d: ", i);
        for (int j = 0; j < n_resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n_processes; i++) {
        printf("For process %d: ", i);
        for (int j = 0; j < n_resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

int isSafe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};

    for (int i = 0; i < n_resources; i++) {
        work[i] = available[i];
    }

    int safeSequence[MAX_PROCESSES];
    int safeCount = 0;

    while (safeCount < n_processes) {
        int found = 0;
        for (int i = 0; i < n_processes; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < n_resources; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == n_resources) {
                    for (int k = 0; k < n_resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[safeCount++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("Unsafe state! System is deadlocked.\n");
            return 0;
        }
    }

    printf("Safe sequence: ");
    for (int i = 0; i < n_processes; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");

    return 1;
}

int requestResources(int process_id, int request[]) {
    for (int i = 0; i < n_resources; i++) {
        if (request[i] > need[process_id][i] || request[i] > available[i])
            return 0;
    }

    for (int i = 0; i < n_resources; i++) {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    if (!isSafe()) {
        // If unsafe, rollback
        for (int i = 0; i < n_resources; i++) {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
        return 0;
    }

    return 1;
}

int main() {
    initialize();

    isSafe();

    printf("\nEnter the process id and resource request for the process:\n");
    int process_id, request[MAX_RESOURCES];
    scanf("%d", &process_id);
    printf("Enter resource request: ");
    for (int i = 0; i < n_resources; i++) {
        scanf("%d", &request[i]);
    }

    if (requestResources(process_id, request)) {
        printf("Resource allocation successful.\n");
    } else {
        printf("Resource allocation unsuccessful. System state remains unchanged.\n");
    }

    return 0;
}
