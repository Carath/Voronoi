#ifndef ZONES_H
#define ZONES_H


#include "settings.h"
#include "map.h"


// STEP_BY_STEP: used for drawing the steps once at a time:
typedef enum {DIRECT, STEP_BY_STEP} AnimationOption;


// Find the influence zone of each point:
void findZones(Map *map, AnimationOption opt);


// Update the map edges by intersecting them two by two:
void updateEdges(Map *map, int i, int j, int k);


// Framework for the retractation. Returns 1 if the segment needs to be freed:
int retract_method(Segment *segment, Line *line, Point *point_ref, Point *intersection);


#endif
