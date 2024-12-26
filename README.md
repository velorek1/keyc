# keyc
Proof-of-concept keylogger for Linux using libevdev
# [keyc] : KeyCapture

An example proof-of-concept keylogger for Linux using `libevdev`. This program captures keyboard input and requires root privileges to run.
Include files obtained from the repository:
libevdev GitLab Repository(https://gitlab.freedesktop.org/libevdev/libevdev.git)

## Requirements

- **libevdev**: Install it on Debian-based systems with:
- sudo apt-get install libevdev-dev


## Compilation
Compile the program with GCC:

- gcc keyc.c -o keybc -levdev

## Example usage. Keys are store in .capt.dat hidden file in the same folder
sudo ./keyc&
