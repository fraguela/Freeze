
#freeze: A library to capture runtime values in constants
#Copyright (C) 2017 Basilio B. Fraguela. Universidade da Coruna

# \file     CMakeLists.txt
# \brief    CMakeLists.txt for building the tests
# \author   Basilio B. Fraguela <basilio.fraguela@udc.es>

cmake_minimum_required( VERSION 2.8.7 )

# Executables that ignore freeze

add_executable(test_basic test_basic.cpp)

add_executable(test_fib_single test_fib_single.cpp)

add_executable(test_struct test_struct.cpp)

# Executables that capture values

add_executable(test_basic_capture test_basic.cpp )
target_compile_definitions( test_basic_capture PUBLIC -DFREEZE_CAPTURE_MODE )
target_link_libraries( test_basic_capture freeze )

add_executable(test_fib_single_capture test_fib_single.cpp )
target_compile_definitions( test_fib_single_capture PUBLIC -DFREEZE_CAPTURE_MODE )
target_link_libraries( test_fib_single_capture freeze )

add_executable(test_struct_capture test_struct.cpp )
target_compile_definitions( test_struct_capture PUBLIC -DFREEZE_CAPTURE_MODE )
target_link_libraries( test_struct_capture freeze )

# Executables that use captures

add_executable( test_basic_use 
	test_basic.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/.test_basic.cpp.freeze.h 
	${CMAKE_CURRENT_BINARY_DIR}/.freezes.h )
target_compile_definitions( test_basic_use PUBLIC -DFROZEN_MODE )
target_include_directories( test_basic_use PUBLIC ${CMAKE_CURRENT_BINARY_DIR} )
add_dependencies( test_basic_use run_test_basic_capture )

add_executable( test_fib_single_use 
	test_fib_single.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/.test_fib_single.cpp.freeze.h
	${CMAKE_CURRENT_BINARY_DIR}/.freezes.h )
target_compile_definitions( test_fib_single_use PUBLIC -DFROZEN_MODE )
target_include_directories( test_fib_single_use PUBLIC ${CMAKE_CURRENT_BINARY_DIR} )
add_dependencies( test_fib_single_use run_test_fib_single_capture )

add_executable( test_struct_use 
	test_struct.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/.test_struct.cpp.freeze.h 	${CMAKE_CURRENT_BINARY_DIR}/.freezes.h )
target_compile_definitions( test_struct_use PUBLIC -DFROZEN_MODE )
target_include_directories( test_struct_use PUBLIC ${CMAKE_CURRENT_BINARY_DIR} )
add_dependencies( test_struct_use run_test_struct_capture )

add_custom_target( run_test_basic_capture
		   COMMAND test_basic_capture
		   DEPENDS test_basic_capture
		   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )

add_custom_target( run_test_fib_single_capture
		   COMMAND test_fib_single_capture
		   DEPENDS test_fib_single_capture
		   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )
		   
add_custom_target( run_test_struct_capture
		   COMMAND test_struct_capture
		   DEPENDS test_struct_capture
		   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )

add_custom_command(OUTPUT 
			${CMAKE_CURRENT_SOURCE_DIR}/.test_basic.cpp.freeze.h
		   BYPRODUCTS
			${CMAKE_CURRENT_BINARY_DIR}/.freezes.h
		   COMMAND test_basic_capture
		   DEPENDS test_basic_capture
		   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )

add_custom_command(OUTPUT 
			${CMAKE_CURRENT_SOURCE_DIR}/.test_fib_single.cpp.freeze.h
		   BYPRODUCTS
			${CMAKE_CURRENT_BINARY_DIR}/.freezes.h
		   COMMAND test_fib_single_capture
		   DEPENDS test_fib_single_capture
		   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )

add_custom_command(OUTPUT 
			${CMAKE_CURRENT_SOURCE_DIR}/.test_struct.cpp.freeze.h
		   BYPRODUCTS
			${CMAKE_CURRENT_BINARY_DIR}/.freezes.h
		   COMMAND test_struct_capture
		   DEPENDS test_struct_capture
		   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )

set_source_files_properties( 
	${CMAKE_CURRENT_SOURCE_DIR}/.test_basic.cpp.freeze.h 	${CMAKE_CURRENT_SOURCE_DIR}/.test_fib_single.cpp.freeze.h 	${CMAKE_CURRENT_SOURCE_DIR}/.test_struct.cpp.freeze.h
	${CMAKE_CURRENT_BINARY_DIR}/.freezes.h
	PROPERTIES GENERATED TRUE)
	    
add_custom_target(run_tests)
set(tests_to_run test_basic test_basic_use test_fib_single test_fib_single_use test_struct test_struct_use)
add_dependencies( run_tests ${tests_to_run} )

add_custom_command(TARGET run_tests PRE_BUILD
		   COMMAND ${CMAKE_COMMAND} -E echo
                   COMMAND ${CMAKE_COMMAND} -E echo '***' BUILT WITH ${CMAKE_CXX_COMPILER} ${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS} '***'
		   COMMAND ${CMAKE_COMMAND} -E echo '    run cmake -DCMAKE_CXX_COMPILER=cxx to choose another compiler'
		   COMMAND ${CMAKE_COMMAND} -E echo)

foreach(test ${tests_to_run})
  add_custom_command(TARGET run_tests PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E echo test ${test} : -------------
                     COMMAND time ${test} || exit 1
                     COMMAND ${CMAKE_COMMAND} -E echo ------------------------ )
endforeach(test)