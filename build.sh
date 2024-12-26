#!/bin/bash
# file: build.sh
echo -e "\e[93mKeyCapture - Coded By v3l0r3k\e[0m"
echo
read -p "[+] Install LibDev libraries? (sudo required) [Y/N]: " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
 sudo apt-get install libevdev-dev
fi
echo
echo [+] Attempting to build...
gcc keyc.c -o keyc -levdev
echo gcc keyc.c -o keyc -levdev
echo -e "Run as \e[93m./keyc\e[0m" 
echo Enjoy it!

