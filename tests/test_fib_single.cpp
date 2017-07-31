#include <iostream>
#include <cstdlib>
#include "freeze/freeze.h"

#define DEFAULT_FIB_N 42

constexpr int fib(int n) {
  return (n < 2) ? n : fib(n-1) + fib(n-2);
}

int main(int argc, char ** argv)
{ FREEZE(int, n);

  std::cout << "Pre n=" << n << '\n';

  if(argc < 2) {
    std::cerr << "missing argument defaults to " << DEFAULT_FIB_N << std::endl;
  }
  
  n = (argc < 2) ? DEFAULT_FIB_N : atoi(argv[1]);
  
  std::cout << fib(n) << '\n';

  return 0;
}