#!/bin/bash

CD=$(dirname $(readlink -f $BASH_SOURCE))

cd $CD/ffserver/


echo " go to a browser and access http://$1:8090/camera.mjpeg to play without ffplay!! "

ffplay http://$1:8090/camera.mjpeg

