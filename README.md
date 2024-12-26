# [keyc] : KeyCapture

An example proof-of-concept keylogger for Linux using `libevdev`. This program captures keyboard input and requires root privileges to run.
Include files obtained from the repository:
libevdev GitLab Repository(https://gitlab.freedesktop.org/libevdev/libevdev.git)

## Requirements (**libevdev**: Install it on Debian-based systems with:)
- sudo apt-get install libevdev-dev


## Compilation
Compile the program with GCC:

- gcc keyc.c -o keyc -levdev

## Example usage. Requires ROOT (Keys are stored in .capt.dat ; a hidden file found in the same folder)
sudo ./keyc&
