#include <stdio.h>

#define MAX_PARTITIONS 5
#define MAX_PROCESSES 5

struct Partition {
    int size;
    int allocated;
};

struct Process {
    int size;
    int allocated_partition;
};

void worstFit(struct Partition partitions[], int num_partitions, struct Process processes[], int num_processes) {
    int i, j;

    for (i = 0; i < num_processes; i++) {
        int worst_index = -1;
        for (j = 0; j < num_partitions; j++) {
            if (!partitions[j].allocated && partitions[j].size >= processes[i].size) {
                if (worst_index == -1 || partitions[j].size > partitions[worst_index].size) {
                    worst_index = j;
                }
            }
        }

        if (worst_index != -1) {
            partitions[worst_index].allocated = 1;
            partitions[worst_index].size -= processes[i].size;
            processes[i].allocated_partition = worst_index;
        } else {
            processes[i].allocated_partition = -1;
        }
    }
}

int main() {
    struct Partition partitions[MAX_PARTITIONS] = {
        {40, 0},
        {10, 0},
        {30, 0},
        {60, 0}
    };

    struct Process processes[MAX_PROCESSES] = {
        {100, -1},
        {50, -1},
        {30, -1},
        {120, -1},
        {35, -1}
    };

    int num_partitions = 4;
    int num_processes = 5;
    int i;

    worstFit(partitions, num_partitions, processes, num_processes);

    printf("Process\tAllocated Partition\n");
    for (i = 0; i < num_processes; i++) {
        printf("%d\t", i + 1);
        if (processes[i].allocated_partition != -1) {
            printf("%d\n", processes[i].allocated_partition + 1);
        } else {
            printf("Not Allocated\n");
        }
    }

    return 0;
}

