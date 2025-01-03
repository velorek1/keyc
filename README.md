# [keyc] : KeyCapture

A simple keylogger for Linux using evdev. This program captures keyboard input and requires root privileges to run.
This program assumes keyboard device file is event0. If different, check cat /proc/bus/input/devices to change that inside the program.

## Compilation
Compile the program with GCC:

- gcc keyc.c -o keyc 

## Example usage. Requires ROOT (Keys are stored in .capt.dat ; a hidden file found in the same folder)
sudo ./keyc&
