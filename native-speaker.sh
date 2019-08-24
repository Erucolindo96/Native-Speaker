#!/bin/sh
appname=`basename $0 | sed s,\.sh$,,`

dirname=`dirname $0`
tmp="${dirname#?}"

if [ "${dirname%$tmp}" != "/" ]; then
	dirname=$PWD/$dirname
fi
LD_LIBRARY_PATH=$dirname/resources/lib
export LD_LIBRARY_PATH
$dirname/$appname "$@"


####napisac skrypt uruchamiajacy program z odpowiednimi ściezkami


