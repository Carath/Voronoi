#ifndef DRAWING_H
#define DRAWING_H


#include "SDLA.h"

#include "settings.h"
#include "map.h"


extern SDL_Renderer *renderer;

extern SDL_Color Red;
extern SDL_Color Lime;
// extern SDL_Color Yellow;


void drawPoint(Point *point, SDL_Color *color);


void drawSegment(Segment *segment, SDL_Color *color);


void drawMap(Map *map);


// Showing the computation step by step:
void show_steps(Map *map);


#endif
