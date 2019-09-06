#!/usr/bin/env bash

function without_sudo()
{
  echo "Script runned withoud sudo!" 
  exit 
}


#instalacja zależnych paczek
sudo apt update || without_sudo
sudo apt install sox -y || without_sudo
#jesli 64 bity - instalacja bibliotek 
ARCH=`uname -m`
echo "arch: "$ARCH
if [ "$ARCH" = "x64_86" ]; then
	sudo dpkg --add-architecture i386
	sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386
fi

appname=`basename $0 | sed s,\.sh$,,`

dirname=`dirname $0`
tmp="${dirname#?}"

if [ "${dirname%$tmp}" != "/" ]; then
		dirname=$PWD/$dirname
fi


#create qt.conf file
echo "[Paths]" >> qt.conf
echo "Prefix = $dirname/resources" >> qt.conf
echo "Lib = lib" >> qt.conf
echo "Plugins = plugins" >> qt.conf


