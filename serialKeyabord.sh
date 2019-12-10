#!/bin/bash

CD=$(dirname $BASH_SOURCE)

s=/dev/ttyACM0
if [ "$1" != "" ] ; then
	s=$1
fi
$CD/bin/miniterm.py $s
