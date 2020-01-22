#include <stdio.h>

#include "user_inputs.h"


static SDL_Event event;
static SDL_Keycode last_pressed_key;
static int key_still_down = 0; // must start with 0.


void input_control(void)
{
	SDL_WaitEvent(&event);

	if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == QUIT_KEY))
		quit = 1;


	else if (key_still_down) // Nothing happens if the last key is still down.
	{
		if (!Keyboard_state[SDL_GetScancodeFromKey(last_pressed_key)])
			key_still_down = 0;
	}


	// Resetting the animation_map:
	else if (key_pressed(REFRESH_KEY))
	{
		initMap(animation_map);

		render_scene = 1;
	}


	else if (key_pressed(DECR_KEY))
	{
		if (animation_map -> PointsNumber > MIN_POINTS_NUMBER)
		{
			int new_pointsNumber = animation_map -> PointsNumber - 1;

			freeMap(animation_map);

			animation_map = createMap(new_pointsNumber);

			initMap(animation_map);

			render_scene = 1;

			printf("\nPoints number got decremented: %d.\n", new_pointsNumber);
		}

		else
			printf("\nMinimum points number reached: %d.\n", MIN_POINTS_NUMBER);
	}


	else if (key_pressed(INCR_KEY))
	{
		int new_pointsNumber = animation_map -> PointsNumber + 1;

		freeMap(animation_map);

		animation_map = createMap(new_pointsNumber);

		initMap(animation_map);

		render_scene = 1;

		printf("\nPoints number got incremented: %d.\n", new_pointsNumber);
	}


	else if (key_pressed(STEPS_KEY))
	{
		animOpt = animOpt == DIRECT ? STEP_BY_STEP : DIRECT;

		printf("Changing the animation option to: %d.\n", animOpt);
	}
}


// Returns 1 if the given key is actually pressed, and if so updates 'last_pressed_key' and 'key_still_down'.
int key_pressed(SDL_Keycode key)
{
	if (Keyboard_state[SDL_GetScancodeFromKey(key)])
	{
		last_pressed_key = key;
		key_still_down = 1;
		return 1;
	}

	else
		return 0;
}
