#/usr/bin/env bash
dir=$1

for file in $dir/*
do
  file=${file%".mp3"}
  echo $file
  madplay --left --output=raw:- $file.mp3 | sfbcep -f 11025 - $file.mfcc
	
done

