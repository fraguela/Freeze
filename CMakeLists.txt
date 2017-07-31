
#freeze: A library to capture runtime values in constants
#Copyright (C) 2017 Basilio B. Fraguela. Universidade da Coruna

# \file     CMakeLists.txt
# \brief    Main CMakeLists.txt of the project
# \author   Basilio B. Fraguela <basilio.fraguela@udc.es>

cmake_minimum_required( VERSION 2.8.7 )

project( freeze )

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set( CMAKE_CXX_STANDARD 11 )

include_directories( include )

add_subdirectory( src )
add_subdirectory( tests )
add_subdirectory( manual_tests )

