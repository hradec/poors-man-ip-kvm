#!/bin/bash



CD=$(dirname $BASH_SOURCE)

cd $CD/src/MultiSerial/
make upload
