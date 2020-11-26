#!/bin/bash

#$1 - название директории
journal_size=$(du -cb /var/log/ktsku/$1/ | awk '{print $1}' | tail -n 1 )

echo ${journal_size}

exit 0


