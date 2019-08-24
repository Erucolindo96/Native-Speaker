#!/usr/bin/env bash

function without_sudo()
{
  echo "Script runned withoud sudo!" 
  exit 
}


#instalacja zależnych paczek
sudo apt install sox -y || without_sudo

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


