#!/bin/bash
# file: build.sh
echo -e "\e[93mKeyCapture - Coded By v3l0r3k\e[0m"
echo
echo [+] Attempting to build...
echo Check cat /proc/bus/input/devices to determine keyboard event file name
gcc keyc.c -o keyc 
echo gcc keyc.c -o keyc
echo -e "Run as \e[93m./keyc\e[0m" 
echo Enjoy it!

