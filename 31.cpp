#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int numTracks = 5;
    int trackPositions[] = {55, 58, 60, 70, 18};
    int initialPosition = 50;
    int totalHeadMovement = 0;

    for (int i = 0; i < numTracks - 1; i++) {
        for (int j = 0; j < numTracks - i - 1; j++) {
            if (trackPositions[j] > trackPositions[j + 1]) {
                int temp = trackPositions[j];
                trackPositions[j] = trackPositions[j + 1];
                trackPositions[j + 1] = temp;
            }
        }
    }

    int insertIndex = 0;
    while (insertIndex < numTracks && trackPositions[insertIndex] < initialPosition) {
        insertIndex++;
    }

    int currentTrack = initialPosition;
    printf("Head Movement: %d", currentTrack);
    totalHeadMovement += abs(currentTrack - trackPositions[insertIndex - 1]);

    for (int i = insertIndex - 1; i >= 0; i--) {
        printf(" -> %d", trackPositions[i]);
        totalHeadMovement += abs(trackPositions[i] - currentTrack);
        currentTrack = trackPositions[i];
    }

    printf(" -> 0");
    totalHeadMovement += currentTrack;

    for (int i = numTracks - 1; i >= insertIndex; i--) {
        printf(" -> %d", trackPositions[i]);
        totalHeadMovement += abs(trackPositions[i] - currentTrack);
        currentTrack = trackPositions[i];
    }

    printf("\n");

    double averageHeadMovement = (double)totalHeadMovement / numTracks;
    printf("Average Head Movement: %.2lf\n", averageHeadMovement);

    return 0;
}

