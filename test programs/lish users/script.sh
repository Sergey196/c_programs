#!/bin/bash
cat /etc/passwd | grep "bash"| awk -F: '{print $1}'  
