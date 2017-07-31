
#freeze: A library to capture runtime values in constants
#Copyright (C) 2017 Basilio B. Fraguela. Universidade da Coruna

# \file     CMakeLists.txt
# \brief    CMakeLists.txt for building the static library libfreeze.a
# \author   Basilio B. Fraguela <basilio.fraguela@udc.es>

cmake_minimum_required( VERSION 2.8.7 )

add_library( freeze STATIC freeze.cpp )

#install

install( TARGETS freeze
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib )

install( DIRECTORY ../include/freeze
         DESTINATION include
         FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" )
