#ifndef FREEZER_FIB_LIB_H
#define FREEZER_FIB_LIB_H

#define FIB_INPUT 41

extern const int const_client;
extern const int const_lib;

int fib(int n);

int const_fib();

#if __cplusplus >= 201103L

/*  constexpr functions cannot be exported
 constexpr int cfib(int n);
*/

/*  constexpr variables must be defined
extern constexpr int cconst_lib;
*/

// It is actually a constexpr 
extern const int cconst_lib;

int cconst_fib();

int const_cfib();

int cconst_cfib();
#endif

#endif