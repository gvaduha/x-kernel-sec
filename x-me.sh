#!/bin/bash

make
insmod bug1

gcc payload.c -o payload

echo "======================================================="

strace ./payload

tail -n 40 /var/log/messages

