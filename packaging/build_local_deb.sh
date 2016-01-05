#!/bin/bash
set -e

cd src
version=`dpkg-parsechangelog --show-field Version`
baseversion=`echo ${version} | sed -n 's/-[0-9]*ppa[0-9]*~.*//p'`
cd ..
tar cjf dontpanic_${baseversion}.orig.tar.bz2 --exclude src/debian --exclude src/.kdev4 src
cd src
debuild
cd ..
