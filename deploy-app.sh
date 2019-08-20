#!/usr/bin/env bash


#
# Usage
# ./deploy-app.sh path_to_build_directory path_to_qt_installation
# 
# This script create tar.gz archieve, which contain all application data.
# You can unpack native-speaker.tar.gz and install app on your machine
#
#


PATH_TO_BUILD=$1
PATH_TO_QT=$2
D_DIR="deploy"
N_SPEAKER_DIR="."

QT_LIBS=('libQt5Multimedia.so.5' 'libQt5Widgets.so.5' 'libQt5Gui.so.5' 'libQt5Core.so.5' 'libQt5Network.so.5' 'libicui18n.so.54' 'libicuuc.so.54' 'libicudata.so.54'  )

if [ -d $PATH_TO_BUILD ]
then
	mkdir $D_DIR || exit
	mkdir $D_DIR/libs || exit
	cp $PATH_TO_BUILD/main/main $D_DIR/native-speaker || exit
	cp $N_SPEAKER_DIR/resources $D_DIR/. -d -r || exit
	cp $N_SPEAKER_DIR/install.sh $D_DIR/. || exit
	echo $PATH_TO_QT > $D_DIR/qt-path || exit
	for lib in "${QT_LIBS[@]}"
	do
		install -m 755 $PATH_TO_QT/$lib -t $D_DIR/libs || exit
	done
	tar -caf native-speaker.tar.gz $D_DIR || exit
	rm -d -r $D_DIR 
fi





