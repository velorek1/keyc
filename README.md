# [keyc] : KeyCapture

A simple keylogger for Linux using evdev. This program captures keyboard input and requires root privileges to run.
This program defaults keyboard device file to be event0. If different, check cat /proc/bus/input/devices and run with paramater specifying device file number (X) as ./keyc X 

## Compilation
Compile the program with GCC:

- gcc keyc.c -o keyc 

## Example usage. Requires ROOT (Keys are stored in .capt.dat ; a hidden file found in the same folder)
sudo ./keyc& 
OR sudo ./keyc X

