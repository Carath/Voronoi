#ifndef UTILITIES_H
#define UTILITIES_H


#include <time.h>

#include "settings.h"


double time_elapsed(clock_t start);


// Returns a random number in [min, max[.
Number uniform_random(Number min, Number max);


// Checks if x = y, short of EPSILON:
int epsilonEquality(Number x, Number y);


// Checks if x < y, short of EPSILON:
int epsilonStrInequality(Number x, Number y);


#endif
