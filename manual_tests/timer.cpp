#include "timer.h"

Timer::Timer()
{
  start();
}

void Timer::start()
{
  gettimeofday(&begin,NULL);
}

double Timer::stop()
{
  gettimeofday(&end,NULL);
  double secs = (double)((end.tv_sec+(end.tv_usec/1000000.0)) - (begin.tv_sec+(begin.tv_usec/1000000.0)));
  return secs;
}