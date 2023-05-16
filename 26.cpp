#include <stdio.h>
#define MAX_SIZE 10
struct Process {
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
};
void priorityScheduling(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    processes[0].waitingTime = 0;
    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].burstTime + processes[i - 1].waitingTime;
    }
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
    }
}
void displayProcesses(struct Process processes[], int n) {
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, processes[i].burstTime, processes[i].priority,
               processes[i].waitingTime, processes[i].turnaroundTime);
    }
}
int main() {
    int n;
    struct Process processes[MAX_SIZE];
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid number of processes. Please enter a value between 1 and %d.\n", MAX_SIZE);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        
        printf("Enter priority for P%d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }
    priorityScheduling(processes, n);
    printf("\nProcess scheduling results:\n");
    displayProcesses(processes, n);
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }
    double avgWaitingTime = (double) totalWaitingTime / n;
    double avgTurnaroundTime = (double) totalTurnaroundTime / n;
    printf("\nAverage Waiting Time: %.2lf\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2lf\n", avgTurnaroundTime);
    return 0;
}

