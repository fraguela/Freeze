#ifndef FREEZE_TIMER_H
#define FREEZE_TIMER_H

#include <sys/time.h>

/// Utility class to measure time
class Timer {
private:

struct timeval begin, end;

public:

Timer();

/// Start measuring time
void start();

// Return time in second since previous invocation to start()
double stop();   
};

#endif
