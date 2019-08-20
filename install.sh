#!/usr/bin/env bash

function without_sudo()
{
  echo "Script runned withoud sudo!" 
  exit 
}


INSTALL_DIR="/opt/native-speaker"

QT_PATH=$(head -n 1 qt-path)

mkdir -p $INSTALL_DIR || without_sudo   
install -m 755 native-speaker -t $INSTALL_DIR || exit
cp -d -r resources $INSTALL_DIR/. || exit
install -m 755 resources/bin/sfbcep -t $INSTALL_DIR/resources/bin || exit

for lib in libs/*
do
	install -m 755 $lib -t $QT_PATH || exit
done



