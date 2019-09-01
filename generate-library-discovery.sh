#!/bin/sh

GSOAP_DIR=gsoap-2.8/gsoap
SOAPCPP2=$GSOAP_DIR/src/soapcpp2
WSDL2H=$GSOAP_DIR/wsdl/wsdl2h

LIBRARY_DIR=onvif-library-discovery
OUTPUT_DIR=$LIBRARY_DIR/generated

WSDL_URLS="https://www.onvif.org/ver10/network/wsdl/remotediscovery.wsdl"

# generate onvif.h
rm -rf $OUTPUT_DIR
mkdir -p $OUTPUT_DIR
cp $GSOAP_DIR/typemap.dat $OUTPUT_DIR
$WSDL2H -O4 -g -t $OUTPUT_DIR/typemap.dat -o $OUTPUT_DIR/onvif.h $WSDL_URLS

# patch onvif.h
LINE_NUM="$(grep -n "wsdd10.h" $OUTPUT_DIR/onvif.h | head -n 1 | cut -d: -f1)"
sed -i $LINE_NUM'i#import "wsse.h"' $OUTPUT_DIR/onvif.h

# generate bindings
$SOAPCPP2 -I $GSOAP_DIR/import -d $OUTPUT_DIR -L -x $OUTPUT_DIR/onvif.h

# copy external files, rename to cpp
cp $GSOAP_DIR/stdsoap2.cpp $GSOAP_DIR/stdsoap2.h $OUTPUT_DIR
cp $GSOAP_DIR/plugin/wsddapi.c $GSOAP_DIR/plugin/wsddapi.h $OUTPUT_DIR
mv $OUTPUT_DIR/wsddapi.c $OUTPUT_DIR/wsddapi.cpp
cp $GSOAP_DIR/plugin/wsaapi.c $GSOAP_DIR/plugin/wsaapi.h $OUTPUT_DIR
mv $OUTPUT_DIR/wsaapi.c $OUTPUT_DIR/wsaapi.cpp
cp $GSOAP_DIR/plugin/threads.c $GSOAP_DIR/plugin/threads.h $OUTPUT_DIR
mv $OUTPUT_DIR/threads.c $OUTPUT_DIR/threads.cpp
