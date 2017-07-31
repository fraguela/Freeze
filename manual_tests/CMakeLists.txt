
#freeze: A library to capture runtime values in constants
#Copyright (C) 2017 Basilio B. Fraguela. Universidade da Coruna

# \file     CMakeLists.txt
# \brief    CMakeLists.txt for benchmarking the advantage of using compile-time constants
# \author   Basilio B. Fraguela <basilio.fraguela@udc.es>

cmake_minimum_required( VERSION 2.8.7 )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR})

add_executable( fib_single fib_single.cpp timer.cpp )
set_property(TARGET fib_single PROPERTY CXX_STANDARD 98)

add_executable( fib_single_cxx11 fib_single.cpp timer.cpp )

add_executable( fib_lib fib_main.cpp fib_lib.cpp timer.cpp )
set_property(TARGET fib_lib PROPERTY CXX_STANDARD 98)

add_executable( fib_lib_cxx11 fib_main.cpp fib_lib.cpp timer.cpp )


add_custom_target(run_manual_tests)
set(manual_tests_to_run fib_single fib_single_cxx11 fib_lib fib_lib_cxx11)
add_dependencies( run_manual_tests ${manual_tests_to_run} )

add_custom_command(TARGET run_manual_tests PRE_BUILD
		   COMMAND ${CMAKE_COMMAND} -E echo
                   COMMAND ${CMAKE_COMMAND} -E echo '***' BUILT WITH ${CMAKE_CXX_COMPILER} ${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS} '***'
		   COMMAND ${CMAKE_COMMAND} -E echo '    run cmake -DCMAKE_CXX_COMPILER=cxx to choose another compiler'
		   COMMAND ${CMAKE_COMMAND} -E echo)

foreach(test ${manual_tests_to_run})
  add_custom_command(TARGET run_manual_tests PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E echo manual test ${test} : -------------
                     COMMAND ${test} || exit 1
                     COMMAND ${CMAKE_COMMAND} -E echo ------------------------ )
endforeach(test)