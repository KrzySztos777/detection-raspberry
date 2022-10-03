#!/bin/bash

#EXAMPLE USAGE: ./main.sh 640 480
WIDTH=$1 #Width of image in pixels
HEIGHT=$2 #Height of image in pixels
FPS=40
NOW=`date +'D%Y-%m-%dT%H-%M-%S'`

cd /home/pi/projektpythongui

raspivid -n -hf -rot 90 -awb horizon -fps $FPS -w $WIDTH -h $HEIGHT -t 0 --raw - -rf rgb -o /dev/null  | 
	#./raspitune.o $WIDTH $HEIGHT |
	./lastframe.o $WIDTH $HEIGHT 3 |
	./detection.elf 2> err|
	python3 ./app.py $WIDTH $HEIGHT |
	ffmpeg  -r $FPS -s ${WIDTH}x${HEIGHT} -f ppm_pipe -i - video${NOW}.avi

