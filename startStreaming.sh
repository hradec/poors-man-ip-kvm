#!/bin/bash

CD=$(dirname $(readlink -f $BASH_SOURCE))

cd $CD/ffserver/
./start.py $@
