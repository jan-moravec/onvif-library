#!/bin/sh

APPLICATION_DIR=onvif-library-test

LIBRARY_DISCOVERY_DIR=onvif-library-discovery

mkdir -p $APPLICATION_DIR/lib

cp -r $LIBRARY_DISCOVERY_DIR/include $APPLICATION_DIR
cp -r $LIBRARY_DISCOVERY_DIR/build/libonvif-discovery.a $APPLICATION_DIR/lib

rm -rf $APPLICATION_DIR/build
mkdir -p $APPLICATION_DIR/build

cd $APPLICATION_DIR/build
cmake ..
make -j8
cd ../..
