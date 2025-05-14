#include <stdio.h>
#include <limits.h>

// Function to display the current frame status
void displayFrames(int frames[], int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

// FIFO Page Replacement Algorithm
void fifo(int pages[], int n, int f) {
    printf("\n📌 FIFO Page Replacement:\n");
    int frames[f], front = 0, pageFaults = 0;

    for (int i = 0; i < f; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            frames[front] = pages[i];
            front = (front + 1) % f;
            pageFaults++;
        }

        printf("After inserting %d: ", pages[i]);
        displayFrames(frames, f);
    }

    printf("🔄 Total Page Faults (FIFO): %d\n", pageFaults);
}

// LRU Page Replacement Algorithm
void lru(int pages[], int n, int f) {
    printf("\n📌 LRU Page Replacement:\n");
    int frames[f], recent[f], time = 0, pageFaults = 0;

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        recent[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int hit = 0;

        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                recent[j] = ++time;
                break;
            }
        }

        if (!hit) {
            int lruIndex = 0, minTime = INT_MAX;
            for (int j = 0; j < f; j++) {
                if (recent[j] < minTime) {
                    minTime = recent[j];
                    lruIndex = j;
                }
            }

            frames[lruIndex] = pages[i];
            recent[lruIndex] = ++time;
            pageFaults++;
        }

        printf("After inserting %d: ", pages[i]);
        displayFrames(frames, f);
    }

    printf("🔄 Total Page Faults (LRU): %d\n", pageFaults);
}

// Optimal Page Replacement Algorithm
void optimal(int pages[], int n, int f) {
    printf("\n📌 Optimal Page Replacement:\n");
    int frames[f], pageFaults = 0;

    for (int i = 0; i < f; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int hit = 0;

        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            int replaceIndex = -1, farthest = i + 1;

            for (int j = 0; j < f; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) break;
                }

                if (k == n) {
                    replaceIndex = j;
                    break;
                } else if (k > farthest) {
                    farthest = k;
                    replaceIndex = j;
                } else if (replaceIndex == -1) {
                    replaceIndex = j;
                }
            }

            frames[replaceIndex] = pages[i];
            pageFaults++;
        }

        printf("After inserting %d: ", pages[i]);
        displayFrames(frames, f);
    }

    printf("🔄 Total Page Faults (Optimal): %d\n", pageFaults);
}

// Main Function
int main() {
    int n, f;

    printf("Enter total number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string (space separated):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    fifo(pages, n, f);
    lru(pages, n, f);
    optimal(pages, n, f);

    return 0;
}

// Enter total number of pages: 12
// Enter the page reference string (space separated):
// 1 3 0 3 5 6 3 0 1 2 4 3
// Enter number of frames: 3
