BINARIES=fib_single_cxx11 fib_single fib_lib_cxx11 fib_lib

all: $(BINARIES)

fib_single : fib_single.cpp timer.cpp
	$(CXX) -O3 -o $@ $^

fib_single_cxx11 : fib_single.cpp timer.cpp
	$(CXX) -O3 -std=c++0x -o $@ $^

fib_lib : fib_main.cpp fib_lib.cpp timer.cpp
	$(CXX) -O3 -o $@ $^

fib_lib_cxx11 : fib_main.cpp fib_lib.cpp timer.cpp
	$(CXX) -O3 -std=c++0x -o $@ $^

test: $(BINARIES)
	./fib_single
	@echo
	./fib_single_cxx11
	@echo
	./fib_lib
	@echo
	./fib_lib_cxx11

clean:
	rm -f $(BINARIES)
