#!/bin/bash -l

ffmpg="/home/rhradec/VLC-2.2.8.glibc2.16-x86_64.AppImage"

vlc() {
    pkill -fc -9 vlc
    $ffmpg \
    v4l2:///dev/video0 \
    :v4l2-width=1024 \
    :v4l2-height=768  \
    --noaudio \
    --no-sout-audio \
    --sout \
    '#transcode{vcodec=mjpg}:std{access=http{mime=multipartx-mixed-replace\;boundary=-7b3cc56e5f51db803f790dad720ed50a},mux=mpjpeg,dst=192.168.0.12:9001}' \
    --daemon --syslog -I http --http-port 8090 --http-password t
}

%vlc  > /tmp/vlc.log 2>&1 &
nc "${IP:-192.168.0.12}" "${PORT:-9001}"
