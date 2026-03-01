cmake_minimum_required(VERSION 3.21...4.1)
project(xptools)

if (APPLE)
	include(cmake/mac.cmake)
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(expat CONFIG REQUIRED)
find_package(PROJ CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(TIFF REQUIRED)
find_package(GeoTIFF CONFIG REQUIRED)
find_package(JPEG REQUIRED)
find_package(unofficial-libsquish CONFIG REQUIRED)
find_package(shapelib CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

if (APPLE)
	find_library(CARBON_FRAMEWORK Carbon REQUIRED)
	find_library(APPKIT_FRAMEWORK AppKit REQUIRED)
endif()

if(WIN32)
    set(BASIC_PLATFORM_DEFINES
        LIN=0
        IBM=1
        APL=0
    )
elseif(APPLE)
    set(BASIC_PLATFORM_DEFINES
        LIN=0
        IBM=0
        APL=1
        _LIBCPP_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION=1
    )
elseif(UNIX)
    set(BASIC_PLATFORM_DEFINES
        LIN=1
        IBM=0
        APL=0
        _LIBCPP_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION=1
    )
endif()

# Build-type specific definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(BASIC_PLATFORM_DEFINES "${BASIC_PLATFORM_DEFINES};DEV=1;BIG=0;LIL=1")
else()
	set(BASIC_PLATFORM_DEFINES "${BASIC_PLATFORM_DEFINES};DEV=0;BIG=0;LIL=1")
endif()

include(cmake/DDSTool.cmake)
include(cmake/DSFTool.cmake)
include(cmake/ObjView.cmake)
include(cmake/WED.cmake)
include(cmake/XGrinder.cmake)
include(cmake/OneOffs.cmake)
