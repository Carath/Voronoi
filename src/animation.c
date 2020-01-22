#include <stdio.h>
#include <stdlib.h>

#include "animation.h"
#include "user_inputs.h"
#include "drawing.h"
#include "zones.h"


// Global variables:

const Uint8 *Keyboard_state;

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Color Red = {255, 0, 0, 255};
SDL_Color Lime = {0, 255, 0, 255};
// SDL_Color Yellow = {255, 255, 0, 255};

int quit = 0;
int render_scene = 1;

Map *animation_map;

AnimationOption animOpt = DIRECT; // default mode.


// Drawing test:
void animation(void)
{
	////////////////////////////////////////////////////////////
	// Initializing SDLA - rendering:

	SDLA_Init(&window, &renderer, "Petri", WINDOW_WIDTH, WINDOW_HEIGHT,
		USE_HARDWARE_ACCELERATION, SDLA_BLENDED);

	////////////////////////////////////////////////////////////
	// Fonts:

	// No font used.

	////////////////////////////////////////////////////////////
	// For user inputs:

	Keyboard_state = SDL_GetKeyboardState(NULL);

	printf("Hotkeys:\n\n");
	printf("-> Quit: ESCAPE\n");
	printf("-> Refresh: SPACE\n");
	printf("-> Decrement points number: M\n");
	printf("-> Increment points number: P\n");
	printf("-> Toggle step by step animation: S\n\n");

	////////////////////////////////////////////////////////////
	// Creating a map:

	int pointsNumber = START_POINTS_NUMBER;

	animation_map = createMap(pointsNumber);

	initMap(animation_map);

	////////////////////////////////////////////////////////////
	// Starting the event loop:

	// int frame_index = 0; // for controlling the scene rendering.

	while (!quit)
	{
		input_control();

		if (render_scene)
		{
			SDLA_ClearWindow(NULL);

			// printMap(animation_map);

			findZones(animation_map, animOpt);

			drawMap(animation_map);

			// Rendering:
			SDL_RenderPresent(renderer);

			// ++frame_index;
			// printf("\nframe_index: %d\n", frame_index);

			render_scene = 0;
		}
	}

	// Freeing everything:

	freeMap(animation_map);

	SDLA_Quit();
}
