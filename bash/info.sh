#!/bin/bash
date >> date.txt
ip a >> ip.txt
uname -a >> uname.txt
free >> ram.txt
cat /etc/*release* >> cat.release.txt 
lsblk -d >> lsblkd.txt
lsblk >> lsblk.txt
lspci >> lspci.txt
whoami >> user.txt
lscpu >> lscpu.txt
