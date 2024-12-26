# keyc
Proof-of-concept keylogger for Linux using libevdev
# [keyc] : KeyCapture

An example proof-of-concept keylogger for Linux using `libevdev`. This program captures keyboard input and requires root privileges to run.

## Requirements

- **libevdev**: Install it on Debian-based systems with:
```bash
sudo apt-get install libevdev-dev

Include files obtained from the repository:
libevdev GitLab Repository(https://gitlab.freedesktop.org/libevdev/libevdev.git)

## Compilation
Compile the program with GCC:

```bash
 gcc keyc.c -o keybc -levdev

## Example usage. Keys are store in .capt.dat hidden file in the same folder
sudo ./keyc&
