#include <stdio.h>
#include <stdlib.h>

int abs_diff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

void clook_disk_scheduling(int tracks[], int n, int head_position, int *total_head_movement) {
    int i, j;
    int current_track, previous_track;

    *total_head_movement = 0;

    for (i = 0; i < n; i++) {
        if (tracks[i] == head_position)
            break;
    }
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (tracks[i] > tracks[j]) {
                int temp = tracks[i];
                tracks[i] = tracks[j];
                tracks[j] = temp;
            }
        }
    }

    previous_track = head_position;

    // Calculate head movement
    for (j = i; j < n; j++) {
        current_track = tracks[j];
        *total_head_movement += abs_diff(previous_track, current_track);
        previous_track = current_track;
    }

    *total_head_movement += abs_diff(previous_track, tracks[0]);
    previous_track = tracks[0];

    for (j = 1; j < i; j++) {
        current_track = tracks[j];
        *total_head_movement += abs_diff(previous_track, current_track);
        previous_track = current_track;
    }
}

int main() {
    int tracks[] = {55, 58, 60, 70, 18};
    int n = sizeof(tracks) / sizeof(tracks[0]);
    int head_position = 50;
    int total_head_movement;

    clook_disk_scheduling(tracks, n, head_position, &total_head_movement);

    printf("Total Head Movement: %d\n", total_head_movement);

    return 0;
}

