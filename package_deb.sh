#!/bin/sh
if [ "$MY_SYN_BUILD_DIR" = "" ]
then
	MY_SYN_BUILD_DIR="build"
fi
cd $MY_SYN_BUILD_DIR
cp bin/* deb/synergy/usr/local/bin/
dpkg-deb --build deb/synergy

if [ "$TRAVIS_BRANCH" != "" ]
then
	mv "deb/synergy.deb" "deb/synergy_${TRAVIS_BRANCH}.deb"
fi

ls -la deb/
