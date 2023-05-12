#include <stdio.h>
#define MAX_PROCESSES 10
typedef struct {
    char pid[3];
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;
int main() {
    int n = 3; 
    int quantum = 4; 
    Process processes[MAX_PROCESSES] = {
        {"P1", 24, 0, 0, 0},
        {"P2", 3, 0, 0, 0},
        {"P3", 3, 0, 0, 0}
    };
    int time = 0;
    int i, j, finished = 0;
    while (finished < n) {
        for (i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time <= quantum) {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    finished++;
                    processes[i].turnaround_time = time - processes[i].burst_time;
                } else {
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                }
                for (j = 0; j < n; j++) {
                    if (j != i && processes[j].remaining_time > 0) {
                        processes[j].waiting_time += quantum;
                    }
                }
            }
        }
    }
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}

