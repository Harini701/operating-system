#include <stdio.h>
int contiguousAllocation(int position) {
    if (position == 1) 
        return 0;
    else if (position <= 100 / 2)
        return position - 1; 
    else 
        return 0;
}
int linkedAllocation(int position) {
    if (position == 1)
        return 2;
    else if (position <= 100 / 2)
        return 3;
    else
        return 2; 
}
int indexedAllocation(int position) {
    if (position == 1) 
        return 2; 
    else if (position <= 100 / 2) 
        return position + 2; 
    else
        return 2;
}
int main() {
    int position;
    printf("Enter the position (1-100) where the block is added: ");
    scanf("%d", &position);
    if (position < 1 || position > 100) {
        printf("Invalid position. Please enter a value between 1 and 100.\n");
        return 1;
    }
    int contiguousIO = contiguousAllocation(position);
    int linkedIO = linkedAllocation(position);
    int indexedIO = indexedAllocation(position);
    printf("Disk I/O operations for contiguous allocation: %d\n", contiguousIO);
    printf("Disk I/O operations for linked allocation: %d\n", linkedIO);
    printf("Disk I/O operations for indexed allocation: %d\n", indexedIO);
    return 0;
}

