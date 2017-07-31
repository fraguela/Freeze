#include "fib.h"

const int const_lib = FIB_INPUT;

int fib(int n) {
  return (n < 2) ? n : fib(n-1) + fib(n-2);
}

int const_fib() {
  return fib(const_lib);
}

#if __cplusplus >= 201103L

constexpr int cconst_lib = FIB_INPUT;

constexpr int cfib(int n) {
  return (n < 2) ? n : cfib(n-1) + cfib(n-2);
}

int cconst_fib() {
  return fib(cconst_lib);
}

int const_cfib() {
  return cfib(const_lib);
}

int cconst_cfib() {
  return cfib(cconst_lib);
}
#endif