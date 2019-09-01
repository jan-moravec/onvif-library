#!/bin/sh
#
# Script will download and build gsoap
#
# Following libraries may be needed:
# sudo apt install build-essential cmake libssl-dev zlib1g-dev

GSOAP_DIR=./gsoap-2.8/gsoap
SOAPCPP2=$GSOAP_DIR/src/soapcpp2
WSDL2H=$GSOAP_DIR/wsdl/wsdl2h

# get archive
if [ ! -f download/gsoap.zip ]; then
    mkdir -p download
    wget -O ./download/gsoap.zip.tmp "https://sourceforge.net/projects/gsoap2/files/gsoap-2.8/gsoap_2.8.91.zip/download"
    mv ./download/gsoap.zip.tmp ./download/gsoap.zip
fi

# unzip
if [ ! -f gsoap-2.8/README.txt ]; then
     unzip ./download/gsoap.zip
fi

# build
if [ ! -f $SOAPCPP2 ] || [ ! -f $WSDL2H ]; then
     cd gsoap-2.8
     ./configure --enable-samples --enable-ipv6
     make -j1
     cd ..
fi