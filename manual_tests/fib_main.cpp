#include <iostream>
#include "timer.h"

#include "fib.h"

const int const_client = FIB_INPUT;

int main(int argc, char ** argv)
{ Timer t;
  int r;

  std::cout << "Computing fib(" << FIB_INPUT << ") :\n";

  std::cout << "const_lib=" << const_lib << '\n';
  
// Fails for C++98
#if __cplusplus >= 201103L
  std::cout << "cconst_lib=" << cconst_lib << '\n';
#endif

  int            n  = FIB_INPUT;
  const     int cn  = FIB_INPUT;
#if __cplusplus >= 201103L
  constexpr int crn = FIB_INPUT;
#endif

  t.start();
  r = fib(n);
  std::cout << t.stop() << " fib(n)=" << r << '\n';
  
  t.start();
  r = fib(cn);
  std::cout << t.stop() << " fib(cn)=" << r << '\n';

#if __cplusplus >= 201103L
  t.start();
  r = fib(crn);
  std::cout << t.stop() << " fib(crn)=" << r << '\n';
#endif

  t.start();
  r = fib(const_client);
  std::cout << t.stop() << " fib(const_client)=" << r << '\n';

  t.start();
  r = fib(const_lib);
  std::cout << t.stop() << " fib(const_lib)=" << r << '\n';

  t.start();
  r = const_fib();
  std::cout << t.stop() << " const_fib()=fib(const_lib)=" << r << '\n';

#if __cplusplus >= 201103L
  t.start();
  r = cconst_fib();
  std::cout << t.stop() << " cconst_fib()=fib(cconst_lib)=" << r << '\n';

  t.start();
  r = const_cfib();
  std::cout << t.stop() << " const_cfib()=cfib(const_lib)=" << r << '\n';
  
  t.start();
  r = cconst_cfib();
  std::cout << t.stop() << " cconst_cfib()=cfib(cconst_lib)=" << r << '\n';
#endif
  
  return 0;
}