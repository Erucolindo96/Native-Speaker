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
if [ "$ARCH" = "x86_64" ]; then
	sudo dpkg --add-architecture i386
	sudo apt install libc6:i386 libncurses5:i386 libstdc++6:i386
fi

appname=`basename $0 | sed s,\.sh$,,`

dirname=`dirname $0`
tmp="${dirname#?}"

if [ "${dirname%$tmp}" != "/" ]; then
		dirname=$PWD/$dirname
fi


#create qt.conf file

if [ -f "qt.conf" ]
then
	rm qt.conf
fi

echo "[Paths]" >> qt.conf
echo "Prefix = $dirname/resources" >> qt.conf
echo "Lib = lib" >> qt.conf
echo "Plugins = plugins" >> qt.conf


