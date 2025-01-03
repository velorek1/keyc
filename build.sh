#!/bin/bash
# file: build.sh
echo -e "\e[93mKeyCapture - Coded By v3l0r3k\e[0m"
echo
echo [+] Attempting to build...
gcc keyc.c -o keyc 
echo gcc keyc.c -o keyc
echo -e "Run as \e[93m./keyc X\e[0m" 
echo -e "Check /proc/bus/input/devices to locate event file keyboard number : X\e[0m" 
echo Enjoy it!

