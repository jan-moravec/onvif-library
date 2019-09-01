#!/bin/sh

LIBRARY_DIR=onvif-library-discovery

rm -rf $LIBRARY_DIR/build
mkdir -p $LIBRARY_DIR/build

cd $LIBRARY_DIR/build
cmake ..
make
cd ../..
