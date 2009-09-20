#!/bin/sh
debugdir="${TARGET_BUILD_DIR}"
rootdir="${TARGET_BUILD_DIR}/${TARGET_NAME}.app"
rsc="$rootdir/Contents/Resources"
#rsync -avzu --delete ./Levels $rsc/
#rsync -avzu $rsc/Levels/ ./Levels
#rsync -avzu --delete ./Images $rsc/
cp ReadMe.txt $debugdir
cd $debugdir
zip Gravity.zip -r Gravity.app ReadMe.txt
cp Gravity.zip /Library/WebServer/Documents/Dreamhost/Site/Gravity/
cp ReadMe.txt /Library/WebServer/Documents/Dreamhost/Site/Gravity/
