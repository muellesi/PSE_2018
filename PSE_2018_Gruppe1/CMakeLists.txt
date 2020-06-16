CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT (pse_2018_gruppe1)


INCLUDE(DownloadProject.cmake)

# Set to RelWithDebInfo to get optimized code with debug symbols
#set( CMAKE_BUILD_TYPE "RelWithDebInfo")
SET( CMAKE_BUILD_TYPE "Debug")

# Enable C++ 11 features
SET (CMAKE_CXX_STANDARD 11)

# Switch for test mode

SET (PSE_TEST_MODE false CACHE BOOL "Set this to true when testing the vehicle in jacked up mode")

IF(PSE_TEST_MODE)
    MESSAGE("TEST MODE ENABLED. MOTOR CONTROLLERS WILL BE DISABLED!")
    add_definitions(-DTEST_MODE)
ENDIF()

# Output paths
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
SET(DOC_OUTPUT_PATH ${CMAKE_BINARY_DIR}/doc)

IF(WIN32)


#----------------------------Google Test Setup---------------------------
# Add gtest
download_project(PROJ googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
        UPDATE_DISCONNECTED 1
        QUIET
        )


add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
include_directories(${googletest_SOURCE_DIR}/include ${googletest_SOURCE_DIR})

# Specify include dir
set(GTEST_INCLUDE_DIR ${googletest_SOURCE_DIR}/include)

# Library
set(GTEST_LIBRARY_PATH ${googletest_BINARY_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a)
set(GTEST_LIBRARY gtest)
set(GTEST_MAIN_LIBRARY gtest_main)

ENDIF(WIN32)

# Enable warnings
add_definitions(-Wextra)

##############################################################################
# The program
##############################################################################
add_subdirectory(src)