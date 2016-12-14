#!/bin/bash

if [ -f "$1" ];then
    sudo dd if=$1 of=/dev/sdc bs=512 seek=1 conv=sync
    echo "Successful!"
fi

sync
sync
sync

