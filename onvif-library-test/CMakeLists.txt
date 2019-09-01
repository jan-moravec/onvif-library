cmake_minimum_required(VERSION 3.0)
project(libonvif-test)

add_executable(onvif-test 
	main.cpp
	include/libonvif/onvifdiscovery.h
)

target_include_directories(onvif-test
	PRIVATE include
)

target_link_libraries(onvif-test 
	PRIVATE ${PROJECT_SOURCE_DIR}/lib/libonvif-discovery.a
	PRIVATE pthread
)