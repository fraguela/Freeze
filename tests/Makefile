BINARIES=test_basic test_basic_capture test_basic_use test_fib_single test_fib_single_capture test_fib_single_use test_struct test_struct_capture test_struct_use

FREEZE_INCLUDE=../include/freeze/freeze.h
FREEZE_SOURCE=../src/freeze.cpp

CXXFLAGS=-O3 -std=c++11 -I../include -I.

all: $(BINARIES)

test_basic test_fib_single test_struct : % : %.cpp $(FREEZE_INCLUDE)
	$(CXX) $(CXXFLAGS) -o $@ $<

test_basic_capture : test_basic.cpp $(FREEZE_SOURCE) $(FREEZE_INCLUDE)
	$(CXX) $(CXXFLAGS) -DFREEZE_CAPTURE_MODE -o $@ test_basic.cpp $(FREEZE_SOURCE)

test_fib_single_capture : test_fib_single.cpp $(FREEZE_SOURCE) $(FREEZE_INCLUDE)
	$(CXX) $(CXXFLAGS) -DFREEZE_CAPTURE_MODE -o $@ test_fib_single.cpp $(FREEZE_SOURCE)

test_struct_capture : test_struct.cpp $(FREEZE_SOURCE) $(FREEZE_INCLUDE)
	$(CXX) $(CXXFLAGS) -DFREEZE_CAPTURE_MODE -o $@ test_struct.cpp $(FREEZE_SOURCE)

test_basic_use : test_basic_capture test_basic.cpp $(FREEZE_INCLUDE)
	./test_basic_capture
	$(CXX) $(CXXFLAGS) -DFROZEN_MODE -o $@ test_basic.cpp

test_fib_single_use : test_fib_single_capture test_fib_single.cpp $(FREEZE_INCLUDE)
	./test_fib_single_capture
	$(CXX) $(CXXFLAGS) -DFROZEN_MODE -o $@ test_fib_single.cpp

test_struct_use : test_struct_capture test_struct.cpp $(FREEZE_INCLUDE)
	./test_struct_capture
	$(CXX) $(CXXFLAGS) -DFROZEN_MODE  -o $@ test_struct.cpp

clean:
	rm -f $(BINARIES) .*freeze*
