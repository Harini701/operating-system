#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define MAX_TRACKS 100

int abs_diff(int a, int b) {
    return abs(a - b);
}

int sstf_disk_scheduling(int tracks[], int num_tracks, int start_track) {
    int total_head_movement = 0;
    bool visited[MAX_TRACKS] = { false };

    int current_track = start_track;

    for (int i = 0; i < num_tracks; i++) {
        int shortest_seek = INT_MAX;
        int shortest_seek_index = -1;

        for (int j = 0; j < num_tracks; j++) {
            if (!visited[j]) {
                int seek = abs_diff(tracks[j], current_track);
                if (seek < shortest_seek) {
                    shortest_seek = seek;
                    shortest_seek_index = j;
                }
            }
        }

        visited[shortest_seek_index] = true;
        total_head_movement += shortest_seek;
        current_track = tracks[shortest_seek_index];
    }

    return total_head_movement;
}

int main() {
    int tracks[] = {55, 58, 60, 70, 18};
    int num_tracks = sizeof(tracks) / sizeof(tracks[0]);
    int start_track = 50;  

    int average_head_movement = sstf_disk_scheduling(tracks, num_tracks, start_track) / num_tracks;

    printf("Average Head Movement: %d\n", average_head_movement);

    return 0;
}

