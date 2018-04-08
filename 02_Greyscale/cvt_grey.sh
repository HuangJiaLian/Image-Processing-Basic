#!/bin/bash

# Tip:
# Install imagemagick by using "sudo  apt-get install imagemagick" 
# before using "convert" command

if [[ $# -ne 1 ]];then
	echo "usage: $0 image_name"
	exit
fi
prefix="gray_"
out_name="$prefix$1"
convert $1 -colorspace Gray $out_name 

echo "Completed. $out_name is saved."