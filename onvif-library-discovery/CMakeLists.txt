cmake_minimum_required(VERSION 3.0)
project(libonvif-discovery)

add_library(onvif-discovery STATIC
	include/libonvif/onvifdiscovery.h
	src/onvifdiscovery.cpp
	src/discovery.h
	src/discovery.cpp
	src/data.h
	src/data.cpp
	generated/onvif.h
	generated/soapH.h
	generated/soapC.cpp
	generated/soapClient.cpp
	generated/soapServer.cpp
	generated/soapStub.h
	generated/stdsoap2.h
	generated/stdsoap2.cpp
	generated/threads.h
	generated/threads.cpp
	generated/wsaapi.h
	generated/wsaapi.cpp
	generated/wsddapi.h
	generated/wsddapi.cpp
	generated/wsdd.nsmap
)

target_include_directories(onvif-discovery
	PUBLIC include
	PRIVATE src
	PRIVATE generated
)