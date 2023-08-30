#!/bin/bash

CD=$(dirname $(readlink -f $BASH_SOURCE))

cd $CD/ffserver/
#./start.py $@

pkill -fc -9 ffserver
$CD/ffserver/ffserver -f $CD/ffserver/ffserver.conf    &
LD_LIBRARY_PATH=$CD/ffserver/debian/ LD_PRELOAD=$(ldconfig -p | grep libc.so.6 | awk '{print $NF}' | grep -v 32):$(ldconfig -p | grep libpthread.so.0 | awk '{print $NF}' | grep -v 32) $CD/ffserver/debian/ffmpeg -f \
video4linux2  -standard PAL  -s 720x576 -i /dev/video0 -vcodec libx264 -preset medium -tune zerolatency -maxrate 2750k -bufsize 3000k -r 5.000  http://localhost:8089/camera.ffm
