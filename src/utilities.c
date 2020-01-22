#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utilities.h"


double time_elapsed(clock_t start)
{
	return (double) (clock() - start) / CLOCKS_PER_SEC;
}


// Returns a random number in [min, max[.
Number uniform_random(Number min, Number max)
{
	return (Number) rand() / RAND_MAX * (max - min) + min;
}


// Checks if x = y, short of EPSILON:
int epsilonEquality(Number x, Number y)
{
	return fabs(x - y) < EPSILON;
}


// Checks if x < y, short of EPSILON:
int epsilonStrInequality(Number x, Number y)
{
	return x + EPSILON < y;
}
