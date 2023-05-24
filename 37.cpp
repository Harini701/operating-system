#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10

int optimal_page_replacement(int pages[], int num_pages, int num_frames) {
    int page_faults = 0;
    int frames[MAX_FRAMES];
    bool is_frame_full[MAX_FRAMES] = { false };

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        bool page_found = false;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                page_found = true;
                break;
            }
        }

        if (!page_found) {
            if (is_frame_full[num_frames - 1]) {
                int index_to_replace = -1;
                int furthest_page_index = 0;

                for (int j = 0; j < num_frames; j++) {
                    int k;
                    for (k = i + 1; k < num_pages; k++) {
                        if (pages[k] == frames[j]) {
                            if (k > furthest_page_index) {
                                furthest_page_index = k;
                                index_to_replace = j;
                            }
                            break;
                        }
                    }

                    if (k == num_pages) {
                        index_to_replace = j;
                        break;
                    }
                }

                frames[index_to_replace] = page;
                page_faults++;
            } else {
                for (int j = 0; j < num_frames; j++) {
                    if (frames[j] == -1) {
                        frames[j] = page;
                        if (j == num_frames - 1) {
                            is_frame_full[j] = true;
                        }
                        break;
                    }
                }
                page_faults++;
            }
        }
    }

    return page_faults;
}

int main() {
    int pages[] = {4, 1, 2, 4, 3, 2, 1, 5};
    int num_pages = sizeof(pages) / sizeof(pages[0]);
    int num_frames = 3;

    int page_faults = optimal_page_replacement(pages, num_pages, num_frames);

    printf("Number of Page Faults: %d\n", page_faults);

    return 0;
}

