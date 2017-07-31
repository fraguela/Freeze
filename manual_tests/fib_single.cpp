#include <iostream>
#include <cstdlib>

#include "Timer.h"

#define FIB_INPUT 41

#if __cplusplus >= 201103L
constexpr int cfib(int n) {
  return (n < 2) ? n : cfib(n-1) + cfib(n-2);
}
#endif

int fib(int n) {
  return (n < 2) ? n : fib(n-1) + fib(n-2);
}

int main(int argc, char ** argv)
{ Timer t;
  int r;

  std::cout << "Computing fib(" << FIB_INPUT << ") :\n";

  int            n  = FIB_INPUT;
  const     int cn  = FIB_INPUT;
#if __cplusplus >= 201103L
  constexpr int ccn = FIB_INPUT;
#endif

  t.start();
  r = fib(n);
  std::cout << t.stop() << " fib(n)=" << r << '\n';
  
  t.start();
  r = fib(cn);
  std::cout << t.stop() << " fib(cn)=" << r << '\n';

#if __cplusplus >= 201103L
  t.start();
  r = fib(ccn);
  std::cout << t.stop() << " fib(ccn)=" << r << '\n';

  t.start();
  r = cfib(n);
  std::cout << t.stop() << " cfib(n)=" << r << '\n';
  
  t.start();
  r = cfib(cn);
  std::cout << t.stop() << " cfib(cn)=" << r << '\n';
  
  t.start();
  r = cfib(ccn);
  std::cout << t.stop() << " cfib(ccn)=" << r << '\n';
#endif

  return 0;
}