#include <iostream>
#include <ostream>
#include <cstring>

enum Dept : int { Math, Engineering, CompScience };

struct MyType {
  int num_elems;
  Dept department;
  const char * name;
  
  // Only required for assertions when NDEBUG is not defined
  bool operator==(const MyType& other) const {
    return (num_elems == other.num_elems) &&
    (department == other.department) &&
    ((name == other.name) || !strcmp(name, other.name));
  }

};

// "freeze.h" must be included after the types to freeze are known
//because in FROZEN_MODE the ".freezes.h" header that instantiates
//the constants is included within "freeze.h"
#include "freeze/freeze.h"

std::ostream& operator << ( std::ostream& os, const MyType& v ) {
  os << '{' << v.num_elems << ", ";
  switch(v.department) {
    case Math: os << "Math"; break;
    case Engineering: os << "Engineering"; break;
    case CompScience: os << "CompScience"; break;
  }
  os << ", \"" << v.name << "\"}";
  return os;
}

FREEZE(MyType, a);

int main(int argc, char **argv)
{
  MyType b = { 1, Math, "Sue" }; //Valid in C++98
  
  a = { 34, Math, "Joe" };       //Requires C++11
  
  std::cout << a << std::endl;
  
  return 0;
}
