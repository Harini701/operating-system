#include <stdio.h>

void sjf_scheduling(int processes[], int bursts[], int n, float *avg_waiting_time, float *avg_turnaround_time) {
    int i, j, temp;
    int waiting_time[n];
    int turnaround_time[n];

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (bursts[i] > bursts[j]) {
                temp = bursts[i];
                bursts[i] = bursts[j];
                bursts[j] = temp;

                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    waiting_time[0] = 0;
    turnaround_time[0] = bursts[0];

    for (i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + bursts[i - 1];
        turnaround_time[i] = waiting_time[i] + bursts[i];
    }
    *avg_waiting_time = 0;
    *avg_turnaround_time = 0;

    for (i = 0; i < n; i++) {
        *avg_waiting_time += waiting_time[i];
        *avg_turnaround_time += turnaround_time[i];
    }

    *avg_waiting_time /= n;
    *avg_turnaround_time /= n;
}

int main() {
    int processes[] = {0, 1, 2};
    int bursts[] = {2, 4, 8};
    int n = sizeof(processes) / sizeof(processes[0]);

    float avg_waiting_time, avg_turnaround_time;

    sjf_scheduling(processes, bursts, n, &avg_waiting_time, &avg_turnaround_time);

    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}

