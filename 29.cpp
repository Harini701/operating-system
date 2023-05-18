#include <stdio.h>
#include <stdbool.h>

#define NUM_PARTITIONS 4

typedef struct {
    int size;
    bool allocated;
} Partition;

void firstFit(Partition partitions[], int numPartitions, int processSize) {
    for (int i = 0; i < numPartitions; i++) {
        if (!partitions[i].allocated && partitions[i].size >= processSize) {
            partitions[i].allocated = true;
            printf("Process of size %d KB allocated to Partition %d\n", processSize, i+1);
            return;
        }
    }
    printf("No suitable partition found for Process of size %d KB\n", processSize);
}

void displayMemoryStatus(Partition partitions[], int numPartitions) {
    printf("Memory Status:\n");
    for (int i = 0; i < numPartitions; i++) {
        printf("Partition %d: %d KB ", i+1, partitions[i].size);
        if (partitions[i].allocated) {
            printf("(Allocated)\n");
        } else {
            printf("(Free)\n");
        }
    }
    printf("\n");
}

int main() {
    Partition partitions[NUM_PARTITIONS] = {
        {40, false},
        {10, false},
        {30, false},
        {60, false}
    };

    int processSizes[] = {100, 50, 30, 120, 35};
    int numProcesses = sizeof(processSizes) / sizeof(processSizes[0]);

    for (int i = 0; i < numProcesses; i++) {
        printf("Trying to allocate Process of size %d KB...\n", processSizes[i]);
        firstFit(partitions, NUM_PARTITIONS, processSizes[i]);
        displayMemoryStatus(partitions, NUM_PARTITIONS);
    }

    return 0;
}

