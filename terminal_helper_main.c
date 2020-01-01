/*
 * Separate utility for controlling console state
 * for fixing console when pseudovi crashes during tests
 */

#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    for (int i=1;i<argc;i++) {
        if (strcmp(argv[i], "mouse-enable") == 0) {
            printf("Enabling mouse mode in terminal...");
            printf("\033[?1003h\n");
        }
        else if (strcmp(argv[i], "mouse-disable") == 0) {
            printf("Disabling mode in terminal...");
            printf("\033[?1003l\n");
        }
        else {
            printf("No valid options detected.");
            printf("Valid options are 'mouse-enable' and 'mouse-disable' (without quotes)");
        }
    }
}

