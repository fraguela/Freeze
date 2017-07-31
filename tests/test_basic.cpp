#include <iostream>

#include "freeze/freeze.h"

FREEZE(int, i);
FREEZE(bool, j);


void f(int v)
{
  i = v;
  std::cout << i << std::endl;
}

int main()
{
  std::cout << "Initial i ==" << i << '\n';

  f(8);

  j = false;

  //f(9); // Should break when FREEZE_CAPTURE_MODE is defined

  return 0;
}