#!/usr/bin/env python2

# ffmpeg can be download statically built from this address (nov/2019)
# https://johnvansickle.com/ffmpeg/releases/ffmpeg-release-amd64-static.tar.xz
# or this: https://ffbinaries.com/downloads

# ffserver can be download statically built from this addess (nov/2019
# https://github.com/vot/ffbinaries-prebuilt/releases/download/v3.4/ffserver-3.4-linux-64.zip

import os
import shlex, subprocess

PORT=8090

CD = os.path.dirname( os.path.abspath( __file__ ) )

ffserver_cmd = '%s/ffserver -f %s/ffserver.conf  > /tmp/ffserver.log 2>&1' % (CD, CD)
ff_cmd = '%s/ffmpeg-bin/ffmpeg -f video4linux2  -standard PAL  -s 720x560 -r 30 -i /dev/video0 http://localhost:%s/camera.ffm  > /tmp/ffserver.log 2>&1' % (CD, PORT)

ffserver = subprocess.Popen( ffserver_cmd.split(' '), bufsize=4096 ) #, shell=True )
ffmpeg = subprocess.Popen( ff_cmd.split(' '), bufsize=4096 ) #, shell=True )

ffmpeg.wait()

while True:
	ffserver.poll()
	ffmpeg.poll()
	print ffserver.returncode, ffmpeg.returncode

	if ffserver.returncode < 0:
		break

	if ffmpeg.returncode < 0:
		break


ffserver.kill()
ffmpeg.kill()
