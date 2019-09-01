#!/bin/sh
#

OUTPUT_DIR=generated
LIBRARY_DISCOVERY_DIR=onvif-library-discovery
LIBRARY_DEVICE_DIR=onvif-library-device

APPLICATION_DIR=onvif-library-test

rm -rf $LIBRARY_DISCOVERY_DIR/build
rm -rf $LIBRARY_DISCOVERY_DIR/$OUTPUT_DIR

rm -rf $LIBRARY_DEVICE_DIR/build
rm -rf $LIBRARY_DEVICE_DIR/$OUTPUT_DIR

rm -rf $APPLICATION_DIR/build
rm -rf $APPLICATION_DIR/include
rm -rf $APPLICATION_DIR/lib