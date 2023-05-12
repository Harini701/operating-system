#include <stdio.h>

#define MAX_PARTITIONS 6
#define MAX_PROCESSES 5

int partitions[MAX_PARTITIONS] = {300, 600, 350, 200, 750, 125};
int processes[MAX_PROCESSES] = {115, 500, 358, 200, 375};

int main() {
    int i, j, max_index, allocated;
    int partitions_copy[MAX_PARTITIONS];
    for (i = 0; i < MAX_PARTITIONS; i++) {
        partitions_copy[i] = partitions[i];
    }
    for (i = 0; i < MAX_PROCESSES; i++) {
        max_index = -1;
        allocated = 0;
        for (j = 0; j < MAX_PARTITIONS; j++) {
            if (processes[i] <= partitions_copy[j]) {
                if (max_index == -1 || partitions_copy[j] > partitions_copy[max_index]) {
                    max_index = j;
                    allocated = 1;
                }
            }
        }
        if (allocated) {
            printf("Process %d with size %d KB is allocated to partition %d with size %d KB\n", i+1, processes[i], max_index+1, partitions[max_index]);
            partitions_copy[max_index] -= processes[i];
        } else {
            printf("Process %d with size %d KB cannot be allocated\n", i+1, processes[i]);
        }
    }

    return 0;
}

