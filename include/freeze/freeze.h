#ifndef __FREEZE_H__
#define __FREEZE_H__

#include <cassert>
#include <sstream>

#ifdef FREEZE_CAPTURE_MODE

#warning Compiling in FREEZE_CAPTURE_MODE

namespace Freeze {
  
  extern void registerFreeze(void *ptr, const char * const file, const char * const var_name, const char * const var_type, const unsigned int line);
  
  extern void registerFreezeValue(void *ptr, const std::ostringstream& ost);
  
  template <typename T>
  class Freeze {
    
    T val_;
    bool initialized_;
    
  public:
    
    Freeze(const char * const file, const char * const var_name, const char * const var_type, const unsigned int line) :
    initialized_(false)
    {
      registerFreeze(this, file, var_name, var_type, line);
    }
    
    const T& operator=(const T& other) {
      
      assert(!initialized_);
      initialized_ =  true;
      
      // Register value
      std::ostringstream ost;
      ost << other;
      registerFreezeValue(this, ost);
      
      // Assignment
      val_ = other;
      return val_;
    }
    
    operator T() const {
      return val_;
    }
    
  };
  
} // namespace Freeze

#define FREEZE(TYPE, VAR) Freeze::Freeze<TYPE> VAR(__FILE__, #VAR, #TYPE, __LINE__)
#define EXTERN_FREEZE(TYPE, VAR) extern Freeze::Freeze<TYPE> VAR;

#else //FREEZE_CAPTURE_MODE
#ifdef FROZEN_MODE

#warning Compiling in FROZEN_MODE

namespace Freeze {

template <typename T>
class Freeze {

  const T val_;
  
public:

#if __cplusplus < 201103L
            Freeze(const T& val) :
#else
  constexpr Freeze(const T& val) :
#endif
  val_(val)
  { }
  
  const T& operator=(const T& other) const {
    assert(val_ == other);
    // ignore assignment
    return val_;
  }

#if __cplusplus < 201103L
            operator T() const {
#else
  constexpr operator T() const {
#endif
    return val_;
  }
  
};
  
};

#include ".freezes.h"

#define FREEZE_COMBINE1(X,Y) X##Y
#define FREEZE_COMBINE(X,Y) FREEZE_COMBINE1(X,Y)

#if __cplusplus < 201103L
#define FREEZE(TYPE, VAR)               const Freeze::Freeze<TYPE> VAR(FREEZE_COMBINE(VAR##_, __LINE__))
#define EXTERN_FREEZE(TYPE, VAR) extern const Freeze::Freeze<TYPE> VAR;

#else
#define FREEZE(TYPE, VAR)               constexpr Freeze::Freeze<TYPE> VAR(FREEZE_COMBINE(VAR##_, __LINE__))
#define EXTERN_FREEZE(TYPE, VAR) extern const Freeze::Freeze<TYPE> VAR;
#endif


#else //FROZEN_MODE

#define FREEZE(TYPE, VAR)               TYPE VAR
#define EXTERN_FREEZE(TYPE, VAR) extern TYPE VAR

#endif //FROZEN_MODE
#endif //FREEZE_CAPTURE_MODE

#endif