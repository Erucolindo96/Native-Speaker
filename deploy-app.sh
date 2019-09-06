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
D_DIR="native-speaker"
N_SPEAKER_DIR="."

QT_LIBS=('libQt5Multimedia.so.5' 'libQt5Widgets.so.5' 'libQt5Gui.so.5' 'libQt5Core.so.5' 'libQt5Network.so.5' 'libicui18n.so.54' 'libicuuc.so.54' 'libicudata.so.54' 'libQt5Core.so.5' 'libQt5DBus.so.5' 'libQt5XcbQpa.so.5')

PREFIX="."
LIB="lib"
PLUGINS="plugins"

if [ -d $PATH_TO_BUILD ]
then
	mkdir $D_DIR || exit
	cp $N_SPEAKER_DIR/resources $D_DIR/. -d -r || exit
	mkdir -p $D_DIR/resources/lib || exit
	
	cp $PATH_TO_BUILD/main/main $D_DIR/native-speaker || exit
	cp $N_SPEAKER_DIR/install.sh $D_DIR/. || exit
	cp $N_SPEAKER_DIR/native-speaker.sh $D_DIR/. || exit
	#for lib in "${QT_LIBS[@]}"
	#do
	#	install -m 755 $PATH_TO_QT/lib/$lib -t $D_DIR/resources/lib || exit
	#done
	cp -d -r $PATH_TO_QT/lib $D_DIR/resources
	cp -d -r $PATH_TO_QT/plugins $D_DIR/resources
	

	
	tar -caf native-speaker.tar.gz $D_DIR || exit
	rm -d -r $D_DIR 
fi





