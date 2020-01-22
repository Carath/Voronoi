#ifndef SETTINGS_H
#define SETTINGS_H


// Doubles better than floats for numerical stability:
#define Number double


#define EPSILON 0.000000001


// Graphical settings:

#define USE_HARDWARE_ACCELERATION 0

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 1000

#define SMALL_MARGIN 50

#define POINT_SIZE 12

#define START_POINTS_NUMBER 15
#define MIN_POINTS_NUMBER 2


// Hotkeys:

#define QUIT_KEY SDLK_ESCAPE
#define REFRESH_KEY SDLK_SPACE
#define DECR_KEY SDLK_m
#define INCR_KEY SDLK_p
#define STEPS_KEY SDLK_s


#endif
