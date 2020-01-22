#ifndef USER_INPUTS_H
#define USER_INPUTS_H


#include "SDLA.h"

#include "settings.h"
#include "zones.h"


extern const Uint8 *Keyboard_state;

extern int quit;
extern int render_scene;

extern Map *animation_map;

extern AnimationOption animOpt;


void input_control(void);


// Returns 1 if the given key is actually pressed, and if so updates 'last_pressed_key' and 'key_still_down'.
int key_pressed(SDL_Keycode key);


#endif
