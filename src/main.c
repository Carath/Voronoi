#include <stdio.h>
#include <stdlib.h>
#include <time.h> // For srand()

#include "animation.h"


int main(void)
{
	srand(time(NULL)); // Initialization of the pseudo-random number generator.

	///////////////////////////////////////////////////////
	// Graphical animation:

	animation();

	///////////////////////////////////////////////////////

	return EXIT_SUCCESS;
}
