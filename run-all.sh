#!/bin/sh
#

echo "============================================="
echo "= BUILDING GSOAP"
echo "============================================="
./build-gsoap.sh

echo "============================================="
echo "= GENERATING DISCOVERY LIBRARY SOURCE CODE"
echo "============================================="
./generate-library-discovery.sh

echo "============================================="
echo "= BUILDING DISCOVERY LIBRARY"
echo "============================================="
./build-library-discovery.sh

echo "============================================="
echo "= TESTING ONVIF LIBRARY"
echo "============================================="
./build-library-test.sh