#!/usr/bin/env python2

# to play, run: ffplay http://<ip address of the machine running this script>:8089/camera.mjpeg
# ex: ffplay http://192.168.0.10:8089/camera.mjpeg

# ffmpeg can be download statically built from this address (nov/2019)
# https://johnvansickle.com/ffmpeg/releases/ffmpeg-release-amd64-static.tar.xz
# or this: https://ffbinaries.com/downloads

# ffserver can be download statically built from this addess (nov/2019
# https://github.com/vot/ffbinaries-prebuilt/releases/download/v3.4/ffserver-3.4-linux-64.zip

import os, sys
import shlex, subprocess
import signal
import sys

PORT=8089

CD = os.path.dirname( os.path.abspath( __file__ ) )

v='/dev/video0'
if len(sys.argv)>1:
	v = sys.argv[1]

ffserver_cmd = '%s/ffserver -f %s/ffserver.conf ' % (CD, CD)
#ff_cmd = '%s/ffmpeg-bin/ffmpeg -f video4linux2  -standard PAL  -s 720x560 -r 30 -i %s http://localhost:%s/camera.ffm' % (CD, v, PORT)
ff_cmd = "LD_PRELOAD=$(ldconfig -p | grep libc.so.6 | awk '{print $NF}' | grep -v 32):$(ldconfig -p | grep libpthread.so.0 | awk '{print $NF}' | grep -v 32) "+\
	 '%s/debian/ffmpeg -f video4linux2  -standard PAL  -s 720x560 -r 30 -i %s http://localhost:%s/camera.ffm' % (CD,v, PORT)

print ffserver_cmd
print ff_cmd

## start ffserver
ffserver = subprocess.Popen( ffserver_cmd, shell=True )

## start ffmpeg
os.environ['LD_LIBRARY_PATH'] = "%s/debian" % CD
ffmpeg = subprocess.Popen( ff_cmd, shell=True )

## start nc to pipe ffserver to the xinetd port
nc=subprocess.Popen( "nc 127.0.0.1 %s" % str(PORT), shell=True )

def signal_handler(signal, frame):
  ffserver.kill()
  ffmpeg.kill()
  nc.kill()
  sys.exit(-1)

signal.signal(signal.SIGINT, signal_handler)
ffmpeg.wait()

while True:
	ffserver.poll()
	ffmpeg.poll()
        nc.poll()
#	print ffserver.returncode, ffmpeg.returncode

	if ffserver.returncode < 0:
		break

	if ffmpeg.returncode < 0:
		break


ffserver.kill()
ffmpeg.kill()
nc.kill()
